#include "TextureBuilder.h"
#include <glut.h>

double r = 1;
int rd = 1;

double rw = 1;
double rl = 1;

bool w = true;
bool rwb = false;
bool rlb = false;

bool s = true;
bool l = true;
bool tex = true;

GLuint texEarthID;


void setupLights() {


	GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat l0Diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
	GLfloat l0Position[] = { 10.0f, 0.0f, 0.0f, s };
	GLfloat l0Direction[] = { -1.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);

	GLfloat l1Diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l1Ambient[] = { 0.0f, 0.1f, 0.0f, 1.0f };
	GLfloat l1Position[] = { 0.0f, 10.0f, 0.0f, s };
	GLfloat l1Direction[] = { 0.0, -1.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Diffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1Ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, l1Position);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1Direction);

	GLfloat l2Diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat l2Ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };
	GLfloat l2Position[] = { 0.0f, 0.0f, 10.0f, s };
	GLfloat l2Direction[] = { 0.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2Diffuse);
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2Ambient);
	glLightfv(GL_LIGHT2, GL_POSITION, l2Position);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2Direction);


}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
	gluPerspective(80, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 10, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	if (rlb)
		glRotated(rl, 1, 1, 1);
	setupLights();
	glPopMatrix();

	setupCamera();

	if (w)
	{
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texEarthID);
		glRotatef(-90, 1, 0, 0);
		GLUquadricObj* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, true);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		gluSphere(sphere, r, 50, 50);
		gluDeleteQuadric(sphere);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		if (rwb)
			glRotated(rw, 1, 1, 1);

		glBegin(GL_QUADS);

		glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 7, 0);
		glVertex3f(7, 7, 0);
		glVertex3f(7, 0, 0);

		glNormal3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 7);
		glVertex3f(0, 7, 7);
		glVertex3f(0, 7, 0);

		glNormal3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(7, 0, 0);
		glVertex3f(7, 0, 7);
		glVertex3f(0, 0, 7);

		glEnd();
		glPopMatrix();
	}



	glFlush();
}

void anim()
{
	r += 0.001*rd;
	if (r<0.05 || r>6)
		rd *= -1;

	rw += 0.1;
	rl += 0.1;

	glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{

	if (k == 'w')//show the walls with the light direction
		w = !w;
	if (k == 'q')//rotating the light
		rlb = !rlb;
	if (k == 'e')//rotate the walls
		rwb = !rwb;
	if (k == 's')//spot light or directional
		s = !s;
	if (k == 'a')
		l = !l;

	if (k == 'z')//stop animation
		glutIdleFunc(0);

	if (k == 'x')//start animation
		glutIdleFunc(anim);

	glEnable(GL_LIGHTING);
	if (!l)
		glDisable(GL_LIGHTING);


	/*if(k=='d')
	tex=!tex;
	glEnable(GL_TEXTURE_2D);
	if(!tex)
	glDisable(GL_TEXTURE_2D);*/

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 6");
	glutDisplayFunc(Display);
	glutIdleFunc(anim);
	glutKeyboardFunc(key);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	//	glEnable(GL_TEXTURE_2D);

	//	loadBMP(&texEarthID, "textures/earth.bmp", false);
	//
	glutMainLoop();
}