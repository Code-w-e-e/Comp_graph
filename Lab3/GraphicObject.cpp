#include "GraphicObject.h"
// Конструктор
GraphicObject::GraphicObject(void)
{
}
// задать позицию объекта
void GraphicObject::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}
// задать угол поворота в градусах относительно оси OY
void GraphicObject::setAngle(float a)
{
	angle = a;
}
// Задать цвет модели
void GraphicObject::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
// вывести объект
void GraphicObject::draw(void)
{
	glPushMatrix();//сохранение матрицы в стеке
	//glTranslatef(position[0], position[1], position[2]);//умножение матрицы модели, на текущую матрицу наблюдения; f - float, d - double
	//glRotatef(angle, 0.0, 1.0, 0.0); //вращение относительно Oy
	//умножение матрицы модели, на текущую матрицу наблюдения;
	glMultMatrixf(modelMatrix);
	glColor3f(color[0], color[1], color[2]);//установка цвета
	glutWireTeapot(1.0);//вывод на экран 
	glPopMatrix();//Восстановление ранее сохраненной в стеке матрицы наблюдения модели

}