/*
판의 크기
최소 : 5 X 5
최대 : 15 X 15
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#define MAXSIZE 15
#define MARK 1
#define UNMARK 0
#define WALL -1

using namespace std;

typedef struct Point
{
	int x, y;
}point;

point direction[8] = {
	{ -1, -1 },{ 0, -1 },{ 1, -1 },{ -1, 0 },
{ 1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 } };

int board[MAXSIZE][MAXSIZE], path[MAXSIZE][MAXSIZE];
int num = 1;

int knightTour(int m, int n, point pos, int counter, int num_wall)
{
	int i;
	point next;
	if (counter == m * n - num_wall)   //나이트투어 종료 조건 = 보드 판 size(m * n) - wall의 개수
		return 1;
	for (i = 0; i < 8; i++)
	{
		{
			next.x = pos.x + direction[i].x;
			next.y = pos.y + direction[i].y;
			if (next.x > 0 && next.x <= n && next.y > 0 && next.y <= m
				&& board[next.y][next.x] != MARK && board[next.y][next.x] != WALL)
			{
				board[next.y][next.x] = MARK;
				path[next.y][next.x] = counter + 1;
				if (knightTour(m, n, next, counter + 1, num_wall))
					return 1;
				board[next.y][next.x] = UNMARK;
			}
		}
	}
	return 0;
}

void printBoard(int board[][MAXSIZE], int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << board[i][j] << "  ";

		cout << endl;
	}
}

void printPath(int path[][MAXSIZE], int m, int n)
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << path[i][j] << "  ";

		cout << endl;
	}
}

int countNumOfWall(int board[][MAXSIZE], int m, int n)
{
	int cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++) {
			if (board[i][j] == WALL)
				cnt++;
		}
	}
	return cnt;
}

int main()
{
	srand((unsigned int) time (NULL));  //매번 프로그램을 실행할 때마다 난수 생성
	int i, j, m, n;
	int num_toSolve = 0;
	int tmp_x, tmp_y;
	point start;
	bool finish = 0;

	//판의 크기
	cout << "판의 크기를 입력하세요. 행 열 순서로 입력합니다.";
	cin >> m >> n; // m = 행, n = 열

	while (!finish) {
	//출발점
		start.y = rand() % m + 1;  //row = 1~n 사이의 난수
		start.x = rand() % n + 1;  //col = 1~m 사이의 난수

		cout << "시작점: " << start.y << " , " << start.x << endl;
		for (i = 1; i <= m; i++)   //보드판 초기화
			for (j = 1; j <= n; j++)
				board[i][j] = UNMARK;

	
		//보드판의 벽 생성
		int num_wall = m * n*0.4; //벽은 전체 보드판의 40%
		int tmp = 0;
		while (tmp < num_wall)
		{
			tmp_x = rand() % n + 1;
			tmp_y = rand() % m + 1;
			if (tmp_x == start.x || tmp_y == start.y)
				continue;
			else if (board[tmp_y][tmp_x] == WALL)
				continue;
			else
			{
				board[tmp_y][tmp_x] = WALL;
				path[tmp_y][tmp_x] = WALL;
				tmp++;
			}
		}

		//num_wall = countNumOfWall(board, m, n);
		cout << "num of wall : " << num_wall << endl;

		//보드판과 path판에 출발점 표시
		board[start.y][start.x] = MARK;
		path[start.y][start.x] = 1;

		printBoard(board, m, n);
		//knightTour(m, n, start, 1, num_wall);  

		if (knightTour(m, n, start, 1, num_wall))
		{
			cout << " ---- board  ---- " << endl;
			printBoard(board, m, n);
			finish = 1;
		}

		if (finish == false) {
			cout << "벽을 생성중입니다" << endl;
			continue;
		}

		cout << endl;
		cout << "---- path ---- " << endl;
		printPath(path, m, n);


		cout << endl;
		cout << " ---- final board ---- " << endl;

		int num_of_zero = m * n*0.4; //풀어야할 칸의 개수는 전체의 30%
		while (1)
		{
			if (num_toSolve == num_of_zero)
				break;
			start.y = rand() % m + 1;  //row = 1~m 사이의 난수
			start.x = rand() % n + 1;
			if (path[start.y][start.x] == 1 || path[start.y][start.x] == m * n)
				continue;
			else if (board[start.y][start.x] == WALL)
				continue;
			else
			{
				path[start.y][start.x] = 0;
				num_toSolve++;
			}
		}
		printPath(path, m, n);
	}

	// 판을 저장
	ofstream write;
	write.open("input.txt");

	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
			write << path[i][j] << "  ";

		write << endl;
	}


	return 0;
}