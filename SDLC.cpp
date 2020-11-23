#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include "SDLC.h"
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
constexpr auto SCREEN_WIDTH = 480;
constexpr auto SCREEN_HEIGHT = 680;
constexpr auto fontsize = 40;
SDL_Color color = { 0,0,0,255 };
//general coordinate
const int coordinate[14][2] = {
	0, 0,     //background; 0
	15,150,   //qipan ;     1
	115,15,   //scoreboard; 2
	10,615,   //start;      3
	130,615,  //back;       4
	250,615,  //pass;       5
	370,615,  //lose;       6
	135,30,   //blank;      7
	190,30,  //blank_score; 8
	240,30,   //white ;     9
	300,30,  //white_score; 10
	180,70, //title_reversi 11
	170,70, //title_think...12
	210,70  //title_pass    13
};
SDLC::SDLC(){
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			logSDLError(std::cout, "SDL_Init");
			exit(1);
		}
		if (TTF_Init() != 0) {
			logSDLError(std::cout, "TTF_Init");
			SDL_Quit();
			exit(1);
		}
		std::cout << "GUI Initializing..." <<std::endl;
		window = SDL_CreateWindow("Reversi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			logSDLError(std::cout, "Createwindow");
			SDL_Quit();
			exit(1);
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer == NULL) {
			logSDLError(std::cout, "CreateRenderer");
			SDL_Quit();
			exit(1);
		}
		background = loadTexture("./pictures/background.png", renderer);
		qipan = loadTexture("./pictures/qipan.png", renderer);
		scoreboard = loadTexture("./pictures/scoreboard.png", renderer);
		start_0 = loadTexture("./pictures/start.png", renderer);
		back_0 = loadTexture("./pictures/back.png", renderer);
		back_1 = loadTexture("./pictures/back1.png", renderer);
		pass_0 = loadTexture("./pictures/pass.png", renderer);
		lose_0 = loadTexture("./pictures/lose.png", renderer);
		start_1 = loadTexture("./pictures/start1.png", renderer);
		pass_1 = loadTexture("./pictures/pass1.png", renderer);
		lose_1 = loadTexture("./pictures/lose1.png", renderer);
		blank = loadTexture("./pictures/blank.png", renderer);
		white = loadTexture("./pictures/white.png", renderer);
		title_reversi = renderText("Reversi", "font.ttf", color, fontsize, renderer);
		title_think = renderText("Think...", "font.ttf", color, fontsize, renderer);
		title_pass = renderText("Pass", "font.ttf", color, fontsize, renderer);
		if (background == NULL || qipan == NULL || scoreboard == NULL ||start_0 == NULL || back_0 == NULL || pass_0 == NULL || lose_0 == NULL ||
			start_1 == NULL || back_1 == NULL || pass_1 == NULL || lose_1 == NULL ||blank == NULL || white == NULL ||title_reversi == NULL || title_think == NULL || title_pass == NULL) {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}		
		std::cout<<"Intialize succeed!"<<std::endl;
	}
SDLC::~SDLC() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(background);
	IMG_Quit();
	SDL_Quit();
}
void SDLC::logSDLError(std::ostream& os, const std::string& msg) {
		os << msg << "error: " << SDL_GetError() << std::endl;
}
SDL_Texture* SDLC::loadTexture(const std::string& file, SDL_Renderer* ren) {
	SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == NULL) {
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}
SDL_Texture* SDLC::renderText(const std::string& message, const std::string& fontfile, SDL_Color color, int fontsize, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont(fontfile.c_str(), fontsize);
	if (font == NULL) {
		logSDLError(std::cout, "TTF_OpenFont");
		return NULL;
	}
	SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
	if (surf == NULL) {
		TTF_CloseFont(font);
		logSDLError(std::cout, "TTF_RenderText");
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL) {
		logSDLError(std::cout, "CreateTexture");
	}
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}
void SDLC::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, SDL_Rect* clip = NULL) {
	SDL_RenderCopy(ren, tex, clip, &dst);
}
void SDLC::renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = NULL) {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != NULL) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	renderTexture(tex, ren, dst, clip);
}



void SDLC::render(int s_start,int s_back,int s_pass,int s_lose,int s_title,int(*p)[8]){
	SDL_RenderClear(renderer);
	renderTexture(background, renderer, coordinate[0][0], coordinate[0][1]);
	renderTexture(qipan, renderer, coordinate[1][0], coordinate[1][1]);
	renderTexture(scoreboard, renderer, coordinate[2][0], coordinate[2][1]);
	if(s_start==START_ON)
	renderTexture(start_1, renderer, coordinate[3][0], coordinate[3][1]);
	else
	renderTexture(start_0, renderer, coordinate[3][0], coordinate[3][1]);
	if(s_back==BACK_ON)
	renderTexture(back_1, renderer, coordinate[4][0], coordinate[4][1]);
	else
	renderTexture(back_0, renderer, coordinate[4][0], coordinate[4][1]);
	if(s_pass==PASS_ON)
	renderTexture(pass_1, renderer, coordinate[5][0], coordinate[5][1]);
	else
	renderTexture(pass_0, renderer, coordinate[5][0], coordinate[5][1]);
	if(s_lose==LOSE_ON)
	renderTexture(lose_1, renderer, coordinate[6][0], coordinate[6][1]);
	else
	renderTexture(lose_0, renderer, coordinate[6][0], coordinate[6][1]);
	switch (s_title) {
	    case TITLE_REVERSI: 
		renderTexture(title_reversi, renderer, coordinate[11][0], coordinate[11][1]);
		break;
		case TITLE_THINK:
		renderTexture(title_think, renderer, coordinate[12][0], coordinate[12][1]);
		break;
		case TITLE_PASS:
		renderTexture(title_pass, renderer, coordinate[13][0], coordinate[13][1]);
		break;

	}
	if(p!=NULL)
	renderchess(p);
	SDL_RenderPresent(renderer);
}
void SDLC::renderchess(int(*p)[8]) {
	int i = 0, j = 0;
	int white_score = 0;
	int blank_score = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (p[i][j] == 1) {
				renderTexture(blank, renderer, 40 + j * 50 + 5, 175 + i * 50 + 5);
				blank_score++;
			}
			else if (p[i][j] == -1) {
				renderTexture(white, renderer, 40 + j * 50 + 5, 175 + i * 50 + 5);
				white_score++;
			}
		}
	}
	SDL_Texture* blank_score_tex = NULL;
	SDL_Texture* white_score_tex = NULL;
	std::string white_score_str;
	std::string blank_score_str;
	white_score_str = white_score / 10 + '0'; white_score_str += white_score % 10 + '0';
	blank_score_str = blank_score / 10 + '0'; blank_score_str += blank_score % 10 + '0';
	white_score_tex = renderText(white_score_str, "font.ttf", color, fontsize, renderer);
	blank_score_tex = renderText(blank_score_str, "font.ttf", color, fontsize, renderer);
	renderTexture(blank, renderer, coordinate[7][0], coordinate[7][1]);
	renderTexture(white, renderer, coordinate[9][0], coordinate[9][1]);
	renderTexture(white_score_tex, renderer, coordinate[10][0], coordinate[10][1]);
	renderTexture(blank_score_tex, renderer, coordinate[8][0], coordinate[8][1]);
	SDL_DestroyTexture(white_score_tex);
	SDL_DestroyTexture(blank_score_tex);
}