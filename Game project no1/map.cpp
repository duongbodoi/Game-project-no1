#include"map.h"
map::map() {
	int x = 0, y = 0;
	int x_pos = 15;
	int y_pos = 508 - 90;
	int vel_x=0, vel_y=0;

}
map::~map() {

}
void map::Handle_event(SDL_Event e, SDL_Renderer* renderer) {
	if (e.type == SDL_KEYDOWN and e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			vel_x += v;
			
			break;
		}
		case SDLK_LEFT:
		{
			vel_x -= v;
			
			break;
		}
		
		default:
			break;
		}
	}
	else if (e.type = SDL_KEYUP and e.key.repeat == 0) {
		switch (e.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			
			vel_x -= v;
			

			break;
		}
		case SDLK_LEFT:
		{
			vel_x += v;
			break;

		}
		default:
			break;
		}
	}
}
void map::move() {
	x_pos += vel_x;
	if (x_pos % SCREEN_WIDTH == 0 ) x = x_pos;

	
}
void map::show(SDL_Renderer* des) {
	SDL_Rect inset = { x,y,SCREEN_WIDTH,SCREEN_HEIGHT };
	SDL_RenderCopy(des, mTexture, &inset, NULL);
}

