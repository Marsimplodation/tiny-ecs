#include <cstdio>
#define ECS_IMPLEMENTATION
#include "tiny_ecs.h"


const float gravity = 9.81f;
const float timeStep = 0.016f;
struct Position{float x, y, z;};
struct Velocity{float dx, dy, dz;};
struct Acceleration{float ddx, ddy, ddz;};

int main (int argc, char *argv[]) {
	ECS::registerType<Position>();
	ECS::registerType<Velocity>();
	ECS::registerType<Acceleration>();
	auto ball = ECS::newEntity();

	ECS::addComponent(ball, Position{0,500,0});
	ECS::addComponent(ball, Velocity{0,30,0});
	ECS::addComponent(ball, Acceleration{0,0,0});
	//gravity system with euler solver
	for(int i = 0; i < 100; ++i) {
		auto pPtr = ECS::getComponent<Position>(ball); 
		auto vPtr = ECS::getComponent<Velocity>(ball); 
		auto aPtr = ECS::getComponent<Acceleration>(ball); 
		if(!pPtr || !vPtr || !aPtr) continue;
		pPtr->x += vPtr->dx * timeStep;
		pPtr->y += vPtr->dy * timeStep;
		pPtr->z += vPtr->dz * timeStep;
		
		vPtr->dx += aPtr->ddx * timeStep;
		vPtr->dy += aPtr->ddy * timeStep;
		vPtr->dz += aPtr->ddz * timeStep;

		aPtr->ddy += -gravity;

		printf("%f %f %f\n", pPtr->x, pPtr->y, pPtr->z);
	}
	
	return 0;
}
