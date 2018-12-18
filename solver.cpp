#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stdio.h>

using namespace std;

int wid, hei;     // puzzle board size : width, height
int board[15][15];
int number[225]={0, };
int idx = 0;

// 좌표를 담는 구조체 : 좌표는 2차원 배열에서 보기 쉽게 i, j로 표현한다.
struct Point{
  int i, j;
};

/*구조체 배열 선언, 초기화
  m_arr = 다음 숫자의 위치를 탐색할 때 어디로 갈지 방향을 나타내는 좌표를 담고 있음(move array) */
struct Point m_arr[8] ={{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
struct Point start;

int puzzle(struct Point p, int num, int &next){
  //cout << endl << "탐색 좌표[i][j] :\t" << p.i << "\t" << p.j << "\tnumber 인덱스 :\t" << next << endl;

  /* 입력으로 받은 마지막 숫자보다 크다 : 퍼즐 끝
     채울 수 있는 공간인데 숫자가 이미 input으로 퍼즐판에 있다 : 다른 곳 탐색
     벽이 아닌 자리에 채우려고 했는데(수정한 부분) 이미 다른 숫자가 있다 : 다른 곳 탐색 */
  if (num >number[idx-1]){
    //cout << "게임 종료 :\t" << number[idx-1] << endl;
    return true;
  }
  // 벽이면 패스(수정한 부분)
  if (board[p.i][p.j]==-1){
    return false;
  }
  if (board[p.i][p.j] == 0 && number[next] == num){
    if(num!=1){
      //cout << "다른 자리에 이미 num이 존재한다. num :\t" << num << endl;
      return false;
    }
  }
  if (board[p.i][p.j] != 0 && board[p.i][p.j] != -1 && board[p.i][p.j] != num){
    //cout << "다른 숫자가 이미 채워져 있음. 채우려는 숫자 :\t" << num << " 퍼즐판에 있는 숫자 :\t" << board[p.i][p.j] << endl;
    return false;
  }

  int back = 0;

  // num을 넣으려는 자리에 이미 num이 있음
  if (board[p.i][p.j] == number[next] && number[next]==num){
    //cout << "이미 num이 자리에 있음!\t" << endl;
    next ++;
    back = num;
  }

  // num을 채우려던 자리에 넣는다.
  //cout << "탐색하던 자리에 넣으려는 숫자 저장!\t" << num << endl;
  board[p.i][p.j] = num;

  // 다음 숫자의 자리를 탐색
  for (int i = 0; i < 8; i++){
    struct Point temp;
    temp.i = p.i + m_arr[i].i;
    temp.j = p.j + m_arr[i].j;
    //여기서 p 좌표가 배열 범위에 잇어야한다. 그거 확인하기!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! (수정한 부분)
    if (temp.i>=0 && temp.i<hei && temp.j >=0 && temp.j < wid){
      if (puzzle(temp, num+1, next)){
        return true;
      }
    }
  }

  // 여기로 넘어오기 전에 위 for문에서 끝나는게(true) 게임이 제대로 끝나는 것
  //cout << "fail...." << endl;
  board[p.i][p.j] = back;
  return false;
}

int main(){

  // 테스트 케이스 수 입력
  int test;
  cin >> test;

  // 테스트 케이스 수만큼 반복
  for (int i=0; i<test; i++){
    int next = 0;
    // puzzle size
    cin >> hei >> wid;

    // puzzle board 채우기
    for (int i = 0; i < hei; i++){
      for (int j = 0; j < wid; j++){
        cin >> board[i][j];
        /* 벽과 빈칸이 아닌 숫자라면 배열에 따로 저장
           그 중 1은 시작점이기때문에 따로 좌표 저장 */
        if (board[i][j] != -1 && board[i][j] != 0){
          number[idx++] = board[i][j];
          if (board[i][j]==1){
            start.i = i;
            start.j = j;
          }
        }
      }
    }

    // 1의 위치
    cout << "start : " << start.i << "\t" << start.j << endl;

    sort(number, number+idx);
    for (int i = 0; i < idx; i++){
      cout << number[i] << "\t";
    }
    cout << endl;

    // 퍼즐 푼다
    puzzle(start, 1, next);

    // 출력
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