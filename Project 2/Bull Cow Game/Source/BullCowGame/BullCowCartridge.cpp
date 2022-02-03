// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "IsogramList.h"

// Called On Game Start
void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();

    DebuggingEnabled = true;

    // Greet User
    PrintLine(TEXT("Welcome to Bull Cows!"));
    BeginGame();
}

// Called On Player Input
void UBullCowCartridge::OnInput(const FString& Input) {

    ClearScreen();

    if (IsGameOver) {

        // Check Whether to Start New Game
        if (Input == "yes") {
            BeginGame();
        } else {

        }
 
    } else {

        // Verify Input
        if (Input.Len() != Isogram.Len()) {
            Lives--;
            PrintLine(TEXT("You goofed the length. (Lives: %i/%i)"), Lives, Isogram.Len());
        } else {
            if (Input == Isogram) {
                PrintLine(TEXT("Yarp"));
            } else if (Lives != 1) {
                Lives--;
                PrintLine(TEXT("Narp. (Lives: %i/%i)"), Lives, Isogram.Len());
            }
        }

        // Check For No Lives
        if (Lives == 0) {
            PrintLine(TEXT("You done goofed Ayayron."));
            EndGame();
        }
    }
}

// Initializes Member Variables & Prompts Player
void UBullCowCartridge::BeginGame() {

    // Initialize Member Variables
    IsGameOver = false;
    Isogram = TEXT("bread");
    Lives = Isogram.Len();
    const TCHAR IsogramCharArray[] = TEXT("bread");

    if (DebuggingEnabled) {
        PrintLine(FString::Printf(TEXT("Isogram: %s"), *Isogram));
    }

    // Prompt User
    PrintLine(FString::Printf(TEXT("Guess the %i letter word."), Isogram.Len()));
}

// Resets Game Variables, Prompts User to Continue
void UBullCowCartridge::EndGame() {
    IsGameOver = true;
    PrintLine(TEXT("Play again? (yes/no)"));
}