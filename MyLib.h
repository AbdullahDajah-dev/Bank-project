#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <limits>
#include <iomanip>
#include <vector>
#include <fstream>
using namespace std;


namespace MyLib
{
    void ResetScreen()
    {
        system("cls");
        system("color 0f");
    }

    void SetTextColor(short ColorCode)
    {
        // Common codes: 2 = Green, 4 = Red, 6 = Yellow, 7 = Standard White
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, ColorCode);
    }

    void ResetTextColor()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 7);
    }

    string Tabs(short HowManyTabs)
    {
        std::string t = "";
        for (int i = 0; i < HowManyTabs; i++)
        {
            t += "\t";
        }
        return t;
    }

    int RandomNumber(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    }

    float ReadNumber(string msg)
    {
        float number = 0;
        cout << msg;
        cin >> number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "Invalid Input, try again: ";
            cin >> number;
        }

        return number;
    }

    int ReadPositiveNumber(string msg = "Enter Positive Number? ")
    {
        int number = 1;
        cout << msg << endl;
        cin >> number;

        while (cin.fail() || number < 1)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                cout << "\nOnly Numbers Allowed\n" << msg << endl;
            }
            else {
                cout << "\nOnly Positive Numbers Allowed\n" << msg << endl;
            }
            cin >> number;
        }
        return number;
    }

    int ReadNumberFromTo(int from, int to, string msg = "Enter number IN range? " )
    {
        int number = 0;
        cout << msg;
        cin >> number;

        while (cin.fail() || number < from || number > to)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                cout << "\nOnly Numbers Allowed\n" << msg;
            }
            else {
                cout << msg;
            }
            cin >> number;
        }
        return number;
    }

    void AddArrayElements(int number, int arr1[100], int& length)
    {
        arr1[length] = number;
        length++;
    }

    void CopyUsingAddArray(int arr1[100], int arr2[100], int length, int& length2)
    {
        for (int i = 0;i < length;i++)
        {
            AddArrayElements(arr1[i], arr2, length2);
        }
    }

    void CopyArray(int arrSoruce[100], int arrDestination[100], int length)
    {
        for (int i = 0;i < length;i++)
        {
            arrDestination[i] = arrSoruce[i];
        }
    }

    void CopyRev(int arrSource[100], int arrDestination[100], int length, int& destination_length4)
    {
        //Copy array in rev order
        destination_length4 = 0;
        for (int i = length - 1;i >= 0;i--)
        {
            arrDestination[destination_length4] = arrSource[i];
            destination_length4++;
        }
    }

    string readtext(string msg = "Enter text? ")
    {
        string text;
        cout << msg << endl;
        getline(cin >> ws, text);

        return text;
    }

    string Encrypt(string text, short key)
    {
        for (int i = 0; i < text.length();i++)
        {
            text[i] = char((int)text[i] + key);
        }
        return text;
    }

    string Decrypt(string text, short key)
    {
        for (int i = 0; i < text.length();i++)
        {
            text[i] = char((int)text[i] - key);
        }
        return text;
    }

    void secondss(int total_seconds)
    {

        int days = total_seconds / (24 * 60 * 60 * 1);
        int remainder = total_seconds % (24 * 60 * 60);
        int hours = remainder / (60 * 60);
        remainder = remainder % (60 * 60);
        int minutes = remainder / 60;
        remainder = remainder % 60;


        printf("%0*d : %0*d : %0*d : %0*d\n", 2, days, 2, hours, 2, minutes, 2, remainder);

        //simplified version of the %0*d, you simply put the number instead of the *

        printf("%02d : %02d : %02d : %02d\n", days, hours, minutes, remainder);

        //without decimals

        printf("without decimals: %d : %d : %d : %d\n", days, hours, minutes, remainder);
    }

    void PrintTable()
    {
        cout << "---------|--------------------------------|---------|" << endl;
        cout << "  Code   |               Name             |   Mark  |" << endl;
        cout << "---------|--------------------------------|---------|" << endl;

        cout << setw(9) << left << "C101" << "|" << setw(32) << left << "Introduction to Programming 1" << "|" << setw(9) << left << "100" << "|" << endl;
        cout << setw(9) << left << "C102" << "|" << setw(32) << left << "Computer Hardware" << "|" << setw(9) << left << "95" << "|" << endl;
        cout << setw(9) << left << "C103" << "|" << setw(32) << left << "Network" << "|" << setw(9) << left << "50" << "|" << endl;
        cout << setw(9) << left << "C104" << "|" << setw(32) << left << "C++" << "|" << setw(9) << left << "100" << "|" << endl;
        cout << setw(9) << left << "C105" << "|" << setw(32) << left << "C#" << "|" << setw(9) << left << "0" << "|" << endl;
        cout << "---------|--------------------------------|---------|" << endl;
    }

    //in main -> int x[10][10]
    void Multitable(int x[10][10])
    {
        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                x[i][j] = (i + 1) * (j + 1);
            }
        }
    }

    void PrintMultiTable(int x[10][10])
    {
        for (int i = 0;i < 10;i++)
        {
            for (int j = 0;j < 10;j++)
            {
                printf("%02d ", x[i][j]);
            }
            cout << endl;
        }
    }

    void ReadIntVector(vector <float>& vNumbers)
    {
        string addmore = "y";

        while (addmore == "y" || addmore == "Y")
        {
            float number = MyLib::ReadNumber("Enter number? ");
            vNumbers.push_back(number);
            cout << "\nwanna add more numbers? Y/N: ";
            cin >> addmore;
        }
    }

    void PrintIntVector(const vector <float>& vNumbers)
    {
        cout << "\nVector numbers: \n";
        for (const float& n : vNumbers)
        {
            printf("%.1f\n", n);
        }
        cout << endl;
    }

    void ReadStringVector(vector <string>& vString, string msg = "Enter Data? ")
    {
        string addmore = "y";

        while (addmore == "y" || addmore == "Y")
        {
            string names = readtext(msg);
            vString.push_back(names);
            cout << "Do you wish to add more? Y/N: ";
            cin >> addmore;
        }
        cout << "\n--> Data Has Been Saved To Vector!\n" << endl;
    }

    void PrintStringVector(const vector <string>& vString)
    {
        cout << "\n=====================\n";
        cout << "    Vector Data           \n";
        cout << "=====================\n\n";
        for (const string& data : vString)
        {
            cout << data << endl;
        }
        cout << endl;
    }

    void VectorPointer()
    {
        vector <int> vNumbers{ 1, 2, 3, 4 ,5 };

        vector <int>::iterator iter;
        for (iter = vNumbers.begin();iter != vNumbers.end();iter++)
        {
            cout << *iter << "  ";
        }
    }

    void CreateAndOpenFile(string FileName, string msg = "Enter text to save? ", string output = "Data saved.")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            string addmore = "y";
            string text;

            while (addmore == "y" || addmore == "Y")
            {
                 text = readtext(msg);
                 MyFile << text << endl;
                 cout << "\nDo you want to continue? Y/N: ";
                 cin >> addmore;
            }

            cout << "\n" << output << endl << endl;

            MyFile.close();
        }
    }

    void PrintFileContent(string FileName)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::in);

        cout << "\n=====================\n";
        cout << "   File Content           \n";
        cout << "=====================\n\n";
        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))

            {
                cout << line << endl;
            }

            MyFile.close();
        }
    }

    void FillDataToVectorFromFile(string FileName, vector <string>& vFileContent)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::in);

        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                vFileContent.push_back(line);
            }
            MyFile.close();
        }
        //and then you print it using this

        /*vector <string> vFileContent;

        FillDataToVector("MyFile.txt", vFileContent);

        for (string& content : vFileContent)
        {
            cout << content << endl;
            
            or u can use the iter (pointer)
            for (iter = vTestFile.begin();iter != vTestFile.end();iter++)
            {
            cout << *iter << endl;
            }
        }*/
    }

    void SaveVectorToFile(string FileName, const vector <string> &vTestFile, string output = "\nData has been saved to ")
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out);

        if (MyFile.is_open())
        {
            for (const string& line : vTestFile)
            {
                if (!line.empty())
                {
                    MyFile << line << endl;
                }
            }
            MyFile.close();
            cout << output << FileName << endl << endl;
        }
    }

    void DeleteRecordFromFile(string FileName, string Record)
    {
        vector <string> vNames;
        FillDataToVectorFromFile(FileName, vNames);

        bool isFound = false;

        for (string& line : vNames)
        {
            if (line == Record)
            {
                line = "";
                isFound = true;
            }
        }

        if (isFound)
        {
            cout << "\nDeleted " << "\"" << Record << "\"" << " Successfully!\n" << endl;
            SaveVectorToFile(FileName, vNames, "Data has been updated in file -> ");
        }
        else {
            cout << "Text wasnt found :-(\n" << endl;
        }
    }

    void ModifyRecordFromFile(string FileName, string Record, string NewRecord)
    {
        vector <string> vNames;
        FillDataToVectorFromFile(FileName, vNames);

        bool isFound = false;

        for (string& line : vNames)
        {
            if (line == Record)
            {
                line = NewRecord;
                isFound = true;
            }
        }
        if (isFound)
        {
            cout << "\nModified Successfully!\n" << endl;

            SaveVectorToFile(FileName, vNames, "Data has been updated in file -> ");

        }
        else {
            cout << "Text wasnt found :-(\n" << endl;

        }
    }

    //for the matrix below dont forget to create array in main -> int x[3][3]
    void FillMatrix(int x[3][3], short rows, short cols)
    {
        short counter = 0;
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                counter++;
                x[i][j] = counter;
            }
        }
    }

    void PrintMatrix(int x[3][3], short rows, short cols)
    {
        cout << "The following is a 3x3 matrix\n";

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                cout << setw(3) << left << x[i][j] << "    ";
            }
            cout << endl;
        }
    }

    void PrintTranspose(int x[3][3], short rows, short cols)
    {
        cout << "The following is a 3x3 matrix Transpose\n";
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                cout << setw(4) << left << x[j][i] << "   "; //trick is here [j][i]
            }
            cout << endl;
        }

    }

    void SumMatrixRows(int x[3][3], short rows, short cols)
    {

        for (int i = 0; i < rows;i++)
        {
            int sum = 0;
            for (int j = 0;j < cols;j++)
            {
                sum += x[i][j];
            }
            cout << "Row [" << i + 1 << "] sum: " << sum;
            cout << endl;
        }
    }

    //another better way to sum the rows
    //The file.txt for this array tasks is at \courses\course7

    int RowSum(int x[3][3], short rows, short cols)
    {
        int sum = 0;
        for (int j = 0;j < cols;j++)
        {
            sum += x[rows][j];
        }
        return sum;
    }

    void PrintEachRowSum(int x[3][3], short rows, short cols)
    {
        cout << "Each row sum\n";
        for (int i = 0;i < rows;i++)
        {
            cout << "Row [" << i + 1 << "] sum = " << RowSum(x, i, cols) << endl;
        }

    }

    void FillArrY(int y[3], int x[3][3], short rows, short cols)
    {
        //main  -> int y[3] , int x[3][3] // this is the rows sums in 1D array

        for (int i = 0;i < rows;i++)
        {
            y[i] = RowSum(x, i, cols);
        }
    }

    void PrintarrY(int y[3], short rows)
    {
        //main  -> int y[3] , int x[3][3] // this is the rows sums in 1D array

        for (int i = 0;i < rows;i++)
        {
            cout << "sum of row [" << i + 1 << "] = " << y[i] << endl;
        }
    }

    int ColSum(int x[3][3], short rows, short cols)
    {
        int sum = 0;
        for (int i = 0; i < rows;i++)
        {
            sum += x[i][cols];
        }
        return sum;
    }

    void FillArrC(int c[3], int x[3][3], short rows, short cols)
    {
        //main  -> int c[3] , int x[3][3] // this is the cols sums in 1D array

        for (int j = 0;j < cols;j++)
        {
            c[j] = ColSum(x, rows, j);
        }
    }

    void PrintArrC(int c[3], short cols)
    {
        for (int j = 0;j < cols;j++)
        {
            cout << "Col [" << j + 1 << "] sum = " << c[j] << endl;
        }
    }

    void MultiMatrixes(int x[3][3], int y[3][3], int c[3][3], short rows, short cols)
    {
        for (int i = 0; i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                c[i][j] = x[i][j] * y[i][j];
            }
        }
    }

    void PrintMatrixes(int x[3][3], short rows, short cols)
    {
        cout << "The following is a 3x3 matrix\n";

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                printf("%02d   ", x[i][j]);
            }
            cout << endl;
        }
    }

    void PrintMiddleRow(int x[3][3], short rows, short cols)
    {
        short middlerow = rows / 2;
        cout << "Middle row is\n";

        for (int j = 0;j < cols;j++)
        {
            printf("%02d  ", x[middlerow][j]);
        }
        cout << endl;
    }

    void PrintMiddleCol(int x[3][3], short rows, short cols)
    {
        short middleCol = cols / 2;
        cout << "Middle Col is\n";

        for (int i = 0;i < rows;i++)
        {
            printf("%02d\n", x[i][middleCol]);
        }
        cout << endl;
    }

    int SumOfMatrix(int x[3][3], short rows, short cols)
    {
        int sum = 0;

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                sum += x[i][j];
            }
        }
        return sum;
    }

    bool Is_Identity(int x[3][3], short rows, short cols)
    {

        //int i[3][3] = { {1,0,0}, {0,1,0}, {0,0,1} }; -> true
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (i == j && x[i][j] != 1)
                {
                    return false;
                }
                else if (i != j && x[i][j] != 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool Is_Typical(int x[3][3], int y[3][3], short rows, short cols)
    {
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (x[i][j] != y[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool Is_Scalar(int x[3][3], short rows, short cols)
    {

        //int i[3][3] = { {1,0,0}, {0,1,0}, {0,0,1} }; -> true

        int first_value = x[0][0];

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (i == j && x[i][j] != first_value)
                {
                    return false;
                }
                else if (i != j && x[i][j] != 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    // here you need to read numberCheck thro a function from lib -> numberCheck = ReadNumber();
    int CheckNumberInMatrix(int x[3][3], short rows, short cols, int numberCheck)
    {
        short counter = 0;

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (numberCheck == x[i][j])
                {
                    counter++;
                }
            }
        }
        return counter;
    }

    void PrintCheckNumberResult(int number, int numberCount)
    {
        if (numberCount > 0)
            cout << "Number " << number << " count in matrix is : " << numberCount;
        else
            cout << "Number " << number << " was not Found";
        cout << endl;
    }

    bool IsSpars(int x[3][3], short rows, short cols)
    {
        short MatrixSize = rows * cols;
        return (CheckNumberInMatrix(x, rows, cols, 0) > (MatrixSize / 2));
    }

    void PrintSparsResult(int x[3][3], short rows, short cols)
    {
        if (IsSpars(x, rows, cols))
            cout << "Yes its sparse" << endl;
        else
            cout << "No its not sparse" << endl;
    }

    float MatrixAvg(int x[3][3], short rows, short cols)
    {
        return (float)MyLib::SumOfMatrix(x, rows, cols) / (rows * cols);
    }

    bool IsNumberExists(int x[3][3], short rows, short cols, int CheckNumber)
    {
        return (CheckNumberInMatrix(x, rows, cols, CheckNumber) > 0);
    }

    void PrintExistsResult(int x[3][3], short rows, short cols, int Number)
    {

        if (!IsNumberExists(x, rows, cols, Number))
        {
            cout << "Number wasnt found in any postion\n";
            return;
        }

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (Number == x[i][j])
                {
                    cout << "Yes its inside the matrix! in postion (" << i << ","
                        << j << ")" << endl;
                }
            }
        }

    }

    bool IsNumberExistsFasterWay(int x[3][3], short rows, short cols, int number)
    {
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (number == x[i][j])
                {
                    return true;
                }
            }
        }
        return false;
    }

    void PrintIntersectedNumbers(int x[3][3], int y[3][3], short rows, short cols)
    {
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                int number = x[i][j];
                if (IsNumberExistsFasterWay(y, 3, 3, number))
                    cout << setw(2) << number << "    ";
            }
        }
    }

    int MaxNumberInMatrix(int x[3][3], short rows, short cols)
    {
        int max_number = x[0][0];

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (i == 0 && j == 0)
                    continue;

                if (x[i][j] > max_number)
                    max_number = x[i][j];
            }
        }
        return max_number;
    }

    int MinNumberInMatrix(int x[3][3], short rows, short cols)
    {
        int min_number = x[0][0];

        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                if (i == 0 && j == 0)
                    continue;

                if (x[i][j] < min_number)
                    min_number = x[i][j];
            }
        }
        return min_number;
    }

    void CopyInRev(int x[3][3], int y[3][3], short rows, short cols)
    {
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols;j++)
            {
                y[i][j] = x[rows - 1 - i][cols - 1 - j];
            }
        }


    }

    bool IsMatrixPlaindrome(int x[3][3], short rows, short cols)
    {
        for (int i = 0;i < rows;i++)
        {
            for (int j = 0;j < cols / 2;j++)
            {
                if (x[i][j] != x[i][cols - 1 - j])
                    return false;
            }
        }
        return true;
    }

    void FibonacciNumberUsingLoop(short number)
    {
        int fibonumber = 0;
        int prev2 = 0, prev1 = 1;
        cout << "1   ";
        for (int i = 2;i <= number;i++)
        {
            fibonumber = prev1 + prev2;
            cout << fibonumber << "  ";
            prev2 = prev1;
            prev1 = fibonumber;
        }
    }

    void FibonacciNumberUsingRecurssion(short number, int prev1 = 0, int prev2 = 1)
    {
        int fibonumber = 0;

        if (number <= 0) return;

        fibonumber = prev1 + prev2;
        cout << fibonumber << "   ";

        //we could use shift here as the previous function 
        //prev2 = prev1 ,  prev1 = fibonumber
        // and then send them to the function below but like this its faster to just send fibonumber and prev1
        //cuz fibonumber is prev1, and prev1 is prev2 after shifting

        FibonacciNumberUsingRecurssion(number - 1, fibonumber, prev1);

    }

    void PrintFirstLetterOfEachWord(string text)
    {
        bool isFirstLetter = true;

        for (int i = 0;i < text.length();i++)
        {
            if (text[i] != ' ' && isFirstLetter)
            {
                cout << text[i] << endl;
            }
            isFirstLetter = (text[i] == ' ' ? true : false);
        }
    }

    string UpperFirstLetterOfEachWord(string& text)
    {
        bool isFirstLetter = true;

        for (int i = 0;i < text.length();i++)
        {
            if (text[i] != ' ' && isFirstLetter)
            {
                text[i] = toupper(text[i]);
            }
            isFirstLetter = (text[i] == ' ' ? true : false);
        }
        return text;
    }

    string FormatToTitleCase(string& text)
    {
        bool isFirstLetter = true;

        for (int i = 0;i < text.length();i++)
        {
            if (text[i] != ' ')
            {
                if (isFirstLetter)
                {
                    text[i] = toupper(text[i]);
                }
                else {
                    text[i] = tolower(text[i]);
                }
            }
            isFirstLetter = (text[i] == ' ' ? true : false);
        }
        return text;
    }

    string ToUpperAllString(string& text)
    {
        for (int i = 0; i < text.length();i++)
        {
            text[i] = toupper(text[i]);
        }
        return text;
    }

    string ToLowerAllString(string& text)
    {
        for (int i = 0; i < text.length();i++)
        {
            text[i] = tolower(text[i]);
        }
        return text;
    }

    char InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    string InvertAllCharacterCase(string& text)
    {
        for (int i = 0; i < text.length();i++)
        {
            text[i] = InvertLetterCase(text[i]);
        }
        return text;
    }

    int TotalLettersInString(string text)
    {
        int counter = 0;
        for (int i = 0;i < text.length();i++)
        {
            if (isalpha(text[i])) counter++;
        }
        return counter;
    }

    int TotalCapitalLetters(string text)
    {
        short UpperCounter = 0;
        for (int i = 0;i < text.length();i++)
        {
            if (isupper(text[i])) UpperCounter++;
        }
        return UpperCounter;
    }

    int TotalLowerLetters(string text)
    {
        short LowerCounter = 0;
        for (int i = 0;i < text.length();i++)
        {
            if (islower(text[i])) LowerCounter++;
        }
        return LowerCounter;
    }

    //Same but better (easy to upgrade & maintain) function than those above using enums 
    // -> enum enWhatToCount { CapitalLetters = 0, SmallLetters, All };
    enum enWhatToCount { CapitalLetters = 0, SmallLetters, All };
    int CountLetters(const string& text, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        int counter = 0;
        for (char c : text)
        {
            switch (WhatToCount)
            {
            case enWhatToCount::CapitalLetters:
                if (isupper(c)) counter++;
                break;
            case enWhatToCount::SmallLetters:
                if (islower(c)) counter++;
                break;
            case enWhatToCount::All:
                if (isalpha(c)) counter++;
                break;
            default:
                break;
            }
        }
        return counter;
    }

    int ChosenLetterRepeatedTimes(const string& text, char ChoseChar, bool MatchCase = true)
    {

        // leave matchcase on true for case sensitive eg: small or capital only
        // while turnin it to false ignore the case sensitive and counts both capital and small

        int CharCounter = 0;

        if (MatchCase)
        {
            for (char c : text)
            {
                if (c == ChoseChar) CharCounter++;
            }
        }
        else {
            for (char c : text)
            {
                if (tolower(c) == tolower(ChoseChar)) CharCounter++;
            }
        }
        return CharCounter;
    }

    void PrintChosenLetterRepeatedTimes(const string& text, bool MatchCase = true)
    {
        char ChoseChar;
        cout << "Choose character to count? ";
        cin >> ChoseChar;
        cin.ignore();

        cout << "Letter (";
        if (MatchCase) cout << ChoseChar;
        else cout << static_cast<char>(toupper(ChoseChar)) << "/" << static_cast<char>(tolower(ChoseChar));
        cout << ") Repeated " << ChosenLetterRepeatedTimes(text, ChoseChar, MatchCase) << " Times." << endl;

    }

    bool isVowel(char c)
    {
        c = tolower(c);

        return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    }

    int VowelsCount(const string& text)
    {
        int VowelCounter = 0;

        for (char c : text)
        {
            if (isVowel(c)) VowelCounter++;
        }
        return VowelCounter;
    }

    void PrintVowels(const string& text)
    {
        bool FoundVowel = false;

        for (char c : text)
        {
            if (isVowel(c))
            {
                cout << c << "  ";
                FoundVowel = true;
            }
        }
        if (!FoundVowel)
        {
            cout << "No Vowels Found!";
        }
        cout << endl;
    }

    void PrintEachWordInString(string text)
    {
        string deli = " ";
        short pos = 0;
        string sWord;

        while ((pos = text.find(deli)) != string::npos)
        {
            sWord = text.substr(0, pos);
            if (sWord != "")
            {
                cout << UpperFirstLetterOfEachWord(sWord) << endl;
            }
            text.erase(0, pos + deli.length());
        }
        if (text != "")
        {
            cout << UpperFirstLetterOfEachWord(text) << endl;
        }
    }

    int CountWordsInString(string text)
    {
        int WordsCounter = 0;
        string deli = " ";
        short pos = 0;
        string sWord;

        while ((pos = text.find(deli)) != string::npos)
        {
            sWord = text.substr(0, pos);

            if (sWord != "") WordsCounter++;
            text.erase(0, pos + deli.length());
        }
        if (text != "") WordsCounter++;

        return WordsCounter;
    }

    string TrimLeft(string text)
    {
        for (int i = 0;i < text.length();i++)
        {
            if (text[i] != ' ')
            {
                return text.substr(i, text.length() - i);
                //return.substr(i) -> it grabs everything from (i) to whatever left in the string 
            }
        }
        return "";
    }

    string TrimRight(string text)
    {
        for (int i = text.length() - 1;i >= 0;i--)
        {
            if (text[i] != ' ')
            {
                return text.substr(0, i + 1);
            }
        }
        return "";
    }

    string Trim(string text)
    {
        return (TrimLeft(TrimRight(text)));
    }

    string JoinString(const vector <string>& vText, string Delim)
    {
        string text = "";
        for (const string& token : vText)
        {
            if (!text.empty())
            {
                text += Delim;
            }
            text += token;
        }
        return text;
    }

    string JoinString(const string arrString[], int length, const string& Delim)
    {
        string text = "";
        for (int i = 0;i < length;i++)
        {
            if (!text.empty())
            {
                text += Delim;
            }
            text += arrString[i];
        }
        return text;
    }

    vector<string> SplitString(string text, string Delim = " ")
    {

        //vector <string> vText -> in main 
        //vText = SplitString(MyLib::readtext(), " ")

        vector <string> vText;
        short pos = 0;
        string sWord;

        while ((pos = text.find(Delim)) != string::npos)
        {
            sWord = text.substr(0, pos);
            sWord = MyLib::Trim(sWord);
            if (sWord != "")
            {
                vText.push_back(sWord);
            }
            text.erase(0, pos + Delim.length());
        }
        text = MyLib::Trim(text);
        if (text != "")
        {
            vText.push_back(text);
        }
        return vText;
    }

    string RevWordsInString(string text, const string& Delim)
    {
        vector <string> vText;
        string revText = "";

        vText = SplitString(text, Delim);

        vector <string>::iterator iter = vText.end();
        while (iter != vText.begin())
        {
            iter--;
            if (!revText.empty())
            {
                revText += Delim;
            }
            revText += *iter;
        }
        return revText;
    }

    string ReplaceWordsInStringWithBulitInFunction(string text, string WordToReplace, string ReplaceTo, bool MatchCase = true)
    {
        if (MatchCase)
        {
            int pos = text.find(WordToReplace);

            while (pos != string::npos)
            {
                text = text.replace(pos, WordToReplace.length(), ReplaceTo);
                pos = text.find(WordToReplace);
            }
        }
        else {
            text = MyLib::ToLowerAllString(text);
            WordToReplace = MyLib::ToLowerAllString(WordToReplace);
            int pos = text.find(WordToReplace);

            while (pos != string::npos)
            {
                text = text.replace(pos, WordToReplace.length(), ReplaceTo);
                pos = text.find(WordToReplace);
            }
        }
        return text;
    }

    string ReplaceWordsInStringCustom(string text, string WordToReplace, string ReplaceTo, bool MatchCase = true)
    {
        vector <string> vText;
        vText = SplitString(text);

        if (MatchCase)
        {
            for (string& line : vText)
            {
                if (line == WordToReplace)
                    line = ReplaceTo;
            }
        }
        else {
            for (string& line : vText)
            {
                if (MyLib::ToLowerAllString(line) == MyLib::ToLowerAllString(WordToReplace))
                    line = ReplaceTo;
            }
        }
        return JoinString(vText, " ");
    }

    string RemovePunctuationsFromString(string text)
    {
        string text2 = "";
        for (int i = 0;i < text.length();i++)
        {
            if (!ispunct(text[i]))
                text2 += text[i];
        }
        return text2;
    }

    void AddDataLineToFile(string FileName, string stDataLine)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl << endl;

            MyFile.close();
        }
    }

    void PressEnterToExit()
    {
        //or we can use system("pasue>0") -> without msg, and ("pause") with msg.
        
        cout << "\nPress Enter to Exit . . . ";
        cin.get();
    }
}