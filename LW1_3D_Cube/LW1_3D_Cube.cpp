// GSP_LW1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma comment (lib, "OpenGL/glut32.lib")
#include "OpenGL/glut.h"
#include <iostream>
#include <windows.h>




double rho = 5.0;
double theta = 45.0;
double phi = 45.0;
double screen_dist = 2.5;
double h = 1.0;


double v11, v12, v13;
double v21, v22, v23;
double v32, v33;
double v43;
// Функция обределения экранных координат пространственной точки
void perspective(double x, double y, double z, double* pX, double* pY) {
	double xe, ye, ze;
	// Координаты глаза
	xe = v11 * x + v21 * y;
	ye = v12 * x + v22 * y + v32 * z;
	ze = v13 * x + v23 * y + v33 * z + v43;

	// Экранные координаты
	*pX = screen_dist * xe / ze;
	*pY = screen_dist * ye / ze;
}
void dw(double x1, double y1, double z1, double x2, double y2, double z2)
{
	double X1, Y1, X2, Y2;
	perspective(x1, y1, z1, &X1, &Y1);
	perspective(x2, y2, z2, &X2, &Y2);
	glBegin(GL_LINES);
	glVertex2d(X1, Y1);
	glVertex2d(X2, Y2);
	glEnd();
}



void coeff(double rho, double theta, double phi)
{
	double th, ph, costh, sinth, cosph, sinph, factor;
	factor = atan(1.0) / 45.0; // коэфф. для пересчёта в радианы
	th = theta * factor; ph = phi * factor;

	costh = cos(th); sinth = sin(th);
	cosph = cos(ph); sinph = sin(ph);

	// элементы матрицы видового преобразования V 
	v11 = -sinth;     v12 = -cosph * costh;     v13 = -sinph * costh;
	v21 = costh;     v22 = -cosph * sinth;      v23 = -sinph * sinth;
	v32 = sinph;                 v33 = -cosph;
	v43 = rho;
}


void Display(void) {
	coeff(rho, theta, phi);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(255, 0, 0);
	dw(h, -h, -h, h, h, -h); // рисование ребра
	dw(h, h, -h, -h, h, -h);
	dw(-h, h, -h, -h, -h, -h);
	dw(-h, -h, -h, h, -h, -h);
	dw(h, -h, h, h, h, h);
	dw(h, h, h, -h, h, h);
	dw(-h, h, h, -h, -h, h);
	dw(-h, -h, h, h, -h, h);
	dw(h, -h, -h, h, -h, h);
	dw(h, h, -h, h, h, h);
	dw(-h, h, -h, -h, h, h);
	dw(-h, -h, -h, -h, -h, h);
	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();
}

void Reshape(GLint w, GLint h)
{
	/* Устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);
}

void main(int argc, char* argv[]) {
	coeff(rho, theta, phi);
	glutInit(&argc, argv); // инициализация GLUT
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowPosition(50, 10);
	glutInitWindowSize(640, 480); // создаем окно
	glutCreateWindow("Красный кубик, задание 2");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}




