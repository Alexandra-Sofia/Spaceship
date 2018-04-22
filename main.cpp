#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "gl/glut.h"

#include "visuals.h"

int main(int argc, char* argv[])
{
	int winID;

	srand(time(NULL));

	glutInit(&argc, argv);  // initialize GLUT library state
	
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );  // RGB color and Double buffer
		
	//glutInitWindowSize(2000,1000);
	glutInitWindowSize(1400,700);
	glutInitWindowPosition(0,0);
	winID = glutCreateWindow("Interstellar");
	//glutFullScreen();
  
	// Configure various properties of the OpenGL rendering context
	Setup();
  
	// Callbacks for the GL and GLUT events:

	// The rendering function 
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
 
	//Enter main event handling loop
	glutMainLoop();

	return 0;	
}  
