#pragma once
#include "FBullCowGame.h"

#include <map>
#include <iostream>

#define  TMap std::map

FBullCowGame::FBullCowGame()
{
	bWinStatus = false;
	MyCurrentTry = 0;
	MyHiddenWord = "";
}

// Getters
int  FBullCowGame::GetMaxTries() const {
	TMap<int, int> WordLengthToMaxTries{ { 3, 6 },{ 4, 8 },{ 5, 10 },{ 6, 14 },{ 7, 20 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int  FBullCowGame::getCurrentTry() const { return MyCurrentTry; }

int FBullCowGame::getHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::isGameWon() const { return bWinStatus; }


void FBullCowGame::Reset()
{
	// Initialise Hidden Word
	// Reset MyCurrentTry and MyMaxTries

	MyHiddenWord = SetHiddenWord();	// Prompt user to choose difficulty and set corresponding hidden word
	MyCurrentTry = 1;
	bWinStatus = false;

	return;
}

// Run incoming guess through error checking functions and return a status for the word
EGuessStatus FBullCowGame::checkGuessValidity(std::string Guess) const
{
	if (!IsIsogram(Guess))// If the guess isn't an isogram 
		return EGuessStatus::Not_Isogram;
	else if (!IsLowercase(Guess))// If the guess isn't all lowercase 
		return EGuessStatus::Not_Lowercase;
	else if (Guess.length() != getHiddenWordLength()) // If length of guess not equal to length of word
		return EGuessStatus::Wrong_Length;
	else // Otherwise
		return EGuessStatus::OK;
}

// Receives a valid guess, increments turns and returns number of Bulls and Cows
FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{
	MyCurrentTry++;

	FBullCowCount BCCount; 
	int HWChar, GChar;
	int WordLength = MyHiddenWord.length(); // Assuming Guess and Hidden word have same length

	// Loop through all letters in the hidden word
	for (HWChar = 0; HWChar < WordLength; HWChar++) {
		// Compare letters against the guess one at a time
		for (GChar = 0; GChar < WordLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[HWChar]) {	// If they match 
				if (HWChar == GChar) { // if they are in the same place increment bull
					BCCount.Bulls += 1;
				}
				else {	//else increment cows
					BCCount.Cows += 1;
				}
			}
		}
	}
	if (BCCount.Bulls == WordLength) {
		bWinStatus = true;
	}
	else {
		bWinStatus = false;
	}
	return BCCount;
}

// Checks if the guess is an isogram
bool FBullCowGame::IsIsogram(std::string Word) const
{
	if (Word.length() < 2) {	// Treat 0 and 1 letter strings as isograms
		return true;
	}

	TMap<char, bool> LetterSeen;	// letters previously seen are marked true to can check for duplicates
	for (auto Letter : Word) {
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
			return false;
		else
			LetterSeen[Letter] = true;
	}
	return true;
}

// Checks whether every letter in the guess is lower case
bool FBullCowGame::IsLowercase(std::string Word) const
{
	if (Word.length() < 1)
		return true;
	for (auto Letter : Word) {
		if (Letter == ' ')
			return false;
		else if (!islower(Letter))
			return false;
	}
	return true;
}

//Selects the Hidden Word from a predetermined set based on the users choice of difficulty
std::string FBullCowGame::SetHiddenWord()
{
	std::map<int, std::string> DifficultyToHiddenWord {{1, "ant"}, {2, "dark"}, {3, "spade"}, {4, "planet"}, {5, "harmony"} };
	
	return DifficultyToHiddenWord[GetDifficulty()];
}

//Gets the difficulty level the user wants to play at
char FBullCowGame::GetDifficulty()
{
	int Difficulty;
	do {
		std::cout << "Enter a number between 1 and 5 to choose difficulty.\n";
		std::cout << "1 is easy, 5 is hard\n";
		std::cin >> Difficulty;
		std::cin.ignore(20, '\n');
		std::cout << std::endl;
	} while (!(Difficulty >= 1 && Difficulty <= 5));
	
	return Difficulty;
}
