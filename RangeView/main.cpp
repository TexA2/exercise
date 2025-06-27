#include <iostream>
#include <vector>
#include <cmath>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

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

    // Переводим углы в радианы
    float fov_up_rad = params.fov_up * M_PI / 180.0f;
    float fov_down_rad = params.fov_down * M_PI / 180.0f;
    float fov_rad = fov_up_rad - fov_down_rad;

    // Заполняем Range Image
    for (const auto& point : input_cloud->points) {
        float range = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);
        //std::cout << "range " << range << " and  params.max_range " << params.max_range << std::endl;
        if (range > params.max_range) continue;

        float yaw = atan2(point.y, point.x);    // Азимут [-π, π]
        float pitch = asin(point.z / range);    // Элевация [-π/2, π/2]

        // Нормализация в пиксельные координаты
        int u = static_cast<int>(0.5f * (1.0f - (yaw / M_PI)) * params.width);
        int v = static_cast<int>((1.0f - (pitch + fov_up_rad) / fov_rad) * params.height);

        if (u >= 0 && u < params.width && v >= 0 && v < params.height) {
            if (range_image[v][u] == 0 || range < range_image[v][u]) {
                range_image[v][u] = range;  // Берем ближайшую точку
            }
        }
    }

    // Создаем новое облако точек для сохранения (u, v, range)
    pcl::PointCloud<pcl::PointXYZ>::Ptr range_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    for (int v = 0; v < params.height; ++v) {
        for (int u = 0; u < params.width; ++u) {
            if (range_image[v][u] > 0) {
                pcl::PointXYZ point;
                point.x = u;  // Координата u (ширина)
                point.y = v;  // Координата v (высота)
                point.z = range_image[v][u];  // Дальность
                range_cloud->push_back(point);
            }
        }
    }

    // Сохраняем в PCD
    pcl::io::savePCDFileASCII(output_pcd_path, *range_cloud);
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
    float fov_down_rad = 0;
    float fov_up_rad = 0;

    for (const auto& p : cloud->points)
    {
        if (p.z < min_z)
        {
            min_z = p.z;
             fov_down_rad = atan2(min_z, sqrt(p.x*p.x + p.y*p.y));
        }

        if (p.z > max_z)
        {
             max_z = p.z;
             fov_up_rad = atan2(max_z, sqrt(p.x*p.x + p.y*p.y));
        }
    }


    float max_range = 0;
    for (const auto& p : cloud->points) 
    {
        float range = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
        if (range > max_range) max_range = range;
    }

    // Параметры Range Image (настрой под свой лидар)
    RangeImageParams params;
    params.width = 1024;
    params.height = 64;
    params.fov_down = fov_down_rad * 180.0f / M_PI;
    params.fov_up = fov_up_rad * 180.0f / M_PI;
    params.max_range = max_range * 1.1f; // +10% запаса


    convertToRangeViewAndSave(cloud, params, "output.pcd");

    return 0;
}