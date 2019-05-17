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
public:
	image read(const char*);
};

class resizeImage :public image {
public:
	image resize(image&, double);
};

class saveImage :public image {
public:
	void save(image&, string);
};