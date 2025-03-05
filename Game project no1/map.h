#pragma once
#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
class map :public Ltexture {
public:
	map();
	~map();
	void show(SDL_Renderer* des);
	void Handle_event(SDL_Event e, SDL_Renderer* renderer);
	void move();
	int v = 2;
private:
	int x_pos, y_pos;
	int vel_x, vel_y;
	int x, y;
};
