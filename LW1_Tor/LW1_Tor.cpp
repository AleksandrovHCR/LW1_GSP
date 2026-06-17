// LW1_Tor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 
#pragma comment (lib, "OpenGL/glut32.lib")
#include "OpenGL/glut.h"
#include <iostream>
#include "stdio.h"
#include "math.h"




float theta = 10;
float phi = 11;

double screen_dist = 2.5;
double h = 1.0;


double v11, v12, v13;
double v21, v22, v23;
double v32, v33;
double v43;


float k;

int l1;
int l2;
int l3;
int l4;

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
	FILE* fp;
	fp = fopen("torus.dat", "r");
	glClearColor(255, 255, 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	int n;
	float* X, * Y, * Z;
	fscanf(fp, "%d", &n);

	X = new float[n * n];
	Y = new float[n * n];
	Z = new float[n * n];

	for (int i = 0; i < n * n; i++) {
		fscanf(fp, "%d %f %f %f", &k, &X[i], &Y[i], &Z[i]);
	}
	for (int j = 0; j < n * n; j++) {
		fscanf(fp, "%d %d %d %d", &l1, &l2, &l3, &l4);
		dw(X[l1], Y[l1], Z[l1], X[l2], Y[l2], Z[l2]);
		dw(X[l2], Y[l2], Z[l2], X[l3], Y[l3], Z[l3]);
		dw(X[l3], Y[l3], Z[l3], X[l4], Y[l4], Z[l4]);
		dw(X[l4], Y[l4], Z[l4], X[l1], Y[l1], Z[l1]);
	}
	fclose(fp);
	delete[] X;
	delete[] Y;
	delete[] Z;
	glFinish();
}

/* Функция вызывается при изменении размеров окна */
void Reshape(GLint w, GLint h)
{
	/* Устанавливаем размеры области отображения */
	glViewport(0, 0, w, h);
}

void ftimer(int value) {
	theta += 10;
	phi += 10;
	coeff(-45, theta, phi);
	glutPostRedisplay();
	glutTimerFunc(100, ftimer, 1);
}


void Calculate_File() {
	FILE* fp;
	int i, j, n;
	float r, R;
	double pi, alpha, beta, cosa, sina, x, x1, y1, z1, delta;
	printf("Input n:");
	scanf("%d", &n);
	printf("Input (R):");
	scanf("%f", &R);
	printf("Input (r):");
	scanf("%f", &r);
	fp = fopen("torus.dat", "w");
	pi = 4.0 * atan(1.0); delta = 2.0 * pi / n;
	fprintf(fp, "%d\n", n); // количество точек объекта
	//  продолжение 
	for (i = 0; i < n; i++) {
		alpha = i * delta; cosa = cos(alpha); sina = sin(alpha);
		for (j = 0; j < n; j++) {
			beta = j * delta; x = R + r * cos(beta);
			x1 = cosa * x; y1 = sina * x; z1 = r * sin(beta);
			fprintf(fp, "%d %f %f %f \n", i * n + j, x1, y1, z1);
		}
	}

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			fprintf(fp, "%d %d %d %d\n", i * n + j, (i + 1) % n * n + j, (i + 1) % n * n + (j + 1) % n, i * n + (j + 1) % n);
		}

	fclose(fp);
}


void main(int argc, char* argv[]) {
	Calculate_File();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Тор. Задание 3");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	glutTimerFunc(1000, ftimer, 1);

	/* Главный цикл приложения */
	glutMainLoop();
}
