#include "Hangman.h"
#include "MyDic.h"
void main()
{
	Hangman	game;   //���� 
	MyDic	word;


	word.load("fff.word");
	int j = rand() % word.count();
	game.play(word.getE(j), word.getK(j)); //��� ���� bring
}