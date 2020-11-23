#include <iostream>
#include <SDL.h>
#include "SDLC.h"
#include "REVERSI.h"

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
#define START_X 10
#define START_Y 615
#define PASS_X 250
#define PASS_Y 615
#define BACK_X 130
#define BACK_Y 615
#define LOSE_X 370
#define LOSE_Y 615
int main(int, char**) {

//initialization (create window and get texture);
SDLC sdlobj;
//creat reversi object;
REVERSI reversi;

SDL_Event e;
int x, y,row,column;
bool quit = false;
bool flag_start = false;
while (!quit) {
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			x = e.button.x;
			y = e.button.y;
			row = (y - 175) / 50;
			column = (x - 40) / 50;
			if (flag_start) {
				if (row >= 0 && row <= 7 && column >= 0 && column <= 7) {
					std::vector<int> action = { row,column };
					if (reversi.update(action)) {
						std::cout << "<player> " << " row: " << action[0] << " column: " << action[1] << " chess: " << (reversi.player_color == 1 ? "black" : "white") << std::endl;
						sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_THINK, reversi.ptr_cur->go);
						std::vector<int> action = reversi.takestep();
						sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
						if (action[0] == -1) {
							sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_PASS, reversi.ptr_cur->go);
							std::cout << "<computer> " << "pass" << std::endl;
							SDL_Delay(500);
						}
						else {
							std::cout << "<computer> " << " row: " << action[0] << ",column: " << action[1] << ",chess: " << (reversi.ai_color == 1 ? "black" : "white");
							std::cout << ",timeused: " << action[2] << "s " << ",time_total: " << reversi.timetotal << "s" << std::endl;
						}
					}
					else 
						std::cout << "<Inlegal action>" << std::endl;
				}
				if (x >= PASS_X + 2 && x <= PASS_X + 98 && y >= PASS_Y + 2 && y <= PASS_Y + 48) {
					sdlobj.render(START_OFF, BACK_OFF, PASS_ON, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
					SDL_Delay(200);
					sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
					std::vector<int> action = { -1,-1 };
					if (reversi.update(action)) {
						std::cout << "<player> " << "pass"  << std::endl;
						sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_THINK, reversi.ptr_cur->go);
						std::vector<int> action = reversi.takestep();
						sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
						if (action[0] == -1) {
							sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_PASS, reversi.ptr_cur->go);
							std::cout << "<computer> " << "pass" << std::endl;
							SDL_Delay(500);
						}
						else {
							std::cout << "<computer> " << " row: " << action[0] << ",column: " << action[1] << ",chess: " << (reversi.ai_color == 1 ? "black" : "white");
							std::cout << ",timeused: " << action[2] << "s " << ",time_total: " << reversi.timetotal << "s" << std::endl;
						}
					}
					else {
						std::cout << "<Inlegal action>" << std::endl;
					}
				}
				if (x >= BACK_X + 2 && x <= BACK_X + 98 && y >= BACK_Y + 2 && y <= BACK_Y + 48) {
					sdlobj.render(START_OFF, BACK_ON, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
					SDL_Delay(200);
					sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
					reversi.back();
				}
				if (x >= LOSE_X + 2 && x <= LOSE_X + 98 && y >= LOSE_Y + 2 && y <= LOSE_Y + 48) {
					sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_ON, TITLE_REVERSI, reversi.ptr_cur->go);
					SDL_Delay(200);
					sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
					double value = reversi.end();
					if (value == -1)
						std::cout << "Congratulations, you win!" <<std:: endl;
					else if (value == 0)
						std::cout << "Draw." << std::endl;
					else
						std::cout << "Computer win." <<std:: endl;
					flag_start = false;		            
				}
			}
			if (x >= START_X + 2 && x <= START_X + 98 && y >= START_Y + 2 && y <= START_Y + 48 && !flag_start) {
				flag_start = true;
				std::cout << "Game started ,have fun!" << std::endl;
				reversi.InitMonte();
				sdlobj.render(START_ON, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
				SDL_Delay(200);
				while (SDL_PollEvent(&e)) {}
				sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
				bool flag_con = true;
				while (flag_con) {
					std::cout << "Choose chess color please <white: -1, blank:1> : ";
					int player;
					std::cin >> player;
					if (player == 1 || player == -1) {
						reversi.Colorset(player);
						flag_con = false;
					}
					else
						std::cout << "Error input,usage: <white: -1, blank:1>" << std::endl;
				}
				if (reversi.ai_color == 1) {
					sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_THINK, reversi.ptr_cur->go);
					std::vector<int> action = reversi.takestep();
					sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
					if (action[0] == -1) {
						sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_PASS, reversi.ptr_cur->go);
						std::cout << "<computer> " << "pass" << std::endl;
						SDL_Delay(500);
					}
					else {
						std::cout << "<computer> " << " row: " << action[0] << ",column: " << action[1] << ",chess: " << (reversi.ai_color == 1 ? "black" : "white") ;
						std::cout << ",timeused: " << action[2] << "s " << ",time_total: " << reversi.timetotal << "s" << std::endl;
					}
				}
			}
			break;
		default:
			break;
		}
	}
	if (flag_start)
		sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, reversi.ptr_cur->go);
	else
		sdlobj.render(START_OFF, BACK_OFF, PASS_OFF, LOSE_OFF, TITLE_REVERSI, NULL);
}
	return 0;
}





