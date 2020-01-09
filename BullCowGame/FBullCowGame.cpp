#pragma once
#include "pch.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	MyHiddenWord = GetHiddenWord();
	MyCurrentTry = 1;
	bGameIsWin = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return int(MyHiddenWord.length() * 1.5 + 0.5);
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWorldLength() const 
{
	return bool(SelectedLengthHiddenWord) ? SelectedLengthHiddenWord : MyHiddenWord.length();
}

FString FBullCowGame::GetHiddenWord()
{
	return Words[bool(SelectedLengthHiddenWord) ? SelectedLengthHiddenWord : DefaultLengthHiddenWord];
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWin;
}

void FBullCowGame::SelectLengthHiddenWord(int32 Length) {
	SelectedLengthHiddenWord = Length;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWorldLength()) {
		return EGuessStatus::Wtong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	for (int32 i = 0; i < MyHiddenWord.length(); i++) {
		for (int32 j = 0; j < Guess.length(); j++) {
			if (MyHiddenWord[i] == Guess[j] && i==j) {
				BullCowCount.Bulls++;
			}
			else if(MyHiddenWord[i] == Guess[j]) {
				BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == MyHiddenWord.length()) {
		bGameIsWin = true;
	}
	else {
		bGameIsWin = false;
	}

	return BullCowCount;
}
