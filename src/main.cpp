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
	ECS::registerMultipleTypes<Velocity, Acceleration>();
	auto ball = ECS::newEntity();

	ECS::addMultipleComponents(ball, Position{0, 500, 0}, Acceleration{0,30,0});
	ECS::addComponent(ball, Velocity{0,30,0});
	//gravity system with euler solver
	for(int i = 0; i < 100; ++i) {
		//multiple components
		auto refs = ECS::getMultipleComponents<Position, Velocity>(ball);
		if(!refs.isValid()) continue;
		auto [position, velocity] = refs.unwrap();

		//single components
		auto accRef = ECS::getComponent<Acceleration>(ball);
		if(!accRef.isValid()) continue;
		auto & acc = *accRef;

		position.x += velocity.dx * timeStep;
		position.y += velocity.dy * timeStep;
		position.z += velocity.dz * timeStep;
		velocity.dy -= gravity * timeStep;
		printf("%f %f %f\n", position.x, position.y, position.z);
		printf("%f\n", acc.ddy); 
	}
	
	return 0;
}
