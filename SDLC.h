#pragma once
#ifndef _SDLC_H_
#define _SDLC_H_
//basic render
#define START_ON 0
#define START_OFF 1
#define BACK_ON 2
#define BACK_OFF 3
#define PASS_ON 4
#define PASS_OFF 5
#define LOSE_ON 6
#define LOSE_OFF 7
#define TITLE_REVERSI 8
#define TITLE_THINK 9
#define TITLE_PASS 10

class SDLC {
public:
	SDLC();	
	~SDLC();
	void render(int,int,int,int, int,int(*)[8]);
private:
	void logSDLError(std::ostream&, const std::string&);
	SDL_Texture* loadTexture(const std::string&, SDL_Renderer*);
	SDL_Texture* renderText(const std::string&, const std::string&, SDL_Color, int, SDL_Renderer*);
	void renderTexture(SDL_Texture*, SDL_Renderer*, SDL_Rect, SDL_Rect*);
	void renderTexture(SDL_Texture*, SDL_Renderer*, int, int, SDL_Rect*);
	void renderchess(int (*)[8]);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* background;
	SDL_Texture* qipan;
	SDL_Texture* scoreboard ;
	SDL_Texture* start_0;
	SDL_Texture* back_0;
	SDL_Texture* pass_0;
	SDL_Texture* lose_0;
	SDL_Texture* start_1;
	SDL_Texture* back_1;
	SDL_Texture* pass_1;
	SDL_Texture* lose_1 ;
	SDL_Texture* blank;
	SDL_Texture* white;
	SDL_Texture* title_reversi;
	SDL_Texture* title_think;
	SDL_Texture* title_pass;
};
#endif
