#pragma once

#include "GameLevel.h"
#include <vector>

class Level1 : public GameLevel
{
	SpriteSheet* sprites;
	HWND lochwnd;
	POINT p;

	std::vector<std::vector<int>> boardArr;

	bool wrong = false;

	int move = 1;
	int grabbed;

	std::vector <int> prevpos;
	std::vector <int> wrongpos;
	std::vector <int> enpassant = {NULL, NULL, -1 };
	static bool truthy(std::vector<int> begin, std::vector<int> target, std::vector<std::vector<int>> locboardArr, int move, std::vector <int> *enpassant, std::vector<std::vector<int>> *boardArr) {
		int beginP = locboardArr[begin[1]][begin[0]] - 8;
		int targetP = locboardArr[target[1]][target[0]] - 8;

		int dif;
		int absx, absy;
		
		if (((move % 2 == 0) && (beginP < 0)) || (move % 2 == 1) && (beginP > 0))
			return false;

		if (targetP != -8) {
			if (beginP * targetP > 0) {
				return false;
			}
		}
		if (!targetP || !beginP) {
			if (targetP + beginP > 0)
				return false;
		}

		switch (beginP)
		{
		case -6:  // Fall Through
		case 0:  // kings
			if ((begin[0] - 1 <= target[0] && target[0] <= begin[0] + 1) &&
				(begin[1] - 1 <= target[1] && target[1] <= begin[1] + 1)) {
				return true;
			}
			return false;

		case -5:
		case 1:  // Queens

			if (target[0] == begin[0]) {
				dif = target[1] - begin[1];
				if (dif > 0) {
					for (uint16_t i = begin[1] + 1; i < target[1]; i++)
					{
						if (locboardArr[i][target[0]])
							return false;
					}
					return true;
				}
					for (uint16_t i = begin[1] - 1; i > target[1]; i--)
					{
						if (locboardArr[i][target[0]])
							return false;
					}
					return true;
				
			}
			if (target[1] == begin[1]) {
				dif = target[0] - begin[0];
				if (dif > 0) {
					for (uint16_t i = begin[0] + 1; i < target[0]; i++)
					{
						if (locboardArr[target[1]][i])
							return false;
					}
					return true;
				}
				for (uint16_t i = begin[0] - 1; i > target[0]; i--)
				{
					if (locboardArr[target[1]][i])
						return false;
				}
				return true;
			}

			if ((target[1] - begin[1]) / (target[0] - begin[0]) == 1) {
				dif = target[0] - begin[0];
				if (dif > 0) {
					for (uint16_t i = 1; i < abs(dif); i++)
					{
						if (locboardArr[begin[1] + i][begin[0] + i])
							return false;
					}
					return true;
				}
				for (uint16_t i = 1; i < abs(dif); i++)
				{
					if (locboardArr[begin[1] - i][begin[0] - i])
						return false;
				}
				return true;
			}
			if ((target[1] - begin[1]) / (target[0] - begin[0]) == -1) {
				dif = target[0] - begin[0];
				if (dif > 0) {
					for (uint16_t i = 1; i < abs(dif); i++)
					{
						if (locboardArr[begin[1] - i][begin[0] + 1])
							return false;
					}
					return true;
				}
				for (uint16_t i = 1; i < abs(dif); i++)
				{
					if (locboardArr[begin[1] + i][begin[0] - 1])
						return false;
				}
				return true;
			}
			return false;

		case -4:
		case 2:  // Rooks
			if (target[0] == begin[0]) {
				dif = target[1] - begin[1];
				if (dif > 0) {
					for (uint16_t i = begin[1] + 1; i < target[1]; i++)
					{
						if (locboardArr[i][target[0]])
							return false;
					}
					return true;
				}
				for (uint16_t i = begin[1] - 1; i > target[1]; i--)
				{
					if (locboardArr[i][target[0]])
						return false;
				}
				return true;

			}
			if (target[1] == begin[1]) {
				dif = target[0] - begin[0];
				if (dif > 0) {
					for (uint16_t i = begin[0] + 1; i < target[0]; i++)
					{
						if (locboardArr[target[1]][i])
							return false;
					}
					return true;
				}
				for (uint16_t i = begin[0] - 1; i > target[0]; i--)
				{
					if (locboardArr[target[1]][i])
						return false;
				}

				return true;
			}
			return false;

		case -3:
		case 3:  // Knights
			absx = abs(begin[0] - target[0]);
			absy = abs(begin[1] - target[1]);
			if (absx && absy) {
				if (absx + absy == 3) {
					return true;
				}
			}
			return false;

		case -2:
		case 4:  // Bishops

			if ((target[1] - begin[1]) / (target[0] - begin[0]) == 1) {
				dif = target[0] - begin[0];
				if (dif > 0) {
					for (uint16_t i = 1; i < abs(dif); i++)
					{
						if (locboardArr[begin[1] + i][begin[0] + i])
							return false;
					}
					return true;
				}
				for (uint16_t i = 1; i < abs(dif); i++)
				{
					if (locboardArr[begin[1] - i][begin[0] - i])
						return false;
				}
				return true;
			}
			if ((target[1] - begin[1]) / (target[0] - begin[0]) == -1) {
				dif = target[0] - begin[0];
				if (dif > 0) {
					for (uint16_t i = 1; i < abs(dif); i++)
					{
						if (locboardArr[begin[1] - i][begin[0] + 1])
							return false;
					}
					return true;
				}
				for (uint16_t i = 1; i < abs(dif); i++)
				{
					if (locboardArr[begin[1] + i][begin[0] - 1])
						return false;
				}
				return true;
			}
			return false;


		case -1:  // White Pawn
			if (target[0] == begin[0]) {
				if (begin[1] == 6 && target[1] == 4) {
					*enpassant = { target[0], target[1] + 1, move };
					return true;
				}
			}
			if (begin[1] - 1 != target[1]) 
				return false;
			if (target[0] == begin[0]) {
				if (!locboardArr[target[1]][target[0]])
					return true;
				return false;
			}
			if (target[0] == begin[0] - 1 || target[0] == begin[0] + 1) {
				if (locboardArr[target[1]][target[0]])
					return true;
				if ((target[0] == (*enpassant)[0]) && (target[1] == (*enpassant)[1]) && move == ((*enpassant)[2] + 1)) {
					(*boardArr)[target[1] + 1][target[0]] = 0;
					return true;
				}
			}
			return false;
		case 5:  // Black Pawn
			if (target[0] == begin[0]) {
				if (begin[1] == 1 && target[1] == 3) {
					*enpassant = { target[0], target[1] - 1, move };
					return true;
				}
			}
			if (begin[1] + 1 != target[1])
				return false;
			if (target[0] == begin[0]) {
				if (!locboardArr[target[1]][target[0]] )
					return true;
				return false;
			}
			if (target[0] == begin[0] - 1 || target[0] == begin[0] + 1) {
				if (locboardArr[target[1]][target[0]])
					return true;
				if ((target[0] == (*enpassant)[0]) && (target[1] == (*enpassant)[1]) && move == ((*enpassant)[2] + 1)) {
					(*boardArr)[target[1] - 1][target[0]] = 0;
					return true;
				}
			}
			return false;

		default:
			return false;
		}

	}

	static bool inchecked(std::vector<std::vector<int>> locboardArr, int move) {


		std::vector <int> begin;
		std::vector<std::vector<int>> bishopCheck;

		for (uint16_t y = 0; y < locboardArr.size(); y++)
		{
			for (uint16_t x = 0; x < locboardArr[y].size(); x++)
			{
				if ((locboardArr[y][x]) == 2 && (move % 2 == 1)) {
					begin = { x, y };
					goto label4white;
				}
				if ((locboardArr[y][x]) == 8 && (move % 2 == 0)) {
					begin = { x, y };
					goto label4black;
				}
			}
		}


	label4white:
		OutputDebugString("I am White\n");
		for (uint16_t i = 1; begin[0] + i < 8; i++)  // Straights
		{
			if (locboardArr[begin[1]][begin[0] + i] == 10 || locboardArr[begin[1]][begin[0] + i] == 9)
				return true;
			if (locboardArr[begin[1]][begin[0] + i])
				break;
		}
		for (uint16_t i = 1; begin[0] - i > 0; i++)
		{
			if (locboardArr[begin[1]][begin[0] - i] == 10 || locboardArr[begin[1]][begin[0] - i] == 9)
				return true;
			if (locboardArr[begin[1]][begin[0] - i])
				break;
		}
		for (uint16_t i = 1; begin[1] + i < 8; i++)
		{
			if (locboardArr[begin[1] + i][begin[0]] == 10 || locboardArr[begin[1] + i][begin[0]] == 9)
				return true;
			if (locboardArr[begin[1] + i][begin[0]])
				break;
		}
		for (uint16_t i = 1; begin[1] - i > 0; i++)
		{
			if (locboardArr[begin[1] - i][begin[0]] == 10 || locboardArr[begin[1] - i][begin[0]] == 9)
				return true;
			if (locboardArr[begin[1] - i][begin[0]])
				break;
		}

		for (uint16_t i = 1; begin[0] + i < 8 && begin[1] + i < 8; i++)   // Diag
		{
			if (locboardArr[begin[1] + i][begin[0] + i] == 12 || locboardArr[begin[1]][begin[0] + i] == 9)
				return true;
			if (locboardArr[begin[1] + i][begin[0] + i])
				break;
		}
		for (uint16_t i = 1; begin[0] - i > 0 && begin[1] - i > 0; i++)
		{
			if (locboardArr[begin[1] - i][begin[0] - i] == 12 || locboardArr[begin[1] - i][begin[0] - i] == 9)
				return true;
			if (locboardArr[begin[1] - i][begin[0] - i])
				break;
		}
		for (uint16_t i = 1; begin[0] + i < 8 && begin[1] - i > 0; i++)
		{
			if (locboardArr[begin[1] - i][begin[0] + i] == 12 || locboardArr[begin[1] - i][begin[0] + i] == 9)
				return true;
			if (locboardArr[begin[1] - i][begin[0] + i])
				break;
		}
		for (uint16_t i = 1; begin[0] - i > 0 && begin[1] + i < 8; i++)
		{
			if (locboardArr[begin[1] + i][begin[0] - i] == 12 || locboardArr[begin[1] + i][begin[0] - i] == 9)
				return true;
			if (locboardArr[begin[1] + i][begin[0] - i])
				break;
		}

		for (uint16_t i = 1; i < 3; i++)  // Knights
		{
			if ((begin[0] - i) > -1) {
				if ((begin[1] + (3 - i)) < 8)
					if (locboardArr[begin[1] + (3 - i)][begin[0] - i] == 11)
						return true;
				if ((begin[1] - (3 - i)) > -1)
					if (locboardArr[begin[1] - (3 - i)][begin[0] - i] == 11)
						return true;
			}
			if ((begin[0] + i) < 8) {
				if ((begin[1] + (3 - i)) < 8)
					if (locboardArr[begin[1] + (3 - i)][begin[0] + i] == 11)
						return true;
				if ((begin[1] - (3 - i)) > -1)
					if (locboardArr[begin[1] - (3 - i)][begin[0] + i] == 11)
						return true;
			}
		}

		if ((locboardArr[begin[1] - 1][begin[0] - 1] == 13) || (locboardArr[begin[1] - 1][begin[0] + 1] == 13))
			return true;

		return false;

	label4black:
		OutputDebugString("I am Black\n");
		for (uint16_t i = 1; begin[0] + i < 8; i++)  // Straights
		{
			if (locboardArr[begin[1]][begin[0] + i] == 4 || locboardArr[begin[1]][begin[0] + i] == 3)
				return true;
			if (locboardArr[begin[1]][begin[0] + i])
				break;
		}
		for (uint16_t i = 1; begin[0] - i > 0; i++)
		{
			if (locboardArr[begin[1]][begin[0] - i] == 4 || locboardArr[begin[1]][begin[0] - i] == 3)
				return true;
			if (locboardArr[begin[1]][begin[0] - i])
				break;
		}
		for (uint16_t i = 1; begin[1] + i < 8; i++)
		{
			if (locboardArr[begin[1] + i][begin[0]] == 4 || locboardArr[begin[1] + i][begin[0]] == 3)
				return true;
			if (locboardArr[begin[1] + i][begin[0]])
				break;
		}
		for (uint16_t i = 1; begin[1] - i > 0; i++)
		{
			if (locboardArr[begin[1] - i][begin[0]] == 4 || locboardArr[begin[1] - i][begin[0]] == 3)
				return true;
			if (locboardArr[begin[1] - i][begin[0]])
				break;
		}

		for (uint16_t i = 1; begin[0] + i < 8 && begin[1] + i < 8; i++)   // Diag
		{
			if (locboardArr[begin[1] + i][begin[0] + i] == 6 || locboardArr[begin[1] + i][begin[0] + i] == 3)
				return true;
			if (locboardArr[begin[1] + i][begin[0] + i])
				break;
		}
		for (uint16_t i = 1; begin[0] - i > 0 && begin[1] - i > 0; i++)
		{
			if (locboardArr[begin[1] - i][begin[0] - i] == 6 || locboardArr[begin[1] - i][begin[0] - i] == 3)
				return true;
			if (locboardArr[begin[1] - i][begin[0] - i])
				break;
		}
		for (uint16_t i = 1; begin[0] + i < 8 && begin[1] - i > 0; i++)
		{
			if (locboardArr[begin[1] - i][begin[0] + i] == 6 || locboardArr[begin[1] - i][begin[0] + i] == 3)
				return true;
			if (locboardArr[begin[1] - i][begin[0] + i])
				break;
		}
		for (uint16_t i = 1; begin[0] - i > 0 && begin[1] + i < 8; i++)
		{
			if (locboardArr[begin[1] + i][begin[0] - i] == 6 || locboardArr[begin[1] + i][begin[0] - i] == 3)
				return true;
			if (locboardArr[begin[1] + i][begin[0] - i])
				break;
		}

		for (uint16_t i = 1; i < 3; i++)  // Knights
		{
			if ((begin[0] - i) > -1) {
				if ((begin[1] + (3 - i)) < 8)
					if (locboardArr[begin[1] + (3 - i)][begin[0] - i] == 5)
						return true;
				if ((begin[1] - (3 - i)) > -1)
					if (locboardArr[begin[1] - (3 - i)][begin[0] - i] == 5)
						return true;
			}
			if ((begin[0] + i) < 8) {
				if ((begin[1] + (3 - i)) < 8)
					if (locboardArr[begin[1] + (3 - i)][begin[0] + i] == 5)
						return true;
				if ((begin[1] - (3 - i)) > -1)
					if (locboardArr[begin[1] - (3 - i)][begin[0] + i] == 5)
						return true;
			}
		}

		if ((locboardArr[begin[1] + 1][begin[0] - 1] == 7) || (locboardArr[begin[1] + 1][begin[0] + 1] == 7))
			return true;

		return false;
	}

public:
	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(double timeDelta) override;
	void EventProcess(UINT uMsg, HWND hwnd, double timeDelta) override;
};

