#include "REVERSI.h"
#include <time.h>
#include <math.h>
#define INT_MIN -2147483648
REVERSI::REVERSI() {
	timetotal = 0;
}

void REVERSI::Reversi(int(*go)[8], int row, int column, int chess_color) {
	int index_row, index_column;
	if (row - 1 >= 0) {
		if (column - 1 >= 0) {
			if (go[row - 1][column - 1] == -chess_color) {
				index_row = row - 1;
				index_column = column - 1;
				while (index_row >= 0 && index_column >= 0) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row--;
					index_column--;
				}
				if (index_row >= 0 && index_column >= 0 && go[index_row][index_column] == chess_color) {
					int i = index_row + 1;
					int j = index_column + 1;
					while (i < row && j < column) {
						go[i][j] = chess_color;
						i++; j++;
					}
				}
			}
		}
		if (go[row - 1][column] == -chess_color) {
			index_row = row - 1;
			index_column = column;
			while (index_row >= 0) {
				if (go[index_row][index_column] != -chess_color)
					break;
				index_row--;
			}
			if (index_row >= 0 && go[index_row][index_column] == chess_color) {
				int i = index_row + 1;
				int j = index_column;
				while (i < row) {
					go[i][j] = chess_color;
					i++;
				}
			}
		}
		if (column + 1 <= 7) {
			if (go[row - 1][column + 1] == -chess_color) {
				index_row = row - 1;
				index_column = column + 1;
				while (index_row >= 0 && index_column <= 7) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row--;
					index_column++;
				}
				if (index_row >= 0 && index_column <= 7 && go[index_row][index_column] == chess_color) {
					int i = index_row + 1;
					int j = index_column - 1;
					while (i < row && j > column) {
						go[i][j] = chess_color;
						i++; j--;
					}
				}
			}
		}
	}
	if (go[row][column - 1] == -chess_color) {
		index_row = row;
		index_column = column - 1;
		while (index_column >= 0) {
			if (go[index_row][index_column] != -chess_color)
				break;
			index_column--;
		}
		if (index_column >= 0 && go[index_row][index_column] == chess_color) {
			int i = index_row;
			int j = index_column + 1;
			while (j < column) {
				go[i][j] = chess_color;
				j++;
			}
		}
	}
	if (go[row][column + 1] == -chess_color) {
		index_row = row;
		index_column = column + 1;
		while (index_column <= 7) {
			if (go[index_row][index_column] != -chess_color)
				break;
			index_column++;
		}
		if (index_column <= 7 && go[index_row][index_column] == chess_color) {
			int i = index_row;
			int j = index_column - 1;
			while (j > column) {
				go[i][j] = chess_color;
				j--;
			}
		}
	}
	if (row + 1 <= 7) {
		if (column - 1 >= 0) {
			if (go[row + 1][column - 1] == -chess_color) {
				index_row = row + 1;
				index_column = column - 1;
				while (index_row <= 7 && index_column >= 0) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row++;
					index_column--;
				}
				if (index_row <= 7 && index_column >= 0 && go[index_row][index_column] == chess_color) {
					int i = index_row - 1;
					int j = index_column + 1;
					while (i > row && j < column) {
						go[i][j] = chess_color;
						i--; j++;
					}
				}
			}
		}
		if (go[row + 1][column] == -chess_color) {
			index_row = row + 1;
			index_column = column;
			while (index_row <= 7) {
				if (go[index_row][index_column] != -chess_color)
					break;
				index_row++;
			}
			if (index_row <= 7 && go[index_row][index_column] == chess_color) {
				int i = index_row - 1;
				int j = index_column;
				while (i > row) {
					go[i][j] = chess_color;
					i--;
				}
			}
		}
		if (column + 1 <= 7) {
			if (go[row + 1][column + 1] == -chess_color) {
				index_row = row + 1;
				index_column = column + 1;
				while (index_row <= 7 && index_column <= 7) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row++;
					index_column++;
				}
				if (index_row <= 7 && index_column <= 7 && go[index_row][index_column] == chess_color) {
					int i = index_row - 1;
					int j = index_column - 1;
					while (i > row && j > column) {
						go[i][j] = chess_color;
						i--; j--;
					}
				}
			}
		}
	}
}
bool REVERSI::legal_action(int(*go)[8], int row, int column, int chess_color) {
	int index_row, index_column;
	bool legal = false;
	if (row - 1 >= 0) {
		if (column - 1 >= 0) {
			if (go[row - 1][column - 1] == -chess_color) {
				index_row = row - 1;
				index_column = column - 1;
				while (index_row >= 0 && index_column >= 0) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row--;
					index_column--;
				}
				if (index_row >= 0 && index_column >= 0 && go[index_row][index_column] == chess_color) {
					legal = true;
					return legal;
				}
			}
		}
		if (go[row - 1][column] == -chess_color) {
			index_row = row - 1;
			index_column = column;
			while (index_row >= 0) {
				if (go[index_row][index_column] != -chess_color)
					break;
				index_row--;
			}
			if (index_row >= 0 && go[index_row][index_column] == chess_color) {
				legal = true;
				return legal;
			}
		}
		if (column + 1 <= 7) {
			if (go[row - 1][column + 1] == -chess_color) {
				index_row = row - 1;
				index_column = column + 1;
				while (index_row >= 0 && index_column <= 7) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row--;
					index_column++;
				}
				if (index_row >= 0 && index_column <= 7 && go[index_row][index_column] == chess_color) {
					legal = true;
					return legal;
				}
			}
		}
	}
	if (go[row][column - 1] == -chess_color) {
		index_row = row;
		index_column = column - 1;
		while (index_column >= 0) {
			if (go[index_row][index_column] != -chess_color)
				break;
			index_column--;
		}
		if (index_column >= 0 && go[index_row][index_column] == chess_color) {
			legal = true;
			return legal;
		}
	}
	if (go[row][column + 1] == -chess_color) {
		index_row = row;
		index_column = column + 1;
		while (index_column <= 7) {
			if (go[index_row][index_column] != -chess_color)
				break;
			index_column++;
		}
		if (index_column <= 7 && go[index_row][index_column] == chess_color) {
			legal = true;
			return legal;
		}
	}
	if (row + 1 <= 7) {
		if (column - 1 >= 0) {
			if (go[row + 1][column - 1] == -chess_color) {
				index_row = row + 1;
				index_column = column - 1;
				while (index_row <= 7 && index_column >= 0) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row++;
					index_column--;
				}
				if (index_row <= 7 && index_column >= 0 && go[index_row][index_column] == chess_color) {
					legal = true;
					return legal;
				}
			}
		}
		if (go[row + 1][column] == -chess_color) {
			index_row = row + 1;
			index_column = column;
			while (index_row <= 7) {
				if (go[index_row][index_column] != -chess_color)
					break;
				index_row++;
			}
			if (index_row <= 7 && go[index_row][index_column] == chess_color) {
				legal = true;
				return legal;
			}
		}
		if (column + 1 <= 7) {
			if (go[row + 1][column + 1] == -chess_color) {
				index_row = row + 1;
				index_column = column + 1;
				while (index_row <= 7 && index_column <= 7) {
					if (go[index_row][index_column] != -chess_color)
						break;
					index_row++;
					index_column++;
				}
				if (index_row <= 7 && index_column <= 7 && go[index_row][index_column] == chess_color) {
					legal = true;
					return legal;
				}
			}
		}
	}
	return legal;
}
void REVERSI::traverse(node* ptr_node) {
	node* ptr = NULL;
	int color = -ptr_node->status;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (ptr_node->go[i][j] == 0) {
				if (legal_action(ptr_node->go, i, j, color)) {
					ptr = new node(color);
					for (int x = 0; x < 8; x++) {
						for (int y = 0; y < 8; y++) {
							ptr->go[x][y] = ptr_node->go[x][y];
						}
					}
					ptr->go[i][j] = color;
					Reversi(ptr->go, i, j, color);
					ptr->parent = ptr_node;
					ptr_node->children.push_back(ptr);
					std::vector<int> action = { i,j };
					ptr_node->children_action.push_back(action);
				}
			}
		}
	}
	if (ptr_node->children.empty()) {
		ptr = new node(color);
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				ptr->go[x][y] = ptr_node->go[x][y];
			}
		}
		ptr->parent = ptr_node;
		ptr_node->children.push_back(ptr);
		std::vector<int> action = { -1,-1 };
		ptr_node->children_action.push_back(action);
	}
}
double REVERSI::score(node* ptr_node) {
	int play_score = 0, ai_score = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (ptr_node->go[i][j] == player_color)
				play_score++;
			if (ptr_node->go[i][j] == ai_color)
				ai_score++;
		}
	}
	if (play_score > ai_score)
		return -1;
	else if (play_score < ai_score)
		return 1;
	return 0;
}
void REVERSI::MontetreeGrowth(node* ptr_node,bool flag) {
	if (ptr_node->children.empty())
		traverse(ptr_node);
		int idx = rand() % ptr_node->children.size();
		if (ptr_node->children_action[idx][0] != -1) {
			MontetreeGrowth(ptr_node->children[idx], true);
		}
		else {
			if (flag) {
				MontetreeGrowth(ptr_node->children[idx], false);
			}
			else {
				double value = score(ptr_node->children[idx]);
				node* pointer = ptr_node->children[idx];
				while (pointer != ptr_cur) {
					pointer->exploer++;
					pointer->reward += value;
					pointer = pointer->parent;
				}
			}
		}	
}

void REVERSI::InitMonte() {
	ptr_root = new node(-1);
	ptr_cur = ptr_root;
	ptr_root->go[3][4] = 1; ptr_root->go[4][3] = 1;
	ptr_root->go[3][3] = -1; ptr_root->go[4][4] = -1;
}
void REVERSI::Colorset(int player) {
	ai_color = -player;
	player_color = player;
}
std::vector<int> REVERSI::takestep() {
	start = clock();
	limit = start + time_limited * CLOCKS_PER_SEC;
	while ((finish=clock()) <= limit)
		MontetreeGrowth(ptr_cur, true);
	int idx = -1;
	double UCT = INT_MIN;
	for (int i = 0; i < ptr_cur->children.size(); i++) {
		double reward = ptr_cur->children[i]->reward;
		int exploer = ptr_cur->children[i]->exploer;
	    double value= reward / exploer + UCT_C * sqrt(log10(exploer) /exploer);
		if (value > UCT) {
			UCT = value;
			idx = i;
		}
	}
	std::vector<int> action = ptr_cur->children_action[idx];
	action.push_back((finish - start) / CLOCKS_PER_SEC);
	timetotal += action[2];
	ptr_cur = ptr_cur->children[idx];
	return action;
}
bool REVERSI::update(std::vector<int>& action) {
	MontetreeGrowth(ptr_cur, true);
	for (int i = 0; i < ptr_cur->children_action.size(); i++) {
		if (ptr_cur->children_action[i][0] == action[0] && ptr_cur->children_action[i][1] == action[1]) {
			ptr_cur = ptr_cur->children[i];
			return true;
		}
	}
	return false;
}
void REVERSI::back() {
	ptr_cur = ptr_cur->parent;
}
double REVERSI::end() {
	double var= score(ptr_cur);
	erasetree(ptr_root);
	ptr_root = NULL;
	ptr_cur = NULL;
	timetotal = 0;
	return var;
}
void REVERSI::erasetree(node* root) {
	for (int i = 0; i < root->children.size(); i++)
		erasetree(root->children[i]);
	delete root;
}