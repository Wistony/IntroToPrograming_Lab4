#include "BMPHEAD.h"
#include "PIXELDATA.h"
#include <string>
using namespace std;

class image {
protected:
	BMPHEAD info;
	PIXELDATA **array;
};

class readImage:private image{
public:
	image read(const char*);
};

class resizeImage :private image {
public:
	image resize(image&, double);
};

class saveImage :private image {
public:
	void save(image&, string);
};