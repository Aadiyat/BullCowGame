
#pragma once
#include <string>

// Use a struct to group number of bulls and cows in one variable
struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

// Use enum to refer to errors by name rather than by number
enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	FBullCowGame(); /

	int GetMaxTries() const;
	int getCurrentTry() const;
	int getHiddenWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValidity(std::string Guess) const;

	void Reset();
	char GetDifficulty();
	std::string SetHiddenWord();
	FBullCowCount SubmitValidGuess(std::string Guess);

	
private:
	// See constructor for initialisation
	int  MyCurrentTry;
	std::string MyHiddenWord;
	bool bWinStatus;

	bool IsIsogram(std::string) const;
	bool IsLowercase(std::string) const;
};