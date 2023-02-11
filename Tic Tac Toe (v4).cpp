#include <iostream>
#include "MyLib.h"
using namespace std;

enum enGameChoices { X = 1, O };
struct stPlayerChoice { short Row = 0, Col = 0; };

short ReadTheGameDimension()
{
    cout << "Please Enter The Game Dimension [3:9]: ";
    return MyLib::ReadNumber(3, 9);
}
char PlayerName(enGameChoices GC)
{
    char Arr[2] = { 'X', 'O' };
    return Arr[GC - 1];
}

bool FindItemIn2DArr(short** XOBoard, stPlayerChoice PChoice)
{
    return XOBoard[PChoice.Row - 1][PChoice.Col - 1] == enGameChoices::O
        || XOBoard[PChoice.Row - 1][PChoice.Col - 1] == enGameChoices::X;
}

void Create2DDynamicArr(short** XOBoard, short GameDimension)
{
    for (short i = 0; i < GameDimension; i++)
        XOBoard[i] = new short[GameDimension];
}
void Delete2DDynamicArr(short** XOBoard, short GameDimension)
{
    for (short i = 0; i < GameDimension; i++)
        delete[] XOBoard[i];
    delete[] XOBoard;
}

void PrintXO2DArr(short** XOBoard, short BoardSize)
{
    cout << "\n___________________________________________________\n" << endl;
    for (short x = 0; x < BoardSize; x++)
    {
        for (short y = 0; y < BoardSize; y++)
        {
            char c = '.';
            if (XOBoard[x][y] == enGameChoices::X)
                c = 'X';
            else if (XOBoard[x][y] == enGameChoices::O)
                c = 'O';
            cout << "    " << c << " ";
        }
        cout << endl << endl;
    }
    cout << "\n___________________________________________________" << endl;
}

short AreTheRowValueEqual(short** XOBoard, short GameDimension, stPlayerChoice PChoice)
{
    enGameChoices value = (enGameChoices)XOBoard[PChoice.Row - 1][0];
    short row = 0;
    for (short i = 0; i < GameDimension; i++)
    {
        if (value == XOBoard[PChoice.Row - 1][i])
            row++;
    }
    if (row == GameDimension)
        return row;
    return false;
}
short AreTheColValueEqual(short** XOBoard, short GameDimension, stPlayerChoice PChoice)
{
    enGameChoices value = (enGameChoices)XOBoard[0][PChoice.Col - 1];
    short Col = 0;
    for (short i = 0; i < GameDimension; i++)
    {
        if (value == XOBoard[i][PChoice.Col - 1])
            Col++;
    }
    if (Col == GameDimension)
        return Col;
    return false;
}

short IsThereAWinner(short** XOBoard, short GameDimension, stPlayerChoice PChoice)
{
    short RowWinner = 0, ColWinner = 0;
    enGameChoices value = (enGameChoices)XOBoard[PChoice.Row - 1][PChoice.Col - 1];

    RowWinner = AreTheRowValueEqual(XOBoard, GameDimension, PChoice);
    if (RowWinner == GameDimension)
        return value;

    ColWinner = AreTheColValueEqual(XOBoard, GameDimension, PChoice);
    if (ColWinner == GameDimension)
        return value;
    else
    {
        short x = 1, Diagonal = 0, RightDiagonal = 0;
        for (short i = 0; i < GameDimension; i++)
        {
            for (short j = 0; j < GameDimension; j++)
            {
                if ((j == GameDimension - x) && value == XOBoard[i][j])
                    RightDiagonal++;
                if (i == j && value == XOBoard[i][j])
                    Diagonal++;
            }
            x++;
        }
        if (RightDiagonal == GameDimension || Diagonal == GameDimension)
            return value;
        else
            return false;
    }
}

void PlayGame()
{
    stPlayerChoice PChoice;
    short Steps = 0, TheWinner, Trials = 1;
    short GameDimension = ReadTheGameDimension();
    short** XOBoard = new short* [GameDimension];
    Create2DDynamicArr(XOBoard, GameDimension);

    PrintXO2DArr(XOBoard, GameDimension);

    bool turn = 0;
    while (true)
    {
        if (Steps == GameDimension * GameDimension)
        {
            cout << "\nTie.";
            break;
        }
        enGameChoices Player = enGameChoices::X;
        if (turn == 1)
            Player = enGameChoices::O;

        cout << "\nPlayer " << PlayerName(Player) << " Turn. Enter Empty Location (r, c): ";
        cin >> PChoice.Row >> PChoice.Col;

        if (PChoice.Row < 1 || PChoice.Col < 1 || PChoice.Row > GameDimension || PChoice.Col > GameDimension || FindItemIn2DArr(XOBoard, PChoice))
        {
            cout << "\nInvalid input. Try again.\n";
            continue;
        }
        XOBoard[PChoice.Row - 1][PChoice.Col - 1] = Player;
        PrintXO2DArr(XOBoard, GameDimension);
        if (Trials >= GameDimension + GameDimension - 1)
        {
            TheWinner = IsThereAWinner(XOBoard, GameDimension, PChoice);
            if (TheWinner == enGameChoices::O || TheWinner == enGameChoices::X)
            {
                cout << "\nPlayer " << PlayerName(Player) << " Won.";
                break;
            }
        }
        turn = !turn;
        Steps++;
        Trials++;
    }
    Delete2DDynamicArr(XOBoard, GameDimension);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}
int main()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayGame();
        printf("\n\nDo you Want to Play again? [N/Y]  ");
        cin >> PlayAgain;
    } while (MyLib::CheckChar(PlayAgain));
    return 0;
}