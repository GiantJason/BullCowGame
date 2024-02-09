#pragma once

#include <iostream>
#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame()
{
	reset();
}

void FBullCowGame::reset()
{
	const int32 MAX_TRIES = 8;
	myMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	hiddenWord = HIDDEN_WORD;

	myCurrTry = 1;
}

int32 FBullCowGame::getCurrTry() const { return myCurrTry; }
bool FBullCowGame::isGameWon(BullCowCount bullCowCount) const { return bullCowCount.bulls == getHiddenWordLen(); }

int32 FBullCowGame::getMaxTries() const {
	TMap<int32, int32> wordLenToMaxTries = { {3, 4}, {4,7}, {5,10}, {6,15} , {7,20} };
	return wordLenToMaxTries[getHiddenWordLen()];
}

int32 FBullCowGame::getHiddenWordLen() const
{
	int wordLen = static_cast<int>(hiddenWord.length());
	return wordLen;
}

BullCowCount FBullCowGame::submitValidGuess(FString guess)
{

	myCurrTry++;
	BullCowCount bullCowCount;

	//loop through all letters and count cows and bulls
	for (int32 i = 0; i < hiddenWord.length(); i++)
	{
		for (int32 j = 0; j < hiddenWord.length(); j++)
		{
			if (guess[i] == hiddenWord[j]) {
				if (i == j) {
					bullCowCount.bulls++;//incriment the bulls
				}
				else {
					bullCowCount.cows++;//incriment the cows
				}
			}
		}
	}

	return bullCowCount;
}

bool FBullCowGame::isIsogram(FString word) const
{
	//treat 0 & 1 letter word as isogram
	if (word.length() <= 1) { return true; }

	//loop through all the letters of the guess and check if it`s an isogram 
	TMap<char, bool> letterSeen;
	for (auto letter : word) {
		letter = tolower(letter); // handle mixed cases
		if (letterSeen[letter]) {
			return false; //is not a isogram
		}
		letterSeen[letter] = true;
	}
	return true;
}

bool FBullCowGame::isLowerCase(FString word) const
{
	for (auto letter : word) {
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const
{
	//if the guess isn`t an isogram 
	if (!isIsogram(guess)) {
		return EGuessStatus::NOT_Isogram;
	}
	//if the guess isn`t all lower case
	if (!isLowerCase(guess)) {
		return EGuessStatus::Not_Lower_Case;
	}
	//if the guess has wrong length
	if (guess.length() != getHiddenWordLen()) {
		return EGuessStatus::Wrong_Length;
	}
	return EGuessStatus::OK;
}
