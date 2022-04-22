#include <iostream>		
#include <fstream>		
#include <string>	
#include <conio.h>		
using namespace std;		

class Hangman {
	string	progress[64];	
	string	problem;		
	string	answer;		
	string	guessed;		
	int	nTries;		
	const int maxTries = 7;	

	void load(const char* progName = "HangmanProgress.txt") {
		ifstream fs(progName);
		if (fs) {
			getline(fs, progress[0]);	// 첫 번째 행은 주석
			for (int i = 0; i < 64; i++)
				getline(fs, progress[i]);
		}
	}
	void print() {
		system("cls");
		cout << "     <Hangman Game>\n";
		for (int i = 0; i < 8; i++)
			cout << '\t' << progress[nTries * 8 + i] << endl;
		cout << "\n\t" << answer;
		cout << "\n\n " << guessed;
	}
	int countMatched(char ch) {
		int nMatched = 0;
		for (int pos = -1; ; ) {
			pos = problem.find(ch, pos + 1);
			if (pos < 0) break;
			answer[pos] = ch;	// 현재 단어를 갱신(맞힌 문자 열기)
			nMatched++;
		}
		return nMatched;
	}
	void guess() {
		char ch = _getch();
		if (ch >= 'a' && ch <= 'z') {
			int pos = guessed.find(ch);
			if (pos < 0) {			// 아직 추측하지 않은 문자
				guessed[ch - 'a'] = ch;	// 예측한 문자 해당 위치 열기
				if (countMatched(ch) == 0) nTries++; // 실패 횟수 증가
			}
		}
	}
public:
	void play(string prob, string kor) {
		load();
		problem = prob;
		answer = string(problem.length(), '-');	// 생성자 사용(7장)
		guessed = string(24, '.');			// 생성자 사용(7장)
		nTries = 0;
		while (nTries < maxTries && answer != problem) {
			print();
			guess();
		}
		print();
		cout << "\n\t" << ((nTries == maxTries) ? "실패" : "정답") << endl;
	}
};