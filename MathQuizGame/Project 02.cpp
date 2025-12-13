#include<iostream>
using namespace std;
#include<cmath>
#include<cstdlib>
#include <ctime>
int PrintRandomNum(int From, int To)
{
    int Rand = 0;
    Rand = rand() % (To - From + 1) + From;
    return Rand;

}

int HowManyQstToAnswer()
{
    short Qst;
    do {
        cout << "How Many Qst You Want To Answer" << endl;
        cin >> Qst;
    } while (Qst < 0);
    return Qst;
}
int QuestLevel()
{
    short Level;
    do {
        cout << "Please Enter Qestion Level, 1=Easy,2=Med,3=Hard,4=Mix" << endl;
        cin >> Level;
    } while (Level > 4 || Level < 1);
    return Level;
}
  
int OperationType()
{
    short Op;
    do {
        cout << "Please Enter Operation Type, 1=Add,2=Sub,3=Mul,4=Div,5=Mix" << endl;
        cin >> Op;
    } while (Op > 5 || Op < 1);
    return Op;
}
char OpType(int Op)
{

   
    switch (Op) {
    case 1:
        return '+';
    case 2:
        return '-';
    case 3:
        return '*';
    case 4:
        return '/';
    case 5:
        short R = PrintRandomNum(1, 4);
        return OpType(R);

    }
}
int QuestionLevel(short Level)
{
   
    switch (Level) {
    case 1:
        return PrintRandomNum(1, 10);
    case 2:
        return PrintRandomNum(10, 50);
    case 3:
        return PrintRandomNum(50, 100);
    case 4:
        return PrintRandomNum(1, 100);
    default :
        return PrintRandomNum(1, 100);

    }
}
bool CalculatAnswer(int Num1, int Num2, int Result, char Op)
{
    switch (Op)
    {
    case '+':
        return Num1 + Num2==Result;
    case '-':
        return Num1 - Num2 == Result;
    case '*':
        return Num1 * Num2 == Result;
    case '/':
        return Num1 / Num2 == Result;
    }
}
    int ShowCalculatAnswer(int Num1, int Num2, int Result, char Op)
    {
        switch (Op)
        {
        case '+':
            return Result = Num1 + Num2;
        case '-':
            return Result = Num1 - Num2;
        case '*':
            return Result = Num1 * Num2;
        case '/':
            return Result = Num1 / Num2;
        }
}
    void PassOrNot(short RightAnswer, short WrongAnswer)
    {
        if (RightAnswer >= WrongAnswer)
        {
    
            cout << "Final Results Is Pass :)";
                system("color 2F");
        }
        else
        {
            cout << "Final Results is Fail :(";
            system("color 4F");
        }
    }
    void PrintFinalResults(short NumberOfQst, short QstLvl, short OpType, short RightAnswers, short WrongAnswers)
    {

        string Op;
        switch (OpType) {
        case 1:
            Op = "Add";
            break;
        case 2:
            Op = "Sub";
            break;
        case 3:
            Op = "Mult";
            break;
        case 4:
            Op = "Dev";
            break;
        case 5:
            Op = "Mix";
            break;
        }
        PassOrNot(RightAnswers, WrongAnswers);
        cout << endl;
        cout << "------------------------------" << endl;
        cout << "Number Of Questions : " << NumberOfQst << endl;
        cout << "Questions Level : " << QstLvl<< endl;
        cout << "Optype : " << Op << endl;
        cout << "Number Of Right Answers : " << RightAnswers << endl;
        cout << "Number Of Wrong Answers : " << WrongAnswers << endl;
        cout << "------------------------------------------" << endl;
    }
void StartQuest(short HowManyQst,short QstLevel)
{
    short OpChoice = OperationType();
  
    short RightAnswer = 0;
    short WrongAnswer = 0;
    int Answer;
    for (int i = 1; i <= HowManyQst; i++)
    {
        char Op;
        if (OpChoice == 5)
        {
            Op = OpType(5);
       }
        else
        {
            Op = OpType(OpChoice);
        }
       
        int Num1 = QuestionLevel(QstLevel);
        int Num2 = QuestionLevel(QstLevel);
        cout << endl;
        cout << "Question [" << i << "/" << HowManyQst << "]" << endl;
        cout << Num1 << " ";
        cout << Op << " ";
      
        cout << Num2 << " = ?" << endl;
        cout << "------------------" << endl;
        cin >> Answer;
        if (CalculatAnswer(Num1, Num2, Answer, Op) == true)
        {
            system("color 2F");
            cout << "Right Answer :)" << endl;
            cout << endl;
            RightAnswer++;
        }
        else
        {
            system("color 4F");
            cout << "Wrong Answer :(" << endl;
            cout << "The Right Answer is " << ShowCalculatAnswer(Num1, Num2, Answer, Op);
            cout << endl;
            WrongAnswer++;
        }


    }
    cout << endl;

  
 
    PrintFinalResults(HowManyQst, QstLevel, OpChoice, RightAnswer, WrongAnswer);
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void StartTheGame()
{
   
    char Answer;
    do {
        ResetScreen();
        short HowManyQst = HowManyQstToAnswer();
        short QstLvl = QuestLevel();
        StartQuest(HowManyQst, QstLvl);
        cout << "Do You Want To Play Again? y/n" << endl;
        cin >> Answer;
        
    } while (Answer == 'Y' || Answer == 'y');
}
int main()
{
   
   
    srand((unsigned)time(NULL));

  
    StartTheGame();
}

