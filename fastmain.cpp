#pragma warning(disable : 4996)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "nodetypes.h"
#include "prototypes.h"
#include <math.h>
#include <queue>
#include <string.h>
#include <unordered_map>
#include <queue>
#include <array>
#include <future>
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;

Node *Root;	   //??? ??? ??? ????(???? ????)
Node *Current; //??? ?????? ????
Leaf *Support; //??? ?????? ??????? ???? ??? ??????
Leaf *Last;	   // Support ??????? ?? ??? ?????(??? ??? ??????? ????)

unordered_map<string, int> database;
unordered_map<uint64_t, int> intDataBase;

int SS[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}}; //??? ????
int IP[4][4];																   //  ??? ???? ????

int ChildNum = 0; // ???? ?????? ??????? ???? ???? ????

int cord[17][2] = {{3, 3}, {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3}, {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3}};

// array<array<int, 4>, 4> pd1 = {{{1, 2, 3, 100}, {5, 6, 100, 100}, {100, 100, 100, 100}, {100, 100, 100, 0}}};	  // ���� ������1
// array<array<int, 4>, 4> pd2 = {{{100, 100, 100, 4}, {100, 100, 7, 8}, {100, 100, 11, 12}, {100, 100, 100, 0}}};	  // ���� ������ 2
// array<array<int, 4>, 4> pd3 = {{{100, 100, 100, 100}, {100, 100, 100, 100}, {9, 10, 100, 100}, {13, 14, 15, 0}}}; // ���� ������ 3

string spd1 = "123*56**********";
string spd2 = "***4**78**BC****";
string spd3 = "********9A**DEF*";

// array<array<int, 4>, 4> pd1 = {{{1, 2, 3, 16}, {5, 6, 16, 16}, {16, 16, 16, 16}, {16, 16, 16, 0}}};	  // ���� ������1
// array<array<int, 4>, 4> pd2 = {{{16, 16, 16, 4}, {16, 16, 7, 8}, {16, 16, 11, 12}, {16, 16, 16, 0}}}; // ���� ������ 2
// array<array<int, 4>, 4> pd3 = {{{16, 16, 16, 16}, {16, 16, 16, 16}, {9, 10, 16, 16}, {13, 14, 15, 0}}};

// queue<pair<array<int, 3>, array<array<int, 4>, 4>>> que1; // bfs�� ���� ť
// queue<pair<array<int, 3>, array<array<int, 4>, 4>>> que2; // bfs�� ���� ť
// queue<pair<array<int, 3>, array<array<int, 4>, 4>>> que3; // ��

queue<pair<array<int, 2>, string>> sque1; // 0의 위치와 bfs count값 그리고 patterdatabase 문자열 값을 담을 큐
queue<pair<array<int, 2>, string>> sque2;
queue<pair<array<int, 2>, string>> sque3;

// 문자열은 0 ~ 15의 값을 가진다.
// 0 1 2 3 || 4 5 6 7 || 8 9 10 11 || 12 13 14 15 라 생각해야함
// 1 4 -1 -4 의 값을 가질 수 있으나 0, 3, 4, 7, 8, 11, 12, 15의 위치에서는 오른쪽 왼쪽 이동이 불가능하다.
// 또한 0 3 에서는 위로의 이동(-3) 12 15 에서는 아래로의 이동(+3)이 제한된다.
// 규칙을 찾아본다면 % 4 가 0인 경우 왼쪽 이동이 안된다. % 4 가 3인 경우 오른쪽 이동이 안된다. 현 인덱스 - 4 가 0 보다 작은 경우 위로의 이동
// (-3)이 제한되며, + 4 가 s.length 보다 크거나 같은경우 아래로의 이동(+3)이 제한

// �񵿱� ó���� �� �Լ��� ���ÿ� ������ �� ����� ������ �����ϱ� ���� ���ɾ�
std::mutex mtx;

// void queInitializer() {
// 	for (int i = 0; i < 4; i++) {
// 		for (int j = 0; j < 4; j++) {
// 			if (pd1[i][j] > 0 && pd1[i][j] < 16) {
// 				que1.push({{i, j, 0}, pd1});
// 			}
// 			if (pd2[i][j] > 0 && pd2[i][j] < 16) {
// 				que2.push({{i, j, 0}, pd2});
// 			}
// 			if (pd3[i][j] > 0 && pd3[i][j] < 16) {
// 				que3.push({{i, j, 0}, pd3});
// 			}
// 		}
// 	}
// }

// array<array<int, 4>, 4> goToBack1(int curI, int curJ, array<array<int, 4>, 4> curArr)
// {
// 	int willChangeI;
// 	int willChangeJ;
// 	if (pd1[curI + 1][curJ] == 0)
// 	{
// 		willChangeI = curI + 1;
// 		willChangeJ = curJ;
// 	}
// 	else if (pd1[curI - 1][curJ] == 0)
// 	{
// 		willChangeI = curI - 1;
// 		willChangeJ = curJ;
// 	}
// 	else if (pd1[curI][curJ + 1] == 0)
// 	{
// 		willChangeI = curI;
// 		willChangeJ = curJ;
// 	}
// 	else
// 	{
// 		willChangeI = curI;
// 		willChangeJ = curJ;
// 	}

// 	int tempValue = pd1[willChangeI][willChangeJ];
// 	pd1[willChangeI][willChangeJ] = pd1[curI][curJ];
// 	pd1[curI][curJ] = tempValue;
// }

// void goToBack2(int curI, int curJ)
// {
// 	int willChangeI;
// 	int willChangeJ;
// 	if (pd2[curI + 1][curJ] == 0)
// 	{
// 		willChangeI = curI + 1;
// 		willChangeJ = curJ;
// 	}
// 	else if (pd2[curI - 1][curJ] == 0)
// 	{
// 		willChangeI = curI - 1;
// 		willChangeJ = curJ;
// 	}
// 	else if (pd2[curI][curJ + 1] == 0)
// 	{
// 		willChangeI = curI;
// 		willChangeJ = curJ;
// 	}
// 	else
// 	{
// 		willChangeI = curI;
// 		willChangeJ = curJ;
// 	}

// 	int tempValue = pd2[willChangeI][willChangeJ];
// 	pd2[willChangeI][willChangeJ] = pd2[curI][curJ];
// 	pd2[curI][curJ] = tempValue;
// }

// void goToBack3(int curI, int curJ)
// {
// 	int willChangeI;
// 	int willChangeJ;
// 	if (pd3[curI + 1][curJ] == 0)
// 	{
// 		willChangeI = curI + 1;
// 		willChangeJ = curJ;
// 	}
// 	else if (pd3[curI - 1][curJ] == 0)
// 	{
// 		willChangeI = curI - 1;
// 		willChangeJ = curJ;
// 	}
// 	else if (pd3[curI][curJ + 1] == 0)
// 	{
// 		willChangeI = curI;
// 		willChangeJ = curJ;
// 	}
// 	else
// 	{
// 		willChangeI = curI;
// 		willChangeJ = curJ;
// 	}

// 	int tempValue = pd3[willChangeI][willChangeJ];
// 	pd3[willChangeI][willChangeJ] = pd3[curI][curJ];
// 	pd3[curI][curJ] = tempValue;
// }

// array<array<int, 4>, 4> switchTable(int curI, int curJ, int prevI, int prevJ, array<array<int, 4>, 4> curArr)
// { // ���� ��ġ �������ִ� �Լ�
// 	int temp = curArr[curI][curJ];
// 	curArr[curI][curJ] = curArr[prevI][prevJ];
// 	curArr[prevI][prevJ] = temp;
// 	return curArr;
// }

string stringSwitchTable(int curI, int prevI, string curString)
{
	char temp = curString[curI];
	curString[curI] = curString[prevI];
	curString[prevI] = temp;
	// cout << "curString : " << curString << endl;
	return curString;
}

// string parseToString(array<array<int, 4>, 4> tempNode)
// {
// 	string result;
// 	for (int i = 0; i < 4; i++)
// 	{
// 		for (int j = 0; j < 4; j++)
// 		{
// 			if (tempNode[i][j] > 0 && tempNode[i][j] < 16)
// 			{
// 				string cur = to_string(tempNode[i][j]);
// 				result += cur;
// 			}
// 			else if (tempNode[i][j] == 100)
// 			{
// 				result += '*';
// 			}
// 			else
// 			{
// 				result += '0';
// 			}
// 		}
// 	}
// 	return result;
// }

void squeInitializer()
{
	for (int i = 0; i < 16; i++)
	{
		if (spd1[i] != '*')
		{
			sque1.push({{i, 0}, spd1});
		}
		if (spd2[i] != '*')
		{
			sque2.push({{i, 0}, spd2});
		}
		if (spd3[i] != '*')
		{
			sque3.push({{i, 0}, spd3});
		}
	}
}

// void squeInitializer()
// {
// 	sque1.push({{0, 0}, spd1});
// 	sque2.push({{3, 0}, spd2});
// 	sque3.push({{8, 0}, spd3});
// }

// void queInitializer() // bfs�� ���ؼ� ť�� 0(��ĭ, �� ������ �� �ִ� ĭ)�� ��ġ�� bfs�� ��ĥ�� ���� �ڽļ��� ī��Ʈ�ϱ� ���� �� 0�� �߰�����
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		for (int j = 0; j < 4; j++)
// 		{
// 			if (pd1[i][j] == 0)
// 			{
// 				que1.push({{i, j, 0}, pd1});
// 			}
// 			if (pd2[i][j] == 0)
// 			{
// 				que2.push({{i, j, 0}, pd2});
// 			}
// 			if (pd3[i][j] == 0)
// 			{
// 				que3.push({{i, j, 0}, pd3});
// 			}
// 		}
// 	}
// }

void sfindUntilNumber1()
{
	while (!sque1.empty())
	{
		pair<array<int, 2>, string> cur = sque1.front();
		sque1.pop();
		// cout << cur.second << endl;
		// 오른쪽
		if (cur.first[0] % 4 != 3)
		{
			if (cur.second[cur.first[0] + 1] != '*')
			{
				sque1.push({{cur.first[0] + 1, 0}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
				cout << "find number! " << endl;
				break;
			}
			else
			{
				sque1.push({{cur.first[0] + 1, 0}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
			}
		}
		// 왼쪽
		if (cur.first[0] % 4 != 0)
		{
			if (cur.second[cur.first[0] - 1] != '*')
			{
				sque1.push({{cur.first[0] - 1, 0}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
				cout << "find number! " << endl;
				break;
			}
			else
			{
				sque1.push({{cur.first[0] - 1, 0}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
			}
		}
		// 위
		if (cur.first[0] - 4 >= 0)
		{
			if (cur.second[cur.first[0] - 4] != '*')
			{
				sque1.push({{cur.first[0] - 4, 0}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
				cout << "find number! " << endl;
				break;
			}
			else
			{
				sque1.push({{cur.first[0] - 4, 0}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
			}
		}
		// 아래
		if (cur.first[0] + 4 < cur.second.length())
		{
			if (cur.second[cur.first[0] + 4] != '*')
			{
				sque1.push({{cur.first[0] + 4, 0}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
				cout << "find number! " << endl;
				break;
			}
			else
			{
				sque1.push({{cur.first[0] + 4, 0}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
			}
		}
	}
}

void sfindUntilNumber2()
{
	while (!sque2.empty())
	{
		pair<array<int, 2>, string> cur = sque2.front();
		sque2.pop();
		// 오른쪽
		if (cur.first[0] % 4 != 3)
		{
			if (cur.second[cur.first[0] + 1] != '*')
			{
				sque2.push({{cur.first[0] + 1, 0}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque2.push({{cur.first[0] + 1, 0}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
			}
		}
		// 왼쪽
		if (cur.first[0] % 4 != 0)
		{
			if (cur.second[cur.first[0] - 1] != '*')
			{
				sque2.push({{cur.first[0] - 1, 0}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque2.push({{cur.first[0] - 1, 0}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
			}
		}
		// 위
		if (cur.first[0] - 4 >= 0)
		{
			if (cur.second[cur.first[0] - 4] != '*')
			{
				sque2.push({{cur.first[0] - 4, 0}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque2.push({{cur.first[0] - 4, 0}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
			}
		}
		// 아래
		if (cur.first[0] + 4 < cur.second.length())
		{
			if (cur.second[cur.first[0] + 4] != '*')
			{
				sque2.push({{cur.first[0] + 4, 0}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque2.push({{cur.first[0] + 4, 0}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
			}
		}
	}
}

void sfindUntilNumber3()
{
	while (!sque3.empty())
	{
		pair<array<int, 2>, string> cur = sque3.front();
		sque3.pop();
		// 오른쪽
		if (cur.first[0] % 4 != 3)
		{
			if (cur.second[cur.first[0] + 1] != '*')
			{
				sque3.push({{cur.first[0] + 1, 0}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque3.push({{cur.first[0] + 1, 0}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
			}
		}
		// 왼쪽
		if (cur.first[0] % 4 != 0)
		{
			if (cur.second[cur.first[0] - 1] != '*')
			{
				sque3.push({{cur.first[0] - 1, 0}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque3.push({{cur.first[0] - 1, 0}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
			}
		}
		// 위
		if (cur.first[0] - 4 >= 0)
		{
			if (cur.second[cur.first[0] - 4] != '*')
			{
				sque3.push({{cur.first[0] - 4, 0}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque3.push({{cur.first[0] - 4, 0}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
			}
		}
		// 아래
		if (cur.first[0] + 4 < cur.second.length())
		{
			if (cur.second[cur.first[0] + 4] != '*')
			{
				sque3.push({{cur.first[0] + 4, 0}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
				break;
			}
			else
			{
				sque3.push({{cur.first[0] + 4, 0}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
			}
		}
	}
}

// void findUntilNumber1() // ���ϵ������� ���ڸ� ã�� ���� �Լ�
// {
// 	while (!que1.empty())
// 	{
// 		pair<array<int, 3>, array<array<int, 4>, 4>> cur = que1.front();
// 		que1.pop();
// 		if (cur.first[0] + 1 < 4)
// 		{
// 			if (cur.second[cur.first[0] + 1][cur.first[1]] > 0 && cur.second[cur.first[0] + 1][cur.first[1]] < 16)
// 			{
// 				que1.push({{cur.first[0] + 1, cur.first[1], 0}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que1.push({{cur.first[0] + 1, cur.first[1], 0}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[0] - 1 >= 0)
// 		{
// 			if (cur.second[cur.first[0] - 1][cur.first[1]] > 0 && cur.second[cur.first[0] - 1][cur.first[1]] < 16)
// 			{
// 				que1.push({{cur.first[0] - 1, cur.first[1], 0}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que1.push({{cur.first[0] - 1, cur.first[1], 0}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[1] + 1 < 4)
// 		{
// 			if (cur.second[cur.first[0]][cur.first[1] + 1] > 0 && cur.second[cur.first[0]][cur.first[1] + 1] < 16)
// 			{
// 				que1.push({{cur.first[0], cur.first[1] + 1, 0}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que1.push({{cur.first[0], cur.first[1] + 1, 0}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[1] - 1 >= 0)
// 		{
// 			if (cur.second[cur.first[0]][cur.first[1] - 1] > 0 && cur.second[cur.first[0]][cur.first[1] - 1] < 16)
// 			{
// 				que1.push({{cur.first[0], cur.first[1] - 1, 0}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que1.push({{cur.first[0], cur.first[1] - 1, 0}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 	}
// }

// void findUntilNumber2() // ���ϵ������� ���ڸ� ã�� ���� �Լ�
// {
// 	while (!que2.empty())
// 	{
// 		pair<array<int, 3>, array<array<int, 4>, 4>> cur = que2.front();
// 		que2.pop();
// 		if (cur.first[0] + 1 < 4)
// 		{
// 			if (cur.second[cur.first[0] + 1][cur.first[1]] > 0 && cur.second[cur.first[0] + 1][cur.first[1]] < 16)
// 			{
// 				que2.push({{cur.first[0] + 1, cur.first[1], 0}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que2.push({{cur.first[0] + 1, cur.first[1], 0}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[0] - 1 >= 0)
// 		{
// 			if (cur.second[cur.first[0] - 1][cur.first[1]] > 0 && cur.second[cur.first[0] - 1][cur.first[1]] < 16)
// 			{
// 				que2.push({{cur.first[0] - 1, cur.first[1], 0}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que2.push({{cur.first[0] - 1, cur.first[1], 0}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[1] + 1 < 4)
// 		{
// 			if (cur.second[cur.first[0]][cur.first[1] + 1] > 0 && cur.second[cur.first[0]][cur.first[1] + 1] < 16)
// 			{
// 				que2.push({{cur.first[0], cur.first[1] + 1, 0}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que2.push({{cur.first[0], cur.first[1] + 1, 0}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[1] - 1 >= 0)
// 		{
// 			if (cur.second[cur.first[0]][cur.first[1] - 1] > 0 && cur.second[cur.first[0]][cur.first[1] - 1] < 16)
// 			{
// 				que2.push({{cur.first[0], cur.first[1] - 1, 0}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que2.push({{cur.first[0], cur.first[1] - 1, 0}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 	}
// }

// void findUntilNumber3() // ���ϵ������� ���ڸ� ã�� ���� �Լ�
// {
// 	while (!que3.empty())
// 	{
// 		pair<array<int, 3>, array<array<int, 4>, 4>> cur = que3.front();
// 		que3.pop();
// 		if (cur.first[0] + 1 < 4)
// 		{
// 			if (cur.second[cur.first[0] + 1][cur.first[1]] > 0 && cur.second[cur.first[0] + 1][cur.first[1]] < 16)
// 			{
// 				que3.push({{cur.first[0] + 1, cur.first[1], 0}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que3.push({{cur.first[0] + 1, cur.first[1], 0}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[0] - 1 >= 0)
// 		{
// 			if (cur.second[cur.first[0] - 1][cur.first[1]] > 0 && cur.second[cur.first[0] - 1][cur.first[1]] < 16)
// 			{
// 				que3.push({{cur.first[0] - 1, cur.first[1], 0}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que3.push({{cur.first[0] - 1, cur.first[1], 0}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[1] + 1 < 4)
// 		{
// 			if (cur.second[cur.first[0]][cur.first[1] + 1] > 0 && cur.second[cur.first[0]][cur.first[1] + 1] < 16)
// 			{
// 				que3.push({{cur.first[0], cur.first[1] + 1, 0}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que3.push({{cur.first[0], cur.first[1] + 1, 0}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		if (cur.first[1] - 1 >= 0)
// 		{
// 			if (cur.second[cur.first[0]][cur.first[1] - 1] > 0 && cur.second[cur.first[0]][cur.first[1] - 1] < 16)
// 			{
// 				que3.push({{cur.first[0], cur.first[1] - 1, 0}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 				break;
// 			}
// 			else
// 			{
// 				que3.push({{cur.first[0], cur.first[1] - 1, 0}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 	}
// }

void sque1BFS()
{
	while (!sque1.empty())
	{
		// if (database.size() >= 524160) break;
		pair<array<int, 2>, string> cur = sque1.front();
		// cout << cur.second << endl;
		sque1.pop();

		std::unique_lock<std::mutex> lock(mtx);
		if (database.find(cur.second) == database.end())
		{
			database.insert({cur.second, cur.first[1]});
			lock.unlock();

			// 오른쪽
			if (cur.first[0] % 4 != 3)
			{
				sque1.push({{cur.first[0] + 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
			}
			// 왼쪽
			if (cur.first[0] % 4 != 0)
			{
				sque1.push({{cur.first[0] - 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
			}
			// 위
			if (cur.first[0] - 4 >= 0)
			{
				sque1.push({{cur.first[0] - 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
			}
			// 아래
			if (cur.first[0] + 4 < cur.second.length())
			{
				sque1.push({{cur.first[0] + 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
			}
		}
		// else
		// {
		// 	// 오른쪽
		// 	if (cur.first[0] % 4 != 3)
		// 	{
		// 		sque1.push({{cur.first[0] + 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
		// 	}
		// 	// 왼쪽
		// 	if (cur.first[0] % 4 != 0)
		// 	{
		// 		sque1.push({{cur.first[0] - 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
		// 	}
		// 	// 위
		// 	if (cur.first[0] - 4 >= 0)
		// 	{
		// 		sque1.push({{cur.first[0] - 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
		// 	}
		// 	// 아래
		// 	if (cur.first[0] + 4 < cur.second.length())
		// 	{
		// 		sque1.push({{cur.first[0] + 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
		// 	}
		// }
	}
}

void sque2BFS()
{
	while (!sque2.empty())
	{
		// if (database.size() >= 524160) break;
		pair<array<int, 2>, string> cur = sque2.front();
		sque2.pop();

		std::unique_lock<std::mutex> lock(mtx);
		if (database.find(cur.second) == database.end() || cur.first[1] < 10)
		{
			database.insert({cur.second, cur.first[1]});
			lock.unlock();

			// 오른쪽
			if (cur.first[0] % 4 != 3)
			{
				sque2.push({{cur.first[0] + 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
			}
			// 왼쪽
			if (cur.first[0] % 4 != 0)
			{
				sque2.push({{cur.first[0] - 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
			}
			// 위
			if (cur.first[0] - 4 >= 0)
			{
				sque2.push({{cur.first[0] - 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
			}
			// 아래
			if (cur.first[0] + 4 < cur.second.length())
			{
				sque2.push({{cur.first[0] + 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
			}
		}
		// else
		// {
		// 	// 오른쪽
		// 	if (cur.first[0] % 4 != 3)
		// 	{
		// 		sque2.push({{cur.first[0] + 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
		// 	}
		// 	// 왼쪽
		// 	if (cur.first[0] % 4 != 0)
		// 	{
		// 		sque2.push({{cur.first[0] - 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
		// 	}
		// 	// 위
		// 	if (cur.first[0] - 4 >= 0)
		// 	{
		// 		sque2.push({{cur.first[0] - 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
		// 	}
		// 	// 아래
		// 	if (cur.first[0] + 4 < cur.second.length())
		// 	{
		// 		sque2.push({{cur.first[0] + 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
		// 	}
		// }
	}
}

void sque3BFS()
{
	while (!sque3.empty())
	{
		// if (database.size() >= 524160) break;
		pair<array<int, 2>, string> cur = sque3.front();
		sque3.pop();

		std::unique_lock<std::mutex> lock(mtx);
		if (database.find(cur.second) == database.end() || cur.first[1] < 0)
		{
			database.insert({cur.second, cur.first[1]});
			lock.unlock();

			// 오른쪽
			if (cur.first[0] % 4 != 3)
			{
				sque3.push({{cur.first[0] + 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
			}
			// 왼쪽
			if (cur.first[0] % 4 != 0)
			{
				sque3.push({{cur.first[0] - 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
			}
			// 위
			if (cur.first[0] - 4 >= 0)
			{
				sque3.push({{cur.first[0] - 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
			}
			// 아래
			if (cur.first[0] + 4 < cur.second.length())
			{
				sque3.push({{cur.first[0] + 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
			}
		}
		// else
		// {
		// 	// 오른쪽
		// 	if (cur.first[0] % 4 != 3)
		// 	{
		// 		sque3.push({{cur.first[0] + 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 1, cur.first[0], cur.second)});
		// 	}
		// 	// 왼쪽
		// 	if (cur.first[0] % 4 != 0)
		// 	{
		// 		sque3.push({{cur.first[0] - 1, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 1, cur.first[0], cur.second)});
		// 	}
		// 	// 위
		// 	if (cur.first[0] - 4 >= 0)
		// 	{
		// 		sque3.push({{cur.first[0] - 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] - 4, cur.first[0], cur.second)});
		// 	}
		// 	// 아래
		// 	if (cur.first[0] + 4 < cur.second.length())
		// 	{
		// 		sque3.push({{cur.first[0] + 4, cur.first[1] + 1}, stringSwitchTable(cur.first[0] + 4, cur.first[0], cur.second)});
		// 	}
		// }
	}
}

// void que1BFS() // �κ� �������� ��ǥ���¿��� �־����鼭 ������ ��� ����� ���� Ž�� �� map�� ����
// {			   // ���ڸ� ã�� ������ bfs
// 	while (!que1.empty())
// 	{
// 		pair<array<int, 3>, array<array<int, 4>, 4>> cur = que1.front();
// 		que1.pop();
// 		// string parsedStr = parseToString(cur.second);
// 		string parsedStr;
// 		for (int i = 0; i < 4; i++)
// 		{
// 			for (int j = 0; j < 4; j++)
// 			{
// 				if (cur.second[i][j] > 0 && cur.second[i][j] < 16)
// 				{
// 					int number = cur.second[i][j];
// 					string cur = to_string(number);
// 					parsedStr += cur;
// 				}
// 				else if (cur.second[i][j] == 100)
// 				{
// 					parsedStr += '*';
// 				}
// 				else
// 				{
// 					parsedStr += '0';
// 				}
// 			}
// 		}

// 		// uint64_t key = 0;
// 		// for (const auto &row : cur.second)
// 		// {
// 		// 	for (int num : row)
// 		// 	{
// 		// 		key = (key << 4) | (num & 0xF);
// 		// 	}
// 		// }

// 		std::unique_lock<std::mutex> lock(mtx);
// 		if (database.find(parsedStr) == database.end())
// 		// if (intDataBase.find(key) == intDataBase.end())
// 		{
// 			database.insert({parsedStr, cur.first[2]});
// 			// intDataBase.insert({key, cur.first[2]});
// 			// �Ʒ��� ���� ���̺� ���� ����� ������ �ʿ���. visited�� �̿��ϴ°� ��������?
// 			// 0�� ����������
// 			// 0�̳� 100�� �ƴ� ���� ������ ������ database���� �񱳸� �����ؾ���.
// 			if (cur.first[0] + 1 < 4)
// 			{
// 				que1.push({{cur.first[0] + 1, cur.first[1], cur.first[2] + 1}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[0] - 1 >= 0)
// 			{
// 				que1.push({{cur.first[0] - 1, cur.first[1], cur.first[2] + 1}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[1] + 1 < 4)
// 			{
// 				que1.push({{cur.first[0], cur.first[1] + 1, cur.first[2] + 1}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[1] - 1 >= 0)
// 			{
// 				que1.push({{cur.first[0], cur.first[1] - 1, cur.first[2] + 1}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		lock.unlock();
// 	}
// }

// void que2BFS() // �κ� �������� ��ǥ���¿��� �־����鼭 ������ ��� ����� ���� Ž�� �� map�� ����
// {
// 	while (!que2.empty())
// 	{
// 		pair<array<int, 3>, array<array<int, 4>, 4>> cur = que2.front();
// 		que2.pop();
// 		string parsedStr;
// 		for (int i = 0; i < 4; i++)
// 		{
// 			for (int j = 0; j < 4; j++)
// 			{
// 				if (cur.second[i][j] > 0 && cur.second[i][j] < 16)
// 				{
// 					int number = cur.second[i][j];
// 					string cur = to_string(number);
// 					parsedStr += cur;
// 				}
// 				else if (cur.second[i][j] == 100)
// 				{
// 					parsedStr += '*';
// 				}
// 				else
// 				{
// 					parsedStr += '0';
// 				}
// 			}
// 		}
// 		// uint64_t key = 0;
// 		// for (const auto &row : cur.second)
// 		// {
// 		// 	for (int num : row)
// 		// 	{
// 		// 		key = (key << 4) | (num & 0xF);
// 		// 	}
// 		// }

// 		std::unique_lock<std::mutex> lock(mtx);
// 		if (database.find(parsedStr) == database.end())
// 		// if (intDataBase.find(key) == intDataBase.end())
// 		{
// 			database.insert({parsedStr, cur.first[2]});
// 			// intDataBase.insert({key, cur.first[2]});
// 			// �Ʒ��� ���� ���̺� ���� ����� ������ �ʿ���. visited�� �̿��ϴ°� ��������?
// 			// 0�� ����������
// 			// 0�̳� 100�� �ƴ� ���� ������ ������ database���� �񱳸� �����ؾ���.
// 			if (cur.first[0] + 1 < 4)
// 			{
// 				que2.push({{cur.first[0] + 1, cur.first[1], cur.first[2] + 1}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[0] - 1 >= 0)
// 			{
// 				que2.push({{cur.first[0] - 1, cur.first[1], cur.first[2] + 1}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[1] + 1 < 4)
// 			{
// 				que2.push({{cur.first[0], cur.first[1] + 1, cur.first[2] + 1}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[1] - 1 >= 0)
// 			{
// 				que2.push({{cur.first[0], cur.first[1] - 1, cur.first[2] + 1}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		lock.unlock();
// 	}
// }

// void que3BFS() // �κ� �������� ��ǥ���¿��� �־����鼭 ������ ��� ����� ���� Ž�� �� map�� ����
// {
// 	while (!que3.empty())
// 	{
// 		pair<array<int, 3>, array<array<int, 4>, 4>> cur = que3.front();
// 		que3.pop();
// 		string parsedStr;
// 		for (int i = 0; i < 4; i++)
// 		{
// 			for (int j = 0; j < 4; j++)
// 			{
// 				if (cur.second[i][j] > 0 && cur.second[i][j] < 16)
// 				{
// 					int number = cur.second[i][j];
// 					string cur = to_string(number);
// 					parsedStr += cur;
// 				}
// 				else if (cur.second[i][j] == 100)
// 				{
// 					parsedStr += '*';
// 				}
// 				else
// 				{
// 					parsedStr += '0';
// 				}
// 			}
// 		}

// 		// uint64_t key = 0;
// 		// for (const auto &row : cur.second)
// 		// {
// 		// 	for (int num : row)
// 		// 	{
// 		// 		key = (key << 4) | (num & 0xF);
// 		// 	}
// 		// }

// 		std::unique_lock<std::mutex> lock(mtx);
// 		if (database.find(parsedStr) == database.end())
// 		// if (intDataBase.find(key) == intDataBase.end())
// 		{
// 			database.insert({parsedStr, cur.first[2]});
// 			// intDataBase.insert({key, cur.first[2]});
// 			// �Ʒ��� ���� ���̺� ���� ����� ������ �ʿ���. visited�� �̿��ϴ°� ��������?
// 			// 0�� ����������
// 			// 0�̳� 100�� �ƴ� ���� ������ ������ database���� �񱳸� �����ؾ���.
// 			if (cur.first[0] + 1 < 4)
// 			{
// 				que3.push({{cur.first[0] + 1, cur.first[1], cur.first[2] + 1}, switchTable(cur.first[0] + 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[0] - 1 >= 0)
// 			{
// 				que3.push({{cur.first[0] - 1, cur.first[1], cur.first[2] + 1}, switchTable(cur.first[0] - 1, cur.first[1], cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[1] + 1 < 4)
// 			{
// 				que3.push({{cur.first[0], cur.first[1] + 1, cur.first[2] + 1}, switchTable(cur.first[0], cur.first[1] + 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 			if (cur.first[1] - 1 >= 0)
// 			{
// 				que3.push({{cur.first[0], cur.first[1] - 1, cur.first[2] + 1}, switchTable(cur.first[0], cur.first[1] - 1, cur.first[0], cur.first[1], cur.second)});
// 			}
// 		}
// 		lock.unlock();
// 	}
// }

// array<uint64_t, 3> convertOriginTo64bitInt(Node *arr)
// {
// 	uint64_t key1 = 0;
// 	uint64_t key2 = 0;
// 	uint64_t key3 = 0;
// 	for (const auto &row : arr->element)
// 	{
// 		for (int num : row)
// 		{
// 			if (num == 1 || num == 2 || num == 3 || num == 5 || num == 6 || num == 0)
// 			{
// 				key1 = (key1 << 4) | (num & 0xF);
// 			}
// 			else
// 			{
// 				num = 16;
// 				key1 = (key1 << 4) | (num & 0xF);
// 			}

// 			if (num == 4 || num == 7 || num == 8 || num == 9 || num == 10 || num == 0)
// 			{
// 				key2 = (key2 << 4) | (num & 0xF);
// 			}
// 			else
// 			{
// 				num = 16;
// 				key2 = (key2 << 4) | (num & 0xF);
// 			}

// 			if (num == 9 || num == 10 || num == 13 || num == 14 || num == 15 || num == 0)
// 			{
// 				key3 = (key3 << 4) | (num & 0xF);
// 			}
// 			else
// 			{
// 				num = 16;
// 				key3 = (key3 << 4) | (num & 0xF);
// 			}
// 		}
// 	}
// 	return {key1, key2, key3};
// }

array<string, 3> parseToStringforOriginArray(Node *tempNode)
{
	string result1;
	string result2;
	string result3;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if (tempNode->element[i][j] == 1 || tempNode->element[i][j] == 2 || tempNode->element[i][j] == 3 || tempNode->element[i][j] == 5 || tempNode->element[i][j] == 6)
			{
				string cur = to_string(tempNode->element[i][j]);
				result1 += cur;
			}
			else if (tempNode->element[i][j] == 0)
			{
				result1 += '*';
			}
			else
			{
				result1 += '*';
			}

			if (tempNode->element[i][j] == 4 || tempNode->element[i][j] == 7 || tempNode->element[i][j] == 8 || tempNode->element[i][j] == 11 || tempNode->element[i][j] == 12)
			{
				if (tempNode->element[i][j] == 11)
				{
					char cur = 'B';
					result2 += cur;
				}
				else if (tempNode->element[i][j] == 12)
				{
					char cur = 'C';
					result2 += cur;
				}
				else
				{
					string cur = to_string(tempNode->element[i][j]);
					result2 += cur;
				}
			}
			else if (tempNode->element[i][j] == 0)
			{
				result2 += '*';
			}
			else
			{
				result2 += '*';
			}

			if (tempNode->element[i][j] == 9 || tempNode->element[i][j] == 10 || tempNode->element[i][j] == 13 || tempNode->element[i][j] == 14 || tempNode->element[i][j] == 15)
			{
				if (tempNode->element[i][j] == 10)
				{
					char cur = 'A';
					result3 += cur;
				}
				else if (tempNode->element[i][j] == 13)
				{
					char cur = 'D';
					result3 += cur;
				}
				else if (tempNode->element[i][j] == 14)
				{
					char cur = 'E';
					result3 += cur;
				}
				else if (tempNode->element[i][j] == 15)
				{
					char cur = 'F';
					result3 += cur;
				}
				else
				{
					string cur = to_string(tempNode->element[i][j]);
					result3 += cur;
				}
			}
			else if (tempNode->element[i][j] == 0)
			{
				result3 += '*';
			}
			else
			{
				result3 += '*';
			}
		}
	}
	array<string, 3> total = {result1, result2, result3};
	return total;
}

///// ���Ϸ� ���� ���� �迭���� �Է� ���� /////
void Input(int ary[4][4])
{

	FILE *in;
	int temp;

	in = fopen("input.txt", "r"); // �Է� ���� �̸��� input.txt

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fscanf(in, "%d", &temp);
			IP[i][j] = temp;
		}
	}

	fclose(in);
}

float CalcFnValue(Node *node)
{
	int i, j, count = 0, temp_dist = 0, dist_sum = 0;
	float fnvalue;

	///////////////////////////////////////
	////// ���⿡ �Ʒ��� ��� ��ſ� ������ ������ �巡��� ������(g(n))�� �̿��Ͽ�
	////// f(n)�� ����ϴ� �˰������� �ۼ��ϵ��� �� !!!!!!!!!!!!!!
	////// ���� Ư���� �ľ��Ͽ� � �������� ����ϸ� ���信 ���� ����� �����ΰ��� �� �ľ��� �� �ֵ��� ������ ������ ��.
	///////////////////////////////////////

	// �� ��ġ�� ���� ���� ������ ���� ��� ���� ���� �巡 ���(h(n))���� ���
	// for(i=0;i<4;i++){
	// 	for(j=0;j<4;j++){
	// 		if(node->element[i][j] != SS[i][j]){
	// 			count++;
	// 		}
	// 	}
	// }
	array<string, 3> result = parseToStringforOriginArray(node);
	// array<uint64_t, 3> result = convertOriginTo64bitInt(node);
	// cout << database.at(result[0]) << ", " << database.at(result[1]) << ", " << database.at(result[2]) << "\n";
	fnvalue = (float)(database[result[0]] + database[result[1]] + database[result[2]] + node->depth);
	// fnvalue = (float)(intDataBase[result[0]] + intDataBase[result[1]] + intDataBase[result[2]] + node->depth);
	// �� �Լ��� �پ��� ���� ��
	// fnvalue = (float)(node->depth + count); // f(n) = e(n) + h(n)  ->  A* �˰�����
	//  fnvalue = (float)(node->depth + 2 * count); // f(n) = e(n) + h(n)  -> h(n)�� ������� ��ȭ
	//  fnvalue = (float)(2 * node->depth + count); // f(n) = e(n) + h(n)  -> e(n)�� ������� ��ȭ

	//  fnvalue = (float)(node->depth); // f(n) = e(n) -> BFS
	//  fnvalue = (float)(count); // f(n) = h(n) -> �ְ� �켱 Ž��

	return fnvalue;
}

///// �ʱ� ��Ʈ ��带 ������ �迭 ���·� �Է��ϰ� �� �����͸� NULL�� ����� �ʱ�ȭ �Լ� /////
void Init(Node *node, int array[4][4])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			node->element[i][j] = array[i][j];
		}
	}

	node->depth = 0;
	node->fnvalue = CalcFnValue(node); /// �ʱ� ���Լ����� ����
	node->unfold = 0;

	node->parent = NULL;

	for (int i = 0; i < 4; i++)
	{
		node->child[i] = NULL;
	}
}

///// �ڽ� ��带 ����� ���� �켱 �θ��� �迭���� �״�� �����ϰ� ������ �������� �ʱ�ȭ�ϴ� �Լ� /////
void CopyAndReset(Node *node, Node *temp)
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp->element[i][j] = node->element[i][j];
		}
	}

	temp->fnvalue = -1.0; /// �ʱ� ���Լ����� 0���� ���� ����
	temp->depth = 0;
	temp->unfold = 0;

	temp->parent = NULL;

	for (int i = 0; i < 4; i++)
	{
		temp->child[i] = NULL;
	}
}

///// ���� ����� �迭 ���°� ary[4][4]�� �־����� �迭 ���¿� �������� Ȯ���ؼ� ������ 1 ����, �ƴϸ� 0 ���� /////
int Same(Node *node1, int ary[4][4])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (node1->element[i][j] != ary[i][j])
			{
				return 0;
			}
		}
	}

	return 1; // ��ǥ ���(���信 ���������� �˸�) Ȯ�� �Ǵ� �ߺ��� ���ϱ� ���� ����
}

///// ���� �Ѱ����� �Ķ���� ����� �迭 ���¸� ȭ�鿡 ����ϴ� �Լ� /////
void PrintBoard(Node *node)
{

	printf("|---|---|---|---|\n");

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (node->element[y][x] == 0)
			{
				printf("|   ");
			}
			else
			{
				printf("|%3d", node->element[y][x]);
			}
		}
		printf("|\n");

		if (y != 3)
			printf("|---|---|---|---|\n");
	}

	printf("|---|---|---|---|\n");
}

///// �̹� ������ ��� ���� ���� �ߺ��� �ִ��� �˻�. �ߺ��Ǵ� ���� ������ 1 ����, ������ 0 ���� /////
int DuplicateAll(Node *node)
{

	int dup = 0;
	Leaf *trace;

	trace = Support;

	while (trace)
	{

		if (Same(node, trace->leaf->element))
		{
			dup = 1;
			break;
		}

		trace = trace->next;
	}

	return dup;
}

///// �ڽ� ����� �迭���� ���� ��ĭ�� ������ ������ �ϳ��� ��ȯ�ϱ� ���� �Լ� /////
void Swap(int *a, int *b)
{

	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

///// 0���� ǥ���Ǵ� ��ĭ�� �ϳ� �������� ���� ����(�ڽ�) ��带 ������ ������ŭ ���� �ڽ����� �����ϴ� �Լ� /////
///// �̹� ������ ��� ����� �Ź� ���ϸ鼭 �ߺ��� ���� ��쿡�� ������. /////
void MakeChildren(Node *node)
{

	int izero, jzero, i;
	Node *temp;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (node->element[i][j] == 0)
			{
				izero = i;
				jzero = j;
				break;
			}
		}
	}

	if ((izero == 1 || izero == 2) && (jzero == 1 || jzero == 2))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp); // �θ� �迭�� �״�� ����

		Swap(&temp->element[izero][jzero], &temp->element[izero - 1][jzero]); // ���� �ϳ��� �����̴� �� ó�� �� ���� ��ȯ

		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp); // �ߺ��� ����̸� �̹� �Ҵ��� �޸𸮸� ������
		}
		else
		{
			node->child[i] = temp;
			ChildNum++; // ��尡 ������ �� ���� ��� Ȯ����� ����
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero - 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero + 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero + 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((izero == 1 || izero == 2) && (jzero == 0))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero - 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero + 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero + 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((izero == 1 || izero == 2) && (jzero == 3))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero - 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero + 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero - 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((jzero == 1 || jzero == 2) && (izero == 0))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero - 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero + 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero + 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((jzero == 1 || jzero == 2) && (izero == 3))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero - 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero + 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero - 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((izero == 0) && (jzero == 0))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero + 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero + 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((izero == 0) && (jzero == 3))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero + 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero - 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((izero == 3) && (jzero == 0))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero - 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero + 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	if ((izero == 3) && (jzero == 3))
	{

		i = 0;

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero - 1][jzero]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}

		temp = (Node *)malloc(sizeof(Node));

		CopyAndReset(node, temp);

		Swap(&temp->element[izero][jzero], &temp->element[izero][jzero - 1]);
		temp->parent = node;

		if (DuplicateAll(temp))
		{
			free(temp);
		}
		else
		{
			node->child[i] = temp;
			ChildNum++;
			i++;
		}
	}

	for (i = 0; i < 4; i++)
	{

		if (node->child[i])
		{

			node->child[i]->depth = node->depth + 1; // ������ �ڽ� ������ ���̰��� �ϳ� ����

			node->child[i]->fnvalue = CalcFnValue(node->child[i]); // �� �Լ����� ���� ����Ͽ� ����
		}
	}

	node->unfold = 1;
}

///// ������ �ڽ� ������ Support ����Ʈ�� ��� �Ŵٴ� �Լ� /////
void StoreLeaf(Node *current)
{

	int i;
	Leaf *templeaf;

	for (i = 0; i < 4; i++)
	{

		if (current->child[i])
		{

			templeaf = (Leaf *)malloc(sizeof(Leaf)); // ���� ������ ������ ����Ű�� ���� ����Ʈ �޸� ����

			Last->next = templeaf;
			templeaf->leaf = current->child[i];
			templeaf->next = NULL;
			Last = Last->next;
		}
	}
}

///// best first Ž���� ���� �� ������ ��� �ĺ� ������ �򰡰��� ���Ͽ� ���� ����(����) ���� ������ ��带 ���� /////
///// ���õ� ��忡 ���� ������ �ּҰ� ���� /////
Node *ChooseBestNode(void)
{

	Leaf *trace, *best;
	Node *tempbest;
	float tempmin = 9999999.0;

	trace = Support->next;

	while (trace)
	{

		if ((trace->leaf->fnvalue < tempmin) && trace->leaf->unfold == 0)
		{
			best = trace;
			tempmin = trace->leaf->fnvalue;
			// �������� ���� ���(unfold == 0�� ���)�� �߿��� fnvalue�� ���� ���� ��带 ã��.
		}
		trace = trace->next;
	}

	tempbest = best->leaf;

	return tempbest; // ��� �ּ� ����
}

int main()
{
	squeInitializer();

	// sfindUntilNumber1();
	// sfindUntilNumber2();
	// sfindUntilNumber3();

	cout << "start"
		 << "\n";
	auto start_time = std::chrono::high_resolution_clock::now();

	thread thread1(sque1BFS);
	thread thread2(sque2BFS);
	thread thread3(sque3BFS);

	thread1.join();
	thread2.join();
	thread3.join();

	auto end_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
	std::cout << "Elapsed time: " << duration << " seconds" << std::endl;
	// future<void> result1 = std::async(launch::async, que1BFS);
	// future<void> result2 = std::async(launch::async, que2BFS);
	// future<void> result3 = std::async(launch::async, que3BFS);

	// result1.get();
	// result2.get();
	// result3.get();

	// que1BFS();
	// que2BFS();
	// que3BFS();

	cout << "complete" << endl;

	auto start_time2 = std::chrono::high_resolution_clock::now();

	int ch, done;
	Node *solution, *trace;

	Root = (Node *)malloc(sizeof(Node));	// �ʱ� ��Ʈ ��忡 �޸� �Ҵ�
	Support = (Leaf *)malloc(sizeof(Leaf)); // �ʱ� �ܼ� ���� ����Ʈ�� �޸� �Ҵ�

	Input(IP);		// ���� ���� �Է�
	Init(Root, IP); // ���� ���·� ��Ʈ ��� ����

	if (Same(Root, SS))
	{ // �ʱ� ������ ��� ���� ��쿡�� �ٷ� �ذ�� ����̹Ƿ� ���α׷� ����
		printf("Done!\n");
		return 0;
	}

	Current = Root; // Ȯ�� ����� ��带 ����Ű�� Current �����͸� ó������ ��Ʈ�� ����Ű�� ��

	Support->leaf = Root;
	Support->next = NULL;
	Last = Support;

	done = 0;

	PrintBoard(Current);											   // �ʱ� ���� �迭 ���
	printf("f(n) = %f  d = %d\n\n", Current->fnvalue, Current->depth); // �� ��忡 ���� �򰡰�, �����̰� ���

	do
	{

		//		PrintBoard(Current);		//�� �ܰ躰 ���� �迭 ���
		//		printf("f(n) = %f  d = %d\n\n", Current->fnvalue, Current->depth);	//�� ��忡 ���� �򰡰�, �����̰� ���

		MakeChildren(Current); // �ڽ� ��� ����

		for (ch = 0; ch < 4; ch++)
		{ // ������ �� �ִ� �ִ� �ڽļ��� 4���̹Ƿ� 4�� �ݺ�

			if (Current->child[ch])
			{ // ���� ������ �ڽĿ� ���ؼ���
				if (Same(Current->child[ch], SS))
				{ // ������ �ڽĵ� �߿� �ش��� �ִ��� ã��, ������ ǥ���ϰ� ���� ����
					solution = Current->child[ch];
					PrintBoard(solution);
					printf("f(n) = %f  d = %d\n", solution->fnvalue, solution->depth);
					// ������ �߰����� ���� ���Լ����� ���̰� ���
					printf("# of children : %d\n", ChildNum); // ������ ã�� ���� ������ ��� �ڽ� ������ ���� ���
					printf("Done!!!\n");
					auto end_time2 = std::chrono::high_resolution_clock::now();
					auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - start_time2).count();
					std::cout << "Elapsed time: " << duration2 << " milliseconds" << std::endl;
					getchar();
					done = 1; // ���� ã������ �ǹ�
					break;
				}
			}
		}

		if (done == 1)
		{ // �ش��� ã���� ��츦 �ǹ��ϰ� �� �� do �ݺ����� �����ϵ��� �Ѵ�.
			break;
		}

		StoreLeaf(Current); // ���� ���� ��� ������ Current�� �ڽĵ��� �ܼ� ���� ����Ʈ�� ����Ű�� ��.

		Current = ChooseBestNode(); // �ٽ� ���ο� ����Ʈ �ĺ� ��带 ����

		//		getchar();

	} while (1);

	trace = solution; // ������ �ذ�� ��� solution ��尡 �߰ߵ� ���� ��带 ����Ŵ. �̸� �̿��Ͽ� �������
					  // �������� �������� ��� ���� ���¸� ����ϱ� ����

	while (trace)
	{ // �������� ���带 ����ϴ� ��ƾ
		PrintBoard(trace);
		printf("f(n) = %f  d = %d\n\n", trace->fnvalue, trace->depth);
		trace = trace->parent;

		getchar();
	}

	printf("d = %d\n", solution->depth);	  // ��θ� ��� ����� �� ���������� �ٽ� �� �� �� ã�� ���� ����� ���̰� ���
	printf("# of children : %d\n", ChildNum); // �ٽ� �� �� �� ������ ��� �ڽ� ������ �� ���

	return 0;
}