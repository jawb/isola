#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include "structs.h"
#include "methods.h"
#include "draw.h"
#include <math.h>

void NewGame () {
	/**
	Cette fonction initialise le jeu , elle aloue l'espace pour les case du jeu et les joueurs, positionne les joueurs
	et initialise l'historique du jeu
	*/
	// Variables locales :
	int i,j; // les compteurs
	int w,h,n;

	//game.numplayers = Sliders[0].value;
	w = game.width;
	h = game.height; 
	n = game.numplayers;

	//Les allocations
	 //Board
	game.board = (Cell**)malloc(w*sizeof(Cell*));
	for ( i = 0; i < w; i++ ) game.board[i] = (Cell*)malloc(h*sizeof(Cell));

	for ( i = 0; i < w; i++ ) {
		for ( j = 0; j < h ; j++ ) {
			game.board[i][j].occupied = false ;
			game.board[i][j].existe = true ;
			game.board[i][j].hover = false ;
		}
	}
	//Players
	game.players = (Player*)malloc(n*sizeof(Player));

	//Positionement des joueurs :
	// Cas de 2 joueurs !
	game.players[0].x = 0;
	game.players[1].x = w - 1;
	if ( h%2 == 0 ) {
		game.players[0].y = h/2;
		game.players[1].y = h/2 - 1;
	}
	else {
		game.players[0].y = (h-1) / 2;
		game.players[1].y = (h-1) / 2;
	}
	i = game.players[0].x;
	j = game.players[0].y;
	game.board[i][j].occupied = true ;
	i = game.players[1].x;
	j = game.players[1].y;
	game.board[i][j].occupied = true ;
	//Initialisation de l'historique :
	game.history = NULL;

	//Initialisation du step et turn
	game.step = 0;
	game.turn = rand() % game.numplayers ;

	//Hover Cells posiible for this palyer
	SetHover(game.players[game.turn].x,game.players[game.turn].y);
}

//Handling history
void AddHistory() {
	Move * pt = game.history;
	game.history = (Move *)malloc(sizeof(Move));
	game.history->prev = pt;
	game.history->next = NULL;
	if(pt != NULL) pt->next = game.history;
	game.history->dx = -1;
	game.history->dy = -1;
}

void CleanHistory()  {
	if(game.history == NULL) return;
	Move * p = game.history;
	Move * q = game.history->next;
	game.history->next = NULL;
	while ( q != NULL ) {
		p = q;
		q = q->next;
		free(p);
	}
}

bool isNext() {
	if(game.history == NULL) return false;
	switch(game.step){
		case 0 :		
			if(game.history->next != NULL) return true;
			else return false;
		break;
		case 1 :
			if(game.history->dx != -1) return true;
			else return false;
		break;
	}
	return false;
}

bool isPrev() {
	if(game.history == NULL) return false;
	if( game.history->prev != NULL ) return true;
	else return false;
}

void Next() {
	switch(game.step){
		case 0 :
			game.step = 1;
			ResetHover(game.players[game.turn].x,game.players[game.turn].y);
			game.history = game.history -> next;
			game.board[game.players[game.turn].x][game.players[game.turn].y].occupied = false;
			game.players[game.turn].x = game.history->tx;
			game.players[game.turn].y = game.history->ty;
			game.board[game.players[game.turn].x][game.players[game.turn].y].occupied = true;
		break;
		case 1 :
			Remove(game.history->dx,game.history->dy);
			NextTurn(); // Juste pour deux joueurs !
			SetHover(game.players[game.turn].x,game.players[game.turn].y);
		break;
	}
}

void Prev() {
	switch(game.step){
		case 0 :
			ResetHover(game.players[game.turn].x,game.players[game.turn].y);
			game.turn = (game.turn + 1) % game.numplayers; // Valable juste dans le cas de deux joueurs
			game.board[game.history->dx][game.history->dy].existe = true;
			game.step = 1;

		break;
		case 1 :
			game.board[game.players[game.turn].x][game.players[game.turn].y].occupied = false;
			game.players[game.turn].x = game.history->fx;
			game.players[game.turn].y = game.history->fy;
			game.board[game.players[game.turn].x][game.players[game.turn].y].occupied = true;
			game.history = game.history -> prev;

			SetHover(game.players[game.turn].x,game.players[game.turn].y);
			game.step = 0;
		break;
	}
}

int Length() {
	int i=0;
	Move * p = game.history;
	while ( p != NULL ) {
		i++;
		p = p->next;
	}
	return i;
}

//Hover

void ResetHover(int x, int y)  {
	int i,j;
	int w = game.width;
	int h = game.height;
	for ( i = x-1; i < x+2; i++ )
	for ( j = y-1; j < y+2; j++ ) {
		if ( i>=0 && j>=0 && i<w && j<h && game.board[i][j].existe )
			game.board[i][j].hover = false;
	}
}

void SetHover(int x, int y)  {
	int i,j;
	int w = game.width;
	int h = game.height;
	for ( i = x-1; i < x+2; i++ )
	for ( j = y-1; j < y+2; j++ ) {
		if ( i>=0 && j>=0 && i<w && j<h && game.board[i][j].existe && !game.board[i][j].occupied )
			game.board[i][j].hover = true;
	}
	game.board[x][y].hover = false;
}

//Abstraction layer

void pMove(int x, int y, int pid)  {
	int a,b;
	a = game.players[pid].x;
	b = game.players[pid].y;
	game.board[a][b].occupied = false;
	CleanHistory();
	AddHistory();
	game.history->pid = pid;
	game.history->fx = a;
	game.history->fy = b;
	game.history->tx = x;
	game.history->ty = y;
	game.players[pid].x = x;
	game.players[pid].y = y;
	game.board[x][y].occupied = true;
	ResetHover(game.history->fx,game.history->fy);
	game.step = 1;
}

void NextTurn()  {
	game.turn = (game.turn + 1) % game.numplayers;
}

void Remove(int x, int y)  {
	game.board[x][y].existe = false;
	game.history->dx = x;
	game.history->dy = y;
	game.step = 0;
	CleanHistory();
}

int Possibility(int pid) {
	int i,j,c=0;
	int x = game.players[pid].x;
	int y = game.players[pid].y;
	int w = game.width;
	int h = game.height;
	for ( i = x-1; i < x+2; i++ )
		for ( j = y-1; j < y+2; j++ ) 
			if ( i>=0 && j>=0 && i<w && j<h && game.board[i][j].existe && !game.board[i][j].occupied )	
				c++;
	return c;
}

bool checkWin(){
	int start = game.turn,p;
	do {
		NextTurn();
		p = Possibility(game.turn);
		if (p == 0) game.players[game.turn].out = true;
	} while ( game.turn != start && p == 0 );

	if ( game.turn == start ) {
		return true;
	}
	return false;
}