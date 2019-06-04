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
	image picture;
	readImage reader;
	saveImage saver;
	resizeImage repicture;
	picture = reader.read(inputFile);
	repicture.resize(picture,3);
	saver.save(picture, outputFile);

	cin.ignore();
	cin.get();
	system("pause");
}