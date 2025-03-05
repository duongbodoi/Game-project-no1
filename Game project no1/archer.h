#pragma once
#include"Basetexture.h"
#include"Mainfunc.h"
class archer :public Ltexture {
public:
	archer();
	~archer();
	enum animate {
		walk_r = 0,
		walk_l = 1,
		reload_ = 2,
		shot_=3,
	};
	virtual bool load_img(std::string file, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void Handle_event(SDL_Event e, SDL_Renderer* renderer);
	void set_clip();
	void move();
	
	const int v = 2;
	
private:
	double vel_x, vel_y;
	double x_pos, y_pos;
	int width_frame;
	int heightframe;
	SDL_Rect frame_clip[4];
	Input input_type;
	int frame;
	int status;
};
class arrow :public Ltexture {
public:
	enum shotarrow {
		reload_ = 0,
		shot_ = 1,
	};
	arrow();
	~arrow();
	void Handle_event(SDL_Event e, SDL_Renderer* renderer);
	void arrow_shot(SDL_Rect archer_rect);
	void show(SDL_Renderer* des);
	int v0 = 100;
	int phi = 5;
	double time = 0;
	double x0, y0;
private:
	double vel_x, vel_y;
	double x_pos, y_pos;
	Input input_type;
};