#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
int PrintRandomNum(int From, int To)
{
    int RandNum = 0;


    RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}
int ReadNum(string message)
{
    int Num;
    do {
        cout << message;
        cin >> Num;
    } while (Num < 0);
    
    return Num;

}


int ChoiceOfComputer()
{ 
    
    return PrintRandomNum(1, 3);
}

int PlayerChoice()
{
    short PlayerCh;
    cout << "Your Choice [1] : Stone // [2] : Paper // [3] : Scissors ?";
    cin >> PlayerCh;
    return PlayerCh;
}

int HowManyRound()
{
    int NumOfRounds;
    cout << "How Many Round From 1 To 10?" << endl;
    cin >> NumOfRounds;
    return NumOfRounds;
}

int WhoIsTheWinner(int ComputerChoice, int PlayerChoice)
{
    if ((PlayerChoice == 1 && ComputerChoice == 2)|| (PlayerChoice == 2 && ComputerChoice==3) || (PlayerChoice==3 && ComputerChoice==1))
    {
        return 1;
    }
    if (PlayerChoice == ComputerChoice)
    {
        return 2;
    }
    if (ComputerChoice == 1 && PlayerChoice==2 || ComputerChoice==2 && PlayerChoice==3 || ComputerChoice==3 && PlayerChoice==1)
        return 3;
}
int PlayerWinsTimes(int ComputerChoice, int PlayerChoice, int Round)
{
    int PlayerWinTimes = 0;
    for (int i = 1; i <= Round; i++)
    {
        if (WhoIsTheWinner(ComputerChoice, PlayerChoice) == 3)
            PlayerWinTimes++;
    }
    return PlayerWinTimes;
}
int ComputerWinsTimes(int ComputerChoice, int PlayerChoice, int Round)
{
    int ComputerWinTimes = 0;
    for (int i = 1; i <= Round; i++)
    {
        if (WhoIsTheWinner(ComputerChoice, PlayerChoice) == 1)
            ComputerWinTimes++;
    }
    return ComputerWinTimes;
}
int DrawTimes(int ComputerChoice, int PlayerChoice, int Round)
{
    int DrawTimes = 0;
    for (int i = 1; i <= Round; i++)
    {
        if (WhoIsTheWinner(ComputerChoice, PlayerChoice) == 2)
        {
            DrawTimes++;
        }
    }
    return DrawTimes;
}
string PrintTheWinner(int ComputerChoice, int PlayerChoice)
{
    string Winner;
    if (WhoIsTheWinner(ComputerChoice, PlayerChoice) == 1)
    {
        return Winner = "Computer";
    }
    if (WhoIsTheWinner(ComputerChoice, PlayerChoice) == 2)
    {
        return Winner = "No Winner";
    }
    if (WhoIsTheWinner(ComputerChoice, PlayerChoice) == 3)
    {
        return Winner = "Player";
    }
}
    int PrintTheColor(int CompuerChoice, int PlayerChoice)
    {
        if (WhoIsTheWinner(CompuerChoice, PlayerChoice) == 1)
        {
            return system("color 4F");
        }
        if (WhoIsTheWinner(CompuerChoice, PlayerChoice) == 2)
        {
            return system("color 6F");
        }
        if (WhoIsTheWinner(CompuerChoice, PlayerChoice) == 3)
        {
            return system("color 2F");
        }
}
    void ResetScreen()
    {
        system("cls");
        system("color 0F");
    }
void PrintRoundResult(int round,int ComputerChoice, int PlayerChoice, string Winner)
{
    string Array[100];
    Array[0] = "Stone";
    Array[1] = "Paper";
    Array[2] = "Scissors";
    cout << "------------Round[" << round << "]---------------" << endl;

    cout << "Player1 Choice : " << Array[PlayerChoice-1] << endl;
    cout << "Computer Choice : " << Array[ComputerChoice-1] << endl;
    cout << "Round Winner : " << Winner << endl;
}
void PrintGameOver()
{
    cout << "--------------------------------\n" << endl;
    cout << "\t\t+++GameOver+++\t\t" << endl;
    cout << "-----------------[Game Results]----------------\t\t" << endl;
}
void GameOverFrontEnd(int Computer,int Player, int Round)
{
    PrintGameOver();
      int PlayerWin=  PlayerWinsTimes(Computer, Player, Round);
   int ComputerWin= ComputerWinsTimes(Computer, Player, Round);
   int DrawTime= DrawTimes(Computer, Player, Round);
   cout << "Game Round : " << Round << endl;
   cout << "Player 1 Won Times : " << PlayerWin << endl;
   cout << "Computer Won Times : " << ComputerWin << endl;
   cout << "Draw Times : " << DrawTime << endl;
   if (ComputerWin > PlayerWin)
   {
       cout << "Final Winner : Computer" << endl;
   }
   if (ComputerWin < PlayerWin)
   {
       cout << "Final Winner : Player" << endl;
   }
   if (ComputerWin == PlayerWin)
   {
       cout << "Final Winner : No Winner" << endl;
   }
}

void HowManyRoundToPlay()
{

    int Rounds = HowManyRound();
   

    for (int i = 1; i <= Rounds; i++)
    {
        cout << "Round [" << i << "] Begins : " << endl;

        int Computer = ChoiceOfComputer();
        int Player = PlayerChoice();
        string Winner = PrintTheWinner(Computer, Player);
       

        cout << "      " << endl;
       
        PrintTheColor(Computer, Player);
        PrintRoundResult(i, Computer, Player, Winner);
        if (i == Rounds)
        {
            GameOverFrontEnd(Computer, Player, Rounds);

        }
       
    }
}

void PlayAgain()
{
    string Answer;
    do {
        ResetScreen();
        HowManyRoundToPlay();

        cout << "Do You Want To Play Again? Y/N" << endl;
            cin >> Answer;

    } while (Answer != "n" && Answer != "N");
}
int main()
{
    srand((unsigned)time(NULL));
  
    PlayAgain();

}