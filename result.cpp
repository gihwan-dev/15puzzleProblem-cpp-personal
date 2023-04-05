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

unordered_map<string, int> database1;
unordered_map<string, int> database2;
unordered_map<string, int> database3;

string spd1 = "123*56**********";
string spd2 = "***4**78**BC****";
string spd3 = "********9A**DEF*";

queue<pair<array<int, 2>, string>> sque1; // 0의 위치와 bfs count값 그리고 patterdatabase 문자열 값을 담을 큐
queue<pair<array<int, 2>, string>> sque2;
queue<pair<array<int, 2>, string>> sque3;

// 문자열은 0 ~ 15의 값을 가진다.

string stringSwitchTable(int curI, int prevI, string curString)
{
	char temp = curString[curI];
	curString[curI] = curString[prevI];
	curString[prevI] = temp;
	// cout << "curString : " << curString << endl;
	return curString;
}

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

void sque1BFS()
{
	while (!sque1.empty())
	{
		// if (database.size() >= 524160) break;
		pair<array<int, 2>, string> cur = sque1.front();
		// cout << cur.second << endl;
		sque1.pop();

		// std::unique_lock<std::mutex> lock(mtx);
		if (database1.find(cur.second) == database1.end())
		{
			database1.insert({cur.second, cur.first[1]});
			// lock.unlock();

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
	}
}

void sque2BFS()
{
	while (!sque2.empty())
	{
		// if (database.size() >= 524160) break;
		pair<array<int, 2>, string> cur = sque2.front();
		sque2.pop();

		// std::unique_lock<std::mutex> lock(mtx);
		if (database2.find(cur.second) == database2.end() || cur.first[1] < 10)
		{
			database2.insert({cur.second, cur.first[1]});
			// lock.unlock();

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
	}
}

void sque3BFS()
{
	while (!sque3.empty())
	{
		// if (database.size() >= 524160) break;
		pair<array<int, 2>, string> cur = sque3.front();
		sque3.pop();

		// std::unique_lock<std::mutex> lock(mtx);
		if (database3.find(cur.second) == database3.end() || cur.first[1] < 0)
		{
			database3.insert({cur.second, cur.first[1]});
			// lock.unlock();

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
	}
}

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

int main() {
	squeInitializer();

	sque1BFS;
	sque2BFS;
	sque3BFS;
}