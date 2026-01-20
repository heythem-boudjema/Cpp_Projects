#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
const string FileName = "BankClientsInfo.txt";
const string FileName2 = "Users.txt";
void LoginPage();
enum enMenu { show = 1, add = 2, del = 3, update = 4, find = 5, transaction = 6, UsersManage = 7 ,Logout=8};
enum enTransaction { diposit = 1, withdraw = 2, ShowBalance = 3, Ex = 4 };
enum enUsersManager {List=1,Add=2,Delete=3,Update=4,Find=5,Main=6};
struct stUsersManager {
    string Username;
    string Password;
    int Permission = 0;
    bool DeleteMark = false;
};
void ManagingUsers(string Username);
enMenu UserChoice(enMenu Choice)
{
    switch (Choice)
    {
    case 1:
        return  enMenu::show;

    case 2:
        return  enMenu::add;

    case 3:
        return   enMenu::del;

    case 4:
        return  enMenu::update;

    case 5:
        return  enMenu::find;

    case 6:
        return enMenu::transaction;
    case 7:
        return enMenu::UsersManage;
    case 8:
        return enMenu::Logout;
    }




}
vector<stUsersManager>LoadClientFileToVector2(string FileName2);
enUsersManager UserManagerChoice(enUsersManager Choice)
{
    switch (Choice)
    {
    case 1:
        return  enUsersManager::List;

    case 2:
        return  enUsersManager::Add;

    case 3:
        return   enUsersManager::Delete;

    case 4:
        return  enUsersManager::Update;

    case 5:
        return  enUsersManager::Find;

    case 6:
        return enUsersManager::Main;

    }




}
enTransaction TransactionChoice(enTransaction Choice)
{
    switch (Choice)
    {
    case 1:
        return  enTransaction::diposit;

    case 2:
        return  enTransaction::withdraw;

    case 3:
        return  enTransaction::ShowBalance;

    case 4:
        return  enTransaction::Ex;

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
void AddClient(string AccountNumber)
{
    stClientInfo Client;
    string s1;
    Client = ReadClientDataWithoutAccountNumber(AccountNumber);
    s1 = ConvertStructToOneLine(Client);
    SaveClientLineToFile(s1);

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
void PrintUsersInfo(stUsersManager info)
{

    cout << "| " << setw(15) << left << info.Username;
    cout << "| " << setw(10) << left << info.Password;
    cout << "| " << setw(30) << left << info.Permission;


}
void PrintOneUser(vector <stUsersManager> vUsers,string Username)
{

    cout << "| " << left << setw(15) << "Username";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(30) << "Permission";

    cout << endl;
   
    for (stUsersManager& i : vUsers)
    {
        if (i.Username == Username)
        {
            PrintUsersInfo(i);
            cout << endl;
            break;
        }
    }
}
void PrintTotalBalance(stClientInfo info)
{

    cout << "| " << setw(30) << left << info.AccountNumber;
    cout << "| " << setw(30) << left << info.PhoneNumber;
    cout << "| " << setw(30) << left << info.AccountBalance;


}
string ConvertStructToOneLine2(stUsersManager& Info, string diameter = "////")
{
    string s1 = "";


    s1 = Info.Username + diameter;
    s1 = s1 + Info.Password + diameter;
    s1 = s1 + to_string(Info.Permission);

    return s1;

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
vector <stUsersManager> SaveVectorDataToFile2(vector <stUsersManager> &vUsers)
{
    vector <stUsersManager> NewVictor;
    fstream file;
    file.open("Users.txt", ios::out);
    string Line;
    if (file.is_open())
    {
        for (stUsersManager& i : vUsers)
        {
            Line = ConvertStructToOneLine2(i);
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
bool FindClientByUsername2(string Username)
{
    vector <stUsersManager> vUsers;
    vUsers=LoadClientFileToVector2(FileName2);
    for (stUsersManager& i : vUsers)
    {
        if (i.Username == Username)
        {
            return true;
        }

    }

    return false;
}
bool DeleteCheckMark(string AccountNumber, vector <stClientInfo>& vClient)
{
    if (FindClientByAccountNumber(AccountNumber, vClient))
    {
        for (stClientInfo& i : vClient)
        {
            if (i.AccountNumber == AccountNumber)
            {
                i.DeleteMark = true;
                break;
            }

        }
        return true;
    }

    return false;
}
bool DeleteCheckMark2(string Username, vector <stUsersManager>& vUsers)
{
    if (FindClientByUsername2(Username))
    {
        for (stUsersManager& i : vUsers)
        {
            if (i.Username == Username)
            {
                i.DeleteMark = true;
                break;
            }

        }
        return true;
    }

    return false;
}
void DeleteClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClient)
{
    string s1 = "";
    if (FindClientByAccountNumber(AccountNumber, vClient))

    {

        DeleteCheckMark(AccountNumber, vClient);

        for (stClientInfo& i : vClient)
        {

            fstream file(FileName, ios::out);
            if (file.is_open())
            {
                for (stClientInfo& i : vClient)
                {
                    if (!i.DeleteMark) // write only clients not deleted
                    {
                        file << ConvertStructToOneLine(i) << endl;
                    }
                }
                file.close();
            }

        }

    }


}
void DeleteClientByUsername2(string Username , vector <stUsersManager> &vUsers)
{
    string s1 = "";
    if (FindClientByUsername2(Username))

    {

        DeleteCheckMark2(Username, vUsers);

        for (stUsersManager& i : vUsers)
        {

            fstream file("Users.txt", ios::out);
            if (file.is_open())
            {
                for (stUsersManager& i : vUsers)
                {
                    if (!i.DeleteMark) // write only clients not deleted
                    {
                        file << ConvertStructToOneLine2(i) << endl;
                    }
                }
                file.close();
            }

        }

    }


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
stUsersManager ConvertLineToRecord2(string s1, string diameter = "////")
{
    stUsersManager Info;
    vector <string> VSpliter;
    VSpliter = Vspliter(s1, diameter);
    Info.Username = VSpliter[0];
    Info.Password = VSpliter[1];
    Info.Permission = stoi(VSpliter[2]);
    return Info;
}

void EditClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClient)
{
    stClientInfo c;
    if (FindClientByAccountNumber(AccountNumber, vClient))
    {
        for (stClientInfo& i : vClient)
        {
            if (i.AccountNumber == AccountNumber)
            {

                c = ChangeClientRecord(AccountNumber);
                i = c;
                break;

            }

        }
        SaveVectorDataToFile(vClient);
    }
}
void Loopforedit(vector <stClientInfo>& vClient)
{
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    char answer = 'y';
    string AccountNumber;
    while (answer == 'y' || answer == 'Y')
    {
        AccountNumber = ReadAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, v1))
        {
            EditClientByAccountNumber(AccountNumber, v1);
            cout << "Client Edited Successfully, Do You Want To Edit Another Client? y/n";
            cin >> answer;

        }



        else
        {
            cout << "Account Number " << AccountNumber << " Not Found, Do You want to try again ?";
            cin >> answer;
        }

    }

}
void LoopForAdd(vector <stClientInfo>& vClient)
{
    vector <stClientInfo> V1 = LoadClientFileToVector(FileName);
    string AccountNumber;
    char answer = 'y';

    while (answer == 'y' || answer == 'Y')
    {

        AccountNumber = ReadAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, V1))
        {

            cout << "Account Number " << AccountNumber << " Already Exist, Do You want to try again ?";
            cin >> answer;

        }



        else
        {

            AddClient(AccountNumber);

            cout << "Client Added Successfully, Do You Want To Add Another Client? y/n";
            cin >> answer;
        }

    }



}
void LoopforDelete(vector <stClientInfo>& vClient)
{
    vector <stClientInfo> V1 = LoadClientFileToVector(FileName);
    string AccountNumber;
    char answer = 'y';
    while (answer == 'y' || answer == 'Y')
    {
        AccountNumber = ReadAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, V1))
        {
            DeleteClientByAccountNumber(AccountNumber, V1);

            cout << "Client Deleted Successfully, Do You Want To Delete Another Client? y/n";
            cin >> answer;
        }
        else
        {
            cout << "Account Number " << AccountNumber << " Not Found, Do You want to try again ?";
            cin >> answer;
        }
    }

}
void LoopForFind(vector <stClientInfo>& vClient)
{
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    string AccountNumber;
    char answer = 'y';
    while (answer == 'y' || answer == 'Y')
    {
        stClientInfo c;
        AccountNumber = ReadAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, v1))
        {
            for (stClientInfo& i : v1)
            {
                if (i.AccountNumber == AccountNumber)
                {
                    PrintClientCard(i);
                    break;

                }

            }


            cout << "Do You Want To Search For Another Client? y/n";
            cin >> answer;
        }
        else
        {
            cout << "Account Number " << AccountNumber << " Not Found, Do You want to try again ?";
            cin >> answer;
        }
    }

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
void ShowAllBalanceMainScreen()
{
    cout << setw(30) << left << "=====================================================" << endl;
    cout << setw(35) << left << "          Show All Balances Menue Screen             " << endl;
    cout << setw(30) << left << "=====================================================" << endl;

}
void Diposit(vector <stClientInfo>& vClient)
{
    system("cls");
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    string AccountNumber;
    char answer = 'y';
    DipositMainScreen();

    while (answer == 'y' || answer == 'Y')
    {

        stClientInfo c;
        AccountNumber = ReadAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, v1))
        {

            int DipoAmount;
            for (stClientInfo& i : v1)
            {
                if (i.AccountNumber == AccountNumber)
                {
                    PrintClientCard(i);
                    cout << endl;
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

                    break;
                }

            }
            cout << "Do You Want To Do Another Diposit? Y/n";
            cin >> answer;

            SaveVectorDataToFile(v1);
        }
        else
        {
            cout << "Account Number " << AccountNumber << " Not Found, Do You want to try again ?";
            cin >> answer;
        }
    }

}
void Withdraw(vector <stClientInfo>& vClient)
{
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    string AccountNumber;
    system("cls");
    WithdrawMainScreen();

    char answer = 'y';
    while (answer == 'y' || answer == 'Y')
    {
        stClientInfo c;
        AccountNumber = ReadAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, v1))
        {
            char Ans = 'y';
            int WithdrawAmount;
            for (stClientInfo& i : v1)
            {
                if (i.AccountNumber == AccountNumber)
                {
                    PrintClientCard(i);
                    cout << endl;
                    cout << "Please Enter Withdraw Amount" << endl;

                    cin >> WithdrawAmount;
                    cout << "Are You Sure You Want To Perform This Transaction?Y/N";
                    cin >> Ans;
                    if (Ans == 'y' or Ans == 'Y')
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
                    break;

                }

            }
            cout << "Do You Want To Do Another Withdraw? Y/n";
            cin >> answer;

            SaveVectorDataToFile(v1);

        }
        else
        {
            cout << "Account Number " << AccountNumber << " Not Found, Do You want to try again ?";
            cin >> answer;
        }
    }

}
void PrintAllBalances(vector <stClientInfo>& vClient)
{
    system("cls");
    ShowAllBalanceMainScreen();
    vector <stClientInfo> v1 = LoadClientFileToVector(FileName);
    cout << "| " << left << setw(30) << "Account Number";
    cout << "| " << left << setw(30) << "Name";
    cout << "| " << left << setw(30) << "Account Balance";
    cout << endl;
    int TotalBalance = 0;
    for (stClientInfo& i : v1)
    {

        PrintTotalBalance(i);
        cout << endl;
        TotalBalance = TotalBalance + i.AccountBalance;
    }
    cout << setw(45) << right << "Total Balance = " << TotalBalance << endl;
}
void ShowCurrentClients()
{

    vector <stClientInfo> vInfo;
    vInfo = LoadClientFileToVector(FileName);
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "PinCode";
    cout << "| " << left << setw(30) << "Name";
    cout << "| " << left << setw(17) << "Phone Number";
    cout << "| " << left << setw(15) << "Account Balance";
    cout << endl;

    for (stClientInfo& i : vInfo)
    {

        PrintClientInfo(i);
        cout << endl;

    }

}
void SaveClientLineToFile2(string s1,string Name)
{
    fstream file;
    file.open(Name, ios::out | ios::app);
    if (file.is_open())
    {
        file << s1 << endl;

    }
    file.close();
}
void Exit()
{

    cout << "Thanks, see You ;)" << endl;
    cout << "Made By Ireland Hacker (;";
    exit(0);

}
stUsersManager ReturnWantedUser(string UserName,vector<stUsersManager>& vUsers)
{
    stUsersManager User;
    for (stUsersManager & i : vUsers)
    {
        if (i.Username == UserName)
        {
            User = i;
            break;
     }

    }
    return User;

}
void TransactionMenue()
{


    cout << setw(30) << left << "=================================" << endl;
    cout << setw(35) << left << "          Transaction Menue Screen             " << endl;
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(30) << left << "[1] Diposit" << endl;
    cout << setw(30) << left << "[2] Withdraw" << endl;
    cout << setw(30) << left << "[3] Total Balance" << endl;
    cout << setw(30) << left << "[4] Main Menue" << endl;
    cout << setw(30) << "=================================" << endl;
    cout << "Choose What You Want " << endl;
}
void TransactionMainScreen(string username);
void MainMunueScreen()
{
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(35) << left << "          Main Menu Screen             " << endl;
    cout << setw(30) << left << "=================================" << endl;
    cout << setw(30) << left << "[1] Show Client List" << endl;
    cout << setw(30) << left << "[2] Add New Cleint" << endl;
    cout << setw(30) << left << "[3] Delete Client" << endl;
    cout << setw(30) << left << "[4] Update Client Info" << endl;
    cout << setw(30) << left << "[5] Find Client" << endl;
    cout << setw(30) << left << "[6] Transaction" << endl;
    cout << setw(30) << left << "[7] Manage Users" << endl;
    cout << setw(30) << left << "[8] Logout" << endl;

    cout << setw(30) << "=================================" << endl;
    cout << "Choose What You Want " << endl;
}
vector<stUsersManager>LoadClientFileToVector2(string FileName);
stUsersManager ReadUserData(bool username=false,string Username="")
{
    char Answer = 'n';
    stUsersManager Info;
    if (username)
    {
        Info.Username = Username;
    }
    else
    {
        cout << "Please Enter UserName" << endl;
        getline(cin >> ws, Info.Username);
    }
    cout << "Please Enter Password" << endl;
    getline(cin, Info.Password);
    cout << "Do You want to give Full Access? Y/n" << endl;
    cin >> Answer;
    if (Answer == 'y' or Answer == 'Y')
    {
        Info.Permission |= -1;
        return Info;

   }
    else
    {
        cout << "Do You Want to give access to :" << endl;
        cout << "show client list?";
        cin >> Answer;
        if (Answer == 'y' or Answer == 'Y')
        {
            Info.Permission |= 1;

        }
        cout << "Add client list?";
        cin >> Answer;
        if (Answer == 'y' or Answer == 'Y')
        {
            Info.Permission |= 2;

        }
        cout << "delete client list?";
        cin >> Answer;
        if (Answer == 'y' or Answer == 'Y')
        {
            Info.Permission |= 4;

        }
        cout << "Update client list?";
        cin >> Answer;
        if (Answer == 'y' or Answer == 'Y')
        {
            Info.Permission |= 8;

        }
        cout << "Find client list?";
        cin >> Answer;
        if (Answer == 'y' or Answer == 'Y')
        {
            Info.Permission |= 16;

        }
        cout << "Transaction Menu?";
        cin >> Answer;
        if (Answer == 'y' or Answer == 'Y')
        {
            Info.Permission |= 32;

        }
       
    }
    return Info;
}
void ShowUserTable(short i)
{

    cout << "               Users List [" << i << "] User(s)             " << endl;
    cout << "--------------------------------------------------------------" << endl;
}
void ShowUsersMenue()
{
    system("cls");

    vector <stUsersManager> vInfo;
    vInfo = LoadClientFileToVector2("Users.txt");
    ShowUserTable(vInfo.size());
    cout << "| " << left << setw(15) << "Username";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(30) << "Permission";
    
    cout << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (stUsersManager& i : vInfo)
    {

        PrintUsersInfo(i);
        cout << endl;

    }

}
void AddNewUser(string UserFileName)
{
    string username = "";
    vector <stUsersManager> vManage = LoadClientFileToVector2("Users.txt");
    char Answer = 'y';
    while (Answer == 'y' or Answer == 'Y')
    {
        system("cls");
        cout << "Please Enter Username" << endl;
        getline(cin >> ws, username);
        if (!FindClientByUsername2(username))
        {
            string s1 = "";
            stUsersManager UserInfo = ReadUserData(true,username);
            s1 = ConvertStructToOneLine2(UserInfo);
            SaveClientLineToFile2(s1, "Users.txt");
            cout << "User Added Successfully, Do You Want To Add Another User ? y/n" << endl;
            cin >> Answer;
        }
        else
        {
            cout << "Username Already exists, Do You Want To Add Another User ? y/n" << endl;
            cin >> Answer;
        }
    }

}
void DeleteUser(vector <stUsersManager>& vUsers)
{
    string Username;
    char Confirm = 'n';
    char Answer = 'y';
    while (Answer == 'y' or Answer == 'Y')
    {
        system("cls");

        cout << "Please Enter Username" << endl;
        getline(cin >> ws, Username);
        if (FindClientByUsername2(Username)) {
            PrintOneUser(vUsers, Username);
            cout << "Are You Sure You Want to delete this user? y/n" << endl;
            cin >> Confirm;
            if (Confirm == 'y' or Confirm == 'Y')
            {
                DeleteCheckMark2(Username, vUsers);
                DeleteClientByUsername2(Username, vUsers);
                cout << "User Deleted Successfully " << endl;
            }
            cout << "Do You Want To Delete Another User? y/n" << endl;
            cin >> Answer;
        }
        else
        {
            cout << "Username Not found, Do You want to Update another user> Y/n" << endl;
            cin >> Answer;
        }
    }
}
void UpdateUser(string Username,vector<stUsersManager> &vUsers)
{

    stUsersManager c;
    if (FindClientByUsername2(Username))
    {
        for (stUsersManager& i : vUsers)
        {
            if (i.Username == Username)
            {

                c = ReadUserData(true,Username);
                i = c;
                break;

            }

        }
        SaveVectorDataToFile2(vUsers);
    }
}
void UpdateUserMain(vector<stUsersManager> &vUsers)
{
    string Username;
    char Confirm = 'n';
    char Answer = 'y';
    while (Answer == 'y' or Answer == 'Y')
    {
        system("cls");

        cout << "Please Enter Username" << endl;
        getline(cin >> ws, Username);
        if (FindClientByUsername2(Username)) {
            PrintOneUser(vUsers, Username);
            cout << "Are You Sure You Want to Update this user? y/n" << endl;
            cin >> Confirm;
            if (Confirm == 'y' or Confirm == 'Y')
            {
                UpdateUser(Username, vUsers);
                cout << "User Updated Successfully!" << endl;
            }
            cout << "Do You Want To Update Another User? y/n" << endl;
            cin >> Answer;
        }
        else
        {
            cout << "Username Not found, Do You want to Update another user> Y/n" << endl;
            cin >> Answer;
        }
    }

}
void ManageUsersHeader()
{
    cout << "---------------------------------------------------" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "           Manage Users Menu Screen                " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "---------------------------------------------------" << endl;
}
void ManageUsersMenuScreen()
{
    ManageUsersHeader();
    cout << "[1] List Users" << endl;
    cout << "[2] Add New User" << endl;
    cout << "[3] Delete User" << endl;
    cout << "[4] Update User" << endl;
    cout << "[5] Find User" << endl;
    cout << "[6] Main Menu" << endl;
    cout << endl;

    cout << "Choose What You Want" << endl;

}
void FindUser()
{
    vector <stUsersManager> vUsers = LoadClientFileToVector2("Users.txt");
    char Answer = 'y';
    string Username = "";
    while (Answer == 'y' or Answer == 'Y')
    {
        system("cls");

        cout << "Please Enter Username" << endl;
        cin >> Username;
        if (FindClientByUsername2(Username))
        {
            PrintOneUser(vUsers, Username);
            cout << "Do You Want To Search For Another Username? y/n ";
            cin >> Answer;
        }
        else
        {
            cout << "User Not Found,Do You Want To Search For Another Username? y/n ";
            cin >> Answer;
        }


    }

}
void Run(string Username)
{
    vector <stClientInfo> vClient = LoadClientFileToVector(FileName);
    vector<stUsersManager> vUsers = LoadClientFileToVector2(FileName2);
    stUsersManager User = ReturnWantedUser(Username, vUsers);
    while (true)
    {
        system("cls");
        MainMunueScreen();

        short Choice;
        cin >> Choice;
        enMenu enChoice = UserChoice(enMenu(Choice));

        system("cls");

        switch (enChoice)
        {
        case enMenu::add:
            LoopForAdd(vClient);
            break;
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
        case enMenu::del:
            LoopforDelete(vClient);
            break;
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
        case enMenu::update:
            Loopforedit(vClient);
            break;
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
        case enMenu::find:
            LoopForFind(vClient);
            break;
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
        case enMenu::show:
            ShowCurrentClients();
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
            break;
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
        case enMenu::Logout:
            LoginPage();
            cout << "\nPress any key to go back to Main Menu...";
            system("pause");
            break;
        case enMenu::transaction:
            if (User.Permission & 32)
            {
                TransactionMainScreen(Username);
            }
            else
            {
                cout << "Access Denied, You dont have permission to see this." << endl;

            }
            system("pause");

            break;
        case enMenu::UsersManage:
            
             ManagingUsers(Username);
            
            
            system("pause");

            break;

        }

    }


    cin.get();
}
bool CheckUserLoginDetails(string username,string password)
{
    vector<stUsersManager> vUsers = LoadClientFileToVector2("Users.txt");
    for (stUsersManager& i : vUsers)
    {
        if (i.Username == username && i.Password == password)
        {
            return true;
        }
    }
    return false;
}
void LoginScreenHeader()
{

    cout << "---------------------------------------------------" << endl;
    cout << "                       Login Screen                " << endl;
    cout << "---------------------------------------------------" << endl;


}



int main()
{
    vector <stClientInfo> VCLIENT;
    vector<stUsersManager> vUsers = LoadClientFileToVector2("Users.txt");
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
vector<stUsersManager>LoadClientFileToVector2(string FileName2)
{
    vector<stUsersManager> Vinfo;
    stUsersManager info;
    string Line;
    fstream file;
    file.open(FileName2, ios::in);
    while (getline(file, Line))
    {

        info = ConvertLineToRecord2(Line, "////");
        Vinfo.push_back(info);
    }
    file.close();
    return Vinfo;
}
void TransactionMainScreen(string username)
{
    vector <stClientInfo> vClient = LoadClientFileToVector(FileName);
    bool stay = true;
    while (stay)
    {
        system("cls");


        TransactionMenue();
        short Choice;
        cin >> Choice;
        if (Choice == 4)
        {
            stay == false;
            break;
        }
        enTransaction enChoice = (enTransaction)Choice;
        enChoice = TransactionChoice(enChoice);

        switch (enChoice)
        {
        case enTransaction::diposit:
            Diposit(vClient);

            break;
        case enTransaction::withdraw:
            Withdraw(vClient);

            break;
        case enTransaction::ShowBalance:
            PrintAllBalances(vClient);
            system("pause");
            break;
        case enTransaction::Ex:

            Run(username);
            break;


        }

    }
}
void ManagingUsers(string Username)
{
    vector<stUsersManager> vUsers = LoadClientFileToVector2("Users.txt");
    stUsersManager User = ReturnWantedUser(Username, vUsers);
    while (true)
    {
        system("cls");
        ManageUsersMenuScreen();
        short Choice;
        cin >> Choice;
        enUsersManager enChoice = (enUsersManager)Choice;
        enChoice = UserManagerChoice(enChoice);

        switch (enChoice)
        {
        case enUsersManager::List:
            if (User.Permission & 1)
            {
                ShowUsersMenue();
            }
            else
            {
                cout << "Access denied, You dont have permission" << endl;
            }
            system("pause");
            break;
        case enUsersManager::Find:
            if (User.Permission & 16)
            {
                FindUser();
            }
            else
            {
                cout << "Access denied, You dont have permission" << endl;
            }
           
            system("pause");
            break;
        case enUsersManager::Update:
            if (User.Permission & 8)
            {
                UpdateUserMain(vUsers);
            }
            else
            {
                cout << "Access denied, You dont have permission" << endl;
            }
            system("pause");
            break;
        case enUsersManager::Delete:
            if (User.Permission & 4)
            {
                DeleteUser(vUsers);
            }
            else
            {
                cout << "Access denied, You dont have permission" << endl;
            }
            system("pause");
            break;

        case enUsersManager::Add:
            if (User.Permission & 2)
            {
                AddNewUser("Users.txt");
            }
            else
            {
                cout << "Access denied, You dont have permission" << endl;
            }
            system("pause");
            break;
        case enUsersManager::Main:

            Run(Username);
            system("pause");
            break;

        }

    }

}
void LoginPage()
{
    LoginScreenHeader();
    string username, password;
    while (true)
    {
        cout << "Please Enter Username" << endl;
        getline(cin>>ws, username);
        cout << "Please Enter Password" << endl;
        getline(cin, password);
        if (CheckUserLoginDetails(username, password))
        {
            Run(username);
            break;
        }
        else
        {
            cout << "Invalid username or password, please try again" << endl;
        }
    }
}
