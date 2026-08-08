
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

void SetColor(int Color)
{
    system("color");
}
enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber;
    enChoice PlayerChoice;
    enChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadHowManyRounds()
{
    short Number = 0;

    do
    {
        cout << "How Many Rounds (1-10)? ";
        cin >> Number;

    } while (Number < 1 || Number > 10);

    return Number;
}

enChoice ReadPlayerChoice()
{
    short Choice = 0;

    do
    {
        cout << "\nYour Choice: [1]Stone [2]Paper [3]Scissors ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 3);

    return (enChoice)Choice;
}

enChoice GetComputerChoice()
{
    return (enChoice)RandomNumber(1, 3);
}
string ChoiceName(enChoice Choice)
{
    switch (Choice)
    {
    case Stone:
        return "Stone";

    case Paper:
        return "Paper";

    case Scissors:
        return "Scissors";
    }

    return "";
}

enWinner WhoWonRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case Stone:

        if (RoundInfo.ComputerChoice == Paper)
            return Computer;
        else
            return Player;

    case Paper:

        if (RoundInfo.ComputerChoice == Scissors)
            return Computer;
        else
            return Player;

    case Scissors:

        if (RoundInfo.ComputerChoice == Stone)
            return Computer;
        else
            return Player;
    }

    return Draw;
}

string WinnerName(enWinner Winner)
{
    switch (Winner)
    {
    case Player:
        return "Player";

    case Computer:
        return "Computer";

    default:
        return "No Winner";
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    if (RoundInfo.Winner == Player)
    {
        system("color 2F");   // √Œ÷—
    }
    else if (RoundInfo.Winner == Computer)
    {
        system("color 4F");   // √Õ„—
    }
    else
    {
        system("color 6F");   // √’›—
    }

    cout << "\n________________ Round ["
        << RoundInfo.RoundNumber
        << "] _________________\n\n";

    cout << "Player Choice   : "
        << ChoiceName(RoundInfo.PlayerChoice) << endl;

    cout << "Computer Choice : "
        << ChoiceName(RoundInfo.ComputerChoice) << endl;

    switch (RoundInfo.Winner)
    {
    case Player:
        SetColor(10);   // √Œ÷—
        break;

    case Computer:
        SetColor(12);   // √Õ„—
        break;

    case Draw:
        SetColor(14);   // √’›—
        break;
    }

    cout << "Round Winner    : "
        << RoundInfo.WinnerName << endl;

    SetColor(7);   // Ì—Ã⁄ «··Ê‰ ≈·Ï «·√»Ì÷

    cout << "\n_________________________________________\n";
}stRoundInfo PlayRound(short RoundNumber)
{
    stRoundInfo Round;

    Round.RoundNumber = RoundNumber;
    Round.PlayerChoice = ReadPlayerChoice();
    Round.ComputerChoice = GetComputerChoice();
    Round.Winner = WhoWonRound(Round);
    Round.WinnerName = WinnerName(Round.Winner);

    PrintRoundResults(Round);

    return Round;
}

enWinner WhoWonGame(short PlayerWonTimes,
    short ComputerWonTimes)
{
    if (PlayerWonTimes > ComputerWonTimes)
        return Player;

    if (ComputerWonTimes > PlayerWonTimes)
        return Computer;

    return Draw;
}stGameResults FillGameResults(short GameRounds,
    short PlayerWonTimes,
    short ComputerWonTimes,
    short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.PlayerWonTimes = PlayerWonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonGame(PlayerWonTimes, ComputerWonTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;

    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;

    for (short Round = 1; Round <= HowManyRounds; Round++)
    {
        RoundInfo = PlayRound(Round);

        switch (RoundInfo.Winner)
        {
        case Player:
            PlayerWonTimes++;
            break;

        case Computer:
            ComputerWonTimes++;
            break;

        default:
            DrawTimes++;
            break;
        }
    }

    return FillGameResults(
        HowManyRounds,
        PlayerWonTimes,
        ComputerWonTimes,
        DrawTimes);
}void ShowFinalGameResults(stGameResults GameResults)
{

    cout << "\n\n";
    cout << "=========================================\n";
    cout << "           Final Game Results\n";
    cout << "=========================================\n";

    cout << "Game Rounds      : " << GameResults.GameRounds << endl;
    cout << "Player Won Times : " << GameResults.PlayerWonTimes << endl;
    cout << "Computer Won     : " << GameResults.ComputerWonTimes << endl;
    cout << "Draw Times       : " << GameResults.DrawTimes << endl;
    cout << "Winner           : " << GameResults.WinnerName << endl;

    cout << "=========================================\n";
}void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");

        stGameResults GameResults =
            PlayGame(ReadHowManyRounds());

        ShowFinalGameResults(GameResults);

        cout << "\nDo You Want To Play Again? (Y/N): ";
        cin >> PlayAgain;

    } while (toupper(PlayAgain) == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    system("pause");
    return 0;
}
