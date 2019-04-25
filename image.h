#ifndef SRC_IMAGE_H_
#define SRC_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

class Image {

	int flag;

public:
	unsigned char* data;
	int width;
	int height;
	int maxgrey;
	Image();
	Image(int _width,  int _heigth) : width(_width), height(_heigth){
		data = new unsigned char[width*height];
		flag = 1;
		maxgrey = 255;
	};
	virtual ~Image();
	int fromFile(char *fileName);
	int toFile(char *fileName);
	unsigned char * operator[](int index);
	//unsigned char getPixel(int x,int y);

private:
	void itochar(int x, char* szBuffer, int radix);
	char* strrev(char* str);

};

#endif /* SRC_IMAGE_H_ */
