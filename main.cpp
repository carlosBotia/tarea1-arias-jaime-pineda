#include <iostream>
#include <stdio.h>
#include "Image.h"
#include <math.h>
#include <sstream>

#include <cmath>
using namespace std;


void *runner(void *);
int ancho=Inicial.width, alto=Inicial.height;

int main(int argc, char** argv)
{
	Image Inicial, Final;
	char *in_path="./imgs/Face.pgm";
	char *out_path = "./imgs/Filtrada.pgm";
	int numThreads, N;

	

	if(Inicial.fromFile(in_path) == -1){
		printf("Error al leer la imagen.\n");
	}
	


//..........----------------------------------------------------------------

	stringstream ss1((char*)argv[1]);
	ss1 >> numThreads;
	pthread_t threads[numThreads];
	pthread_attr_t attr[numThreads];
	int bandera=0;

	for(int i=0; i<numThreads; i++){
		if(bandera!=numThreads)
		{
			cout <<"Filtro de imagen con:  "<< numThreads <<" Hilos" <<endl;
		}
		bandera=numThreads;
		
		pthread_attr_init(&attr[i]);
		pthread_create(&threads[i], &attr[i], runner, NULL);
	}
	for(int i=0; i<numThreads; i++){
		pthread_join(threads[i], NULL);
	}
	

	Final = Image(ancho, alto);
	memcpy(Final.data, Inicial.data, alto*ancho);// Copia la informacion de una imagen a otra//Mostrar por consola el resultado de la operación del hilo}
	 
}


//-----------------------------------------------------------------------

void *runner(void *)
{


	char gx[5][5] = {{2,2,4,2,2},{1,1,2,1,1},{0,0,0,0,0},{-1,-1,-2,-1,-1},{-2,-2,-4,-2,-2}};
	char gy[5][5] = {{2,1,0,-1,-2},{2,1,0,-1,-2},{4,2,0,-2,-4},{2,1,0,-1,-2},{2,1,0,-1,-2}};

	char guia[(ancho+2)][(alto+2)];
	int filtro1[(ancho)][(alto)];
	int filtro2[(ancho)][(alto)];

	int n=0;
	for(int y=0; y< (alto+2) ;y++)
	{
		for(int x =0; x< (ancho+2) ;x++)
		{
			if(y==0 || y == alto)
				guia[x][y]=0;	
			else if(x==0 || x == ancho)
				guia[x][y]=0;
			else
			{
				guia[x][y]= Inicial.data[n];
				n++;
			}
			
		}
	}
	
	n=0;
	for(int y=0;y<alto;y++) // alto
	{	
		for(int x=0;x<ancho;x++) //ancho
		{
			for(int j=0; j<5;j++)
			{
				for(int i=0;i<5;i++)					
				{
					filtro1[x][y]+=((guia[x+i][y+j])*(gx[i][j]));				
					filtro2[x][y]+=((guia[x+i][y+j])*(gy[i][j]));		
				}
			}
			int dato=sqrt((filtro1[x][y]*filtro1[x][y])+(filtro2[x][y]*filtro2[x][y]));
			if(dato<0)
			dato=0;
			if(dato>255)
			dato=255;
			Final.data[n]=(char)dato;	// retornarr		
			n++;
		}
	}




	if(Final.toFile(out_path) == -1){
	  	printf("Error al escribir la imagen.\n");
		exit(1);
	}
	exit(0);

}



*/
#include <iostream>
#include <stdio.h>
#include "Image.h"
#include <math.h>
#include <pthread.h>
#include <sstream>
#include <cmath>
#include <stdlib.h>
using namespace std;




//_dede_________

void *funcion (void*);
int m=0;
int n=0;
Image Inicial, Final;
char gx[3][3] = {{1,0,-1},{2,0,-2},{1,0,-1}};
char gy[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
char *in_path="./imgs/lena.pgm";
	char *out_path = "./imgs/Filtrada.pgm";
	int dato=0;
	//int ancho=Inicial.width, alto=Inicial.height;


int main(int argc, char** argv)
{
	

	int numThreads, N;
	

	if(Inicial.fromFile(in_path) == -1){
		printf("Error al leer la imagen.\n");
	}
	// mi funcion ________


stringstream ss((char*)argv[1]);
ss >> numThreads;
	
	

	pthread_t threads[numThreads];
	pthread_attr_t attr[numThreads];
	
  
	for(int i=0; i<numThreads; i++)
	{
		
		pthread_attr_init(&attr[i]);
		pthread_create(&threads[i], &attr[i],funcion, NULL);
		pthread_join(threads[i], NULL);
	}

	//______
	//funcion();









}
void *funcion(void* )
{
int ancho=Inicial.width, alto=Inicial.height;
	char guia[(ancho+2)][(alto+2)];
	int filtro1[(ancho)][(alto)];
	int filtro2[(ancho)][(alto)];
	Final = Image(ancho, alto);
	memcpy(Final.data, Inicial.data, alto*ancho);

	 n=0;
	for(int y=0; y< (alto+2) ;y++)
	{
		for(int x =0; x< (ancho+2) ;x++)
		{
			if(y==0 || y == alto)
				guia[x][y]=0;	
			else if(x==0 || x == ancho)
				guia[x][y]=0;
			else
			{ 
				guia[x][y]= Inicial.data[n];
				n++;
			}
			
		}
	}
	
	m=0;
	for(int y=0;y<alto;y++) // alto
	{	
		for(int x=0;x<ancho;x++) //ancho
		{
			for(int j=0; j<3;j++)
			{
				for(int i=0;i<3;i++)					
				{
					filtro1[x][y]+=((guia[x+i][y+j])*(gx[i][j]))/2;				
					filtro2[x][y]+=((guia[x+i][y+j])*(gy[i][j]))/2;		
				}
			}
			dato=sqrt((filtro1[x][y]*filtro1[x][y])+(filtro2[x][y]*filtro2[x][y]));
			if(dato<0)
			dato=0;
			if(dato>255)
			dato=255;
			Final.data[m]=(char)dato;			
			m++;
		}
	}	

	

	if(Final.toFile(out_path) == -1){
	  	printf("Error al escribir la imagen.\n");
		exit(1);
	}
	pthread_exit(0);
}
