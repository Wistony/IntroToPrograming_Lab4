#include "BMPHEAD.h"
#include "PIXELDATA.h"
#include <string>
using namespace std;

class image {
public:
	BMPHEAD info;
	PIXELDATA **bitmap;
};

class readImage:public image{
	void readInfoHeader(image&,FILE*);
public:
	image read(const char*);
};

class resizeImage {
	void interpolation(image* startImage, image* finishImage);
public:
	image resize(image&, double);
};

class saveImage :public image {
	void saveInfoHeader(image&,FILE*);
public:
	void save(image&, const char*);
};