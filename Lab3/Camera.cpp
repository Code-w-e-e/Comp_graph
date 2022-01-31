#include "Camera.h"

const int K = 70; 
Camera::Camera() {
	radius = sqrt(625);
}
Camera::~Camera() {
}
void Camera::simulate(float sec) {
	time = sec;
}

void Camera::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward) {
	Camera::left = left;
	Camera::right = right;
	Camera::up = up;
	Camera::down = down;
	Camera::forward = forward;
	Camera::backward = backward;

	if (left) { //если левая стрелка, то
		Ox += K * time; //смещаем камеру по гориз со скоростью изменения времени*K
	}
	if (right) {
		Ox += -K * time;
	}
	if (up) {

		if (Oz < K) {
			Oz += K * time;
		}

	}
	if (down) {
		if (Oz > -K) {
			Oz += -K * time;
		}

	}
	if (forward) {
		if (radius > 10) {
			radius += -20 * time;
		}
	}
	if (backward) {
		if (radius < 50) {
			radius += 50 * time;
		}
	}
}


void Camera::apply() {
	x = radius * cos(Ox * 0.0175) * cos(Oz * 0.0175);//перевели в радианы и находим сферические координаты
	z = radius * sin(Ox * 0.0175) * cos(Oz * 0.0175);
	y = radius * sin(Oz * 0.0175);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}