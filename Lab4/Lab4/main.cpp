#include <iostream>
#include <string>
#include "image.h"

using namespace std;

int main(int argc, char* argv[]) {
	//const char* inputFile = argv[1];
	//const char* outputFile = argv[2];
	//double coefficient = stoi(argv[3]);
	const char* inputFile = "bmp.bmp";
	image picture;
	readImage reader;
	picture = reader.read(inputFile);


	cin.ignore();
	cin.get();
	system("pause");
}