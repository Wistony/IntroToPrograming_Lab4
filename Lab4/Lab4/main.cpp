#include <iostream>
#include <string>
#include "image.h"

using namespace std;

int main(int argc, char* argv[]) {
	//const char* inputFile = argv[1];
	//const char* outputFile = argv[2];
	//double coefficient = stoi(argv[3]);
	const char* inputFile = "bmp.bmp";
	const char* outputFile = "new1.bmp";

	double coefficient;
	cin >> coefficient;
	image picture, resizePicture;
	readImage reader;
	resizeImage resizer;
	saveImage saver;
	picture = reader.read(inputFile);
	resizePicture = resizer.resize(picture, coefficient);
	saver.save(resizePicture, outputFile);

	cin.ignore();
	cin.get();
	system("pause");
}