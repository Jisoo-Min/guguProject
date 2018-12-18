#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stdio.h>

using namespace std;

int wid, hei;     // puzzle board size : width, height
int board[15][15];
int number[225]={0, };
int idx = 0;

// ��ǥ�� ��� ����ü : ��ǥ�� 2���� �迭���� ���� ���� i, j�� ǥ���Ѵ�.
struct Point{
  int i, j;
};

/*����ü �迭 ����, �ʱ�ȭ
  m_arr = ���� ������ ��ġ�� Ž���� �� ���� ���� ������ ��Ÿ���� ��ǥ�� ��� ����(move array) */
struct Point m_arr[8] ={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
struct Point start;

int puzzle(struct Point p, int num, int &next){
  //cout << endl << "Ž�� ��ǥ[i][j] :\t" << p.i << "\t" << p.j << "\tnumber �ε��� :\t" << next << endl;

  /* �Է����� ���� ������ ���ں��� ũ�� : ���� ��
     ä�� �� �ִ� �����ε� ���ڰ� �̹� input���� �����ǿ� �ִ� : �ٸ� �� Ž��
     ���� �ƴ� �ڸ��� ä����� �ߴµ�(������ �κ�) �̹� �ٸ� ���ڰ� �ִ� : �ٸ� �� Ž�� */
  if (num >number[idx-1]){
    //cout << "���� ���� :\t" << number[idx-1] << endl;
    return true;
  }
  // ���̸� �н�(������ �κ�)
  if (board[p.i][p.j]==-1){
    return false;
  }
  if (board[p.i][p.j] == 0 && number[next] == num){
    if(num!=1){
      //cout << "�ٸ� �ڸ��� �̹� num�� �����Ѵ�. num :\t" << num << endl;
      return false;
    }
  }
  if (board[p.i][p.j] != 0 && board[p.i][p.j] != -1 && board[p.i][p.j] != num){
    //cout << "�ٸ� ���ڰ� �̹� ä���� ����. ä����� ���� :\t" << num << " �����ǿ� �ִ� ���� :\t" << board[p.i][p.j] << endl;
    return false;
  }

  int back = 0;

  // num�� �������� �ڸ��� �̹� num�� ����
  if (board[p.i][p.j] == number[next] && number[next]==num){
    //cout << "�̹� num�� �ڸ��� ����!\t" << endl;
    next ++;
    back = num;
  }

  // num�� ä����� �ڸ��� �ִ´�.
  //cout << "Ž���ϴ� �ڸ��� �������� ���� ����!\t" << num << endl;
  board[p.i][p.j] = num;

  // ���� ������ �ڸ��� Ž��
  for (int i = 0; i < 8; i++){
    struct Point temp;
    temp.i = p.i + m_arr[i].i;
    temp.j = p.j + m_arr[i].j;
    //���⼭ p ��ǥ�� �迭 ������ �վ���Ѵ�. �װ� Ȯ���ϱ�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (������ �κ�)
    if (temp.i>=0 && temp.i<hei && temp.j >=0 && temp.j < wid){
      if (puzzle(temp, num+1, next)){
        return true;
      }
    }
  }

  // ����� �Ѿ���� ���� �� for������ �����°�(true) ������ ����� ������ ��
  //cout << "fail...." << endl;
  board[p.i][p.j] = back;
  return false;
}

int main(){

  // �׽�Ʈ ���̽� �� �Է�
  int test;
  cin >> test;

  // �׽�Ʈ ���̽� ����ŭ �ݺ�
  for (int i=0; i<test; i++){
    int next = 0;
    // puzzle size
    cin >> hei >> wid;

    // puzzle board ä���
    for (int i = 0; i < hei; i++){
      for (int j = 0; j < wid; j++){
        cin >> board[i][j];
        /* ���� ��ĭ�� �ƴ� ���ڶ�� �迭�� ���� ����
           �� �� 1�� �������̱⶧���� ���� ��ǥ ���� */
        if (board[i][j] != -1 && board[i][j] != 0){
          number[idx++] = board[i][j];
          if (board[i][j]==1){
            start.i = i;
            start.j = j;
          }
        }
      }
    }

    // 1�� ��ġ
    cout << "start : " << start.i << "\t" << start.j << endl;

    sort(number, number+idx);
    for (int i = 0; i < idx; i++){
      cout << number[i] << "\t";
    }
    cout << endl;

    // ���� Ǭ��
    puzzle(start, 1, next);

    // ���
    cout << "finish!" << endl;
    for (int i = 0; i < hei; i++){
      for (int j = 0; j < wid; j++){
        cout << board[i][j] << "\t";
      }
      cout << endl;
    }
  }
}



/* input
0 33 35 0 0 -1 -1 -1
0 0 24 22 0 -1 -1 -1
0 0 0 21 0 0 -1 -1
0 26 0 13 40 11 -1 -1
27 0 0 0 9 0 1 -1
-1 -1 0 0 18 0 0 -1
-1 -1 -1 -1 0 7 0 0
-1 -1 -1 -1 -1 -1 5 0
*/

/* output
 32 33 35 36 37
 31 34 24 22 38
 30 25 23 21 12 39
 29 26 20 13 40 11
 27 28 14 19  9 10  1
       15 16 18  8  2
             17  7  6  3
                    5  4
*/

/* input
1 0 0 0
0 0 0 5
9 0 0 0
0 0 0 16


output
1 2 3 4
8 7 6 5
9 10 11 12
16 15 14 13 */