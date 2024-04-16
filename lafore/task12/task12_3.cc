//Напишите программу , возращающую размер файла, указанного в командой строке.
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

	if (argc != 2)
	{
		cerr <<"\nНеверное заданные аргументы\n";
		exit(-1);
	}

	ifstream infile;

	infile.open(argv[1], ios::binary);
	infile.seekg(0, ios::end);
	int size = infile.tellg();

	infile.close();
	cout << "\nРазер файла " << argv[1] << " " << size << " байт." << endl;

	return 0;
}
