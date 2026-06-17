// GSP_LW1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#pragma comment (lib, "OpenGL/glut32.lib")
#include "OpenGL/glut.h"
#include <iostream>
#include <windows.h>






void Display(void) {
	int n = 8;
	double alpha = 3.1415 / n, x1 = -0.5, y1 = -0.5, x2 = -0.5,
		y2 = 0.5, x3 = 0.5, y3 = 0.5, x4 = 0.5, y4 = -0.5;
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);


	for (int i = 0; i <= n; i++) {
		glColor3ub(255. / n * i, 0, 0);
		glBegin(GL_QUADS);
		glVertex2f((x1 * cos(alpha * i) - y1 * sin(alpha * i)) + (float)i / (float)n,
			x1 * sin(alpha * i) + y1 * cos(alpha * i));
		glVertex2f((x2 * cos(alpha * i) - y2 * sin(alpha * i)) + (float)i / (float)n,
			x2 * sin(alpha * i) + y2 * cos(alpha * i));
		glVertex2f((x3 * cos(alpha * i) - y3 * sin(alpha * i)) + (float)i / (float)n,
			x3 * sin(alpha * i) + y3 * cos(alpha * i));
		glVertex2f((x4 * cos(alpha * i) - y4 * sin(alpha * i)) + (float)i / (float)n,
			x4 * sin(alpha * i) + y4 * cos(alpha * i));
		glEnd();
	}
	glFinish();
}

void Reshape(GLint w, GLint h) {

	/* Устанавливаем размеры области отображения */

	glViewport(0, 0, w, h);
}





int main(int argc, char* argv[])
{
	//  std::cout << "Hello World!\n";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Красный квадрат. Задание 1");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	/*Главный цикл приложения */
	glutMainLoop();

}


