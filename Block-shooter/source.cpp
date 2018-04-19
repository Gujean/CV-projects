#include <windows.h>
#include <gl/freeglut.h>
#include <gl/glut.h>
#include <iostream>
using namespace std;

int shoot = 0;
int fall = 0;
double i = 2.1;
double j = 1.0;
double viteza = 0.5;
double *v = new double[300]; //vector pt bullet in care retin i-ul
double *a = new double[300]; // vector pt asteroizi in care se da un i random
int k = 0;
int c = 0;
double *height = new double[300]; //vector pt asteroizi in care retin inaltimea
double *inaltime = new double[300]; // vector pt bullet in care retin inaltimea de la care pleaca fiecare bullet
double alpha = 1.0;
bool gameOver = false;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);

}
void remover(int x, int y)
{
	for (int x1 = x; x1 < k; x1++)
	{
		v[x1] = v[x1 + 1];
		inaltime[x1] = inaltime[x1 + 1];
	}
	k--;
	for (int y1 = y; y1 < c; y1++)
	{
		a[y1] = a[y1 + 1];
		height[y1] = height[y1 + 1];
	}
	c--;
}
void check()
{
	for (int x = 1; x <= k; x++)
		for (int y = 1; y <= c; y++)
		{
			if (a[y] <= v[x] && a[y] + 30 >= v[x] && inaltime[x] >= height[y]) {
				remover(x, y);
			}
			
		}
	for (int y = 1; y <= c; y++)
	{
		if (i - a[y] > -30 && i - a[y] < 20 && height[y] >= 140 && height[y] <= 220) {

			gameOver = true;
			PlaySound("finish.wav", NULL, SND_ASYNC | SND_FILENAME);
		}

	}
}
void reseter()
{
	k = 0;
	c = 0;
	alpha = 1.0;
	shoot = 0;
	fall = 0;
	i = 2.1;
}
void keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		k++;
		shoot = 1;
		inaltime[k] = 220;
		v[k] = i;
		PlaySound("shot.wav", NULL, SND_ASYNC | SND_FILENAME );
		break;
	case GLUT_KEY_DOWN:
		c++;
		fall = 1;
		height[c] = 500;
		a[c] = rand() % 700 + 50;
		PlaySound("meteor.wav", NULL, SND_ASYNC | SND_FILENAME);
		break;
	case GLUT_KEY_LEFT:
		if (gameOver == true)
		{
			gameOver = false;
			reseter();
		}
		break;

	}
}

void racheta() {
	
	//glColor3f(0.137255, 0.419608, 0.556863);
	glColor3f(0.184314, 0.309804, 0.309804);
	glBegin(GL_POLYGON);
	glVertex2i(10, 120);
	glVertex2i(0, 110);
	glVertex2i(0, 80);
	glVertex2i(-10, 40);
	glVertex2i(30, 40);
	glVertex2i(20, 80);
	glVertex2i(20, 110);

	glColor3f(0.90, 0.91, 0.98);
	glVertex2i(10, 120);
	glVertex2i(0, 110);
	glVertex2i(20, 110);
	glEnd();
	//aripa stanga
	glColor3f(0.90, 0.91, 0.98);
	glBegin(GL_POLYGON);
	glVertex2i(0, 80);
	glVertex2i(-10, 40);
	glVertex2i(0, 40);
	glEnd();
	//aripa dreapta
	glColor3f(0.90, 0.91, 0.98);
	glBegin(GL_POLYGON);
	glVertex2i(20, 40);
	glVertex2i(30, 40);
	glVertex2i(20, 80);
	glEnd();
	//foc stanga
	glColor3f(0.81, 0.71, 0.23);
	glBegin(GL_POLYGON);
	glVertex2i(10, 40);
	glVertex2i(5, 35);
	glVertex2i(0, 40);
	glEnd();
	//foc dreapta
	glColor3f(0.81 , 0.71 , 0.23);
	glBegin(GL_POLYGON);
	glVertex2i(20, 40);
	glVertex2i(15, 35);
	glVertex2i(10, 40);
	glEnd();
	
}

void deseneazaScena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (gameOver == false)
	{	//miscarea rachetei
		glPushMatrix();
		glTranslated(i, 100.0, 0.0);
		glPushMatrix();

		//desenare racheta 
		racheta();

		glPopMatrix();
		glPopMatrix();

		//bullet
		if (shoot == 1) {
			for (int l = 0; l <= k; l++) {
				if (inaltime[l] < 620) {
					// urcare bullet
					glPushMatrix();
					glTranslated(v[l], inaltime[l], 0.0);
					glPushMatrix();
					// desenare bullet
					glRotated(viteza, 0.0, 0.0, 1.0);
					glColor3f(0.0, 0.5, 0.0);
					glRecti(0.0, 0.0, 10, 10);

					glPopMatrix();
					glPopMatrix();

				}
			}
			for (int l = 0; l <= k; l++) {
				inaltime[l] += 1.0;
			}
			viteza += 0.4;

		}

		// asteroizi
		if (fall == 1) {
			for (int g = 0; g <= c; g++) {
				if (height[g] > 150) {
					//caderea
					glPushMatrix();
					glTranslated(a[g], height[g], 0.0);
					// desenarea
					glColor3f(0.435294 , 0.258824 , 0.258824);
					glRecti(0.0, 0.0, 30, 30);
					glPopMatrix();
				}
			}
			for (int g = 0; g <= c; g++) {
				height[g] -= 0.2;
			}

			viteza += 0.1;
		}
		
		check();
		Sleep(5);
	}
	else
	{
		glColor3f(1.0, 1.0, 1.0);
		// GAME OVER
		glRasterPos2f(380, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'G');
		glRasterPos2f(394, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
		glRasterPos2f(408, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');
		glRasterPos2f(422, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
		glRasterPos2f(450, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
		glRasterPos2f(464, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'V');
		glRasterPos2f(478, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
		glRasterPos2f(490, 200);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');

		// KEY LEFT-RESTART
		glRasterPos2f(380, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'K');
		glRasterPos2f(392, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
		glRasterPos2f(404, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
		glRasterPos2f(420, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'L');
		glRasterPos2f(432, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
		glRasterPos2f(444, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'F');
		glRasterPos2f(456, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
		glRasterPos2f(465, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
		glRasterPos2f(475, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
		glRasterPos2f(488, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
		glRasterPos2f(501, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'S');
		glRasterPos2f(514, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
		glRasterPos2f(527, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
		glRasterPos2f(540, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'R');
		glRasterPos2f(553, 180);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'T');
	}
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miscad(void)
{
	i = i + alpha;
	if (i > 750.0)
		alpha = -1.0;
	else if (i < 0.0)
		alpha = 1.0;
	//j = j + 5.0;

	glutPostRedisplay();
}

void miscas(void)
{
	i = i + alpha;
	if (i < 0.0)
		alpha = 1.0;
	else if (i > 750.0)
		alpha = -1.0;
	//j = j + 5.0;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = -1.0; glutIdleFunc(miscas);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = 1.0; glutIdleFunc(miscad);
		break;

	default:
		break;
	}
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Block Shooting");
	init();
	glutDisplayFunc(deseneazaScena);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	glutMainLoop();

}
