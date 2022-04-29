#include<iostream>
#include<cstdlib>
#include <ctime>
#include<Windows.h>
#include"Myfs.h"
#include <conio.h>

#define SUITS 4
#define FACES 13
#define TableHeight  30
#define TableWidth  150

using namespace std;

int main()
{
    const char* suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    const char* faces[13] = { "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10", "J ", "Q ", "K ", "A " };
    int deck[SUITS][FACES];
  
    gameLevels(deck, suits, faces);

    return 0;
}
