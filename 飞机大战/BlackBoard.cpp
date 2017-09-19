#include "stdafx.h"

#include <math.h>
#include <iostream>

#include "GL/glut.h"

#include "BlackBoard.h"

using std::cout;
using std::endl; 

void BlackBoard::InitCommandLine(int *argc, char **argv)
{
	glutInit(argc, argv); 
}

void BlackBoard::InitWindowSize(int width, int height) 
{ 
	_width = width; 
	_height = height; 

	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(_width, _height);

	glutCreateWindow("BlackBoard");
}

void BlackBoard::UpdateWindowSize(int width, int height)
{
	_width = width;
	_height = height; 

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}


void BlackBoard::InitDisplayCallback(CallbackFunction callback) 
{ 
	glutDisplayFunc(callback);
} 

void BlackBoard::InitKeyboardCallback(KeyboardFunction callback) 
{ 
	glutKeyboardFunc(callback);
} 

void BlackBoard::InitReshapeCallback(ReshapeFunction callback)
{
	glutReshapeFunc(callback); 
}

void BlackBoard::InitMouseButtonCallback(MouseButtonFunction callback)
{
	glutMouseFunc(callback);
}

void BlackBoard::InitMouseMotionCallback(MouseMotionFunction callback)
{
	glutMotionFunc(callback);
}

void BlackBoard::InitIdleCallback(IdleFunction callback)
{
	glutIdleFunc(callback);
}

void BlackBoard::InstallTimerCallback(unsigned int millis, TimerFunction callback, int value)
{
	glutTimerFunc(millis, callback, value);
}

void BlackBoard::Show()
{
	std::cout<<"w,a,s,d,' '分别控制向上，向左，向下，向右，发射子弹"<<std::endl;
	std::cout<<"have fun"<<std::endl;
	glutMainLoop();
}

void BlackBoard::SetColor(double r, double g, double b)
{
	glColor3f(r, g, b);
}

void BlackBoard::Update()
{
	glutPostRedisplay();
}

void BlackBoard::DrawLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glVertex2f(GLfloat(x1) / _width * 2, GLfloat(y1) / _height * 2);
	glVertex2f(GLfloat(x2) / _width * 2, GLfloat(y2) / _height * 2);
	glEnd();

}

void BlackBoard::DrawCircle(int x, int y, int r)
{
	const int CIRCLE_SEGMENTATION = 360; 
	const GLfloat Pi = 3.1415926536f;

	GLfloat x0 = GLfloat(x) / _width * 2;
	GLfloat y0 = GLfloat(y) / _height * 2;

	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < CIRCLE_SEGMENTATION; ++i)
	{
		glVertex2f(x0 + GLfloat(r) * cos(2 * Pi * i / CIRCLE_SEGMENTATION) / _width * 2, y0 + GLfloat(r) * sin(2 * Pi * i / CIRCLE_SEGMENTATION) / _height * 2);
	}
	glEnd();
}

void BlackBoard::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);   
}

void BlackBoard::Flush()
{
	glFlush();
}



