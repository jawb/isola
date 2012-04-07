#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdlib.h>
#include "structs.h"
#include "methods.h"
#include "draw.h"
#include "save.h"

char* getPath(char *title){
	char *path, *dirname, *ext;
	path = (char *)malloc(63*sizeof(char));
	dirname = (char *)malloc(7*sizeof(char));
	ext = (char *)malloc(5*sizeof(char));
	strcpy(dirname,"games/");
	strcpy(ext,".isl");
	path = strcat(dirname,title);
	path = strcat(path,".isl");
	return path;
}

void Save(char *title) {
	if( strcmp(title,"") == 0 ) return;
	FILE * f;
	int i,w,h;
	w = game.width;
	h = game.height;
	Move *temp;
	
	f = fopen(getPath(title),"wb");
	fwrite(&game.numplayers,sizeof(int),1,f);
	fwrite(&game.width,sizeof(int),1,f);
	fwrite(&game.height,sizeof(int),1,f);
	fwrite(&game.turn,sizeof(int),1,f);
	fwrite(&game.step,sizeof(int),1,f);
	for(i=0;i<w;i++)
	{
		fwrite(game.board[i],sizeof(Cell),h,f);	
	}

	fwrite(game.players,sizeof(Player),game.numplayers,f);
	temp = game.history;
	// l'utilisateur ne peut sauvegarder que si history != NULL
	while(temp->prev != NULL) temp = temp -> prev ;
	while(temp != game.history->next){
		fwrite(temp,sizeof(int),7,f);
		temp = temp -> next;
	}
	fclose(f);
}

void Load(char * name){
	FILE * f;
	int r,t[7],w,h,i;
	f = fopen(name,"rb");
	
	fread(&game.numplayers,sizeof(int),1,f);
	fread(&game.width,sizeof(int),1,f);
	fread(&game.height,sizeof(int),1,f);
	NewGame();
	fread(&game.turn,sizeof(int),1,f);
	fread(&game.step,sizeof(int),1,f);

	w = game.width;
	h = game.height;
	for(i=0;i<w;i++)
	{
		fread(game.board[i],sizeof(Cell),h,f);	
	}
	
	fread(game.players,sizeof(Player),game.numplayers,f);

	r = fread(t,sizeof(int),7,f);
	while(r == 7){
		AddHistory();
		game.history->pid = t[0];
		game.history->fx = t[1];
		game.history->fy = t[2];
		game.history->tx = t[3];
		game.history->ty = t[4];
		game.history->dx = t[5];
		game.history->dy = t[6];
		r = fread(t,sizeof(int),7,f);
	}
	fclose(f);
}