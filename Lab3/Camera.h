#pragma once
#include <windows.h>
#include "GL/freeglut.h"
#include "math.h"


class Camera
{
private:
	// необходимые свойства
	float radius;
	bool left, right, up, down, forward, backward;
	float time, x, y, z, Ox = 0, Oz = 0; //Ox(по горизонту), Oz(по вертикали) - положение камеры в начале 
public:
	// конструктор по умолчанию
	Camera();
	// деструктор ‐ сохранение новых параметров камеры
	~Camera();
	// установка признаков нажатых клавиш
	void setKey(bool left, bool right, bool up, bool down, bool forward, bool backward);
	// движение камеры в ранее выбранном направлении
	// параметр ‐ количество секунд прошедших с момента последнего вызова
	void simulate(float sec);
	// функция для установки матрицы камеры
	void apply();
};
