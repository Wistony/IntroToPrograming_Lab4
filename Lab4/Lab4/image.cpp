#include"image.h"
#include <iostream>
using namespace std;

image readImage::read(const char* nameFile) {
	FILE* inputFile;
	inputFile = fopen(nameFile, "rb");
	if (inputFile == NULL) {
		cout << " File don`t open ";
		return;
	}

	fread(&info.id, sizeof(info.id), 1, inputFile);
	fread(&info.filesize, sizeof(info.filesize), 1, inputFile);
	fread(&info.reserved, sizeof(info.reserved), 1, inputFile);
	fread(&info.headersize, sizeof(info.headersize), 1, inputFile);
	fread(&info.infoSize, sizeof(info.infoSize), 1, inputFile);
	fread(&info.width, sizeof(info.width), 1, inputFile);
	fread(&info.depth, sizeof(info.depth), 1, inputFile);
	fread(&info.biPlanes, sizeof(info.biPlanes), 1, inputFile);
	fread(&info.bits, sizeof(info.bits), 1, inputFile);
	fread(&info.biCompression, sizeof(info.biCompression), 1, inputFile);
	fread(&info.biSizeImage, sizeof(info.biSizeImage), 1, inputFile);
	fread(&info.biXPelsPerMeter, sizeof(info.biXPelsPerMeter), 1, inputFile);
	fread(&info.biYPelsPerMeter, sizeof(info.biYPelsPerMeter), 1, inputFile);
	fread(&info.biClrUsed, sizeof(info.biClrUsed), 1, inputFile);
	fread(&info.biClrImportant, sizeof(info.biClrImportant), 1, inputFile);

	PIXELDATA **bitmap = new PIXELDATA*[info.depth];
	for (int i = 0; i < info.depth; i++) 
		bitmap[i] = new PIXELDATA[info.width];

	for (int i = 0; i < info.depth; i++) {
		for (int j = 0; j < info.width; j++) {
			fread(&bitmap[i][j].blueComponent, 1, 1, inputFile);
			fread(&bitmap[i][j].greenComponent, 1, 1, inputFile);
			fread(&bitmap[i][j].redComponent, 1, 1, inputFile);
		}
	}
	
	fclose(inputFile);
}