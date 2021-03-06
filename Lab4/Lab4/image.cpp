#define _CRT_SECURE_NO_WARNINGS
#include"image.h"
#include <iostream>
using namespace std;

void readImage::readInfoHeader(image& picture,FILE* inputFile) {
	fread(&picture.info.id, sizeof(picture.info.id), 1, inputFile);
	fread(&picture.info.filesize, sizeof(picture.info.filesize), 1, inputFile);
	fread(&picture.info.reserved, sizeof(picture.info.reserved), 1, inputFile);
	fread(&picture.info.headersize, sizeof(picture.info.headersize), 1, inputFile);
	fread(&picture.info.infoSize, sizeof(picture.info.infoSize), 1, inputFile);
	fread(&picture.info.width, sizeof(picture.info.width), 1, inputFile);
	fread(&picture.info.depth, sizeof(picture.info.depth), 1, inputFile);
	fread(&picture.info.biPlanes, sizeof(picture.info.biPlanes), 1, inputFile);
	fread(&picture.info.bits, sizeof(picture.info.bits), 1, inputFile);
	fread(&picture.info.biCompression, sizeof(picture.info.biCompression), 1, inputFile);
	fread(&picture.info.biSizeImage, sizeof(picture.info.biSizeImage), 1, inputFile);
	fread(&picture.info.biXPelsPerMeter, sizeof(picture.info.biXPelsPerMeter), 1, inputFile);
	fread(&picture.info.biYPelsPerMeter, sizeof(picture.info.biYPelsPerMeter), 1, inputFile);
	fread(&picture.info.biClrUsed, sizeof(picture.info.biClrUsed), 1, inputFile);
	fread(&picture.info.biClrImportant, sizeof(picture.info.biClrImportant), 1, inputFile);
}

image readImage::read(const char* nameFile) {
	image picture;
	FILE* inputFile;
	PIXELDATA emptyPixel;
	inputFile = fopen(nameFile, "rb");
	if (inputFile == NULL) {
		cout << " File don`t open ";
		exit(1);
	}
	
	readInfoHeader(picture, inputFile);

	picture.bitmap = new PIXELDATA*[picture.info.depth];
	for (int i = 0; i < picture.info.depth; i++) 
		picture.bitmap[i] = new PIXELDATA[picture.info.width];

	int bytesPerLine = picture.info.width * 3;
	int multiplicity = bytesPerLine % 4;

	for (int i = 0; i < picture.info.depth; i++) {
		for (int j = 0; j < picture.info.width; j++) {
			fread(&picture.bitmap[i][j].blueComponent, 1, 1, inputFile);
			fread(&picture.bitmap[i][j].greenComponent, 1, 1, inputFile);
			fread(&picture.bitmap[i][j].redComponent, 1, 1, inputFile);
		}
		if (multiplicity) 
			fread(&emptyPixel, 1, 4 - multiplicity, inputFile);
	}
	fclose(inputFile);

	return picture;
}

void saveImage::saveInfoHeader(image& picture,FILE* outputFile) {
	fwrite(&picture.info.id, sizeof(picture.info.id), 1, outputFile);
	fwrite(&picture.info.filesize, sizeof(picture.info.filesize), 1, outputFile);
	fwrite(&picture.info.reserved, sizeof(picture.info.reserved), 1, outputFile);
	fwrite(&picture.info.headersize, sizeof(picture.info.headersize), 1, outputFile);
	fwrite(&picture.info.infoSize, sizeof(picture.info.infoSize), 1, outputFile);
	fwrite(&picture.info.width, sizeof(picture.info.width), 1, outputFile);
	fwrite(&picture.info.depth, sizeof(picture.info.depth), 1, outputFile);
	fwrite(&picture.info.biPlanes, sizeof(picture.info.biPlanes), 1, outputFile);
	fwrite(&picture.info.bits, sizeof(picture.info.bits), 1, outputFile);
	fwrite(&picture.info.biCompression, sizeof(picture.info.biCompression), 1, outputFile);
	fwrite(&picture.info.biSizeImage, sizeof(picture.info.biSizeImage), 1, outputFile);
	fwrite(&picture.info.biXPelsPerMeter, sizeof(picture.info.biXPelsPerMeter), 1, outputFile);
	fwrite(&picture.info.biYPelsPerMeter, sizeof(picture.info.biYPelsPerMeter), 1, outputFile);
	fwrite(&picture.info.biClrUsed, sizeof(picture.info.biClrUsed), 1, outputFile);
	fwrite(&picture.info.biClrImportant, sizeof(picture.info.biClrImportant), 1, outputFile);
}

void saveImage::save(image& picture, const char* nameFile) {
	FILE* outputFile;
	outputFile = fopen(nameFile, "wb");
	int8_t emptyPixel = 0x00;

	saveInfoHeader(picture, outputFile);

	int bytesPerLine = picture.info.width * 3;
	int multiplicity = bytesPerLine % 4;

	for (int i = 0; i < picture.info.depth; i++) {
		for (int j = 0; j < picture.info.width; j++) {
			fwrite(&picture.bitmap[i][j].blueComponent, 1, 1, outputFile);
			fwrite(&picture.bitmap[i][j].greenComponent, 1, 1, outputFile);
			fwrite(&picture.bitmap[i][j].redComponent, 1, 1, outputFile);
		}
		if (multiplicity)
			fwrite(&emptyPixel, 1, 4 - multiplicity, outputFile);
	}

	fclose(outputFile);
}

image resizeImage::resize(image& picture, double coefficient) {
	image resizePicture;
	resizePicture.info = picture.info;
	resizePicture.info.depth *= coefficient;
	resizePicture.info.width *= coefficient;
	int bytesPerLine = resizePicture.info.width * 3;
	int multiplicity = bytesPerLine % 4;
	resizePicture.info.biSizeImage = resizePicture.info.width * 3 * resizePicture.info.depth + (4 - multiplicity) * resizePicture.info.width;
	resizePicture.info.filesize = resizePicture.info.biSizeImage + sizeof(resizePicture.info);

	resizePicture.bitmap = new PIXELDATA*[resizePicture.info.depth];
	for (int i = 0; i < resizePicture.info.depth; i++)
		resizePicture.bitmap[i] = new PIXELDATA[resizePicture.info.width];



	float t;
	int x, y, x_diff, y_diff;
	float x_ratio = (((float)(picture.info.depth - 1)) / resizePicture.info.depth);
	float y_ratio = (((float)(picture.info.width - 1)) / resizePicture.info.width);
	float d1, d2, d3, d4;
	PIXELDATA p1, p2, p3, p4, temp;

	for (int i = 0; i < resizePicture.info.depth;i++) {
		for (int j = 0; j < resizePicture.info.width;j++) {
			x = floor(x_ratio*i);
			y = floor(y_ratio*j);
			x_diff = (x_ratio*i) - x;
			y_diff = (y_ratio*j) - y;

			d1 = (1 - x_diff) * (1 - y_diff);
			d2 = x_diff * (1 - y_diff);
			d3 = x_diff * y_diff;
			d4 = (1 - x_diff) * y_diff;

			p1 = picture.bitmap[x][y];
			p2 = picture.bitmap[x][y + 1];
			p3 = picture.bitmap[x + 1][y + 1];
			p4 = picture.bitmap[x + 1][y];
			
			temp.blueComponent = p1.blueComponent * d1 + p2.blueComponent * d2 + p3.blueComponent*d3 + p4.blueComponent*d4;
			temp.greenComponent = p1.greenComponent*d1 + p2.greenComponent*d2 + p3.greenComponent*d3 + p4.greenComponent*d4;
			temp.redComponent = p1.redComponent*d1 + p2.redComponent*d2 + p3.redComponent*d3 + p4.redComponent*d4;

			resizePicture.bitmap[i][j] = temp;
		}
	}
	return resizePicture;
}