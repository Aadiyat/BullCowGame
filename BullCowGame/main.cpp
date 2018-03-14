/*
This is the console exucutable.
This handles user interaction
Game logic is in BullCowGame class
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetValidGuess();
void PrintGuess(std::string Guess);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate new game which is reused across plays

					 // the entry point for the application
					 // The main game loop will repeat if the player decides to play again.
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}


void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a word puzzle game.\n";
	std::cout << "          |\\__________________/|          " << std::endl;
	std::cout << "          \\___________________/           " << std::endl;
	std::cout << "             |  _        _  |              " << std::endl;
	std::cout << "             | |_|      |_| |              " << std::endl;
	std::cout << "              \\            /              " << std::endl;
	std::cout << "               \\          /               " << std::endl;
	std::cout << "                \\________/                " << std::endl;
	std::cout << "                 \\o____o/                 " << std::endl;
	std::cout << "___________________________________________" << std::endl;

	std::cout << std::endl;

	return;
}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset(); // Reset is called at the start of PlayGame
					// The variable initialisations for a new game are in the reset() method
	int maxTries = BCGame.GetMaxTries();
	std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram?\n";
	std::cout << "Maximum number of turns: " << maxTries << "\n\n";

	// Game runs until the player guesses the word or runs out of tries
	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries) {
		std::string Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// Loop continually till user enters valid guess
std::string GetValidGuess()
{
	std::string Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid; // Initialise Status to invalid till we confirm it's OK

	do {
		int currentTry = BCGame.getCurrentTry();
		std::cout << "Current try: " << currentTry << " of " << BCGame.GetMaxTries() << std::endl;
		std::cout << "Enter your guess: ";
		getline(std::cin, Guess);

		// Returns status of word
		Status = BCGame.checkGuessValidity(Guess);

		// Based on word status send error message to user or continue with valid guess
		switch (Status) {
		case EGuessStatus::Wrong_Length: // Same as saying if Status == EGuessStatus::Wrong_Length
			std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter guess in all lowercase.\n\n";
			break;
		default:
			// Assume that the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Ask for guess till player inputs a valid guess
	return Guess;
}

void PrintGuess(std::string Guess)
{
	std::cout << "Your guess was: " << Guess << std::endl;
	return;
}

// Asks the player if they want to play again. Returns true if the player enters y or Y
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (Y/N) ";
	std::string Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

// Prints a message depending on whether the player has won the game or not
void PrintGameSummary()
{
	if (BCGame.isGameWon()) {
		std::cout << "You won!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
	return;
}