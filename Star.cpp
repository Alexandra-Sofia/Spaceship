#include <iostream>
#include "gl/glut.h"   // - An interface and windows management library

#include "Star.h"

using namespace std;

GLfloat light_position[4];

double randfloat(double, double);

Star::Star() {}
Star::~Star() {}

void Star::Set(double r1, double r2, float x1, float y1)
{
	cout << "Star creation:\n";

	radius_inner = r1;
	radius_outer = r2;
	radius_tmp = randfloat(r1, r2);
	radius_change = 0.002;

	if(rand()%2==0) radius_change *= -1;

	x = x1;
	y = y1;
}

void Star::StarDraw(double xmove, double ymove, int height, int width)
{
	glPushMatrix();

		x += xmove;
		y += ymove;

		
		if(x > width) {
			x = -width;
		}
		else if(x < - width) {
			x = width;
		}
		else if(y > height) {
			y = -height;
		}
		else if(y < -height) {
			y = height;
		}
		
		glTranslatef(x , y, 0.0);
		glutSolidSphere(radius_inner , 5, 5);

		glColor4f(1.0, 1.0, 1.0, 1.0 - radius_tmp);
		glutSolidSphere(radius_tmp, 5, 5);

		radius_tmp -= radius_change;
		if(radius_tmp > radius_outer || radius_tmp < radius_inner ) { radius_change *= -1; }


	glPopMatrix();
}

void Star::SunDraw(double xmove, double ymove, int height, int width)
{
	glPushMatrix();

		glTranslatef(0.0, 0.0, 10.0);

		x += xmove;
		y += ymove;

		light_position[0]=x;
		light_position[1]=y;
		light_position[2]=0.0;
		glLightfv( GL_LIGHT0, GL_POSITION, light_position);

		glTranslatef(x , y, 0.0);

		glColor3f(1.0, 1.0, 0.0);
		glutSolidSphere(radius_inner , 60, 25);


		glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glutSolidSphere(radius_inner , 60, 25);
		glPopMatrix();

		glPushMatrix();
			glColor4f(1.0, 1.0, 0.0, double(1.0 / radius_tmp) );
			glutSolidSphere(radius_tmp, 60, 25);
		glPopMatrix();

		radius_tmp -= radius_change;
		if(radius_tmp > radius_outer || radius_tmp < radius_inner ) { radius_change *= -1; }


	glPopMatrix();
}

void Star::Print()
{
	cout << "Radius inner: " << radius_inner << "\nRadius outer:  " << radius_outer << "\nPosition: " << x << ", " << y << "\n\n";
}

//////////////////////////////////////

Sky::Sky() {}
Sky::~Sky() {}

void Sky::Set()
{
	cout << "Sky Constructor\n\n" ;

	asteroid.Load("myasteroid.obj");
	asteroid.notset=true;
	time=10;

	num_of_stars=1000;
	xmove=0.0;
	ymove=0.0;

	double radiusMin=0.05;
	double radiusMax=0.3;

	height = glutGet(GLUT_WINDOW_HEIGHT)/10;
	width = glutGet(GLUT_WINDOW_WIDTH)/10;

	height = height/2 ;
	width = width/2 ;

	Sun.Set(5.0, 6.0, width/3, height/3);
	light_position[0]=width/3;
	light_position[1]=height/3;
	light_position[2]=0.0;
	light_position[3]=0.0;
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);


	stars = (class Star*) malloc(num_of_stars * sizeof(class Star));
	
	for(int i=0; i<num_of_stars; i++) {

		if(rand()%3==0) {
			stars[i].Set(radiusMin,radiusMin, randfloat(-width , width ), randfloat(-height , height ));
			continue;
		}

		double radius1 = randfloat(radiusMin, radiusMax);
		double radius2 = randfloat(radius1 , radiusMax);
		
		stars[i].Set(radius1,radius2, randfloat(-width , width ), randfloat(-height , height ));

	}
}

void Sky::SkyDraw()
{
	glPushMatrix();

		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(0.0, 0.0, -50.0);

		for(int i=0; i<num_of_stars; i++)
			stars[i].StarDraw(xmove, ymove, height, width);

		Sun.SunDraw(xmove, ymove, height, width);

		if(time==0)
		{
			if(asteroid.notset==true)
			{
				int w, h;

				w = rand()%10;
				h = rand()%10;

				if(rand()%2!=0) w *= -1;
				if(rand()%2!=0) h *= -1;
				
				asteroid.Set((double) w, (double) h, 1.0);
				asteroid.notset=false;
			}

			asteroid.AsteroidDraw();
			if(asteroid.posz > 50)
			{
				time=rand()%200+10;
				asteroid.notset=true;
			}

			
		}
		else time--;

	glPopMatrix();

	xmove=0;
	ymove=0;
}



unsigned int Sky::getTime()
{
	return time;
}

bool Sky::AsteroidNotSet()
{
	 std::cout << asteroid.notset << "\n";

	return asteroid.notset;
}







