#include <iostream>
#include <string>
#include "image.h"

using namespace std;

int main(int argc, char* argv[]) {
	char* inputFile = argv[1];
	char* outputFile = argv[2];
	double coefficient = stod(argv[3]);
	
	cout << " Increase the image " << coefficient << " times..." << endl;
	image picture, resizePicture;
	readImage reader;
	resizeImage resizer;
	saveImage saver;
	picture = reader.read(inputFile);
	resizePicture = resizer.resize(picture, coefficient);
	saver.save(resizePicture, outputFile);
	cout << " Increase done successfully!" << endl;
	cout << " Image save to " << outputFile;

	return 0;
}