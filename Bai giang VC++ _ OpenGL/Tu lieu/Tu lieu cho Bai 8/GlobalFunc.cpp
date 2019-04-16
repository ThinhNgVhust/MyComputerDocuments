
#include "stdafx.h"
#include "GlobalFunc.h"
#include "glut.h"

bool ReadSTLFile(char *filename,float * & coord,long & count)
{
	float v1,v2,v3; 
	float* vertex=NULL;
	long i=0;
	FILE *f;
	fopen_s(&f,filename,"rt");
	if(f== NULL) return false;
	else
	{ 
		vertex= (float*)realloc(vertex,0);
		while(fgetc(f)!= '\n'){}
		while(1)
		{
  			if(fscanf_s(f,"%*s%*s%f%f%f",&v1,&v2,&v3)<3) break;
			vertex= (float*) realloc(vertex,(i+1)*12*sizeof(float));
			vertex[12*i]= v1; vertex[12*i+1]= v2; vertex[12*i+2]= v3;
			fscanf_s(f,"%*s%*s");
			for(int j=1;j<4;j++)
			{
				fscanf_s(f,"%*s%f%f%f%f",&v1,&v2,&v3);
				vertex[12*i+3*j]= v1; vertex[12*i+3*j+1]= v2; vertex[12*i+3*j+2]= v3; 
			}
			fscanf_s(f,"%*s%*s");
			i++;
		} 
		count= i*12; 
		coord = vertex;
		vertex = NULL;
		fclose(f);
		return true;
	}
}

void DrawSTLData(float *a, long c)
{
	int i,j;
	for(i=0; i<c/12; i++) 
	{
		j=i*12;
		glBegin(GL_TRIANGLES);
		glNormal3f(a[j],a[j+1],a[j+2]);
		glVertex3f(a[j+3],a[j+4],a[j+5]);
		glVertex3f(a[j+6],a[j+7],a[j+8]);
		glVertex3f(a[j+9],a[j+10],a[j+11]);
		glEnd();
	}
}