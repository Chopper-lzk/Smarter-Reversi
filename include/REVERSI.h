#pragma once
#ifndef _REVERSI_H_
#define _REVERSI_H_
#include<vector>
#include<time.h>
constexpr auto time_limited = 2;
constexpr auto UCT_C = 0.5;
struct node {
	int go[8][8] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
	};;
	node* parent=NULL;
	std::vector<node*> children;
	std::vector<std::vector<int>> children_action;
	double reward = 0;
	int exploer = 0;
	int status;
	node(int _status):status(_status){}
};
class REVERSI{
public:	
	int player_color;
	int ai_color;
	double timetotal;
	REVERSI();
	void InitMonte();
	void Colorset(int);
	std::vector<int> takestep();
	bool update(std::vector<int>&);
	void back();
	double end();

private:
	clock_t limit;
	clock_t start;
	clock_t finish;

	void traverse(node*);
	void Reversi(int(*)[8], int, int, int);
	bool legal_action(int(*)[8], int, int, int);
	double score(node* ptr_node);
	void MontetreeGrowth(node*,bool);	
	void erasetree(node*);
public:
	node* ptr_root;
	node* ptr_cur;
};
#endif 
