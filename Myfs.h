#pragma once
#include<iostream>
#include<cstdlib>
#include <ctime>
#include<Windows.h>

#define SUITS 4
#define FACES 13
#define TableHeight  30
#define TableWidth  150

using namespace std;


void gotoxy(int x, int y);
void setColor(int k);

void shuffleCards(int deck[][FACES]);
void findPosition(int deck[][FACES], int pos, int& a, int& b);
void printOneCard(const char* suits, const char* faces, int x, int y);

void printCardsShuffling(int deck[SUITS][FACES], const char* suits[], const char* faces[]);

int** dealingForHand(int deck[SUITS][FACES]);
void printHand(int** hand, const char* suits[], const char* faces[]);

int** createHandTest(int deck[SUITS][FACES], int a[]);

int isFourOfAKind(int** hand);
int isFullHouse(int** hand);
int isFlush(int** hand);
int isStraight(int** hand);
int isStraightFlush(int** hand);
int isThreeOfAKind(int** hand);
int isTwoPairs(int** hand);
int isPair(int** hand);
int getHighestCard(int** hand);

int*** dealingForHands(int deck[SUITS][FACES], int n);
int getStatusOfHand(int** hand);
int* rankingHands(int*** hands, int n);
int* evaluateHands(int deck[SUITS][FACES], int n, int s);

void replaceHandDealer(int deck[SUITS][FACES], int***& hands, int n);

void drawMoreCards(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n);

void printFrame();

void ShowTableView();

void CreateTableView();

void AddToTableView(string s, int x, int y, int color);

void PrintPlayerCard(int SumPlayer, int deck[SUITS][FACES], const char* suits[], const char* faces[]);

void UpdateRank(int* rank, int n);

void UpdateScore(int*** hands, int n);

void CheckWin(int*** hands, int* res, int n);

void gameLevels(int deck[SUITS][FACES], const char* suits[], const char* faces[]);


void EasyGame(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n);
void MediumGame(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n);
void HardGame(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n);

void printCardOfPlayerT(int t, int x, int y, int deck[SUITS][FACES], const char* suits[], const char* faces[], int n);
