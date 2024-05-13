#include<iostream>
#include<cstdlib>
#include<string>
using namespace std;

enum enGameChoice { stone = 1, Paper = 2, scissors = 3 };
enum enWinner { Player = 1, Computer = 2, draw = 3 };

struct stRoundInfo
{
	short Round = 0;
	enGameChoice PlayerChoice;
	enGameChoice Computerchoice;
	enWinner winner;
	string WinnerName;

};

struct stGameResult
{
	short GameRound = 0;
	short PlayerWinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner  GameResult;
	string WinnerName = " ";
};


int RandomNumber(int from, int to)
{
	int Random = rand() % (to - from + 1) + from;
	return Random;

}

short HowManyRound()
{
	short NombreDeJeux;
	do
	{
		cout << " Enter nobre de jeux entre 1 et 10 " << endl;
		cin >> NombreDeJeux;
	} while (NombreDeJeux < 0 || NombreDeJeux>10);

	return NombreDeJeux;

}

enGameChoice ReadPlayerChoice()
{
	short choice = 1;
	do
	{
		cout << "\n\nyour choice: [1]:Stone, [2]: Paper, [3]: scissors ? ";
		cin >> choice;
	} while (choice < 1 || choice >3);

	return (enGameChoice)choice;
}

enGameChoice ReadComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);

}


string WinnerName(enWinner winner)
{
	string ArrWinnerName[3] = { "Player", "Computer" , " No winner" };

	return ArrWinnerName[winner - 1];
}

string choiceName(enGameChoice choice)
{
	string ArrGameChoice[3] = { "Stone" , "Paper", " scissors" };
	return (ArrGameChoice)[choice - 1];


}


enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.Computerchoice)
	{
		return enWinner::draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::stone:
		if (RoundInfo.Computerchoice == enGameChoice::Paper)

		{
			return  enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.Computerchoice == enGameChoice::scissors)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::scissors:
		if (RoundInfo.Computerchoice == enGameChoice::stone)
		{
			return enWinner::Computer;
		}
		break;

	}


	enWinner::Player;

}

enWinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
		return enWinner::Player;
	else if (PlayerWinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::draw;


}

void AfficherCouleurWinner(enWinner winner)
{
	switch (winner)
	{
	case enWinner::Player:
	{
		system("color 2F");
		break;
	}
	case enWinner::Computer:

	{
		system("color 4F");
		cout << "\a";
		break;
	}
	default:
	{
		system(" color 6F");
		break;
	}
	}

}

void PrintRoundResult(stRoundInfo RoundInfo)
{

	{
		cout << "\n--------Round["<< RoundInfo.Round<<"]-------------------\n";
		cout << " Player choice   : " << choiceName(RoundInfo.PlayerChoice) << endl;
		cout << " Computer choice : " << choiceName(RoundInfo.Computerchoice) << endl;
		cout << " Round Winner    : " << RoundInfo.WinnerName << endl;
		cout<<"-------------------------------------\n";
		AfficherCouleurWinner(RoundInfo.winner);

	}


}
stGameResult FillGameResults(short GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResults;

	GameResults.GameRound = GameRounds;
	GameResults.PlayerWinTimes = PlayerWinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameResult = WhoWinTheGame(PlayerWinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameResult);

	return GameResults;


}
string Tabs(short nomberofTabs)
{
	string t = " ";
	t = t + "\t";
	return t;

}

void AfficherLeTitre()
{
	cout << Tabs(2) << "\t\t\t-------------------------------------------------\n";
	cout << Tabs(2) << "\t\t\t ++++++ G a m e   O v e r ++++++\t\n";
	cout << Tabs(2) << "\t\t\t-------------------------------------------------\n";
}

stGameResult PlayGame(short NombredeJeux)
{

	stRoundInfo RoundInfo;
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short i = 1; i <= NombredeJeux; i++)
	{
		cout << "\n\nRound [ " << RoundInfo.Round +1 << " ] begins " << endl;
		RoundInfo.Round = i;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.Computerchoice = ReadComputerChoice();
		RoundInfo.winner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.winner);


		if (RoundInfo.winner == enWinner::Player)
			PlayerWinTimes++;

		else if (RoundInfo.winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}

	return FillGameResults(NombredeJeux, PlayerWinTimes, ComputerWinTimes, DrawTimes);

}

void ShowFinalGame(stGameResult GameResults)
{
	cout << Tabs(2) << "\n\t\t\t\t------------------ [Game Results]--------------" << endl;
	cout << Tabs(2) << "\t\t\tGame Rounds      : " << GameResults.GameRound << endl;
	cout << Tabs(2) << "\t\t\tPlayer Won Times : " << GameResults.PlayerWinTimes << endl;
	cout << Tabs(2) << "\t\t\tComuter Win Times: " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << "\t\t\tDraw Times       : " << GameResults.DrawTimes << endl;

	cout << Tabs(2) << "\t\t\tFinal Winer      : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "\t\t\t----------------------------------------------------" << endl;


	AfficherCouleurWinner(GameResults.GameResult);
}

void Renesialiser()
{
	system("cls");
	system("color 0F");

}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		Renesialiser();

		stGameResult GameResults = PlayGame(HowManyRound());
		AfficherLeTitre();
		ShowFinalGame(GameResults);
		cout << endl << Tabs(3) << "\ndo you want to play again?(Y/N) ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');



}



int main()
{
	srand((unsigned)time(NULL));

	StartGame();
	return 0;
}