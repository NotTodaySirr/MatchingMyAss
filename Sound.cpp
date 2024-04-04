#include<iostream>
#include"Sound.h"
#include<Windows.h>

void MatchingSound()
{
	PlaySound(TEXT("MatchingSound.wav"), NULL, SND_FILENAME | SND_SYNC);
}

void IncorrectSound()
{
	PlaySound(TEXT("incorrectSound.wav"), NULL, SND_FILENAME | SND_SYNC);
}

void WinningSound()
{
	PlaySound(TEXT("WinningSound.wav"), NULL, SND_FILENAME | SND_SYNC);
}

void LosingSound()
{
	PlaySound(TEXT("LosingSound.wav"), NULL, SND_FILENAME | SND_SYNC);
}