typedef struct Player {
	int x;
	int y;
	bool out;
	//bool com; // True : C'est l'ordinateur qui joue !
	//char* name;
} Player;

typedef struct Cell {
	bool occupied;
	bool existe;
	bool hover;
} Cell;

typedef struct Move {
	int pid;
	int fx;
	int fy;
	int tx;
	int ty;
	int dx;
	int dy;
	struct Move* next;
	struct Move* prev;
} Move;

typedef struct Game {
	bool    play; // 
	int     numplayers;
	int     width;
	int     height;
	int     turn;
	int     step; // 0 : move ; 1 : remove !
	Cell**  board;
	Player* players;
	Move*   history;
} Game;

Game game; // La structure du jeu
int current; // La page actuelle
SDL_Surface* screen,*s;
TTF_Font* font, *fontb;
int cmm;