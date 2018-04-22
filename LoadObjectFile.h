#ifndef LOADOBJECTFILE_H
#define LOADOBJECTFILE_H

#include <iostream>
#include <string>

struct point
{
	float x; 
	float y; 
	float z; 
};

struct face
{
	int vtx[4];
};

struct model
{
	struct point *vertices;
	struct face *faces;
	int num_vertices;
	int num_faces;
};

void LoadObjectFile(char *, model *);

void DisplayModel(model *);

//////////////////////

void vinsert(struct point&, std::string&);
void finsert(struct face&, std::string&);
void finsert2(struct face&, std::string&);

//////////////////////

double randfloat(double, double);


#endif
//*/