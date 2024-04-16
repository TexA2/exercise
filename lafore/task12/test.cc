// Напишите программу , эмулюрующую команду COPY (MS DOS).
// Программа должна копировать содержимое одного файла в другой.
// Должно использоваться 2 аргумента командной строки - исходный файл и файл назначения.

#include <iostream>
#include <fstream>
//#include <process.h>

using namespace std;


int main(int argc, char* argv[]){

	if (argc != 3)
	{
		cerr <<"\n Формат команды: что_копируем куда_копируем.";
		exit(-1);
	}

	ifstream infile;

	infile.open(argv[1], ios::binary);
	infile.seekg(0, ios::end);

	int size = infile.tellg();
	cout << "\n Размер файла: " << size << " байта."<< endl;

	infile.seekg(0);

	char buf[size];

	infile.read( reinterpret_cast<char*>(buf), sizeof(buf));
	infile.close();

	ofstream outfile;

	outfile.open(argv[2], ios::trunc | ios::binary);

	if (!outfile)
	{
		cerr<< "Невозможно открыть файл для записи\n";
		exit(-1);
	}

	outfile.write( reinterpret_cast<char*>(buf), sizeof(buf));
	outfile.close();

	cout <<"\nФайл скопирован" << endl;

	return 0;
}
