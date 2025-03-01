#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintGameSummary();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame;
void SelectLengthHiddenWord();

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		if (bPlayAgain) {
			SelectLengthHiddenWord();
		}
	} 
	while (bPlayAgain);

	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();

	return;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wtong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWorldLength() << " letter word." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl << std::endl;
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	
	return Guess;
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWorldLength() << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;

	return;
}

bool AskToPlayAgain() 
{
	FText Response = "";
	do {
		std::cout << "Do you want to play again? (y/n) ";
		std::getline(std::cin, Response);
		std::cout << std::endl;
	} while (!(Response[0] == 'y' || Response[0] == 'Y' || Response[0] == 'n' || Response[0] == 'N'));

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done - you win!!!" << std::endl << std::endl;
	}
	else {
		std::cout << "Better luck next time!" << std::endl << std::endl;
	}
}

void SelectLengthHiddenWord() 
{
	int32 Length;
	FText Str = "";
	do {
		std::cout << "Enter length hidden word (from 2  to 6): ";
		std::getline(std::cin, Str);
		std::cout << std::endl;
		try { 
			Length = stoi(Str);
		}
		catch (const std::exception&) { 
			Length = 0;
		}
	} while (bool(Length) == 0);
	BCGame.SelectLengthHiddenWord(stoi(Str));
	return;
}
