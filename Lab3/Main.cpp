#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "GL/freeglut.h"
#include <cmath>
#include <algorithm>
#include "GraphicObject.h"
#include "Camera.h"


using namespace std;
LARGE_INTEGER Old_Value, New_Value, frequency, n_v, o_v;
float count_fps = 0.0;


int matrix1[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 3,0,0,1 };
int matrix2[16] = { 1,0,0,0, 0,1,0,0, 0,0, 1,0, -3,0,0,1 };
int matrix3[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,-3,1 };
int matrix4[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,3,1 };





float SimulationTime() {
	Old_Value = New_Value;
	QueryPerformanceCounter(&New_Value);
	return (float(New_Value.QuadPart - Old_Value.QuadPart)) / frequency.QuadPart;//по формуле из лб
}





const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
Camera camera;

// функция вызывается каждые 20 мс
void Simulation()
{
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float Simulation_Time_Passed = SimulationTime();
	// ПЕРЕМЕЩЕНИЕ КАМЕРЫ
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP);
	bool CameraDown = GetAsyncKeyState(VK_DOWN);
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);
	camera.simulate(Simulation_Time_Passed);
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	//count_fps++;
	// эта же функция будет вызвана еще раз через 20 мс
};

void FPS() {
	QueryPerformanceCounter(&n_v);

	float delta = float(n_v.QuadPart - o_v.QuadPart) / frequency.QuadPart;
	string msg;

	if (delta >= 1.0) {
		msg += "FPS = ";
		msg += to_string((float)count_fps);
		char buf[255];
		strcpy(buf, msg.c_str());
		glutSetWindowTitle(buf);
		count_fps = 0;
		o_v = n_v;
	}

}


// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	camera.apply();
	// выводим объекты
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects[i].draw();
	};
	count_fps++;
	// смена переднего и заднего буферов
	glutSwapBuffers();
	FPS();
	count_fps++;
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	//printf("Key code is %i\n", (unsigned int)key);
};


int main(int argc, char* argv[]) {

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// создание окна:
// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	
	glutCreateWindow("Lab 3 ");
	
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	
	graphicObjects[0].setColor(1.0, 1.0, 0.0);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[0].modelMatrix[i] = matrix1[i];
	}

	graphicObjects[1].setColor(1.0, 0.0, 1.0);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[1].modelMatrix[i] = matrix2[i];
	}

	graphicObjects[2].setColor(1.0, 1.0, 1.0);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[2].modelMatrix[i] = matrix3[i];
	}

	graphicObjects[3].setColor(0.0, 1.0, 1.0);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[3].modelMatrix[i] = matrix4[i];
	}

	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutIdleFunc(Simulation);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	QueryPerformanceCounter(&n_v);
	QueryPerformanceFrequency(&frequency);
	
	glutMainLoop();
}
