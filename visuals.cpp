#include <iostream>     // - Just for some ASCII messages
#include "gl/glut.h"   // - An interface and windows 
                       //   management library

#include "visuals.h"   // Header file for our OpenGL functions
#include "Star.h"
#include "Spaceship.h"

class Sky sky;
class Spaceship ship;

bool collision_detection(double, double, double, double, double, double);
bool collision;

void keimeno(const char *, float);

void Idle()
{
	if(sky.AsteroidNotSet()==false)
		collision = collision_detection(ship.x, ship.y, ship.z, sky.asteroid.get_posx(), sky.asteroid.get_posy(), sky.asteroid.get_posz());
	glutPostRedisplay(); // redrawing	
}

bool collision_detection(double x, double y, double z, double astrx, double astry, double astrz)
{
	if( abs(z-astrz) <= 2)
	{		
		if( abs(x-astrx) <= 6 )
		{
			if( abs(y-astry) <= 3 ) {
				return true;
			}
		}
	}
	return false;
}

void keimeno(const char *str,float size)
{
	glPushMatrix();
		glScalef(size,size,size);

		for (int i=0;i<strlen(str);i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();
}


void end(){
		
	glPushMatrix();
	glTranslatef(0,8.0,-16.0);
	glTranslatef(-4.0,0.0,0.0);
	glColor3f(1.0, 1.0, 1.0);
	keimeno("*--*FATAL COLLISION*--*",0.005f);
	glTranslatef(1.0,-1.0,0.0);
	keimeno("-*-GAME OVER-*-",0.005f);
	glTranslatef(-0.3,-1.0,0.0);
	keimeno("-PRESS Q TO EXIT-",0.005f);
	glPopMatrix();
}

void Render()
{  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clean up the colour of the window
															// and the depth buffer
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	//glColor3f(1.0, 0.5, 0.2);								// Set drawing colour = orange
	//glColor3f(1.0, 0.0, 0.0);


	if(collision==false)
	{		
		sky.SkyDraw();
		ship.SpaceshipDraw();
	}
	else
	{
		end();
		sky.SkyDraw();
		ship.SpaceshipDraw();

	}

	glutSwapBuffers();
}

//-----------------------------------------------------------

void Keyboard(unsigned char key,int x,int y)
{
	if(collision==true && key!='q') return;

	switch(key)
	{		
		case 'q' : exit(0);
			break;
		case 'w':
			sky.ymove = 1;
			ship.angleX += 3;
			break;
		case 's':
			sky.ymove = -1;
			ship.angleX -= 3;
			break;
		case 'd':
			sky.xmove = 1;			
			ship.angleY -= 3;
			break;
		case 'a':
			sky.xmove = -1;			
			ship.angleY += 3;
			break;
		default:
			break;

	}

	glutPostRedisplay();

}

void SpecialKeys(int key, int x, int y)
{
	if(collision==true) return;

	switch(key)
	{
		case GLUT_KEY_UP:
						
			if(ship.angleX < 45)
			{
				ship.angleX += 5;
				ship.y += 1;
			}
			break;
		case GLUT_KEY_DOWN:
			
			if(ship.angleX > -45)
			{
				ship.angleX -= 5;
				ship.y -= 1;
			}
			break;
		case GLUT_KEY_RIGHT:
			
			if(ship.angleZ > -90)
			{
				ship.angleZ -= 3;
				ship.x += 1;
			}
			break;
		case GLUT_KEY_LEFT:
			
			
			if(ship.angleZ < 90)
			{
				ship.angleZ += 3;
				ship.x -= 1;
			}
			break;
		default:
			break;
	}
}

void Setup() 
{
	sky.Set();
	ship.Set();

	collision=false;

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	//GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	//glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, specularLight );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glFrontFace(GL_CW);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

// w and h are window sizes returned by glut
void Resize(int w, int h)
{
	if (h==0) h=1;
	glViewport(0,0,w,h);

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();					// initialise gl projection matrix
 
	gluPerspective(60.0f, (GLfloat)w/(GLfloat)h, 0.1f, 500.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

}