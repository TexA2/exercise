#include <iostream>
#include <vector>
#include <cmath>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


#include <pcl/visualization/pcl_visualizer.h> 
#include <pcl/visualization/cloud_viewer.h>


void createDepthMap(const pcl::PointCloud<pcl::PointXYZI>::Ptr& cloud);

// Параметры Range Image
struct RangeImageParams {
    float fov_up = 15.0f;    // Верхний угол обзора (град)
    float fov_down = -15.0f; // Нижний угол обзора (град)
    int width = 1024;        // Ширина изображения (пикс)
    int height = 64;         // Высота изображения (пикс)
    float max_range = 100.0f; // Максимальная дальность (м)
};

// Преобразование облака в Range View и сохранение в PCD
void convertToRangeViewAndSave(
    const pcl::PointCloud<pcl::PointXYZI>::Ptr& input_cloud,
    const RangeImageParams& params,
    const std::string& output_pcd_path) 
{
    // Инициализация матрицы дальностей
    std::vector<std::vector<float>> range_image(
        params.height,
        std::vector<float>(params.width, 0.0f)
    );

// Инициализация матрицы интенсивности
    std::vector<std::vector<float>> intensity_image(
        params.height,
        std::vector<float>(params.width, 0.0f)
    );

    // Переводим углы в радианы
    float fov_up_rad = params.fov_up * M_PI / 180.0f;
    float fov_down_rad = params.fov_down * M_PI / 180.0f;
    float fov_rad = fov_up_rad - fov_down_rad;

    // Заполняем Range Image
    for (const auto& point : input_cloud->points) {
        float range = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
        if (range > params.max_range) continue;  // можно как включить так и выключыить посмотреть где лучше

        float yaw = atan2(point.y, point.x);    // Азимут [-π, π]
        float pitch = asin(point.z / range);    // Элевация [-π/2, π/2]

        // Обеспечиваем, что yaw ∈ [-π, π]
        yaw = std::fmod(yaw + M_PI, 2.0f * M_PI) - M_PI;

        // Вычисляем u с проверкой границ
        int u = static_cast<int>((0.5f * (1.0f - yaw / M_PI)) * params.width);
        u = std::max(0, std::min(u, params.width - 1));

        // Обеспечиваем, что pitch ∈ [fov_down_rad, fov_up_rad]
        pitch = std::max(fov_down_rad, std::min(pitch, fov_up_rad));

        // Вычисляем v с проверкой границ
        int v = static_cast<int>((1.0f - (pitch - fov_down_rad) / fov_rad) * params.height);
        v = std::max(0, std::min(v, params.height - 1));

        if (u >= 0 && u < params.width && v >= 0 && v < params.height) {
            if (range_image[v][u] == 0 || range < range_image[v][u]) {
                range_image[v][u] = range;  // Берем ближайшую точку
                intensity_image[v][u] = point.intensity;
            }
        }
    }

    // Создаем новое облако точек для сохранения (u, v, range)
    pcl::PointCloud<pcl::PointXYZI>::Ptr range_cloud(new pcl::PointCloud<pcl::PointXYZI>);
    range_cloud->reserve(params.width * params.height / 2); 

    for (int v = 0; v < params.height; ++v) {
        for (int u = 0; u < params.width; ++u) {
            if (range_image[v][u] > 0) {
                pcl::PointXYZI point;
                point.x = u;  // Координата u (ширина)
                point.y = v;  // Координата v (высота)
                point.z = range_image[v][u];  // Дальность
                point.intensity = intensity_image[v][u];
                range_cloud->push_back(point);
            }
        }
    }

    createDepthMap(range_cloud);
    // Сохраняем в PCD
    pcl::io::savePCDFileASCII(output_pcd_path, *range_cloud);
    std::cout << "Range View saved to " << output_pcd_path << std::endl;
}

// Функция для создания цветной карты глубины
void createDepthMap(const pcl::PointCloud<pcl::PointXYZI>::Ptr& cloud)
{

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr colored_cloud (new pcl::PointCloud<pcl::PointXYZRGB>);

    colored_cloud->width = cloud->width;
    colored_cloud->height = cloud->height;
    colored_cloud->resize(cloud->size());

    // Находим минимальное и максимальное расстояние
    float min_depth = std::numeric_limits<float>::max();
    float max_depth = -std::numeric_limits<float>::max();
    
    for (const auto& point : cloud->points) {
        float depth = sqrt(point.x*point.x + point.y*point.y + point.z*point.z);
        if (depth < min_depth) min_depth = depth;
        if (depth > max_depth) max_depth = depth;
    }



    // Найдем min и max по Z для нормализации
    float z_min = std::numeric_limits<float>::max();
    float z_max = std::numeric_limits<float>::lowest();

    for (const auto& pt : cloud->points)
    {
        if (pt.z < z_min) z_min = pt.z;
        if (pt.z > z_max) z_max = pt.z;
    }

    float z_range = z_max - z_min;

    if (z_range == 0) z_range = 1.0f; // защита от деления на 0

    // Функция для интерполяции цвета (синий -> красный)
    auto depthToRGB = [](float depth_norm) -> std::tuple<uint8_t, uint8_t, uint8_t> {
        // depth_norm от 0 до 1
        // Синий (близко) RGB(0,0,255)
        // Красный (далеко) RGB(255,0,0)
        uint8_t r = 0;
        uint8_t g = static_cast<uint8_t>(depth_norm * 255);;
        uint8_t b = static_cast<uint8_t>((1.0f - depth_norm) * 255);
        return std::make_tuple(r, g, b);
    };

    // Преобразуем точки
    for (size_t i = 0; i < cloud->points.size(); ++i)
    {
        const auto& pt_in = cloud->points[i];
        auto& pt_out = colored_cloud->points[i];

        pt_out.x = pt_in.x;
        pt_out.y = pt_in.y;
        pt_out.z = pt_in.z;

        float depth_norm = (pt_in.z - z_min) / z_range;
        auto [r, g, b] = depthToRGB(depth_norm);

        pt_out.r = r;
        pt_out.g = g;
        pt_out.b = b;
    }



// сохранение 
    std::string output_pcd_path = "colored_cloud.pcd";

    pcl::io::savePCDFileASCII(output_pcd_path, *colored_cloud);
    std::cout << "Range View saved to " << output_pcd_path << std::endl;
}






int main() {
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);

    if (pcl::io::loadPCDFile<pcl::PointXYZI>("/workspace/Server/Issue/RangeView/d0Part.pcd", *cloud) == -1) {
        std::cerr << "Error: Could not read PCD file!" << std::endl;
        return -1;
    }


    float min_z = std::numeric_limits<float>::max();
    float max_z = -std::numeric_limits<float>::max();

    float fov_down_rad = std::numeric_limits<float>::max();
    float fov_up_rad = -std::numeric_limits<float>::max();

    for (const auto& p : cloud->points)
    {
        if (p.z < min_z) min_z = p.z;
        if (p.z > max_z) max_z = p.z;
    }

   std::vector<float> ranges;

    for (const auto& p : cloud->points) 
    {
    float xy_dist = sqrt(p.x * p.x + p.y * p.y);
    float pitch = atan2(p.z, xy_dist);  // угол места
    
    if (p.z <= min_z + 0.01f) {  // учитываем точки близкие к min_z
        fov_down_rad = std::min(fov_down_rad, pitch);
    }
    if (p.z >= max_z - 0.01f) {  // учитываем точки близкие к max_z
        fov_up_rad = std::max(fov_up_rad, pitch);
    }

    ranges.push_back(sqrt(p.x*p.x + p.y*p.y + p.z*p.z));
    }


    std::sort(ranges.begin(), ranges.end());
    float max_range = ranges[ranges.size() * 0.95f];  // 95-й процентиль (игнорируем 5% выбросов)   

    std::cout << ranges.size() << std::endl;

    // Параметры Range Image (настрой под свой лидар)
    RangeImageParams params;
    params.width = 1024;
    params.height = 128;
    params.fov_down = fov_down_rad * 180.0f / M_PI;
    params.fov_up = fov_up_rad * 180.0f / M_PI;
    params.max_range = max_range * 1.1f; // +10% запаса


    convertToRangeViewAndSave(cloud, params, "output.pcd");

    return 0;
}