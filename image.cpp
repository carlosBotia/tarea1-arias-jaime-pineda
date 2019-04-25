#include "Image.h"

Image::Image() {
	// TODO Auto-generated constructor stub

}

Image::~Image() {
	// TODO Auto-generated destructor stub
}


int Image::fromFile(char *fileName)
{
	Image *image = this;
	FILE *in_file;
	char ch;
	int type;
	char version[3];
	char line[100];
	char mystring [20];
	char *pch;
	int i;
	long int position;

	in_file = fopen(fileName, "r");
	if (in_file == NULL)
	{
		printf("ERROR: Unable to open file %s\n\n", fileName);
		return -1;
	}
	printf("\nReading image file: %s\n", fileName);
	// Determine image type (only pgm format is allowed)*/
	ch = fgetc(in_file);
	if(ch != 'P')
	{
		printf("ERROR: Not valid pgm file type\n");
		return -1;
	}

	ch = fgetc(in_file);


	/*convert the one digit integer currently represented as a character to

         an integer(48 == '0')*/

	type = ch - 48;

	if(type != 5)
	{
		printf("ERROR: only pgm raw format is allowed\n");
		return -1;
	}
	// Skip comments
//	char line[100];
	while ((ch = fgetc(in_file)) != EOF && isspace(ch));
	position = ftell(in_file);


	// skip comments
	if (ch == '#')
		{
			fgets(line, sizeof(line), in_file);
			while ((ch = fgetc(in_file)) != EOF && isspace(ch));
			position = ftell(in_file);
		}

	fseek(in_file, position-1, SEEK_SET);

	fgets (mystring , 20, in_file);
	pch = (char *)strtok(mystring," ");
	image->width = atoi(pch);
	pch = (char *)strtok(NULL," ");
	image->height = atoi(pch);
	fgets (mystring , 5, in_file);
	image->maxgrey = atoi(mystring);
	image->data = (unsigned char*)malloc(sizeof(unsigned char)*(image->height*image->width));//new unsigned char[row*col];
	image->flag = 1;
	for(i=0;i<(image->height*image->width);i++)
	{
		ch = fgetc(in_file);
		image->data[i] = (unsigned char)ch;
	}
	fclose(in_file);
	return 0;
}

int Image::toFile(char *fileName)
{
	Image *image = this;
	char parameters_str[5];
	int i;
	const char *format = "P5";
	if (image->flag == 0)
	{
		return -1;
	}
	FILE *fp = fopen(fileName, "w");
	if (!fp)
	{
		printf("Unable to open file %s\n", fileName);
		return -1;
	}
	fputs(format, fp);
	fputc('\n', fp);

	itochar(image->width, parameters_str, 10);
	fputs(parameters_str, fp);
	parameters_str[0] = 0;
	fputc(' ', fp);

	itochar(image->height, parameters_str, 10);
	fputs(parameters_str, fp);
	parameters_str[0] = 0;
	fputc('\n', fp);

	itochar(image->maxgrey, parameters_str, 10);
	fputs(parameters_str, fp);
	fputc('\n', fp);

	for (i = 0; i < (image->width * image->height); i++)
	{
		fputc(image->data[i], fp);
	}
	fclose(fp);
	return 0;
}

void Image::itochar(int x, char* szBuffer, int radix)
{
	int i = 0, n, xx;
	n = x;
	while (n > 0)
	{
		xx = n%radix;
		n = n/radix;
		szBuffer[i++] = '0' + xx;
	}
	szBuffer[i] = '\0';
	strrev(szBuffer);
}

char* Image::strrev(char* str)
{
	char *p1, *p2;
	if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
	{
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}

unsigned char * Image::operator[](int index){
	return data+(index*width);
}

