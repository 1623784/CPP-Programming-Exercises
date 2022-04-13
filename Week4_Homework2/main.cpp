#include "matter2.h"



static void init() {
	for (int i = 0; i < DIM * DIM - 1; i++)
		map[i / DIM][i % DIM] = i + 1;
	map[DIM - 1][DIM - 1] = 0;
	x = DIM - 1; y = DIM - 1;

	srand(time(NULL));
	st = clock();
	tt= 0;
}

static void display() {
	system("cls");
	printf("\t3x3 \n\t");

	for (int r = 0; r < DIM; r++) {
		for (int c = 0; c < DIM; c++) {
			if (map[r][c] > 0)
				printf("%3d", map[r][c]);
			else printf("   ");
		}
		printf("\n\t");
	}

	clock_t t1 = clock();
	double d = (double)(t1 - st) / CLOCKS_PER_SEC;
	printf("\t횟수 : %6\n\t시간 : %3 f\n\n", nm, d);
}

static bool move(int dir) {
	if (dir == Right && x > 0) {
		map[y][x] = map[y][x - 1];
		map[y][--x] = 0;
	}
	else if (dir == Left && x < DIM - 1) {
		map[y][x] = map[y][x + 1];
		map[y][++x] = 0;
	}
	else if (dir == Up && y < DIM - 1) {
		map[y][x] = map[y + 1][x];
		map[++y][x] = 0;
	}
	else if (dir == Down && y > 0) {
		map[y][x] = map[y - 1][x];
		map[--y][x] = 0;
	}
	else return false;

	nm++;
	return true;
}

static void shuffle(int sff) {
	for (int i = 0; i < sff; i++) {
		int key = DirKey[rand() % 4];
		if (move(key) == false) { i--; continue; }
		display();
		Sleep(50);
	}
}

static bool isDone() {
	for (int r = 0; r < DIM; r++) {
		for (int c = 0; c < DIM; c++) {
			if (map[r][c] != r * DIM + c + 1)
				return (r == DIM - 1) && (c == DIM - 1);
		}
	}
	return true;
}

static int getDirKey() { return _getche() == 224 ? _getch() : 0; }




static int mapTmp[DIM][DIM];
static int history[1000];
static int nh = 0, _x, _y;

void backupInitMap(bool backup = true) {
	if (backup) {
		for (int i = 0; i < DIM; i++)
			for (int j = 0; j < DIM; j++)
				mapTmp[i][j] = map[i][j];
		_x = x;
		_y = y;
	}
	else {
		for (int i = 0; i < DIM; i++)
			for (int j = 0; j < DIM; j++)
				map[i][j] = mapTmp[i][j];
		_x = x;
		_y = y;
	}
}

int play3x3() {
	init();


	display();
	printf("\n 퍼즐 섞기");
	_getche();
	shuffle(20);

	backupInitMap();

	printf("\n 게임 시작");
	_getche();

	tt= 0;
	nh = 0;
	while (!isDone()) {
		history[nh] = getDirKey();
		move(history[nh]);
		display();
		nh++;
	}
	printf("\n re");
	_getche();

	init();
	backupInitMap(false);
	display();
	printf("\n 아무키누르기");
	_getche();

	for (int i = 0; i < nh; i++) {
		move(history[i]);
		display();
		Sleep(200)
			;
	}
	return 1;
}