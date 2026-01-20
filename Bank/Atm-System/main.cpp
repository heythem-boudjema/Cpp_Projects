#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
const string FileName = "BankClientsInfo.txt";
enum enMenu { show = 1, add = 2, del = 3, update = 4, find = 5, transaction = 6, ex = 7 };
enum enTransaction { QuickWithdraw = 1, NormalWithdraw = 2, Diposit = 3, CheckBalance = 4,Logout=5 };

enTransaction TransactionChoice(short Choice)
{
    switch (Choice)
    {
    case 1:
        return  enTransaction::QuickWithdraw;

    case 2:
        return  enTransaction::NormalWithdraw;

    case 3:
        return  enTransaction::Diposit;

    case 4:
        return  enTransaction::CheckBalance;
    case 5:
        return  enTransaction::Logout;
      
    }
}
string ReadAccountNumber()
{
    string s1;
    cout << "Please Enter Account Number" << endl;
    getline(cin >> ws, s1);
    return s1;
}
struct stClientInfo {
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance;
    bool DeleteMark = false;
};
stClientInfo ReadClientData()
{
    stClientInfo Info;
    cout << "Please Enter Client Account Number" << endl;
    getline(cin, Info.AccountNumber);
    cout << "Please Enter Client PinCode" << endl;
    getline(cin, Info.PinCode);
    cout << "Please Enter Client Name" << endl;
    getline(cin, Info.Name);
    cout << "Please Enter Client phone Number" << endl;
    getline(cin, Info.PhoneNumber);
    cout << "Please Enter Client Account Balance" << endl;
    cin >> Info.AccountBalance;
    return Info;
}
void LoginPage();
vector<stClientInfo> LoadClientFileToVector(string FileName);
stClientInfo ReadClientDataWithoutAccountNumber(string AccountNumber)
{

    stClientInfo Info;

    Info.AccountNumber = AccountNumber;
    cout << "Please Enter Your PinCode" << endl;
    getline(cin, Info.PinCode);
    cout << "Please Enter Your Name" << endl;
    getline(cin, Info.Name);
    cout << "Please Enter Your phone Number" << endl;
    getline(cin, Info.PhoneNumber);
    cout << "Please Enter Your Account Balance" << endl;
    cin >> Info.AccountBalance;

    return Info;
}
string ConvertStructToOneLine(stClientInfo& Info, string diameter = "////")
{
    string s1 = "";


    s1 = Info.AccountNumber + diameter;
    s1 = s1 + Info.PinCode + diameter;
    s1 = s1 + Info.Name + diameter;
    s1 = s1 + Info.PhoneNumber + diameter;
    s1 = s1 + to_string(Info.AccountBalance);

    return s1;

}
void SaveClientLineToFile(string s1)
{
    fstream file;
    file.open(FileName, ios::out | ios::app);
    if (file.is_open())
    {
        file << s1 << endl;

    }
    file.close();
}
bool FindClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClient)
{

    for (stClientInfo& i : vClient)
    {
        if (i.AccountNumber == AccountNumber)
        {
            return true;
        }

    }

    return false;
}
vector <string> Vspliter(string S1, string diameter)
{
    vector <string> Spliter;
    short Pos = 0;
    string Word;
    while ((Pos = S1.find(diameter)) != std::string::npos)
    {
        Word = S1.substr(0, Pos);
        if (Word != "")
        {
            Spliter.push_back(Word);

        }

        S1.erase(0, Pos + diameter.length());
    }

    if (S1 != "")
    {
        Spliter.push_back(S1);

    }
    return Spliter;

}
void PrintClientInfo(stClientInfo info)
{

    cout << "| " << setw(15) << left << info.AccountNumber;
    cout << "| " << setw(10) << left << info.PinCode;
    cout << "| " << setw(30) << left << info.Name;
    cout << "| " << setw(17) << left << info.PhoneNumber;
    cout << "| " << setw(15) << left << info.AccountBalance;




}
void PrintTotalBalance(stClientInfo info)
{

    cout << "| " << setw(30) << left << info.AccountNumber;
    cout << "| " << setw(30) << left << info.PhoneNumber;
    cout << "| " << setw(30) << left << info.AccountBalance;


}
bool CheckClientLoginDetails(string AccountNumber,string PinCode, vector <stClientInfo>& vClient)
{

    for (stClientInfo& i : vClient)
    {
        if (i.AccountNumber == AccountNumber && i.PinCode == PinCode)
        {
            return true;
        }

    }

    return false;
}

vector <stClientInfo> SaveVectorDataToFile(vector <stClientInfo>& Vclient)
{
    vector <stClientInfo> NewVictor;
    fstream file;
    file.open(FileName, ios::out);
    string Line;
    if (file.is_open())
    {
        for (stClientInfo& i : Vclient)
        {
            Line = ConvertStructToOneLine(i);
            file << Line << endl;


        }
        file.close();

    }
    return NewVictor;
}
void PrintClientCard(stClientInfo Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.PhoneNumber;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}
vector <string> SplitStringToVector(string S1, string diameter = "////")
{
    vector <string> Spliter;
    short Pos = 0;
    string Word;
    while ((Pos = S1.find(diameter)) != std::string::npos)
    {
        Word = S1.substr(0, Pos);
        if (Word != "")
        {
            Spliter.push_back(Word);

        }

        S1.erase(0, Pos + diameter.length());
    }

    if (S1 != "")
    {
        Spliter.push_back(S1);

    }
    return Spliter;

}
stClientInfo ConvertVectorLineToRecord(string s1, string diameter)
{
    stClientInfo Info;
    vector <string> VSpliter;
    VSpliter = SplitStringToVector(s1, diameter);
    Info.AccountNumber = VSpliter[0];
    Info.PinCode = VSpliter[1];
    Info.Name = VSpliter[2];
    Info.PhoneNumber = VSpliter[3];
    Info.AccountBalance = stod(VSpliter[4]);
    return Info;
}

stClientInfo ChangeClientRecord(string AccountNumber)
{
    stClientInfo Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";

    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.PhoneNumber);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
stClientInfo ConvertLineToRecord(string s1, string diameter = "////")
{
    stClientInfo Info;
    vector <string> VSpliter;
    VSpliter = Vspliter(s1, diameter);
    Info.AccountNumber = VSpliter[0];
    Info.PinCode = VSpliter[1];
    Info.Name = VSpliter[2];
    Info.PhoneNumber = VSpliter[3];
    Info.AccountBalance = stod(VSpliter[4]);
    return Info;
}

void DipositMainScreen()
{
    cout << setw(30) << left << "===========================================" << endl;
    cout << setw(35) << left << "          Diposit Menue Screen             " << endl;
    cout << setw(30) << left << "===========================================" << endl;

}
void WithdrawMainScreen()
{
    cout << setw(30) << left << "============================================" << endl;
    cout << setw(35) << left << "          Withdraw Menue Screen             " << endl;
    cout << setw(30) << left << "============================================" << endl;

}
void DipositScreen(string AccountNumber)
{
    system("cls");
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    DipositMainScreen();
        stClientInfo c;
        int DipoAmount;
        for (stClientInfo& i : v1)
        {
            if (i.AccountNumber == AccountNumber)
            {

                cout << "Please Enter Diposit Amount" << endl;
                char Ans = 'y';
                cin >> DipoAmount;
                cout << "Are You Sure You Want To Perform This Transaction?Y/N ";
                cin >> Ans;

                if (Ans == 'y' || Ans == 'Y')
                {
                    i.AccountBalance += DipoAmount;
                    cout << "Done Successfully, New Balance : " << i.AccountBalance << endl;
                }

            }
            break;

        }
        SaveVectorDataToFile(v1);
    
}
void QuickWithdrawMenu()
{
    cout << "----------------------------------------" << endl;
    cout << "            Quick Withdraw              " << endl;
    cout << "----------------------------------------" << endl;

    cout << setw(20) << "[1] 20         [2] 50" << endl;
    cout << setw(20) << "[3] 100        [4] 200" << endl;
    cout << setw(20) << "[5] 400        [6] 600" << endl;
    cout << setw(20) << "[7] 800        [8] 1000" << endl;
    cout << setw(20) << "[9] exit"<< endl;
    cout << "----------------------------------------" << endl;


}
short QuickWithdrawOptions()
{
    short Withdraw = 0;
    while (Withdraw < 1 || Withdraw >9)
    {
        cout << "Choose From [1] to [9] " << endl;
        cin >> Withdraw;
    }
    if (Withdraw == 1)
        return 20;
    if (Withdraw == 2)
        return 50;
    if (Withdraw == 3)
        return 100;
    if (Withdraw == 4)
        return 200;
    if (Withdraw == 5)
        return 400;
    if (Withdraw == 6)
        return 600;
    if (Withdraw == 7)
        return 800;
    if (Withdraw == 8)
        return 1000;
    if (Withdraw == 9)
        return 9;


}
void QuickWithdrawHeader()
{
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(35) << left << "          Quick Withdraw Screen        " << endl;
    cout << setw(30) << left << "=================================" << endl;
}

void QuickWithdrawal(string AccountNumber,vector <stClientInfo>& vClient)
{
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    system("cls");
        stClientInfo c;
            short WithdrawAmount;
            QuickWithdrawMenu();
            for (stClientInfo& i : v1)
            {
                char Ans = 'n';
                if (i.AccountNumber == AccountNumber)
                {
                    cout << "Your Balance is : " << i.AccountBalance << endl;
                    WithdrawAmount = QuickWithdrawOptions();
                    if (WithdrawAmount == 9)
                        break;
                    cout << "Are You Sure You Want To Perform This Transaction?Y/N";
                    cin >> Ans;
                    if (Ans == 'y' or Ans == 'Y')
                    {
                        while (WithdrawAmount > i.AccountBalance)
                        {
                            cout << "Amount Exceed the Balance, You Can Withdraw Up To " << i.AccountBalance << endl;
                            cout << "Please Choose Another Amount To Withdraw ";
                            WithdrawAmount = QuickWithdrawOptions();
                        }
                        {
                            i.AccountBalance = i.AccountBalance - WithdrawAmount;
                            cout << "Done Successfully, New Balance : " << i.AccountBalance << endl;
                        }
                    }
                    break;

                }

            }
          
            SaveVectorDataToFile(v1);
        }
void NormalWithdrawal(string AccountNumber, vector <stClientInfo>& vClient)
{
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    system("cls");
    WithdrawMainScreen();

    stClientInfo c;

    char Ans = 'n';
    int WithdrawAmount = 1;
    for (stClientInfo& i : v1)
    {
        if (i.AccountNumber == AccountNumber)
        {
            while (WithdrawAmount % 5 != 0)
            {
                cout << "Please Enter Withdraw Amount Multiple of 5" << endl;
                cin >> WithdrawAmount;
            }
            cout << "Are You Sure You Want To Perform This Transaction?Y/N";
            cin >> Ans;
            if (Ans == 'y' or Ans == 'Y')
            {
                while (WithdrawAmount > i.AccountBalance)
                {
                    cout << "Amount Exceed the Balance, You Can Withdraw Up To " << i.AccountBalance << endl;
                    cout << "Please Enter Another Amount To Withdraw ";
                    cin >> WithdrawAmount;
                }
                {
                    i.AccountBalance = i.AccountBalance - WithdrawAmount;
                    cout << "Done Successfully, New Balance : " << i.AccountBalance << endl;
                }
                
            }
            break;
        }

    }


    SaveVectorDataToFile(v1);
}
void ShowCurrentBalanceHeader()
{
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(35) << left << "          Show Balance Screen        " << endl;
    cout << setw(30) << left << "=================================" << endl;
}
void ShowCurrentBalance(string AccountNumber)
{
    system("cls");
    vector <stClientInfo> vInfo;
    vInfo = LoadClientFileToVector(FileName);
    ShowCurrentBalanceHeader();
    for (stClientInfo& i : vInfo)
    {
        if (i.AccountNumber == AccountNumber)
        {
            cout << "Your Balance is : " << i.AccountBalance << endl;
            break;
        }
    }
}
void Exit()
{

    cout << "Thanks, see You ;)" << endl;
    cout << "Made By Ireland Hacker (;";
    exit(0);

}
void MainMunueScreen()
{
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(35) << left << "          ATM Main Menu Screen        " << endl;
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(30) << left << "[1] Quick Withdraw" << endl;
    cout << setw(30) << left << "[2] Normal Withdraw" << endl;
    cout << setw(30) << left << "[3] Diposit" << endl;
    cout << setw(30) << left << "[4] Check Balance" << endl;
    cout << setw(30) << left << "[5] Logout" << endl;
    cout << setw(30) << "=================================" << endl;
    cout << "Choose What You Want " << endl;
}
void LoginScreenHeader()
{
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(35) << left << "          Login Screen        " << endl;
    cout << setw(30) << left << "=================================" << endl;
}
void AtmMainMenuScreen(string AccountNumber, vector <stClientInfo>& vClient)
{
    short Choice;
    while (true) {
        system("cls");
        MainMunueScreen();
        enTransaction enChoice;
        cin >> Choice;
        enChoice = TransactionChoice(Choice);
        switch (enChoice)
        {
        case enTransaction::Diposit:
            DipositScreen(AccountNumber);
            system("pause");

            break;
        case enTransaction::CheckBalance:
            ShowCurrentBalance(AccountNumber);
            system("pause");

            break;
        case enTransaction::QuickWithdraw:
            QuickWithdrawal(AccountNumber, vClient);
            system("pause");

            break;
        case enTransaction::NormalWithdraw:
            NormalWithdrawal(AccountNumber, vClient);
            system("pause");

            break;

        case enTransaction::Logout:
            LoginPage();

            break;
        }
    }

}

int main()
{
    LoginPage();

}
vector<stClientInfo>LoadClientFileToVector(string FileName)
{
    vector<stClientInfo> Vinfo;
    stClientInfo info;
    string Line;
    fstream file;
    file.open(FileName, ios::in);
    while (getline(file, Line))
    {

        info = ConvertLineToRecord(Line, "////");
        Vinfo.push_back(info);
    }
    file.close();
    return Vinfo;
}
void LoginPage()
{
    system("cls");
    vector <stClientInfo> vClient = LoadClientFileToVector(FileName);
    string AccountNumber;
    string PinCode;
    LoginScreenHeader();
    while (true)
    {
        cout << "Please Enter Account Number" << endl;
        cin >> AccountNumber;
        cout << "Please Enter Pin Code" << endl;
        cin >> PinCode;
        if (CheckClientLoginDetails(AccountNumber, PinCode, vClient))
        {
            AtmMainMenuScreen(AccountNumber, vClient);
        }
        else
        {
            cout << "Invalid Account Number/PinCode, Please Enter Again" << endl;
        }

    }




}
