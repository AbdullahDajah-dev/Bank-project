#pragma warning(disable : 4996)
#include <iostream>
#include <cmath>
#include <string>
#include "MyLib.h"
#include <iomanip>
#include <cctype>
#include <fstream>
#include <vector>

using namespace std;

const string ClientFileName = ("Clients.txt");

enum enMainMenu {Exit = 0, allClients, AddNew, DeleteClient, UpdateInfo, Search, Transactions };

enum enTransactionsMenu {Deposite = 1, Withdraw, ShowTotalBalances, ShowMainMenu};

void HandleMainMenuChoice(enMainMenu);
void ShowTransactionMenu();

void MainMenuScreen()
{
	cout << "====================================\n"
		<< MyLib::Tabs(1) << "Main Menu Screen\n"
		<< "====================================" << endl;
	cout << "[1] Show Clients List.\n"
		<< "[2] Add New Client.\n"
		<< "[3] Delete Client.\n"
		<< "[4] Update Client Info.\n"
		<< "[5] Find Client.\n"
        << "[6] Transactions.\n"
		<< "[0] Exit\n";
	cout << "====================================\n" << endl;

}

enMainMenu MainMenuButtons()
{
	int userChoice = MyLib::ReadNumberFromTo(0, 6, "Select from the list please? ");
	return (enMainMenu)userChoice;
	
}

struct stClientData
{
	string AccountNumber;
	string PinCode;
	string ClientName;
	string PhoneNumber;
	string Address;
	double Balance = 0;
	bool MarkForDelete = false;
};

string ConvertRecordToLine(stClientData ClientRecord, string Delim = "#//#")
{
    string Client = "";

    Client += ClientRecord.AccountNumber + Delim;
    Client += ClientRecord.PinCode + Delim;
    Client += MyLib::FormatToTitleCase(ClientRecord.ClientName) + Delim;
    Client += MyLib::FormatToTitleCase(ClientRecord.Address) + Delim;
    Client += ClientRecord.PhoneNumber + Delim;
    Client += to_string(ClientRecord.Balance);

    return Client;
}

stClientData ConvertLineToRecord(string DataLine, string Delim = "#//#")
{
    vector <string> vClientData;
    stClientData ClientData;

    vClientData = MyLib::SplitString(DataLine, Delim);

    ClientData.AccountNumber = vClientData[0];
    ClientData.PinCode       = vClientData[1];
    ClientData.ClientName    = vClientData[2];
    ClientData.Address       = vClientData[3];
    ClientData.PhoneNumber   = vClientData[4];
    ClientData.Balance       = stod(vClientData[5]);

    return ClientData;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClientData Client;

        while (getline(MyFile, Line))
        {
            if (Line.empty() || Line == "") continue;

            Client = ConvertLineToRecord(Line);

            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

stClientData ReadClientData()
{
	stClientData client;

	client.AccountNumber  = MyLib::readtext("Enter account number?");

    while (ClientExistsByAccountNumber(client.AccountNumber, ClientFileName))
    {
        cout << "\nClient with [" << client.AccountNumber << "] already exists"
           ", Enter another account number?\n\n";
         getline(cin >> ws, client.AccountNumber);
    }

	client.PinCode        = MyLib::readtext("Enter PIN Code?");
	client.ClientName     = MyLib::readtext("Enter client name?");
	client.Address        = MyLib::readtext("Enter Client address?");
	client.PhoneNumber    = MyLib::readtext("Enter phone number?");
	client.Balance        = MyLib::ReadPositiveNumber("Enter Balance?");

	return client;
}

void AddDataLineToFile(string FileName, string DataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << DataLine << endl << endl;

        MyFile.close();
    }
}

vector<stClientData> LoadDataFromFile(string FileName)
{

    vector <stClientData> vClientRecord;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    string line;
    stClientData Client;

    if (MyFile.is_open())
    {
        while (getline(MyFile, line))
        {
            if (line.empty() || line == "") continue;

            Client = ConvertLineToRecord(line);
            vClientRecord.push_back(Client);
        }
        MyFile.close();
    }
    return vClientRecord;
}

void AddNewClient(string FileName)
{
    stClientData newClient = ReadClientData();
    AddDataLineToFile(FileName, ConvertRecordToLine(newClient));
}

void AddClients(string FileName)
{
    char AddMore = 'Y';

    do
    {
        MyLib::ResetScreen();
        cout << "- - - - - - - - - - - - - - -\n";
        cout << "    |- Add New Client -|\n";
        cout << "- - - - - - - - - - - - - - -\n";
        AddNewClient(FileName);

        cout << "\n- - - - - - - - - - - - - - -\n";
        cout << "|- Client has been added. -|\n";
        cout << "- - - - - - - - - - - - - - -\n\n";
        cout << "Do you want to add more? Y/N: ";
             
        cin >> AddMore;
        cin.ignore();
    } while (toupper(AddMore) == 'Y');
    
}

void PrintClientRecord(stClientData ClientRecord)
{
    cout << "| " << left << setw(15) << ClientRecord.AccountNumber;
    cout << "| " << left << setw(12) << ClientRecord.PinCode;
    cout << "| " << left << setw(20) << MyLib::FormatToTitleCase(ClientRecord.ClientName);
    cout << "| " << left << setw(20) << MyLib::FormatToTitleCase(ClientRecord.Address);
    cout << "| " << left << setw(12) << ClientRecord.PhoneNumber;
    cout << "| " << left << setw(12) << ClientRecord.Balance;
}

void ShowClientsList()
{
    const vector <stClientData> vClientsList = LoadDataFromFile(ClientFileName);

    cout << "\n" << MyLib::Tabs(5) << "Clients List (" << vClientsList.size() << ") Client(s).";
    cout << "\n___________________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(12) << "PIN Code";
    cout << "| " << left << setw(20) << "Client Name";
    cout << "| " << left << setw(20) << "Adress";
    cout << "| " << left << setw(12) << "Phone Number";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n___________________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (const stClientData& client : vClientsList)
    {
        PrintClientRecord(client);
        cout << endl;
    }
    cout << "\n___________________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void PrintClientRecordBalanceLine(stClientData Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.ClientName;
    cout << "| " << setw(12) << left << Client.Balance;
}

void ShowTotalBalance()
{
    vector <stClientData> vClients = LoadDataFromFile(ClientFileName);

    cout << "\n" << MyLib::Tabs(5) << "Balances List(" << vClients.size() << ") Client(s).";

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;
    
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClientData& C : vClients)
        {
            PrintClientRecordBalanceLine(C);
            TotalBalances += C.Balance;

            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << MyLib::Tabs(5) << " Total Balances = " << TotalBalances;
}

bool FindClientByAccountNumber(string AccountNumber, const vector <stClientData>& vClientList, stClientData& Client)
{
    for (const stClientData& C : vClientList)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void PrintClientCard(stClientData ClientCard)
{
    cout << "\n|- The following are the Client details -|\n\n";
    cout << "Account Number : " << ClientCard.AccountNumber << endl;
    cout << "PIN Code       : " << ClientCard.PinCode << endl;
    cout << "Client Name    : " << ClientCard.ClientName << endl;
    cout << "Client Adress  : " << ClientCard.Address << endl;
    cout << "Phone Number   : " << ClientCard.PhoneNumber << endl;
    cout << "Balance        : " << ClientCard.Balance << endl;
}

void PrintSearchResult(string FileName)
{
    stClientData Client;
    vector <stClientData> vClientList = LoadDataFromFile(FileName);

    cout << "\n|- Search -|\n\n";
    string AccountNumber = MyLib::readtext("Enter account number? ");

    while (!FindClientByAccountNumber(AccountNumber, vClientList, Client))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found\n\n";
        AccountNumber = MyLib::readtext("Enter account number? ");
    }
    PrintClientCard(Client);
}

bool MarkClientForDelete(string AccountNumber, vector <stClientData>& vClientList)
{
    for (stClientData& C : vClientList)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void SaveClientsDataToFile(string FileName, const vector <stClientData>& vClientList)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (const stClientData& C : vClientList)
        {
            if (!C.MarkForDelete)
            {
                MyFile << ConvertRecordToLine(C) << endl << endl;
            }
        }
        MyFile.close();
    }
}

bool DeleteClientFromList(vector <stClientData> &vClientList, string FileName)
{
    stClientData Client;
    char DeleteClient = 'N';
    cout << "\n|- Client Deletion -|\n\n";
    string AccountNumber = MyLib::readtext("Enter account number? ");

    while (!FindClientByAccountNumber(AccountNumber, vClientList, Client))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found\n\n";
        AccountNumber = MyLib::readtext("Enter account number? ");
    }

    PrintClientCard(Client);
    cout << "\n\nAre you sure you want to delete this client? Y/N: ";
    cin >> DeleteClient;
    cin.ignore();

    if (toupper(DeleteClient) == 'Y')
    {
        MarkClientForDelete(AccountNumber, vClientList);
        SaveClientsDataToFile(FileName, vClientList);
        vClientList = LoadDataFromFile(FileName); //Refresh the vector data.
        cout << "\n\n- - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "  Client has been Deleted Successfully.\n";
        cout << "- - - - - - - - - - - - - - - - - - - - - - -\n";
        return true;
    }
    cout << "\n\nDeletion Cancelled.\n" << endl;

    return false;
}

void RemoveClientFromList()
{
    vector <stClientData> vClientList = LoadDataFromFile(ClientFileName);
    DeleteClientFromList(vClientList, ClientFileName);
}

stClientData ModifyClientRecord(string AccountNumber)
{
    stClientData Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n|- Updating Client Data -|\n\n";

    Client.PinCode     = MyLib::readtext("PIN Code?");
    Client.ClientName  = MyLib::readtext("Cleint Name?");
    Client.Address     = MyLib::readtext("Client Adress?");
    Client.PhoneNumber = MyLib::readtext("Phone Number?");
    Client.Balance     = MyLib::ReadPositiveNumber("Balance?");

    cin.ignore();
    return Client;
}

void ChangeClientRecord(string AccountNumber, vector <stClientData>& vClientList)
{
    for (stClientData& C : vClientList)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C = ModifyClientRecord(AccountNumber);
            break;
        }
    }
}

bool UpdateClientData(vector <stClientData>& vClientList, string FileName)
{
    stClientData Client;
    char UpdateData = 'N';

    cout << "\n|- Client Data Update -|\n\n";
    string AccountNumber = MyLib::readtext("Enter account number?");

    while (!FindClientByAccountNumber(AccountNumber, vClientList, Client))
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") Not Found\n\n";
        AccountNumber = MyLib::readtext("Enter account number? ");
    }
    PrintClientCard(Client);

    cout << "\nAre you sure you want to update this Client? Y/N: ";
    cin >> UpdateData;
    cin.ignore();

    if (toupper(UpdateData) == 'Y')
    {
        ChangeClientRecord(AccountNumber, vClientList);
        SaveClientsDataToFile(FileName, vClientList);
        vClientList = LoadDataFromFile(FileName); //Refresh
        cout << "\n\n- - - - - - - - - - - - - - - - - - - - - - -\n";
        cout << "  Client Data has been Updated Successfully.\n";
        cout << "- - - - - - - - - - - - - - - - - - - - - - -\n";
        return true;
    }
    cout << "\nUpdate Cancelled.\n" << endl;

    return false;
}

void ClientInfoUpdate()
{
    vector <stClientData> vClientList = LoadDataFromFile(ClientFileName);
    UpdateClientData(vClientList, ClientFileName);
}

void WaitForUser()
{
    cout << "\nPress any key to continue . . . ";
    system("pause>0");
}

void ShowExitScreen()
{
    cout << "\n\n======================================\n"
        << "Thank you for using our services.\n"
        << "======================================\n";
}

enTransactionsMenu ChooseProcess()
{
    int UserChoice = MyLib::ReadNumberFromTo(1, 4, "Select from the list please? ");
    return (enTransactionsMenu)UserChoice;
}

bool ChangeBalanceByAccountNumber(string AccountNumber, double amount, vector <stClientData>& vClient)
{
    char answer = 'N';

    cout << "Are you sure you want to perform this transaction? Y/N: ";
    cin >> answer;

    if (toupper(answer) == 'Y')
    {
        for (stClientData& C : vClient)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.Balance += amount;
                SaveClientsDataToFile(ClientFileName, vClient);
                cout << "\n\nDone Successfully. New balance is: "
                    << C.Balance;
                return true;
            }
        }
    }
        return false;
}

void ShowDepositeScreen()
{
    cout << "- - - - - - - - - - \n"
        << "Deposite Screen\n"
        << "- - - - - - - - - - \n";

    stClientData Client;
    vector <stClientData> vClient = LoadDataFromFile(ClientFileName);
    string AccountNumber = MyLib::readtext("Enter account number?");

    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exits";
        AccountNumber = MyLib::readtext("Enter account number?");
    }

    PrintClientCard(Client);
    cout << "\n" << endl;
    double amount = 0;
    amount = MyLib::ReadPositiveNumber("Please enter deposite amount?");
    cout << "\n" << endl;
    ChangeBalanceByAccountNumber(AccountNumber, amount, vClient);
}

void ShowWithdrawScreen()
{
    cout << "- - - - - - - - - - \n"
        << "Withdraw Screen\n"
        << "- - - - - - - - - - \n";
    stClientData Client;
    vector <stClientData> vClient = LoadDataFromFile(ClientFileName);
    string AccountNumber = MyLib::readtext("Enter account number?");

    while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exits";
        AccountNumber = MyLib::readtext("Enter account number?");
    }

    PrintClientCard(Client);
    cout << "\n" << endl;
    double amount = 0;
    amount = MyLib::ReadPositiveNumber("Please enter withdraw amount?");
    
    while (amount > Client.Balance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to "
            << Client.Balance << endl;
        amount = MyLib::ReadPositiveNumber("Please enter a valid amount?");
    }
    cout << "\n" << endl;
    ChangeBalanceByAccountNumber(AccountNumber, amount * -1, vClient);

}

void HandleTransactionsMenu(enTransactionsMenu Choice)
{
        switch (Choice)
        {
        case enTransactionsMenu::Deposite:
            MyLib::ResetScreen();
            ShowDepositeScreen();
            WaitForUser();
            break;

        case enTransactionsMenu::Withdraw:
            MyLib::ResetScreen();
            ShowWithdrawScreen();
            WaitForUser();
            break;

        case enTransactionsMenu::ShowTotalBalances:
            MyLib::ResetScreen();
            ShowTotalBalance();
            WaitForUser();
            break;

        case enTransactionsMenu::ShowMainMenu:
            break;
        }
   
}

void ShowTransactionMenu()
{
    enTransactionsMenu Choice;

    do
    {
        MyLib::ResetScreen();

        cout << "====================================\n"
            << MyLib::Tabs(1) << "Transactions Screen\n"
            << "====================================" << endl;
        cout << "[1] Deposite.\n"
            << "[2] Withdraw.\n"
            << "[3] Total Balances.\n"
            << "[4] Main Menu.\n"
            << "====================================\n" << endl;

        Choice = ChooseProcess();
        HandleTransactionsMenu(Choice);

    } while (Choice != enTransactionsMenu::ShowMainMenu);
}

void HandleMainMenuChoice(enMainMenu Choice)
{
    switch (Choice)
    {
    case enMainMenu::allClients:
        MyLib::ResetScreen();
        ShowClientsList();
        WaitForUser();
        break;

    case enMainMenu::AddNew:
        MyLib::ResetScreen();
        AddClients(ClientFileName);
        WaitForUser();
        break;

    case enMainMenu::DeleteClient:
        MyLib::ResetScreen();
        ShowClientsList();
        RemoveClientFromList();
        WaitForUser();
        break;

    case enMainMenu::UpdateInfo:
        MyLib::ResetScreen();
        ShowClientsList();
        ClientInfoUpdate();
        WaitForUser();
        break;

    case enMainMenu::Search:
        MyLib::ResetScreen();
        PrintSearchResult(ClientFileName);
        WaitForUser();
        break;

    case enMainMenu::Transactions:
        MyLib::ResetScreen();
        ShowTransactionMenu();
        break;
    }
}

void StartProgram()
{
    enMainMenu choice;

    do
    {
        MyLib::ResetScreen();

        MainMenuScreen();

        choice = MainMenuButtons();

        HandleMainMenuChoice(choice);

    } while (choice != enMainMenu::Exit);

    ShowExitScreen();
    cin.ignore();
    MyLib::PressEnterToExit();
}



int main()
{


    StartProgram();
   

	return 0;
}