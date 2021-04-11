/*
**********  Seventh task on C++ course                                       ****
**********  Filename >main.cpp                                               ****
**********  IDE > QT Creator 4.13.2||CodeBlocks 20.03 + GCC 10.2.0           ****
**********  Created by > "~ORDA~" , Anton Bondarenko                         ****
**********  Date 08.04.2021                                                  ****
*/



//Запрограммировать игру крестики нолики на поле 3х3. Прислать архив всего проекта или ссылку на гит репозиторий.
//Для джуниоров: не обязательно делать крутой искусственный интеллект в игре. Но у вас должны корректно работать все основные моменты в игре, как например и главный цикл игры в main.
//Челендж для опытных и продвинутых: сделать решение на поле 4х4 или 5х5 или на динамическом поле, размер которого ввел пользователь.
//Также можно запросить у пользователя количество фигур необходимое для выигрыша, 3-5.

#include "main.h"
#include <random>
#include <stdlib.h>
#include <chrono>
using namespace std;
enum Cell {EMPTY='_',CROSS='X',ZERO='O'};//EMPTY,FIRST_PL,SECOND_PL

enum Progress{IN_PROGRESS, WON_1ST_PL, WON_2_PL,DRAW};

struct Coord
  {
    size_t x;
    size_t y;
   };

struct Game
{
    Cell **pField;
    Cell human;    //1ST_PL in future
    Cell ai;       //2ND_PL in future
    bool humanFirst;
    size_t turn;
    Progress progress;
    const size_t size=3;
};
void myClear()
{
system("clear");
}

int32_t getRandomNum(int32_t min, int32_t max)
{
const static auto seed = chrono::system_clock::now().time_since_epoch().count();
static mt19937_64 generator(seed);
uniform_int_distribution<int32_t> dis(min, max);
return dis(generator);
}
void initGame (Game &g)
{

    g.pField=new Cell*[g.size];
    for (size_t i=0; i<g.size; i++)
    g.pField[i]=new Cell[g.size];
    for (size_t y=0; y<g.size; y++)
    {
        for(size_t x=0; x<g.size; x++)
        {
            g.pField[y][x]=EMPTY;
        }

    }

    g.progress=IN_PROGRESS;
    if(getRandomNum(0,1000)>500)// if(getRandomNum(0,100)>500)
      {
        g.human=CROSS;
        g.ai=ZERO;
        g.humanFirst=true;
        g.turn=0;
       }
    else
    {
        g.human=ZERO;
        g.ai=CROSS;
        g.humanFirst=false;
        g.turn=1;
    }
}

void deinitGame(Game& g)
{
    for(size_t i=0;i<g.size; i++)
    {
        delete[] g.pField[i];
    }
    g.pField=nullptr;
}
void drawField(Game& g)
{
    cout <<"   ";
    for(size_t x=0; x<g.size; x++)
    {
      cout <<x+1<<"   ";
    }
     cout << endl;
    for (size_t y=0; y<g.size; y++)
    {
        cout <<y+1<<"| ";
        for(size_t x=0; x<g.size; x++)
        {
           cout<< (char)g.pField[y][x]<<" ";
        cout <<"| ";
        }
       cout << endl;
    }
    cout<< endl<<"HUMAN: "<<(char)g.human<<endl<<"AI: "<<(char)g.ai<<endl;
}
Coord getCoordHuman(Game& g )
{
    Coord c = { 0 ,0 };
    do {
        cout<<"Enter x coord: ";
        cin>>c.x;
        cout<<"Enter Y coord: ";
        cin>>c.y;
    }while(c.x>g.size||c.y>g.size||g.pField[c.y-1][c.x-1]!=EMPTY);
    c.x--;
    c.y--;
    return{c.x,c.y};
}

Coord getCoordAI(Game& g )
{

  if(g.pField[1][1]==EMPTY)
  {
      return {1,1};
  }
  if(g.pField[0][0]==EMPTY)
  {
      return {0,0};
  }
  if(g.pField[0][2]==EMPTY)
  {
      return {2,0};
  }
  if(g.pField[2][0]==EMPTY)
  {
      return {0,2};
  }
  if(g.pField[2][2]==EMPTY)
  {
    return {2,2};
  }
// углы закончились пошли строки
  if(g.pField[0][1]==EMPTY)
  {
      return {1,0};
  }
  if(g.pField[1][0]==EMPTY)
  {
      return {0,1};
  }
  if(g.pField[1][2]==EMPTY)
  {
      return {2,1};
  }
  if(g.pField[2][1]==EMPTY)
  {
      return {1,2};
  }

}

Progress isWon(const Game &g)
{
    for(int y =0; y<g.size; y++)
    {
        if(g.pField[y][0] == g.pField[y][1] && g.pField[y][0] == g.pField[y][2])
        {
            if(g.pField[y][0]==g.human)
            {
             return WON_1ST_PL;
            }
           else if (g.pField[y][0] == g.ai )
            {
                return WON_2_PL;
            }
        }
    }

    for(int x =0;x<g.size; x++)
    {
        if( g.pField[0][x] == g.pField[1][x] && g.pField [0][x] == g.pField[2][x])
        {
            if( g.pField[0][x] == g.human )
            {
             return WON_1ST_PL;
            }
           else if (g.pField[0][x] == g.ai )
            {
                return WON_2_PL;
            }
        }
    }
    if( g.pField[0][0] == g.pField[1][1] && g.pField [0][0] == g.pField[2][2])
    {
        if( g.pField[0][0] == g.human )
        {
         return WON_1ST_PL;
        }
       else if (g.pField[0][0] == g.ai )
        {
            return WON_2_PL;
        }
    }
    if( g.pField[2][0] == g.pField[1][1] && g.pField [2][0] == g.pField[0][2])
    {
        if( g.pField[1][1] == g.human )
        {
         return WON_1ST_PL;
        }
       else if (g.pField[1][1] == g.ai )
        {
            return WON_2_PL;
        }
    }
   bool empty=false;
    for (int y=0;y<g.size;y++)
   {
      for (int x=0;x<g.size;x++)
      {
        if(g.pField[y][x]==EMPTY)
          {
            empty=true;
          }

        }
   }
    if(empty)
       return IN_PROGRESS;
    else
       return DRAW;
}
int main(int argc, char *argv[])
{
   //int x;
   Game game;
   initGame(game);
   drawField(game);
   while(game.progress==IN_PROGRESS)
   {
   if(game.turn % 2 == 0)
      {
       Coord c = getCoordHuman(game );
       game.pField[c.y][c.x] = game.human;
       drawField(game);
       }

    else
      {
       Coord ch = getCoordAI(game );
       game.pField[ch.y][ch.x] = game.ai;
       }
   game.turn++;
   myClear();
   drawField(game);

   game.progress=isWon(game);

    }
if(game.progress==WON_1ST_PL)
    cout<<"1ST player WON\n";
if(game.progress==WON_2_PL)
    cout<<"2ND player WON\n";
if(game.progress==DRAW)
    cout<<"Both loosers\n";
   deinitGame(game);



    return 0;//
}
