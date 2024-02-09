#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct BullCowCount 
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status, OK, NOT_Isogram, Wrong_Length, Not_Lower_Case
};

enum class EResetStatus 
{
	OK, No_Hidden_Word
};

class FBullCowGame 
{
public:
	FBullCowGame();
	void reset(); 
	int32 getMaxTries() const;// get max tries of a BC game
	int32 getCurrTry() const; // get current try of a BC game
	int32 getHiddenWordLen() const;
	BullCowCount submitValidGuess(FString);
	bool isGameWon(BullCowCount) const; // check whether game is won 
	EGuessStatus checkGuessValidity(FString) const; // check the validility of player`s input string 

private:
	int32 myCurrTry;
	int32 myMaxTries;
	FString hiddenWord;

	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;
};