#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "texturas/RgbImage.h"

using namespace std;

float camaraX = -20;
float camaraY = 20;
float camaraZ = 30;
float centroX = 0;
float centroY = 10;
float centroZ = 0;
float angulo = 2.3088;
float radio = 62;

GLuint texturas[12];
GLUquadric* quad;

/*VARIABLES DE MOVIMIENTO*/

float giroSol = 0;
float giroPersonaje = 0;
float carroPosZ = 0;
int carroLadoZ = 1;

//float dezplazamiento = -45;
//float movimientoCamara = 0.5;

void loadTextureFromFile(const char* filename, int index) {
	RgbImage theTexMap(filename);

	glGenTextures(1, &texturas[index]);
	glBindTexture(GL_TEXTURE_2D, texturas[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
}

void cargarImagenes() {
	loadTextureFromFile("texturas/piso.bmp", 0);
	loadTextureFromFile("texturas/sol.bmp", 1);
	loadTextureFromFile("texturas/fondo1.bmp", 2);
	loadTextureFromFile("texturas/fondo2.bmp", 3);
	loadTextureFromFile("texturas/fondo3.bmp", 4);
	loadTextureFromFile("texturas/navidad.bmp", 5);
	loadTextureFromFile("texturas/tronco.bmp", 6);
	loadTextureFromFile("texturas/copa_arbol.bmp", 7);

}

void iniciarVentana(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)w / (float)h, 1, 200);

}

void inicializarLuces() {

	GLfloat light_ambient[] = { 0.3,0.3,0.3,1 };
	GLfloat light_diffuse[] = { 0.3,0.3,0.3,1 };
	GLfloat light_specular[] = { 0.2,0.2,0.2,1 };

	float reflejo[] = { 0,0,0,1 };
	float posicionLuz[] = { 0,70,0,1 };
	int sombra = 128;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, reflejo);
	glMateriali(GL_FRONT, GL_SHININESS, sombra);
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

	//Luces Piso

	GLfloat light_ambient1[] = { 0.1,0.1,0.1,1 };
	GLfloat light_diffuse1[] = { 0.1,0.1,0.1,1 };
	GLfloat light_specular1[] = { 0.1,0.1,0.1,1 };
	float posicionLuz1[] = { -50,0,0,1 };
	float posicionLuz2[] = { 0,0,50,1 };
	float posicionLuz3[] = { 50,0,0,1 };
	float posicionLuz4[] = { 0,0,-50,1 };

	//glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicionLuz1);

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT2, GL_POSITION, posicionLuz2);

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT3, GL_POSITION, posicionLuz3);

	glEnable(GL_LIGHT4);
	glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT4, GL_POSITION, posicionLuz4);

}

void piso() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[0]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, -1, 0);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1);  glVertex3d(-50, 0, -50);
	glTexCoord2d(1, 1); glVertex3d(50, 0, -50);
	glTexCoord2d(1, 0); glVertex3d(50, 0, 50);
	glTexCoord2d(0, 0); glVertex3d(-50, 0, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void dibujarEjes() {

	glPushMatrix();
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(50, 0, 0);

	glColor3ub(0, 255, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 50, 0);

	glColor3ub(0, 0, 255);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 50);

	glEnd();

	glPopMatrix();

}

void barriga() {

	glPushMatrix();
	glTranslated(0, 7, 0);
	glutSolidSphere(8, 80, 80);
	glPopMatrix();
}

void cabeza() {

	glPushMatrix();
	glTranslated(0, 18, 0);
	glutSolidSphere(6, 80, 80);
	glPopMatrix();
}

void sombrero() {

	glPushMatrix();
	glTranslated(0, 22, 0);
	glScaled(3, 0.6, 3);
	glutSolidSphere(2, 50, 50);
	glPopMatrix();
}

void copa() {

	glPushMatrix();
	glTranslated(0, 22, 0);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 4, 4, 8, 50, 50);
	glPopMatrix();
}

void tapa() {
	glPushMatrix();
	glTranslated(0, 30, 0);
	glScaled(3, 0.6, 3);
	glutSolidSphere(1.35, 50, 50);
	glPopMatrix();
}

void ojo(float posX, float rot) {
	glPushMatrix();
	glTranslated(posX, 19, 5.5);
	glRotated(rot, 0, 0, 1);
	glScaled(0.9, 0.7, 0.7);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
}

void nariz() {
	glPushMatrix();
	glTranslated(0, 17.5, 2.5);
	glScaled(3, 1.5, 3);
	glutSolidCone(1, 2, 10, 10);
	glPopMatrix();
}

void point() {
	glPushMatrix();
	glTranslated(0, 5, 7);
	glutSolidSphere(1, 80, 80);
	glPopMatrix();
}

void point1() {
	glPushMatrix();
	glTranslated(0, 7, 7.3);
	glutSolidSphere(1, 80, 80);
	glPopMatrix();
}

void point2() {
	glPushMatrix();
	glTranslated(0, 9, 7);
	glutSolidSphere(1, 80, 80);
	glPopMatrix();
}

void point3() {
	glPushMatrix();
	glTranslated(0, 11, 6.1);
	glutSolidSphere(1, 80, 80);
	glPopMatrix();
}

void corbata() {
	glPushMatrix();
	glTranslated(0, 14, 0);
	glScaled(3, 0.6, 3);
	glutSolidSphere(2, 80, 80);
	glPopMatrix();
}

void corbata1() {
	glPushMatrix();
	glTranslated(0, 14.2, 5.3);
	glRotated(-90, -40, 0, 55);
	glScaled(1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 5, 50, 50);
	glPopMatrix();
}

void corbata2() {
	glPushMatrix();
	glTranslated(0, 14.2, 5.3);
	glRotated(-90, -40, 0, -55);
	glScaled(1, 1, 1);
	gluCylinder(gluNewQuadric(), 0.5, 0.5, 5, 50, 50);
	glPopMatrix();
}

void puño() {
	glPushMatrix();
	glTranslated(2.2, 11.45, 8.35);
	glutSolidSphere(0.6, 80, 80);
	glPopMatrix();
}

void puño2() {
	glPushMatrix();
	glTranslated(-2.2, 11.45, 8.35);
	glutSolidSphere(0.6, 80, 80);
	glPopMatrix();
}

void brazo() {
	glPushMatrix();
	glTranslated(6, 9, 3);
	glRotated(90, -20, 90, 90);
	glScaled(1, 1, 5);
	glutSolidCone(2, 2, 80, 80);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-6, 9, 3);
	glRotated(-90, 20, 90, 90);
	glScaled(1, 1, 5);
	glutSolidCone(2, 2, 80, 80);
	glPopMatrix();
}

void boca() {
	glPushMatrix();
	glTranslated(0, 15.85, 5.4);
	glRotated(90, 0, 0, 90);
	glScaled(1, 5, 1);
	glutSolidCube(0.6);
	glPopMatrix();
}

void guantes() {
	glPushMatrix();
	glTranslated(11.5, 15, 7);
	glutSolidSphere(1.2, 80, 80);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-11.5, 15, 7);
	glutSolidSphere(1.2, 80, 80);
	glPopMatrix();
}

void soporte() {
	glPushMatrix();
	glColor3ub(115, 98, 84);
	glTranslated(0, -3, 0);
	glScaled(6, 1, 6);
	glutSolidSphere(1.35, 50, 50);
	glPopMatrix();
}

void personaje() {
	glPushMatrix();
	glTranslated(0, 0, 0);
	glColor3ub(255, 255, 255);
	barriga();
	cabeza();
	glColor3ub(0, 35, 255);
	sombrero();
	copa();
	tapa();
	glColor3ub(0, 0, 0);
	ojo(-1.7, 45);
	ojo(1.7, -45);

	glColor3ub(255, 10, 10);
	nariz();

	glColor3ub(235, 113, 29);
	point();
	point1();
	point2();
	point3();
	glColor3ub(255, 0, 0);
	corbata();
	corbata1();
	corbata2();
	puño2();
	puño();
	guantes();
	glColor3ub(105, 46, 46);
	brazo();
	glColor3ub(0, 0, 0);
	boca();

	glPopMatrix();
}

void sol() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[1]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 5, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void pared() {

	// Pared 1
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-50, 49, 0);
	glScaled(0.5, 12.5, 12.5);
	glutSolidCube(8);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[2]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-47.9, -1, -49.9);
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3d(0, 0, 100);
	glTexCoord2d(1, 1); glVertex3d(0, 100, 100);
	glTexCoord2d(0, 1); glVertex3d(0, 100, 0);
	glTexCoord2d(0, 0); glVertex3d(0, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Pared 2

	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0, 49, -52);
	glScaled(12.5, 12.5, 0.5);
	glutSolidCube(8);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[3]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(0.1, -1, -49.9);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3d(-50, 100, 0);
	glTexCoord2d(1, 1); glVertex3d(50, 100, 0);
	glTexCoord2d(1, 0); glVertex3d(50, 0, 0);
	glTexCoord2d(0, 0); glVertex3d(-50, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Pared 3
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(52, 49, 0);
	glScaled(0.5, 12.5, 12.5);
	glutSolidCube(8);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[4]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(49, -1, -49.5);
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3d(0, 0, 100);
	glTexCoord2d(1, 1); glVertex3d(0, 100, 100);
	glTexCoord2d(0, 1); glVertex3d(0, 100, 0);
	glTexCoord2d(0, 0); glVertex3d(0, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void navidad() {
	glPushMatrix();
	glutSolidCube(1);
	glColor3ub(115, 98, 84);
	glTranslated(3, 2.5, 0);
	glScaled(3, 0.8, 1);
	glutSolidCube(8);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[5]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(3.1, -1, 4.1);
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3d(-12.1, 7, 0);
	glTexCoord2d(1, 1); glVertex3d(12., 7, 0);
	glTexCoord2d(1, 0); glVertex3d(12., 0, 0);
	glTexCoord2d(0, 0); glVertex3d(-12.1, 0, 0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void tronco() {

	//Tronco 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(8, 13, -28);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 1, 2, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 2
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(28, 13, 0);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 1, 2, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 3
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(30, 13, -25);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 1, 3, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 4
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, -20);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 5
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, -10);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 6
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(10, 13, -15);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 7
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(25, 13, 36);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 2, 3, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Tronco 8
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 0);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, -40);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, -30);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Tronco 9
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 10);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Tronco 10
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 20);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 30);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 40);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(40, 13, 40);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(10, 13, 40);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(10, 13, 20);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[6]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(30, 13, 20);
	glRotated(90, 50, 0, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluCylinder(quad, 0.5, 1, 15, 50, 50);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}


void copas() {

	//Copa 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(8, 15, -28);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 5, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Copa 2
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(28, 15, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 5, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Copa 3
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(30, 15, -25);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 8, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Copa 4
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, -20);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Copa 5
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 10, -10);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Copa 6
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(10, 15, -15);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 2);
	gluSphere(quad, 5, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//Copa 7
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(25, 20, 36);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 8, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Copa 8
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 10, 0);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 10, -40);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 10, -30);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Copa 9
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 10);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	//Copa 10
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 20);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 30);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(-40, 13, 40);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(40, 13, 40);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(10, 13, 40);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);


	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(10, 13, 20);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);


	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturas[7]);
	glPushMatrix();
	glColor3ub(255, 255, 255);
	glTranslated(30, 13, 20);

	quad = gluNewQuadric();
	gluQuadricTexture(quad, 1);
	gluSphere(quad, 3, 50, 50);


	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void cuarto() {

	glPushMatrix();
	glTranslated(0, 5, 0);
	glColor3ub(135, 132, 26);
	glutSolidCube(10);
	glPopMatrix();
}

void tejado() {

	glPushMatrix();
	glTranslated(0, 10, -5);
	glRotated(180, 0, 1, 0);
	glBegin(GL_QUADS);
	glColor3ub(203, 113, 38);
	glVertex3d(-5, 0, 0);
	glVertex3d(0, 5, 0);
	glVertex3d(0, 5, -10);
	glVertex3d(-5, 0, -10);
	glEnd();
	glPopMatrix();
}

void tejado2() {

	glPushMatrix();
	glTranslated(-5, 15, -5);
	glRotated(180, 1, 1, 0);
	glBegin(GL_QUADS);
	glColor3ub(203, 113, 38);
	glVertex3d(-5, 0, 0);
	glVertex3d(0, 5, 0);
	glVertex3d(0, 5, -10);
	glVertex3d(-5, 0, -10);
	glEnd();
	glPopMatrix();
}

void triangulo(float posZ, float rot) {

	glPushMatrix();
	glTranslated(0, 10, posZ);
	glRotated(rot, 0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(-5, 0, 0);
	glVertex3d(5, 0, 0);
	glVertex3d(0, 5, 0);
	glEnd();
	glPopMatrix();

}

void barra(float posX, float posZ, float giro) {
	glPushMatrix();
	glColor3ub(130, 81, 64);
	glTranslated(posX, 12.2, posZ);
	glRotated(giro, 0, 0, 1);
	glScaled(8.5, 1, 1);
	glutSolidCube(1);
	glPopMatrix();

}

void barralados(float posX) {
	glPushMatrix();
	glColor3ub(130, 81, 64);
	glTranslated(posX, 9.9, 0);
	glRotated(45, 0, 0, 1);
	glScaled(1, 1, 10);
	glutSolidCube(1);
	glPopMatrix();

}

void bloquePiedra() {

	glPushMatrix();
	glColor3ub(184, 182, 177);
	glutSolidCube(1);
	glPopMatrix();

}

void bordeCasa() {

	glPushMatrix();
	glTranslated(0, 0.5, -0.21);
	glScaled(11, 1, 10.4);
	bloquePiedra();
	glPopMatrix();

}

void marcoPuerta(int rojo, int verde, int azul) {
	glPushMatrix();
	glColor3ub(rojo, verde, azul);
	glTranslated(0, 4, 4.51);
	glScaled(5, 8, 1);
	glutSolidCube(1);
	glPopMatrix();
}

void puerta() {
	glPushMatrix();
	glTranslated(1.5, 0, 0);
	marcoPuerta(175, 120, 90);
	glPushMatrix();
	glTranslated(0, 0.7, 0.01);
	glScaled(0.7, 0.8, 1);
	marcoPuerta(130, 81, 64);
	glPopMatrix();
	glPopMatrix();
}

void bloquePuerta() {
	glPushMatrix();
	glTranslated(1.5, 0.5, 6);
	glScaled(5, 1, 2);
	bloquePiedra();
	glPopMatrix();
}

void piedraEsquina() {

	glPushMatrix();
	glTranslated(-3.8, 5, 4.2);
	glScaled(2.5, 1, 2);
	bloquePiedra();
	glPopMatrix();

}

void ventanaGrande() {

	glColor3ub(175, 120, 90);
	glPushMatrix();
	glTranslated(-4, 8, 0);
	glutSolidCube(6);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7, 11, 0);
	glRotated(90, 0, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex3d(-3, 0, 0);
	glVertex3d(3, 0, 0);
	glVertex3d(0, 3, 0);
	glEnd();
	glPopMatrix();

}

void tejado3(float posZ) {

	glPushMatrix();
	glColor3ub(255, 178, 136);
	glTranslated(-4, 8, 0);
	glBegin(GL_QUADS);
	glVertex3d(-3, 3, posZ);
	glVertex3d(-3, 6, 0);
	glVertex3d(3, 6, 0);
	glVertex3d(3, 3, posZ);
	glEnd();
	glPopMatrix();

}

void bases() {

	//base del carro

	glPushMatrix();
	glTranslated(0, 5, 0);
	glColor3ub(255, 0, 0);
	glScaled(4, 1, 2);
	glutSolidCube(4);
	glPopMatrix();

	// carrosa
	glPushMatrix();
	glTranslated(0, 9, 0);
	glScaled(2, 1, 2);
	glutSolidCube(4);
	glPopMatrix();

	// puertas
	glPushMatrix();
	glTranslated(-2, 9, 0);
	glColor3ub(0, 0, 0);
	glScaled(0.7, 0.7, 2.01);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.85, 9, 0);
	glColor3ub(0, 0, 0);
	glScaled(0.6, 0.8, 1.80);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated( 2, 9, 0);
	glColor3ub(0, 0, 0);
	glScaled(0.7, 0.7, 2.01);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	glTranslated( 2.85, 9, 0);
	glColor3ub(0, 0, 0);
	glScaled(0.6, 0.8, 1.80);
	glutSolidCube(4);
	glPopMatrix();

	//luces

	glPushMatrix();
	glTranslated(0, 6, -2);
	glColor3ub(248, 185, 16);
	glScaled(16.01, 1, 1);
	glutSolidCube(1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 6, 2);
	glColor3ub(248, 185, 16);
	glScaled(16.01, 1, 1);
	glutSolidCube(1);
	glPopMatrix();


}

void ruedas() {

glPushMatrix();

	glColor3ub(0, 0, 0);
	glTranslated(-3.5, 3.5, 4);
	glutSolidTorus(0.7, 1.4 , 50, 50);

glPopMatrix();

glPushMatrix();

glColor3ub(0, 0, 0);
glTranslated(-3.5, 3.5, -4);
glutSolidTorus(0.7, 1.4, 50, 50);

glPopMatrix();

glPushMatrix();

glColor3ub(0, 0, 0);
glTranslated(4, 3.5, 4);
glutSolidTorus(0.7, 1.4, 50, 50);

glPopMatrix();

glPushMatrix();

glColor3ub(0, 0, 0);
glTranslated(4, 3.5, -4);
glutSolidTorus(0.7, 1.4, 50, 50);

glPopMatrix();


}

void relleno() {
	glPushMatrix();

	glColor3ub(186, 183, 176);
	glTranslated(-3.5, 3.5, 4);
	glutSolidTorus(0.3, 0.6, 50, 50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(-3.5, 3.5, -4);
	glutSolidTorus(0.3, 0.6, 50, 50);

	glPopMatrix();

	glPushMatrix();

	glTranslated(4, 3.5, 4);
	glutSolidTorus(0.3, 0.6, 50, 50);

	glPopMatrix();

	glPushMatrix();
	glTranslated(4, 3.5, -4);
	glutSolidTorus(0.3, 0.6, 50, 50);

	glPopMatrix();
}

void carro() {
	glPushMatrix();
	glTranslated(0, 0, 0);
		bases();
		ruedas();
		relleno();
	glPopMatrix();
}



void casa() {

	glPushMatrix();

	glTranslated(-12, 00, -30);
	cuarto();
	triangulo(5, 180);
	triangulo(-5, 0);
	tejado();
	tejado2();
	barra(-2.7, 5, 45);
	barra(2.7, 5, -45);
	barra(-2.7, -5, 45);
	barra(2.7, -5, -45);
	barralados(5);
	barralados(-5);
	bordeCasa();
	puerta();
	bloquePuerta();
	piedraEsquina();
	//ventanaGrande();
	//tejado3(3);
	//tejado3(-3);


	glPopMatrix();

}


void dibujar() {
	inicializarLuces();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(radio * cos(angulo), camaraY, radio * sin(angulo), centroX, centroY, centroZ, 0, 1, 0);
	//gluLookAt(camaraX, camaraY, camaraZ, centroX, 0, centroZ, 0, 1, 0);
	glClearColor(31 / (float)255, 205 / (float)255, 211 / (float)255, 1);

	piso();
	dibujarEjes();

	giroPersonaje += -1;
	glPushMatrix();
		glTranslated(3, 7, 0);
		glRotated(giroSol, 0, 1, 0);
	personaje();
	glPopMatrix();

	casa();

	giroSol += 1;
	glPushMatrix();
	glTranslated(23, 45, -15);
	glRotated(giroSol, 0, 1, 0);
	sol();
	glPopMatrix();

	pared();
	navidad();
	tronco();
	copas();

	glPushMatrix();
		glTranslated(3, 10, 0);
		soporte();
	glPopMatrix();

	glPushMatrix();

	carroPosZ += 0.4 * carroLadoZ;
	if (carroPosZ > 47) {
		carroLadoZ = -1;
	}
	if (carroPosZ < -47) {
		carroLadoZ = 1;
	}
	
	glTranslated(-25, -3, carroPosZ);
	glRotated(90, 0, 360, 0);
	carro();

	glPopMatrix();

	glutSwapBuffers();

}

void teclado_especial(int tecla, int x, int y) {
	cout << "Angulo: " << angulo << "Camara Y: " << camaraY << "Radio: " << radio << "Centro Y: " << centroY << "\n";
	switch (tecla)
	{
	case 100:
		angulo += 0.01;
		break;

	case 102:
		angulo -= 0.01;
		break;

	case 101:
		camaraY += 1;
		break;

	case 103:
		camaraY -= 1;
		break;

	case 104:
		radio -= 2;
		break;

	case 105:
		radio += 2;
		break;

	case 106:
		centroY += 2;
		break;

	case 107:
		centroY -= 2;
		break;
	}

}

/*void teclado_especial1(int tecla, int x, int y) {

	//cout << tecla;

	switch (tecla)

	{

		//Para animar camara

	case 100:

		camaraX -= movimientoCamara;

		centroX -= movimientoCamara;

		break;

	case 102:

		camaraX += movimientoCamara;

		centroX += movimientoCamara;

		break;



	case 101:

		camaraZ -= movimientoCamara;

		centroZ -= movimientoCamara;

		break;



	case 103:

		camaraZ += movimientoCamara;

		centroZ += movimientoCamara;

		break;

	}

}

//void teclado(unsigned char key, int x, int y) {

	switch (key)

	{

	case 'a':

		camaraX -= movimientoCamara;

		break;

	case 'z':

		camaraX += movimientoCamara;

		break;

	case 's':

		camaraY += movimientoCamara;

		break;

	case 'x':

		camaraY -= movimientoCamara;

		break;

	case 'd':

		camaraZ -= movimientoCamara;

		break;

	case 'c':

		camaraZ += movimientoCamara;

		break;

	}
	
}*/

void timer(int t) {

	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);

}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(1540, 990);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Ventana");
	cargarImagenes();
	glutReshapeFunc(iniciarVentana);
	glutDisplayFunc(dibujar);
	glutSpecialFunc(teclado_especial);
	//glutKeyboardFunc(teclado);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	return 0;
}
