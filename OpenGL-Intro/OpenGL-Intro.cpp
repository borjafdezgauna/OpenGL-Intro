#include <math.h>
#define GLEW_STATIC
#include "../3rd-party/glew-2.0.0/src/glew.h"
#include "../3rd-party/freeglut3/include/GL/freeglut.h"
#pragma comment(lib,"opengl32.lib")

#define MOVE_STEP .4
#define ANGLE_STEP 0.2
#define PI 3.1416f

float g_x = 0.0f;
float g_y = 0.0f;
float g_z = 10.0f;
float g_roll = 0.0f;
float g_pitch = 0.0f;
float g_yaw = 0.0f;
int g_w;
int g_h;
float g_cubeAngle = 0.f;



void Keyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	g_x -= MOVE_STEP * sin(g_yaw * PI / 180);
		g_z -= MOVE_STEP * cos(g_yaw * PI / 180); break;
	case '2':	g_x += MOVE_STEP * sin(g_yaw * PI / 180);
		g_z += MOVE_STEP * cos(g_yaw * PI / 180); break;
	case '6': g_yaw -= ANGLE_STEP; break;
	case '4': g_yaw += ANGLE_STEP; break;
	case 27: exit(0);
	}
}

void Set3DView()
{
	//set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	//set modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-g_roll, 0.0, 0.0, 1.0);
	glRotatef(-g_yaw, 0.0, 1.0, 0.0);
	glRotatef(-g_pitch, 1.0, 0.0, 0.0);
	glTranslatef(-g_x, -g_y, -g_z);
}



void DrawCube()
{
	glColor3f(0.5, 1.0, 0.5);
	glMatrixMode(GL_MODELVIEW);

	glRotatef(g_cubeAngle, 1.0, 0.0, 0.0);
	glutWireCube(1.0);
}

void DrawScene(void)
{
	//clean the backbuffer
	glClear(GL_COLOR_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	DrawCube();

}

void Reshape(int w, int h)
{
	//Reshape callback function
	g_h = h;
	g_w = w;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

int main(int argc, char** argv)
{

	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutCreateWindow(argv[0]);
	
	//glutFullScreen(); //<- if we enable this, we won't be able to debug it


	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);


	while (1)
	{
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle += 0.1;
		//queued events?
		glutMainLoopEvent();


		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
	return 0;


}

