#include <iostream>
#include "gl/glut.h"

#include "Asteroid.h"

extern bool collision;

Asteroid::Asteroid() {}
Asteroid::~Asteroid() {}

void Asteroid::Load(char* str)
{
	LoadObjectFile(str, &md);
}

void Asteroid::Set(double x, double y, double z)
{
	size[0]=randfloat(0.1, 0.3);
	size[1]=randfloat(0.1, 0.3);
	size[2]=randfloat(0.1, 0.3);

	sizetmp[0]= 0.01 * size[0];
	sizetmp[1]= 0.01 * size[1];
	sizetmp[2]= 0.01 * size[2];

	posx=x;
	posy=y;
	posz=z;

	ratesize=0.0005;
	rate=0.1;

}

void Asteroid::AsteroidDraw()
{
	glPushMatrix();
		
		glColor3f(0.1, 0.1, 0.1);
		glTranslatef(posx, posy, posz);
		glRotatef(rotx,1,0,0);
		glScalef(sizetmp[0], sizetmp[1], sizetmp[2]);

		DisplayModel(&md);

	glPopMatrix();
	
	// Increase variables
	if(collision==true) return;

	posz += rate;
	if(sizetmp[0]<size[0])
		for(int i=0; i<3; i++) sizetmp[i] += ratesize;
	if(rotx>=360) { rotx = 0.0; }
	rotx+=0.2;
}

double Asteroid::get_posx() { return posx; }
double Asteroid::get_posy() { return posy; }
double Asteroid::get_posz() { return (posz-50); }

