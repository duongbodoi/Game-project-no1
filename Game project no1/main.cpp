#include"Mainfunc.h"
#include"Basetexture.h"
#include"archer.h"
#include"map.h"

map backgr;

bool Init() {
	bool check = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		check = false;
		cout << "error init";
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow("duongbodoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		check = false;
		cout << "error window";
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			cout << "error renderer";
			check = false;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			int imgflag = IMG_INIT_PNG;
			if (!(IMG_Init(imgflag) && imgflag)) {
				check = false;
				cout<< "error IMG";
			}
		}
	}
	return check;
}
bool loadmedia() {
	bool check = true;
	if (!backgr.loadfromfile("mapbgr.png",renderer)) {
		cout << "error loadmedia";
		check = false;
	}
	return check;
}
void close() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_QUIT;
}
int main(int argv, char* argc[]) {
	if (!Init()) return -1;
	if (!loadmedia()) return -1;
	//
	archer hero;
	hero.load_img("archer.png", renderer);
	hero.set_clip();
	//
	arrow shot_arrow_;
	shot_arrow_.loadfromfile("arrow.png", renderer);
	bool runing = true;
	while (runing) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				runing = false;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				printf("Mouse Clicked at: (%d, %d)\n", x, y);
			}
			hero.Handle_event(e,renderer);
			shot_arrow_.Handle_event(e, renderer);
			backgr.Handle_event(e, renderer);
		}
		backgr.move();
		hero.move();
		shot_arrow_.arrow_shot(hero.get_rect());
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		//sheet.render(renderer,NULL);
		backgr.show(renderer);
		hero.show(renderer);
		shot_arrow_.show(renderer);
		SDL_RenderPresent(renderer);
	}
	close();
	return 0;
}
//PULL firt 1
// PULL 2
//pulll 3;