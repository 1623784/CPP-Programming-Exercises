#include "Hangman.h"
#include "MyDic.h"
void main()
{
	Hangman	game;   //선언 
	MyDic	word;


	word.load("fff.word");
	int j = rand() % word.count();
	game.play(word.getE(j), word.getK(j)); //언어 각각 bring
}