/**
 * File: World.hpp
 */

#include "World.hpp"

World::World() {
	list[0] = new Paddle();
	list[1] = new Paddle();
	list[2] = new Ball();
	list[3] = new Table();

	//Mesh* mymesh = new Mesh();
	//mymesh->readMesh("FILE.3VN"); FOR IF WE GET TO 3VN FILES
	//list[1] = mymesh;
}

World::~World(){
	delete list[0];
	delete list[1];
	delete list[2];
	delete list[3];
}

void World::draw_world() {

	list[0]->draw();
	list[1]->draw();
	list[2]->draw();
	list[3]->draw();
	

}

void World::reset(){
    list[0]->reset();
    list[1]->reset();
    list[2]->reset();
    list[3]->reset();
}

