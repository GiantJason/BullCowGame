/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using FTEXT = std::string;
using int32 = int;


void printIntro();
FTEXT getValidGuess();
void playGame();
bool askToPlayAgain();

FBullCowGame BCGame; // instantiate a game, which we re-use across play
bool playAgain = false;
int32 maxTries = BCGame.getMaxTries();

int32 main()
{
	do {
		printIntro();
		playGame();
		if (askToPlayAgain()) {
			playAgain = true;
		}
	} while (playAgain);

	return 0;
}

void printIntro() {
	//introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word guess game.\n" << std::endl;
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.getHiddenWordLen() << " letter isogram I`m thinking of?\n " << std::endl;
}

//loop continuelly until the user get the valid guess
FTEXT getValidGuess() {

	EGuessStatus status = EGuessStatus::Invalid_Status;
	FTEXT Guess = "";

	do {
		int32 currTry = BCGame.getCurrTry();

		//get a guess from a player
		std::cout << "Try " << currTry << " of " << maxTries << ". Enter your guess: ";

		std::getline(std::cin, Guess);

		//check the validity of guess
		status = BCGame.checkGuessValidity(Guess);

		switch (status) {
		case EGuessStatus::NOT_Isogram:
			std::cout << "Please enter a word without repeating letters\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter an isogram of " << BCGame.getHiddenWordLen() << " letters\n";
			break;
		case EGuessStatus::Not_Lower_Case:
			std::cout << "Please enter an isogram with lower cases\n";
			break;
		default:
			//assume that the input guess is right
			status = EGuessStatus::OK;
		}
	} while (status != EGuessStatus::OK);

	return Guess;
}

void playGame() {

	BullCowCount bullCowCount;

	//ask the guess for the number of max loop times
	while (!BCGame.isGameWon(bullCowCount) && BCGame.getCurrTry() <= maxTries) {
		FTEXT guess = getValidGuess();

		//submit valid guess to the game
		bullCowCount = BCGame.submitValidGuess(guess);
		std::cout << "bulls: " << bullCowCount.bulls;
		std::cout << ", cows: " << bullCowCount.cows << "\n\n";
	}
	//game is won
	if (BCGame.isGameWon(bullCowCount)) {
		std::cout << "Congratualions, you`ve won this game!!!\n\n";
		return;
	}

	//max tries used
	std::cout << "Sorry, you`ve just lost the game.\n\n";


}

bool askToPlayAgain()
{
	FTEXT response;
	//ask the player to replay the game or not
	std::cout << "Do you want to play again?(Y/N): ";

	getline(std::cin, response);

	std::cout << std::endl;
	return response[0] == 'Y' || response[0] == 'y';
}


