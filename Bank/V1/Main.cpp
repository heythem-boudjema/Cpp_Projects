#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
const string FileName = "BankClientsInfo.txt";
enum enMenu {show=1,add=2,del=3,update=4,find=5,transaction=6,ex=7};
enum enTransaction {diposit=1,withdraw=2,ShowBalance=3,Ex=4};
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
        return enMenu::ex;

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
string ConvertStructToOneLine(stClientInfo &Info, string diameter = "////")
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
void PrintTotalBalance(stClientInfo info)
{

    cout << "| " << setw(30) << left << info.AccountNumber;
    cout << "| " << setw(30) << left << info.PhoneNumber;
    cout << "| " << setw(30) << left << info.AccountBalance;


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
vector <string> SplitStringToVector(string S1, string diameter="////")
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
stClientInfo ConvertLineToRecord(string s1, string diameter="////")
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
void EditClientByAccountNumber(string AccountNumber, vector <stClientInfo>& vClient)
{
    stClientInfo c;
    if (FindClientByAccountNumber(AccountNumber, vClient))
    {
        for (stClientInfo& i : vClient)
        {
            if (i.AccountNumber == AccountNumber)
            {
               
               c=ChangeClientRecord(AccountNumber);
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
        TotalBalance = TotalBalance + i.AccountBalance ;
    }
    cout <<  setw(45) << right << "Total Balance = " << TotalBalance << endl;
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
void Exit()
{

    cout << "Thanks, see You ;)" << endl;
    cout << "Made By Ireland Hacker (;";
    exit(0);

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
void TransactionMainScreen(vector <stClientInfo>&);
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
    cout << setw(30) << left << "[7] Exit" << endl;
    cout << setw(30) << "=================================" << endl;
    cout << "Choose What You Want " << endl;
}
void Run(vector <stClientInfo>& vClient)
{
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
            case enMenu::ex:
                Exit();
                cout << "\nPress any key to go back to Main Menu...";
                system("pause");
                break;
            case enMenu::transaction:
                TransactionMainScreen(vClient);
               
                break;
            }

        }

        
        cin.get();
    }
int main()
{
    vector <stClientInfo> VCLIENT;
    Run(VCLIENT);


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
void TransactionMainScreen(vector <stClientInfo>& vClient)
{
   
    bool stay = true;
    while (stay)
    {
        system("cls");


        TransactionMenue();
        short Choice;
        cin >> Choice;
        if (Choice==4)
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

            Run(vClient);
            break;


        }

    }
}
