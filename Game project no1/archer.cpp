#include"archer.h"
archer::archer() {
	vel_x = 0;
	vel_y = 0;
	x_pos = 15;
	y_pos = 508-90;
	frame = 0;
	width_frame = 0;
	heightframe = 0;
	status = -1;
}
archer::~archer(){

}
bool archer::load_img(std::string file, SDL_Renderer* renderer) {
	bool ret = Ltexture::loadfromfile(file, renderer);
	if (ret == true) {
		width_frame = 90;
		heightframe = 90 ;
	}
	return ret;
}
void archer::set_clip() {
	if (width_frame > 0 and heightframe > 0) {
		frame_clip[0].x = 0;
		frame_clip[0].y = 0;
		frame_clip[0].w = width_frame;
		frame_clip[0].h = heightframe;

		frame_clip[1].x = width_frame;
		frame_clip[1].y = 0;
		frame_clip[1].w = width_frame;
		frame_clip[1].h = heightframe;

		frame_clip[2].x = width_frame*2;
		frame_clip[2].y = 0;
		frame_clip[2].w = width_frame;
		frame_clip[2].h = heightframe;

		frame_clip[3].x = width_frame*3;
		frame_clip[3].y = 0;
		frame_clip[3].w = width_frame;
		frame_clip[3].h = heightframe;


	}
}
void archer::show(SDL_Renderer* des) {
	if (status == walk_l) {
		load_img("archer_left.png", des);
	}
	else if (status == reload_ or status==shot_) {
		load_img("reload.png", des);

	}
	else if (status == walk_r) {
		load_img("archer.png", des);
	}
	
	if (input_type.left == 1 or input_type.right == 1  ) {
		frame++;
		if (frame / 16 >= 2) {
			frame = 0;
		}
	}
	else if (input_type.reload == 1) {
		frame++;
		if (frame / 16 >= 3) {
			frame = 32;
		}
	}
	else if (input_type.shot == 1) {
		frame++;
		if (frame / 16 >= 4) {
			input_type.shot = 0;
		}
	}
	else {
		frame = 15;
	}
	
	mrect.x = x_pos;
	mrect.y = y_pos;
	SDL_Rect* current_clip = &frame_clip[frame/16];
	SDL_Rect offset = { mrect.x,mrect.y,width_frame,heightframe };
	SDL_RenderCopy(des, mTexture, current_clip,& offset);
}
void archer::Handle_event(SDL_Event e, SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN and e.key.repeat==0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			vel_x += v;
			status = walk_r;
			input_type.right = 1;
			break;
		}
		case SDLK_LEFT:
		{
			vel_x -= v;
			status = walk_l;
			input_type.left = 1;
			break;
		}
		case SDLK_UP:
		{
			status = reload_;
			input_type.reload = 1;
			break;
		}
		default:
			break;
		}
	}
	else if (e.type = SDL_KEYUP and e.key.repeat==0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status = -1;
			vel_x -= v;
			input_type.right = 0;
			input_type.shot = 0;

			break;
		}
		case SDLK_LEFT:
		{
			status = -2;
			vel_x += v;
			input_type.shot = 0;
			input_type.left = 0;
			break;

		}
		case SDLK_UP:
		{
			
			status = shot_;
			input_type.reload = 0;
			input_type.shot = 1;
			break;

		}
		default:
			break;
		}
	}
}
void archer::move() {
	x_pos += vel_x;
	if (x_pos >= SCREEN_WIDTH) x_pos = 0;
	//if (x_pos <= 0) x_pos -= vel_x;
}

// arrow
arrow::arrow() {
	vel_x = 0;
	vel_y = 0;
	x_pos = 0;
	y_pos = 300;
}
arrow::~arrow() {

}
void arrow::Handle_event(SDL_Event e, SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN ) {
		if (e.key.repeat == 0 and e.key.keysym.sym == SDLK_UP) v0 = 100;
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
		{
			input_type.reload = 1;
			input_type.shot = 0;
			break;
		}
		default:
			break;
		}
	}
	else if (e.type = SDL_KEYUP and e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{
		
		case SDLK_UP:
		{
			input_type.reload = 0;
			input_type.shot = 1;
			break;

		}
		default:
			break;
		}
	}
}
void arrow::arrow_shot(SDL_Rect archer_rect) {
	x0 = archer_rect.x+20;
	y0 = archer_rect.y+25;
	double radian = phi * PI / 180;
	if (input_type.reload == 1) {
		v0 += 1;
		if (v0 >= 300) v0 = 300;
		time = 0;
		x_pos =x0 ;
		y_pos =y0 ;
		vel_x = v0 * cos(radian);
		vel_y = v0 * sin(radian);
		
	}
	if (input_type.shot == 1) {
		time += 0.1;
		vel_x = v0 * cos(radian) * time;
		vel_y = v0 * sin(radian) - 9.8 * time;
		x_pos = x0 + v0 * cos(radian) * time;;
		y_pos = y0 - (v0 * sin(radian) * time - 0.5 * 9.8 * time * time);
		
	}
}
void arrow::show(SDL_Renderer* des) {
	if (input_type.shot == 1) {
		mrect.x = x_pos;
		mrect.y = y_pos;
		SDL_RenderCopy(des, mTexture, NULL, &mrect);
	}

}