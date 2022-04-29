#include<iostream>
#include <conio.h>
#include<cstdlib>
#include <ctime>
#include<Windows.h>
#include"Myfs.h"

#define SUITS 4
#define FACES 13
#define TableHeight  30
#define TableWidth  160


using namespace std;

char TableView[TableHeight][TableWidth];
int TableViewColor[TableHeight][TableWidth];

void gotoxy(int x, int y)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = { x,y };
    SetConsoleCursorPosition(hStdout, position);
}

void setColor(int k)
{
    HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleColor, k);
}

/*void swap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}*/

void shuffleCards(int deck[][FACES])
{
    srand(time(0));
    int random;
    int temp[60] = { 0 };
    for (int i = 0; i < SUITS; i++)
    {
        for (int j = 0; j < FACES; j++)
        {
            random = rand() % 52 + 1;
            if (temp[random] == 0)
            {
                deck[i][j] = random;
                temp[random] = random;
            }
            else
            {
                j--;
            }
        }
    }
}

void findPosition(int deck[][FACES], int pos, int& a, int& b)
{
    for (int i = 0; i < SUITS; i++)
    {
        for (int j = 0; j < FACES; j++)
        {
            if (deck[i][j] == pos)
            {
                a = i;
                b = j;
            }
        }
    }
}

void printOneCard(const char* suits, const char* faces, int x, int y)
{
    int temp = 0, color;
    if (suits == "Hearts")
    {
        temp = 3;
        color = 244;
    }
    if (suits == "Diamonds")
    {
        temp = 4;
        color = 244;
    }
    if (suits == "Clubs")
    {
        temp = 5;
        color = 240;
    }
    if (suits == "Spades")
    {
        temp = 6;
        color = 240;
    }
    string tempS = "";
    tempS = tempS + char(218) + char(196) + char(196) + char(191);
    AddToTableView(tempS, y, x, color);

    tempS = "";
    tempS = tempS + char(124) + faces + char(124);
    AddToTableView(tempS, y + 1, x, color);

    tempS = "";
    tempS = tempS + char(124) + " " + char(temp) + char(124);
    AddToTableView(tempS, y + 2, x, color);

    tempS = "";
    tempS = tempS + char(192) + char(196) + char(196) + char(217);
    AddToTableView(tempS, y + 3, x, color);
}

void printCardsShuffling(int deck[SUITS][FACES], const char* suits[], const char* faces[])
{
    int a, b;
    int pos = 1;
    int x = 5;
    int y = 5;
    while (pos <= 52)
    {
        findPosition(deck, pos, a, b);
        printOneCard(suits[a], faces[b], x, y);
        x += 5;
        if (pos == 13 || pos == 26 || pos == 39 || pos == 52)
        {
            y += 5;
            x = 5;
        }
        pos++;
    }
}

int** dealingForHand(int deck[SUITS][FACES])
{
    int** hand = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        hand[i] = new int[2];
    }
    int pos = 1;
    int a, b;
    int temp = 0;
    while (pos < 6)
    {
        findPosition(deck, pos, a, b);
        {
            hand[temp][0] = a;
            hand[temp][1] = b;
            temp++;
            pos++;
        }
    }
    return hand;
}

void printHand(int** hand, const char* suits[], const char* faces[])
{
    int x = 0;
    int y = 0;
    for (int temp = 0; temp < 5; temp++)
    {
        for (int i = 0; i < SUITS; i++)
        {
            for (int j = 0; j < FACES; j++)
            {
                if ((hand[temp][0] == i) && (hand[temp][1] == j))
                {
                    printOneCard(suits[i], faces[j], x, y);
                    x += 4;
                }
            }
        }
    }
}

int** createHandTest(int deck[SUITS][FACES], int a[])
{
    int x, y;
    int** hand = new int* [5];
    for (int i = 0; i < 5; i++)
    {
        findPosition(deck, a[i], x, y);
        hand[i][0] = x;
        hand[i][1] = y;
    }
    return hand;
}

int isFourOfAKind(int** hand)
{
    int temp = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (hand[i][1] == hand[j][1])
            {
                temp++;
            }
        }
    }
    if (temp == 6) return 1;
    return 0;
}

int isFullHouse(int** hand)
{
    int res = 0;
    int temp1 = -1, temp2, res1 = 0, res2 = 0;
    for (int i = 1; i < 5; ++i)
    {
        if (hand[0][1] != hand[i][1])
        {
            temp1 = hand[0][1];
            temp2 = hand[i][1];
        }
    }
    if (temp1 == -1) return 0;
    for (int i = 0; i < 5; ++i)
    {
        if (hand[i][1] == temp1)
        {
            res1++;
        }
        if (hand[i][1] == temp2)
        {
            res2++;
        }
    }
    if ((res1 == 3 && res2 == 2) || (res1 == 2 && res2 == 3))
    {
        return 1;
    }
    return 0;
}

int isFlush(int** hand)
{
    for (int i = 0; i < 4; i++)
    {
        if (hand[i][0] != hand[i + 1][0])
        {
            return 0;
        }
    }
    return 1;
}

int isStraight(int** hand)
{
    int array[5];
    int temp;
    for (int i = 0; i < 5; i++)
    {
        array[i] = hand[i][1];
    }
    for (int i = 0; i < 4; i++)
    {
        if (array[i] > array[i + 1])
        {
            temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;
            i = -1;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (array[i + 1] - array[i] != 1)
        {
            return 0;
        }
    }
    return 1;
}

int isStraightFlush(int** hand)
{
    if ((isFlush(hand) == 1) && (isStraight(hand) == 1))
    {
        return 1;
    }
    return 0;
}

int isThreeOfAKind(int** hand)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (hand[i][1] == hand[j][1])
            {
                count++;
            }
        }
    }
    if (count == 3)
    {
        return 1;
    }
    return 0;
}

int isTwoPairs(int** hand) 
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (hand[i][1] == hand[j][1])
            {
                count++;
            }
        }
    }
    if (count == 2)
    {
        return 1;
    }
    return 0;
}

int isPair(int** hand) {
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (hand[i][1] == hand[j][1])
            {
                count++;
            }
        }
    }
    if (count == 1)
    {
        return 1;
    }
    return 0;
}

int getHighestCard(int** hand)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (hand[i][1] <= hand[j][1])
            {
                swap(hand[i][1], hand[j][1]);
                swap(hand[i][0], hand[j][0]);
            }
        }
    }
    return hand[0][1];
}

int*** dealingForHands(int deck[SUITS][FACES], int n)
{
    int*** hands = new int** [n];
    int a, b;
    int pos = 1;
    for (int i = 0; i < n; i++)
    {
        hands[i] = new int* [5];
        for (int j = 0; j < 5; j++)
        {
            hands[i][j] = new int[2];
        }
    }
    if (n > 6)
    {
        cout << "Num of player are not valid.";
        return 0;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                findPosition(deck, pos, a, b);
                pos++;
                hands[i][j][0] = a;
                hands[i][j][1] = b;
            }
        }
        return hands;
    }
}

int getStatusOfHand(int** hand)
{
    if (isStraightFlush(hand) == 1)
        return 8;
    else if (isFourOfAKind(hand) == 1)
        return 7;
    else if (isFullHouse(hand) == 1)
        return 6;
    else if (isFlush(hand) == 1)
        return 5;
    else if (isStraight(hand) == 1)
        return 4;
    else if (isThreeOfAKind(hand) == 1)
        return 3;
    else if (isTwoPairs(hand) == 1)
        return 2;
    else if (isPair(hand) == 1)
        return 1;
    else
        return 0;
}

int* rankingHands(int*** hands, int n)
{
    int* array = new int[n];
    int* res = new int[n];
    for (int i = 0; i < n; i++)
    {
        array[i] = getStatusOfHand(hands[i]);
        res[i] = i;
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i] < array[i + 1])
        {
            swap(array[i], array[i + 1]);
            swap(res[i], res[i + 1]);
            i = -1;
        }
    }
    return res;
}

int* evaluateHands(int deck[SUITS][FACES], int n, int s)
{
    int*** hands = new int** [n];
    int* temp = new int[n];
    int th;
    for (int i = 0; i < n; i++)
    {
        hands[i] = new int* [5];
        for (int j = 0; j < 5; j++)
        {
            hands[i][j] = new int[2];
        }
    }
    while (s > 0)
    {
        hands = dealingForHands(deck, n);
        for (int i = 0; i < n; i++)
        {
            temp[i] = temp[i] + getStatusOfHand(hands[i]);
        }
        s--;
    }
    int max = temp[0];
    int dem = 0;
    for (int i = 0; i < n; i++)
    {
        if (temp[i] > max)
        {
            max = temp[i];
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (temp[i] == max)
        {
            dem++;
            th = i;
        }
    }
    if (dem == 1)
    {
        cout << "congratulate the player " << th << " th." << '\n';
    }
    else
    {
        int* ths = new int[dem];
        int j = 0;
        for (int i = 0; i < n; i++)
        {
             if (temp[i] == max)
             {
                    ths[j] = i;
                    i++;
             }
        }
        for (int i = 0; i < dem; i++)
        {
            cout << "congratulate the player " << ths[i] << " th." << '\n';
        }
    }
    return temp;
}

void replaceHandDealer(int deck[SUITS][FACES], int*** &hands, int n)
{
    int pos = n * 5 + 1;
    int temp = rand() % 3 + 1;

    int a, b, vt, x, y;
    while (temp > 0)
    {
        findPosition(deck, pos, a, b);
        vt = rand() % 5 + 1;
        findPosition(deck, vt, x, y);
        swap(deck[a][b], deck[x][y]);
        hands[0][vt-1][0] = a;
        hands[0][vt-1][1] = b;
        temp--;
        pos++;
    }
}

void drawMoreCards(int deck[SUITS][FACES],const char* suits[], const char* faces[], int n)
{
    int*** hands = dealingForHands(deck, n);
    CreateTableView();
    printFrame();
    int a, b, x, y, vitridoi = n * 5 + 1;
    string name;
    char check;
    for (int i = 1; i < n; ++i)
    {
        printCardOfPlayerT(i, i * 5 + 1, i * 5 + 5, deck, suits, faces, n);
        for (int j = 0; j < 3; ++j)
        {
            name = "Do you want to draw card?(1:YES  2:NO)";
            check = '0';
            AddToTableView(name, 12, 76 - (name.size() / 2), 14);
            ShowTableView();
            while (check > '2' || check < '1') check = _getch();
            if (check == '2') continue;

            name = "        Choose a card to discard(1-5)        ";
            AddToTableView(name, 12, 76 - (name.size() / 2), 14);
            findPosition(deck, vitridoi, a, b);
            printOneCard(suits[a], faces[b], 74, 13);
            ShowTableView();
            check = '0';
            while (check > '5' || check < '1') check = _getch();
            int pos = i * 5 + (check - '0');
            findPosition(deck, pos, x, y);
            hands[i][pos - (i * 5 + 1)][0] = a;
            hands[i][pos - (i * 5 + 1)][1] = b;
            swap(deck[a][b], deck[x][y]);
            printFrame();
            for (int k = 1; k <= i; ++k)
                printCardOfPlayerT(k, k * 5 + 1, k * 5 + 5, deck, suits, faces, n);
            ++vitridoi;
        }
    }
    printFrame();
}

void printFrame()
{
    //Broadgame
    TableView[1][25] = char(201);
    TableViewColor[1][25] = 14;
    for (int i = 26; i <= 125; ++i)
    {
        TableView[1][i] = char(205);
        TableViewColor[1][i] = 14;
    }
    TableView[1][126] = char(187);
    TableViewColor[1][126] = 14;

    for (int i = 2; i < 26; ++i)
    {

        TableView[i][25] = char(186);
        TableViewColor[i][25] = 14;

        TableView[i][126] = char(186);
        TableViewColor[i][126] = 14;
    }

    TableView[26][25] = char(200);
    TableViewColor[26][25] = 14;

    for (int i = 26; i <= 125; ++i)
    {
        TableView[26][i] = char(205);
        TableViewColor[26][i] = 14;
    }

    TableView[26][126] = char(188);
    TableViewColor[26][126] = 14;

    int a = 1;
    int b = 1;

    for (int i = 2; i <= 25; i++)
    {
        for (int j = 26; j <= 125; j++)
        {
            TableViewColor[i][j] = 34;
        }

    }

    // RankGame
    string temp = "";
    temp = temp + char(201) + char(205) + char(205) + "[ RANK ]" + char(205) + char(205) + char(187);
    AddToTableView(temp, 1, 137, 14);
    for (int i = 2; i < 12; ++i)
    {
        TableView[i][137] = char(186);
        TableView[i][150] = char(186);
    }
    temp = "";
    for (int i = 0; i < 14; ++i)
        temp = temp + char(205);
    temp[0] = char(200);
    temp[13] = char(188);
    AddToTableView(temp, 12, 137, 14);

    //Score board
    temp = "";
    temp = temp + char(201) + char(205) + char(205) + "[ Score board ]" + char(205) + char(205) + char(187);
    AddToTableView(temp, 14, 137, 14);
    for (int i = 15; i < 26; ++i)
    {
        TableView[i][137] = char(186);
        TableView[i][157] = char(186);
    }
    temp = "";
    for (int i = 0; i < 21; ++i)
        temp = temp + char(205);
    temp[0] = char(200);
    temp[20] = char(188);
    AddToTableView(temp, 26, 137, 14);
}

void ShowTableView()
{
    gotoxy(0, 0);
    for (int i = 0; i < TableHeight; ++i)
    {
        for (int j = 0; j < TableWidth; ++j)
        {
            setColor(TableViewColor[i][j]);
            cout << TableView[i][j];
        }
        cout << '\n';
    }
}

void CreateTableView()
{
    gotoxy(0, 0);
    for (int i = 0; i < TableHeight; ++i)
    {
        for (int j = 0; j < TableWidth; ++j)
        {
            TableViewColor[i][j] = 14;
            TableView[i][j] = ' ';
        }
        cout << '\n';
    }
}

void AddToTableView(string s, int x, int y, int color)
{
    for (int i = 0; i < s.size(); ++i)
    {
        TableView[x][y + i] = s[i];
        TableViewColor[x][y + i] = color;
    }
}

void PrintPlayerCard(int SumPlayer, int deck[SUITS][FACES], const char* suits[], const char* faces[])
{
    //SumPlayer từ 2-6;
    int a, b;
    string name = "Dealer";
    AddToTableView(name, 27, 73, 11);
    for (int pos = 1; pos <= 5; ++pos) //dealer
    {
        findPosition(deck, pos, a, b);
        printOneCard(suits[a], faces[b], 64 + (pos % 5) * 5, 22);
    }

    name = "Player 1";
    AddToTableView(name, 0, 72, 11);
    for (int pos = 6; pos <= 10; ++pos) //player 1
    {
        findPosition(deck, pos, a, b);
        printOneCard(suits[a], faces[b], 64 + (pos % 5) * 5, 2);
    }

    name = "Player ";
    int row = 9, col = 27;
    for (int pos = 11; pos <= 50; ++pos)
    {
        if (SumPlayer * 5 < pos) return;
        findPosition(deck, pos, a, b);
        printOneCard(suits[a], faces[b], col + (pos % 5) * 5, row);
        if (pos % 10 == 0)
        {
            row += 5;
            col = 27;
        }
        if (pos % 10 == 5)
        {
            col = 100;
        }
        if (pos % 10 == 1)
        {
            AddToTableView(name + char((pos / 5) + '0'), row + 2, 17, 11);
        }
        if (pos % 10 == 6)
        {
            AddToTableView(name + char((pos / 5) + '0'), row + 2, 127, 11);
        }
    }
}

void UpdateRank(int* rank, int n)
{
    string temp = "  Player    ";
    for (int i = 0; i < n; ++i)
    {
        if (rank[i] == 0)
        {
            AddToTableView("   Dealer   ", i + 2, 138, 14);
        }
        else
        {
            temp[9] = char(rank[i] + '0');
            AddToTableView(temp, i + 2, 138, 14);
        }
    }
}

void UpdateScore(int*** hands, int n)
{
    string rk = "   Dealer:   points";
    int temp = getStatusOfHand(hands[0]);
    rk[11] = char(temp + '0');
    AddToTableView(rk, 15, 138, 14);

    rk = " Player  :   points";
    for (int i = 1; i < n; ++i)
    {
        temp = getStatusOfHand(hands[i]);
        rk[8] = char(i + '0');
        rk[11] = char(temp + '0');
        AddToTableView(rk, 15 + i, 138, 14);
    }
}

void gameLevels(int deck[SUITS][FACES], const char* suits[], const char* faces[])
{   char choice = '0';
    int n = 1;
    while (true)
    {
        shuffleCards(deck);
        CreateTableView();
        printFrame();
        choice = '0';
        string name = "Number of players : ";
        AddToTableView(name, 12, 66, 14);
        AddToTableView("1 - player", 15, 70, 14);
        AddToTableView("2 - player", 16, 70, 14);
        AddToTableView("3 - player", 17, 70, 14);
        AddToTableView("4 - player", 18, 70, 14);
        AddToTableView("5 - player", 19, 70, 14);
        ShowTableView();
        while (choice < '1' || choice > '5') choice = _getch();
        n = int(choice - '0') + 1;
        printFrame();

        choice = '0';
        AddToTableView("1-Easy", 15, 70, 14);
        AddToTableView("2-Medium", 17, 70, 14);
        AddToTableView("3-Difficult", 19, 70, 14);
        ShowTableView();

        
        while (choice < '1' || choice > '3')
        {
            choice = _getch();
        }
        int*** hands = dealingForHands(deck, n);

        if (choice == '1')
        {
            EasyGame(deck, suits, faces, n);
        }
        else if (choice == '2')
        {
            MediumGame(deck, suits, faces, n);
        }
        else if (choice == '3')
        {
            HardGame(deck, suits, faces, n);
        }
        Sleep(5000);
        AddToTableView("           New game? (1:YES - 2:NO)           ", 12, 53, 14);
        ShowTableView();
        choice = '0';
        while (choice < '1' || choice > '2') choice = _getch();
        if (choice == '2') break;
    }
}

void CheckWin(int***hands, int* res, int n)
{
    string temp = "Congratulations Player 1, you win!";
 
    int* array = new int[n];
    for (int i = 0; i < n; i++)
    {
        array[i] = getStatusOfHand(hands[i]);
    }

    int max = array[0];
    for (int i = 0; i < n; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    int dem = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] == max)
        {
            dem++;
        }
    }

    if ((dem > 1) && (dem < n))
    {
        int val = 0;
        for (int i = 0; i < dem; i++)
        {
            if (res[i] == 0)
                temp = "       Dealer win       ";
            else
                temp[23] = char(res[i] + '0');
            int vt = 76 - (temp.size() / 2);
            UpdateRank(res, n);
            AddToTableView(temp, 10 + val, vt, 14);
            ShowTableView();
            val += 2;
            temp = "Congratulations Player 1, you win!";
        }
    }
    else if (dem == n)
    {
        temp = "      No one wins!      ";
        int vt = 76 - (temp.size() / 2);
        UpdateRank(res, n);
        AddToTableView(temp, 12, vt, 14);
        ShowTableView();
    }
    else
    {
        if (res[0] == 0)
            temp = "       Dealer win       ";
        else
            temp[23] = char(res[0] + '0');
        int vt = 76 - (temp.size() / 2);
        UpdateRank(res, n);
        AddToTableView(temp, 12, vt, 14);
        ShowTableView();
    }
}

void EasyGame(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n)
{
    int*** hands = dealingForHands(deck, n);
    CreateTableView();
    printFrame();
    PrintPlayerCard(n, deck, suits, faces);
    int* res = rankingHands(hands, n);
    
    UpdateRank(res, n);
    UpdateScore(hands, n);
    ShowTableView();

    CheckWin(hands, res, n);
}

void MediumGame(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n)
{
    int*** hands = dealingForHands(deck, n);
    int*** kiemtra = hands;
    CreateTableView();
    printFrame();
    PrintPlayerCard(n, deck, suits, faces);
    int* res = rankingHands(hands, n);
    UpdateRank(res, n);
    UpdateScore(hands, n);

    replaceHandDealer(deck, hands, n);
    string temp = "Dealer playing..."; // Bai cua dealer se bien doi do dealer se random boc bai
    AddToTableView(temp, 12, 76 - (temp.size() / 2), 14);
    ShowTableView();
    Sleep(2000);


    res = rankingHands(hands, n);
    PrintPlayerCard(n, deck, suits, faces);
    UpdateRank(res, n);
    UpdateScore(hands, n);
    
    CheckWin(hands, res, n);
    ShowTableView();
    
}

void printCardOfPlayerT(int t, int x, int y, int deck[SUITS][FACES], const char* suits[], const char* faces[], int n)
{
    string name;
    int row=1, col=1;
    if (t == 1)
        row = 2, col = 64;
    if (t == 2)
        row = 9, col = 27;
    if (t == 3)
        row = 9, col = 100;
    if (t == 4)
        row = 14, col = 27;
    if (t == 5)
        row = 14, col = 100;

    name = "Player  ";
    name[7] = char(t + '0');
    if (t == 1)
    {
        AddToTableView(name, 0, 72, 11);
    }
    else if (t % 2 == 0)
    {
        AddToTableView(name, row + 2, 17, 11);
    }
    else
    {
        AddToTableView(name, row + 2, 127, 11);
    }
    for (int i = x, a, b; i <= y; ++i)
    {
        findPosition(deck, i, a, b);
        printOneCard(suits[a], faces[b], col, row);
        col += 5;
    }

}

void HardGame(int deck[SUITS][FACES], const char* suits[], const char* faces[], int n)
{
    drawMoreCards(deck, suits, faces, n);
    printFrame();
    EasyGame(deck, suits, faces, n);
}
