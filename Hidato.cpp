/*
���� ũ��
�ּ� : 5 X 5
�ִ� : 15 X 15
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
	if (counter == m * n - num_wall)   //����Ʈ���� ���� ���� = ���� �� size(m * n) - wall�� ����
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
	srand((unsigned int) time (NULL));  //�Ź� ���α׷��� ������ ������ ���� ����
	int i, j, m, n;
	int num_toSolve = 0;
	int tmp_x, tmp_y;
	point start;
	bool finish = 0;

	//���� ũ��
	cout << "���� ũ�⸦ �Է��ϼ���. �� �� ������ �Է��մϴ�.";
	cin >> m >> n; // m = ��, n = ��

	while (!finish) {
	//�����
		start.y = rand() % m + 1;  //row = 1~n ������ ����
		start.x = rand() % n + 1;  //col = 1~m ������ ����

		cout << "������: " << start.y << " , " << start.x << endl;
		for (i = 1; i <= m; i++)   //������ �ʱ�ȭ
			for (j = 1; j <= n; j++)
				board[i][j] = UNMARK;

	
		//�������� �� ����
		int num_wall = m * n*0.4; //���� ��ü �������� 40%
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

		//�����ǰ� path�ǿ� ����� ǥ��
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
			cout << "���� �������Դϴ�" << endl;
			continue;
		}

		cout << endl;
		cout << "---- path ---- " << endl;
		printPath(path, m, n);


		cout << endl;
		cout << " ---- final board ---- " << endl;

		int num_of_zero = m * n*0.4; //Ǯ����� ĭ�� ������ ��ü�� 30%
		while (1)
		{
			if (num_toSolve == num_of_zero)
				break;
			start.y = rand() % m + 1;  //row = 1~m ������ ����
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

	// ���� ����
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