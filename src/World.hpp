#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Paddle.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Table.hpp"
#include "Ball.hpp"
#include <iostream>
#include <list>
#include <vector>


class World {
public:
	Shape* list[4];
	World();
	~World();
	void draw_world(); // draw all objects in the world
	void reset();
};

#endif
