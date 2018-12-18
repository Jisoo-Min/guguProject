//4각형 모양은 결국 King's Tour 이다.
//통상 알고 있던 Knight's Tour 에서 이동가능한 방향을 King's Tour 대로 하면
//King's Tour 대로 작동한다.
//백트래킹 알고리즘을 사용할 경우
//모든 경우의 수를 측정하므로, 속도가 매우 느리다.
//이를 보완하기 위해 랜덤하게 이동한 후 0을 채우는 방식으로 구현하였다.
//모든 경우의 수를 파악하여 해결하는 것이 아닌, Hidato Puzzle의 문제 해결에 최적화된 알고리즘을 설계한다. 최소의 complexity를 가지는 솔루션을 구상 하고 이를 코드화 한다.

//6각형 모양은 King's Tour를 응용하여 이동 가능한 방향을 설정한다.
//예를 들어 한 변의 길이가 3인 육각형이라면 실제 2차원 배열은 9*5 사이즈의
//1 1 0 1 0 1 0 1 1
//1 0 1 0 1 0 1 0 1
//0 1 0 1 0 1 0 1 0
//1 0 1 0 1 0 1 0 1
//1 1 0 1 0 1 0 1 1
//배열 중 0에만 칠한다.
//King's Tour와 다른 점은 위, 아래로 가는 방향이 없으며 좌, 우로 움직일 시에는 1칸이 아닌 2칸으로 움직인다.
//Hexagonal Grid 를 2차원 배열로 표현하기 위해 작성하였다.

#include <iostream>
#include <ctime>
#include <algorithm>
#include <limits> 
#include <fstream>
#include <random>
using namespace std;
int direction_size = 6;

struct Direction
{
   //x변화량
   int dx;
   //y변화량
   int dy;
};

Direction *arrDirection;

class Hidato
{
   public:
   int **map;
   int width;
   int height;
   int GetZeroCount();
   void Generate(int x, int y, int val);
   void Print();
   void PrintAnswer(int row, int col);
   void PrintAnswer();
   void PrintQuestion(int row, int col);
   void FillEmpty();
   void Reset();
   private:
   //현재 위치와 방향을 받고 해당 방향으로 이동 가능한지 체크
   bool MoveCheck(int x, int y, Direction d)
   {
      //map을 벗어나면 False 리턴
      if((x + d.dx) >= width || (x+d.dx) < 0 || (y+d.dy) >= height || (y+d.dy) < 0)
         return false;
      //이동할 자리가 빈자리(0)가 아니라면
      if(map[y + d.dy][x+d.dx] != 0)
         return false;
      
      //이동 가능하므로 true 리턴
      return true;
   }
   
   bool FillMoveCheck(int x, int y, Direction d)
   {
      //map을 벗어나면 False 리턴
      if((x + d.dx) >= width || (x+d.dx) < 0 || (y+d.dy) >= height || (y+d.dy) < 0)
         return false;
      //이동할 자리가 있을 경우 True 리턴
      if(map[y + d.dy][x+d.dx] != 0 && map[y + d.dy][x+d.dx] <= width*height)
         return true;

      return false;
   }
   
   //Map에서 val 이상일 경우 1씩 더한다.
   void UpValue(int val)
   {
      for(int i = 0 ; i < height; i++)
      {
         for(int j = 0 ; j < width; j++)
         {
            if(map[i][j] >= val)
               map[i][j] +=1;
         }
      }
   }
};

//Hidato Map에서 0의 개수를 출력한다.
int Hidato::GetZeroCount()
{
   int cnt = 0;
   for(int i = 0 ; i < height; i++)
   {
      for(int j = 0 ; j < width; j++)
      {
         if(map[i][j] == 0)
            cnt++;
      }
   }
   return cnt;
}

//Hidato 맵 0으로 초기화
void Hidato::Reset()
{
   for(int i = 0 ; i < height ; i ++)
   {
      for(int j = 0 ;j < width; j++)
         map[i][j] = 0;
   }
}


//히다토 답 출력
void Hidato::PrintAnswer(int row, int col)
{
   ofstream os;
   os.open("answerInput.txt");
   os << row << " " << col << endl;

   for(int i = 0 ; i < height; i++)
   {
      for(int j = 0 ; j < width; j++)
      {
         if(map[i][j] <= width*height)\
         {
            printf(" %3d", map[i][j]);
            os << map[i][j]<<" ";
         }

         else
         {
            cout << " -1";
            os << " -1";
         }

      }
      cout << endl;
      os << endl;
   }

   os.close();
}

void Hidato::PrintQuestion(int row, int col)
{
   ofstream os;
   os.open("input.txt");
   os << row << " " << col << endl;

   for(int i = 0 ; i < height; i++)
   {
      for(int j = 0 ; j < width; j++)
      {
         if(map[i][j] <= width*height)
         {
            printf(" %3d", map[i][j]);
            os << map[i][j]<< " ";
         }

         else
         {
            cout << " -1";
            os << " -1";
         }

      }
      cout << endl;
      os << endl;
   }

   os.close();
}

void Hidato::PrintAnswer()
{
   for(int i = 0 ; i < height; i++)
   {
      for(int j = 0 ; j < width; j++)
      {
         if(map[i][j] <= width*height)
         {
            printf(" %3d", map[i][j]);
         }

         else
         {
            cout << " ";
         }

      }
      cout << endl;
   }

}
void Hidato::Generate(int x, int y, int val)
{
   //처음 시작일 경우
   if(val == 1)
   {
      map[y][x] = val++;
      Generate(x, y, val);
   }
   //처음 시작이 아닐 경우
   else
   {
      //현재 위치로부터 이동 가능한 방향 확인
      int dir[] = {0,0,0,0,0,0,0,0};
      int cnt = 0;
      for(int i = 0 ; i < direction_size ; i++)
      {
         bool result = MoveCheck(x, y, arrDirection[i]);
         //이동 가능하다면 이동 가능한 방향 리스트에 추가한다.
         if(result)
            dir[cnt++] = i;
      }
      //이동 방향이 없다면 종료한다.
      if(cnt == 0)
         return;
      //이동 방향이 한가지라면
      else if(cnt == 1)
      {
         Direction nextDirect = arrDirection[dir[0]];
         map[y + nextDirect.dy][x + nextDirect.dx] = val++;
         Generate(x + nextDirect.dx, y + nextDirect.dy, val);
      }
      //이동 방향이 두가지 이상이라면
      else
      {
         int direct = rand() % (cnt - 1);
         Direction nextDirect = arrDirection[dir[direct]];
         map[y + nextDirect.dy][x + nextDirect.dx] = val++;
         Generate(x + nextDirect.dx, y + nextDirect.dy, val);
      }
   }
}

//0으로 된 칸을 최대한 채운다.
void Hidato::FillEmpty()
{
   bool finish = false;
   for(int i = 0 ; i < height ; i++)
   {
      for(int j = 0 ; j < width; j++)
      {
         //0일 경우
         if(map[i][j] == 0)
         {
            if(finish)
            {
               finish = false;
               continue;
            }
            int dir[] = {0,0,0,0,0,0,0,0};
            int cnt = 0;
            for(int k = 0 ; k < direction_size ; k++)
            {
               bool result = FillMoveCheck(j, i, arrDirection[k]);
               //주변에 숫자가 있을 경우 방향 리스트에 추가한다.
               if(result)
                  dir[cnt++] = k;
            }
            
            //주변 숫자가 2개 이상이라면
            if(cnt > 1)
            {
               //방향 Array를 섞어서 문제의 난이도를 올려준다.
               random_shuffle(dir, dir + cnt);
               for(int start = 0; start < cnt; start++)
               {
                  if(finish)
                     break;
                  //start 방향의 숫자를 저장한다.
                  Direction next = arrDirection[dir[start]];
                  int value = map[i + next.dy][j + next.dx];
                  //제외한 칸이면 무시한다.
                  if(value >= 99999)
                  {
                     map[i][j] = -1;
                     break;
                  }
                  for(int k = 0 ; k < cnt; k++)
                  {
                     if(start == k)
                        continue;
                     Direction nextVal = arrDirection[dir[k]];
                     int valueNext = map[i + nextVal.dy][j + nextVal.dx];
                     //인접한 n, n+1을 찾았다면 0을 타고 길을 만든다
                     if(value + 1 == valueNext)
                     {
                        //n+1 이상의 수를 1씩 더한다.
                        UpValue(valueNext);
                        //0을 n+1로 바꿔주고
                        map[i][j] = valueNext;
                        finish = true;
                     }
                  }
               }
            }
         }
      }
   }
}



int main(void)
{
   int mode = 0;
   cout << "만들 모양을 입력해 주세요.\n사각형 히다토 : 1 \n 독특한 모양 히다토 : 2 \n육각형 히다토 : 3" << endl;
   cin >> mode;
   
   //사각형
   if(mode == 1)
   {
      direction_size = 8;
      //방향 8개 설정
      arrDirection = new Direction[8];
      //up
      Direction up;
      up.dx= 0; up.dy= -1;
      arrDirection[0] = up;
      //upright
      Direction upright;
      upright.dx= 1; upright.dy= -1;
      arrDirection[1] = upright;
      //right
      Direction right;
      right.dx= 1; right.dy= 0;
      arrDirection[2] = right;
      //downright
      Direction downright;
      downright.dx= 1; downright.dy= 1;
      arrDirection[3] = downright;
      //down
      Direction down;
      down.dx= 0; down.dy= 1;
      arrDirection[4] = down;
      //downleft
      Direction downleft;
      downleft.dx= -1; downleft.dy= 1;
      arrDirection[5] = downleft;
      //left
      Direction left;
      left.dx= -1; left.dy= 0;
      arrDirection[6] = left;
      //upleft
      Direction upleft;
      upleft.dx= -1; upleft.dy= -1;
      arrDirection[7] = upleft;

      //Random Seed값 설정
      srand((unsigned int)time(NULL));

      //맵 m x 사이즈 받기
      int m, n;
      int row;
      int col;
      cout << "Enter Size" << endl;
      cout << "Width : ";
      cin >> m;
      col = m;
      cout << "Height : ";
      cin >> n;
      row = n;
      //맵 메모리 할당하기
      int **map = new int*[n];
      for(int i = 0 ; i < n; i ++)
         map[i] = new int[m];

      //맵 0으로 초기화
      for(int i = 0; i < n ; i ++)
      {
         for(int j = 0;j < m; j++)
            map[i][j] = 0;
      }

      //원하는 맵 입력 받기
   
      cout << endl;


      //Hidato 생성
      Hidato *h;
      h = new Hidato();
      h->width = m;
      h->height = n;
      //0의 개수를 최대한 줄이기 위해 10번까지 만들어본다.
      for(int i = 0 ; i < 10; i++)
      {
         //사용자가 원하는 맵을 깊은 복사를 통해 새로 구현한다.
         int **newmap = new int*[n];
         for(int tmp = 0; tmp < n ; tmp++)
            newmap[tmp] = new int[m];

         for(int j = 0; j < n; j++)
         {
            for(int k = 0 ; k < m ; k++)
               newmap[j][k] = map[j][k];
         }
         h->map = newmap;

         int startX, startY;
         while(true)
         {
            startX = rand() % m;
            startY = rand() % n;
            //시작좌표가 가능한 곳이라면
            if(map[startY][startX] == 0)
               break;
         }
         //1부터 그리기 시작한다.
         h->Generate(startX, startY, 1);
         //다그린 후에 0을 최대한 없애기 위하여 숫자를 채운다.
         int zeroCnt = -1;
         while(h->GetZeroCount() != zeroCnt)
         {
            zeroCnt = h->GetZeroCount();
            h->FillEmpty();
         }
         //0의 개수가 0이라면 탈출한다.
         if(zeroCnt == 0)
         {
            cout << "출제 완료!" << endl;
            break;
         }
      }
      //최대한 채운 경우 답을 출력한다.
      h->PrintAnswer(row, col);

      int maxAnswer = row * col * 0.5;
      int cnt = 0;
      for(int i = 0; i < row; i++)
      {
         for(int j = 0; j < col; j++)
         {
            int randNum = (rand()%3 + 1) % 2;
            //cout << "rand" << " " << randNum << endl;
            if(randNum == 0)
            {
               h->map[i][j] = 0;
            }
            if(cnt > maxAnswer)
               break;
            if(map[i][j] == -1 || map[i][j] == 99999)
               continue;
            cnt++;
         }
      }
      
      h->PrintQuestion(row, col);

      cout << endl <<  "0의 개수 : " << h->GetZeroCount() << endl;
   }
   if(mode == 2)
   {
      direction_size = 8;
      //방향 8개 설정
      arrDirection = new Direction[8];
      //up
      Direction up;
      up.dx= 0; up.dy= -1;
      arrDirection[0] = up;
      //upright
      Direction upright;
      upright.dx= 1; upright.dy= -1;
      arrDirection[1] = upright;
      //right
      Direction right;
      right.dx= 1; right.dy= 0;
      arrDirection[2] = right;
      //downright
      Direction downright;
      downright.dx= 1; downright.dy= 1;
      arrDirection[3] = downright;
      //down
      Direction down;
      down.dx= 0; down.dy= 1;
      arrDirection[4] = down;
      //downleft
      Direction downleft;
      downleft.dx= -1; downleft.dy= 1;
      arrDirection[5] = downleft;
      //left
      Direction left;
      left.dx= -1; left.dy= 0;
      arrDirection[6] = left;
      //upleft
      Direction upleft;
      upleft.dx= -1; upleft.dy= -1;
      arrDirection[7] = upleft;

      //Random Seed값 설정
      srand((unsigned int)time(NULL));

      //맵 m x 사이즈 받기
      int m, n;
      int row;
      int col;
      cout << "Enter Size" << endl;
      cout << "Width : ";
      cin >> m;
      col = m;
      cout << "Height : ";
      cin >> n;
      row = n;
      //맵 메모리 할당하기
      int **map = new int*[n];
      for(int i = 0 ; i < n; i ++)
         map[i] = new int[m];

      //맵 0으로 초기화
      for(int i = 0; i < n ; i ++)
      {
         for(int j = 0;j < m; j++)
            map[i][j] = 0;
      }

      //원하는 맵 입력 받기
      cout << "원하는 퍼즐모양 번호 입력하세요 : 1 또는 2" <<endl;
      int puzzleNum = 0;
      cin >> puzzleNum;

      if(puzzleNum == 1)
      {
         //첫째줄 볼록하게 만들기 
         for(int i = 0; i < col ; i = i+2)
         {map[0][i] = 99999;}
         //마지막줄 볼록하게 만들기
         for(int i = 0; i < col ; i = i+2)
         {map[row-1][i] = 99999;}
         //제일 왼쪽 볼록하게 만들기
         for(int i = 0; i < row; i = i+2)
         {map[i][0] = 99999;}
         //제일 오른쪽 볼록하게 만들기
         for(int i = 1; i < row; i = i+2)
         {map[i][col-1] = 99999;}
         cout << endl;
      }else if(puzzleNum == 2)
      {
         for(int i = row*0.4; i < row - row*0.4 ; i++)
         {
            for(int j = col*0.4; j < col - col*0.4; j++)
            {
               map[i][j]= 99999;
            }
         }
      }


      //Hidato 생성
      Hidato *h;
      h = new Hidato();
      h->width = m;
      h->height = n;
      //0의 개수를 최대한 줄이기 위해 10번까지 만들어본다.
      for(int i = 0 ; i < 10; i++)
      {
         //사용자가 원하는 맵을 깊은 복사를 통해 새로 구현한다.
         int **newmap = new int*[n];
         for(int tmp = 0; tmp < n ; tmp++)
            newmap[tmp] = new int[m];

         for(int j = 0; j < n; j++)
         {
            for(int k = 0 ; k < m ; k++)
               newmap[j][k] = map[j][k];
         }
         h->map = newmap;

         int startX, startY;




         while(true)
         {
            startX = rand() % m;
            startY = rand() % n;
            //시작좌표가 가능한 곳이라면
            if(map[startY][startX] == 0)
               break;
         }
         //1부터 그리기 시작한다.
         h->Generate(startX, startY, 1);
         //다그린 후에 0을 최대한 없애기 위하여 숫자를 채운다.
         int zeroCnt = -1;
         while(h->GetZeroCount() != zeroCnt)
         {
            zeroCnt = h->GetZeroCount();
            h->FillEmpty();
         }
         //0의 개수가 0이라면 탈출한다.
         if(zeroCnt == 0)
         {
            cout << "출제 완료!" << endl;
            break;
         }
      }
      //최대한 채운 경우 답을 출력한다.
      h->PrintAnswer(row, col);


      int maxAnswer = row * col * 0.3;
      int cnt = 0;
      for(int i = 0; i < row; i++)
      {
         for(int j = 0; j < col; j++)
         {
            int randNum = (rand()%3 + 1) % 2;
            if((h->map[i][j] == -1) || (h->map[i][j] == 99999) || (map[i][j]== -1) || (map[i][j] == 99999))
            {
               h->map[i][j] = -1;
               map[i][j] = -1;
            }
            else if(randNum == 0)
            {
               h->map[i][j] = 0;
               map[i][j] = 0;
               cnt++;
            }
            if(cnt > maxAnswer)
               break;
         }
      }
      cout << endl;
      h->PrintQuestion(row, col);

      cout << endl <<  "0의 개수 : " << h->GetZeroCount() << endl;
   }
   else if(mode == 3)
   {
      direction_size = 6;
      //방향 6개 설정
      //6각형 모양의 경우 상, 하는 없고 좌 우의 경우 2칸씩이다.
      arrDirection = new Direction[6];
      //upright
      Direction upright;
      upright.dx= 1; upright.dy= -1;
      arrDirection[0] = upright;
      //right
      Direction right;
      right.dx= 2; right.dy= 0;
      arrDirection[1] = right;
      //downright
      Direction downright;
      downright.dx= 1; downright.dy= 1;
      arrDirection[2] = downright;
      //downleft
      Direction downleft;
      downleft.dx= -1; downleft.dy= 1;
      arrDirection[3] = downleft;
      //left
      Direction left;
      left.dx= -2; left.dy= 0;
      arrDirection[4] = left;
      //upleft
      Direction upleft;
      upleft.dx= -1; upleft.dy= -1;
      arrDirection[5] = upleft;
      //Random Seed값 설정
      srand((unsigned int)time(NULL));

      //맵 m x 사이즈 받기
      int size;
      cout << "Enter length of one side of hexagon" << endl;
      cin >> size;

      int m = 1 + 4*(size - 1);
      int n = 1 + 2*(size - 1);


      //맵 메모리 할당하기
      int **map = new int*[n];
      for(int i = 0 ; i < n; i ++)
         map[i] = new int[m];

      //Hexagonal Map Initialize
      for(int i = 0; i < n ; i ++)
      {
         for(int j = 0; j < m; j++)
         {
            //가운데보다 위 라인이면
            if(i < size-1 )
            {
               //공백처리함.
               if( j + i < (size-1) )
                  map[i][j] = 99999;
               else if( j > m - size + i)
                  map[i][j] = 99999;
               else if( j >= size - i - 1)
               {
                  //홀수 사이즈라면
                  if(size % 2 == 1)
                  {
                     if(j % 2 != i % 2)
                        map[i][j] = 99999;
                     else
                        map[i][j] = 0;
                  }
                  else
                  {
                     if(j % 2 != i % 2)
                        map[i][j] = 0;
                     else
                        map[i][j] = 99999;
                  }
               }
            }
            //가운데 라인이면
            else if( i == size - 1)
            {
               if(j % 2)
                  map[i][j] = 99999;
               else
                  map[i][j] = 0;
            }
            //그 이외의 라인이면 위에라인 복사하기
            else
            {
               map[i][j] = map[n - i - 1][j];
            }
         }
      }

      int num = 0;
      for(int i = 0 ; i < n; i++)
      {
         for(int j = 0 ; j < m; j++)
         {
            if(map[i][j] == 0)
               map[i][j] = ++num;
            if(map[i][j] <= m*n)
               printf("%3d", map[i][j]);
            else
               cout << " ";
         }
         cout << endl;
      }

      cout << endl;

      int deleteVal = 0;
      //지울 번호 고르기
      while(true)
      {
         cout << "Delete number. -1 to exit." << endl;
         cin.ignore(100,'\n');
         cin >> deleteVal;
         if(deleteVal == -1)
            break;
         for(int i = 0 ; i < n; i++)
         {
            for(int j = 0 ; j < m; j++)
            {
               if(map[i][j] == deleteVal)
                  map[i][j] = 99999;
            }
         }   
      }

      for(int i = 0 ; i < n; i++)
      {
         for(int j = 0 ; j < m; j++)
         {         
            if(map[i][j] != 99999)
               map[i][j] = 0;
         }
      }   

      //Hidato 생성
      Hidato *h;
      h = new Hidato();
      h->width = m;
      h->height = n;
      //0의 개수를 최대한 줄이기 위해 10번까지 만들어본다.
      for(int i = 0 ; i < 10; i++)
      {
         //사용자가 원하는 맵을 깊은 복사를 통해 새로 구현한다.
         int **newmap = new int*[n];
         for(int tmp = 0; tmp < n ; tmp++)
            newmap[tmp] = new int[m];

         for(int j = 0; j < n; j++)
         {
            for(int k = 0 ; k < m ; k++)
               newmap[j][k] = map[j][k];
         }
         h->map = newmap;
         int startX, startY;
         while(true)
         {
            startX = rand() % m;
            startY = rand() % n;
            //시작좌표가 가능한 곳이라면
            if(map[startY][startX] == 0)
               break;
         }
         //1부터 그리기 시작한다.
         h->Generate(startX, startY, 1);
         //다그린 후에 0을 최대한 없애기 위하여 숫자를 채운다.
         int zeroCnt = -1;
         while(h->GetZeroCount() != zeroCnt)
         {
            zeroCnt = h->GetZeroCount();
            h->FillEmpty();
         }
         //0의 개수가 0이라면 탈출한다.
         if(zeroCnt == 0)
         {
            cout << "출제 완료!" << endl;
            break;
         }
      }
      //최대한 채운 경우 답을 출력한다.
      h->PrintAnswer();
      cout << endl <<  "0의 개수 : " << h->GetZeroCount() << endl;
   }
   
}