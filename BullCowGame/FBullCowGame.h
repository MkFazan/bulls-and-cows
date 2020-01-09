#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wtong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWorldLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset();
	void SelectLengthHiddenWord(int32);
	FBullCowCount SubmitValidGuess(FString);

	const int32 DefaultLengthHiddenWord = 3;

private:
	TMap<int32, FString> Words{ {2, "or"}, {3, "end"}, {4, "qwer"}, {5, "pasta"}, {6, "zxcvbn"} };
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWin = false;
	int32 SelectedLengthHiddenWord = 0;

	FString GetHiddenWord();
	
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
