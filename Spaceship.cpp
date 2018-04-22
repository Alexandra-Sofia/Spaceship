#include <iostream>
#include "gl/glut.h"

#include "Spaceship.h"

Spaceship::Spaceship() {}
Spaceship::~Spaceship() {}

void Spaceship::Set()
{
	x=0.0;
	y=0.0;
	z=-20.0;
	angleX=0.0;
	angleY=0.0;
	angleZ=0.0;

	angle=5;
}

void Spaceship::SpaceshipDraw()
{
	glPushMatrix();
			
		glTranslatef(0.0, 0.0, z);
		glTranslatef(0.0, y, 0.0);
		glTranslatef(x, 0.0, 0.0);

		glRotatef(angleX, 1, 0, 0);
		glRotatef(angleY, 0, 1, 0);
		glRotatef(angleZ, 0, 0, 1);

		starship();
					
	glPopMatrix(); 
}

void Spaceship::starship()
{
	
	glScalef(0.1, 0.1, 0.1);
	//-------Body-----------------------------------
	glPushMatrix();
	glColor3f(0.6, 0.0, 0.3);
	glScalef(2.0, 2.0, 5.0);
	glutSolidSphere(5.0,30,30);
	glColor3f(0.0, 0.8, 0.8);
	glTranslatef(0.0,0.0,-2.5);
	glutSolidSphere(3.0,30,30);
	glPopMatrix();
	//-------wings----------------------------------
	glPushMatrix();
	glColor3f(0.0, 0.8, 0.8);
	glScalef(10.0, 1.0, 1.0);
	glutSolidSphere(5.0,30,30);
	glPopMatrix(); 
	//------wright propeller---------------------------------
	glPushMatrix();
	glColor3f(0.6, 0.0, 0.3);
	glTranslatef(30.0,0.0,-4.0);
	glutSolidSphere(3.5,30,30);
	//-----
	glRotatef(angle, 0, 0, 1);
	//-----
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0,0.0,-4.0);
	glScalef(0.5, 2.0, 0.5);
	glutSolidSphere(3.0,30,30);
	glScalef(4.0, 0.25, 1.0);
	glutSolidSphere(3.0,30,30);
	//-----
	glPopMatrix(); 
	//------left propeller---------------------------------
	glPushMatrix();
	glColor3f(0.6, 0.0, 0.3);
	glTranslatef(-30.0,0.0,-4.0);
	glutSolidSphere(3.5,30,30);
	//-----
	glRotatef(angle, 0, 0, 1);
	//-----
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0,0.0,-4.0);
	glScalef(0.5, 2.0, 0.5);
	glutSolidSphere(3.0,30,30);
	glScalef(4.0, 0.25, 1.0);
	glutSolidSphere(3.0,30,30);
	//-----
	glPopMatrix();
	//------tail-----------------------------------
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.0,5.0,20.0);
	glRotatef(45, 1, 0, 0);
	glScalef(1.0, 2.0, 1.0);
	glutSolidSphere(5.0,30,30);
	glPopMatrix(); 
	//-------moretail-------------------------------
	glPushMatrix();
	glColor3f(0.0, 0.8, 0.8);
	glTranslatef(0.0,13.0,25.0);
	glScalef(5.0, 0.7, 1.0);
	glutSolidSphere(5.0,30,30);
	glPopMatrix(); 
	//-------Alien-----------------------------------
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.0,8.0,-7.0);
	glScalef(0.5, 1.0, 0.5);
	glutSolidSphere(6.5,30,30);
	//eyes---------
	glTranslatef(2.0,3.0,-5.0);
	glScalef(2.0, 1.0, 0.5);
	//1w------------------
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(1.0,30,30);
	//2w--------------
	glTranslatef(-2.0,0.0,0.0);
	glutSolidSphere(1.0,30,30);
	//3w--------------
	glTranslatef(1.0,2.0,1.0);
	glutSolidSphere(0.5,30,30);
	glPopMatrix(); 
	//--------------------------------
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glScalef(0.5, 0.5, 1.0);
	//---1b
	glTranslatef(0.0,0.0,-0.5);
	glutSolidSphere(1.0,30,30);
	//--2b
	glTranslatef(-4.0,0.0,0.0);
	glutSolidSphere(1.0,30,30);
	//--3b
	glTranslatef(2.0,3.8,0.0);
	glutSolidSphere(0.5,30,30);
	glPopMatrix();
	//----------------------------------------------
	glPopMatrix(); 
	//--------bridge---------------------------------
	glPushMatrix();
	glColor4f(0.0, 1.0, 1.0, 0.3);
	glTranslatef(0.0,8.0,-7.0);
	glScalef(1.0, 1.2, 1.5);
	glutSolidSphere(6.0,30,30);
	glPopMatrix(); 

	// Propeler rotation
	angle=angle+2;
}
