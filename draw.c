#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "structs.h"
#include "methods.h"
#include "draw.h"
#include "save.h"

// Cette fonction précede le Drawing pour allouer l'espace et initialiser les valeurs des variables
void InitDraw() {
	int i;
	close.pos.x = 754;
	close.pos.y = 0;
	close.bg.w = 46;
	close.bg.h = 32;
	close.bg.x = 174;
	close.bg.y = 632;
	close.hv.w = 46;
	close.hv.h = 32;
	close.hv.x = 174;
	close.hv.y = 600;
	close.hover = false;

	min.pos.x = 708;
	min.pos.y = 0;
	min.bg.w = 46;
	min.bg.h = 32;
	min.bg.x = 128;
	min.bg.y = 632;
	min.hv.w = 46;
	min.hv.h = 32;
	min.hv.x = 128;
	min.hv.y = 600;
	min.hover = false;

	page[0].numb = 3;
	page[1].numb = 2;
	page[2].numb = 2;
	page[3].numb = 4;
	page[4].numb = 2;
	page[5].numb = 1;

	page[0].numi = 1;
	page[1].numi = 1;
	page[2].numi = 1;
	page[3].numi = 0;
	page[4].numi = 1;
	page[5].numi = 1;

	page[0].buttons = malloc(sizeof(Button)*page[0].numb);
	page[1].buttons = malloc(sizeof(Button)*page[1].numb);
	page[2].buttons = malloc(sizeof(Button)*page[2].numb);
	page[3].buttons = malloc(sizeof(Button)*page[3].numb);
	page[4].buttons = malloc(sizeof(Button)*page[4].numb);
	page[5].buttons = malloc(sizeof(Button)*page[5].numb);

	page[0].imgs = malloc(sizeof(Rect)*page[0].numi);
	page[1].imgs = malloc(sizeof(Rect)*page[1].numi);
	page[2].imgs = malloc(sizeof(Rect)*page[2].numi);
	page[3].imgs = malloc(sizeof(Rect)*page[3].numi);
	page[4].imgs = malloc(sizeof(Rect)*page[4].numi);
	page[5].imgs = malloc(sizeof(Rect)*page[5].numi);

	//Les Bouttons de la page 0 : Page Principale 
	// Le boutton New Game
	page[0].buttons[0].pos.x = 272;
	page[0].buttons[0].pos.y = 360;
	page[0].buttons[0].bg.w = 256;
	page[0].buttons[0].bg.h = 64;
	page[0].buttons[0].bg.x = 220;
	page[0].buttons[0].bg.y = 632;
	page[0].buttons[0].hv.w = 256;
	page[0].buttons[0].hv.h = 64;
	page[0].buttons[0].hv.x = 476;
	page[0].buttons[0].hv.y = 632;
	page[0].buttons[0].hover = false;

	// Le boutton Load Game
	page[0].buttons[1].pos.x = 272;
	page[0].buttons[1].pos.y = 424;
	page[0].buttons[1].bg.w = 256;
	page[0].buttons[1].bg.h = 64;
	page[0].buttons[1].bg.x = 220;
	page[0].buttons[1].bg.y = 696;
	page[0].buttons[1].hv.w = 256;
	page[0].buttons[1].hv.h = 64;
	page[0].buttons[1].hv.x = 476;
	page[0].buttons[1].hv.y = 696;
	page[0].buttons[1].hover = false;

	// Le boutton About Game
	page[0].buttons[2].pos.x = 272;
	page[0].buttons[2].pos.y = 488;
	page[0].buttons[2].bg.w = 256;
	page[0].buttons[2].bg.h = 64;
	page[0].buttons[2].bg.x = 220;
	page[0].buttons[2].bg.y = 760;
	page[0].buttons[2].hv.w = 256;
	page[0].buttons[2].hv.h = 64;
	page[0].buttons[2].hv.x = 476;
	page[0].buttons[2].hv.y = 760;
	page[0].buttons[2].hover = false;

	page[0].imgs[0].pos.x = 98;
	page[0].imgs[0].pos.y = 30;
	page[0].imgs[0].bg.w = 604;
	page[0].imgs[0].bg.h = 320;
	page[0].imgs[0].bg.x = 0;
	page[0].imgs[0].bg.y = 920;

	page[1].imgs[0].pos.x = 98;
	page[1].imgs[0].pos.y = 30;
	page[1].imgs[0].bg.w = 604;
	page[1].imgs[0].bg.h = 320;
	page[1].imgs[0].bg.x = 0;
	page[1].imgs[0].bg.y = 920;

	page[1].buttons[0].pos.x = 706;
	page[1].buttons[0].pos.y = 536;
	page[1].buttons[0].bg.w = 84;
	page[1].buttons[0].bg.h =  64;
	page[1].buttons[0].bg.x = 128;
	page[1].buttons[0].bg.y = 792;
	page[1].buttons[0].hv.w = 84;
	page[1].buttons[0].hv.h =  64;
	page[1].buttons[0].hv.x = 128;
	page[1].buttons[0].hv.y = 856;
	page[1].buttons[0].hover = false;

	page[1].buttons[1].pos.x = 622;
	page[1].buttons[1].pos.y = 536;
	page[1].buttons[1].bg.w = 84;
	page[1].buttons[1].bg.h =  64;
	page[1].buttons[1].bg.x = 716;
	page[1].buttons[1].bg.y = 1112;
	page[1].buttons[1].hv.w = 84;
	page[1].buttons[1].hv.h =  64;
	page[1].buttons[1].hv.x = 716;
	page[1].buttons[1].hv.y = 1176;
	page[1].buttons[1].hover = false;

	page[2].imgs[0].pos.x = 30;
	page[2].imgs[0].pos.y = 10;
	page[2].imgs[0].bg.w = 128;
	page[2].imgs[0].bg.h = 40;
	page[2].imgs[0].bg.x = 604;
	page[2].imgs[0].bg.y = 920;

	page[2].buttons[0].pos.x = 706;
	page[2].buttons[0].pos.y = 536;
	page[2].buttons[0].bg.w = 84;
	page[2].buttons[0].bg.h =  64;
	page[2].buttons[0].bg.x = 716;
	page[2].buttons[0].bg.y = 1112;
	page[2].buttons[0].hv.w = 84;
	page[2].buttons[0].hv.h =  64;
	page[2].buttons[0].hv.x = 716;
	page[2].buttons[0].hv.y = 1176;
	page[2].buttons[0].hover = false;

	// History Back 
	page[3].buttons[0].pos.x = 128;
	page[3].buttons[0].pos.y = 10;
	page[3].buttons[0].bg.w = 42;
	page[3].buttons[0].bg.h =  32;
	page[3].buttons[0].bg.x = 128;
	page[3].buttons[0].bg.y = 664;
	page[3].buttons[0].hv.w = 42;
	page[3].buttons[0].hv.h =  32;
	page[3].buttons[0].hv.x = 128;
	page[3].buttons[0].hv.y = 696;
	page[3].buttons[0].hover = false;

	// History Next
	page[3].buttons[1].pos.x = 170;
	page[3].buttons[1].pos.y = 10;
	page[3].buttons[1].bg.w = 42;
	page[3].buttons[1].bg.h =  32;
	page[3].buttons[1].bg.x = 170;
	page[3].buttons[1].bg.y = 664;
	page[3].buttons[1].hv.w = 42;
	page[3].buttons[1].hv.h =  32;
	page[3].buttons[1].hv.x = 170;
	page[3].buttons[1].hv.y = 696;
	page[3].buttons[1].hover = false;

	// Save
	page[3].buttons[2].pos.x = 212;
	page[3].buttons[2].pos.y = 10;
	page[3].buttons[2].bg.w = 42;
	page[3].buttons[2].bg.h =  32;
	page[3].buttons[2].bg.x = 175;
	page[3].buttons[2].bg.y = 728;
	page[3].buttons[2].hv.w = 42;
	page[3].buttons[2].hv.h =  32;
	page[3].buttons[2].hv.x = 175;
	page[3].buttons[2].hv.y = 728;
	page[3].buttons[2].hover = false;

	// New game
	page[3].buttons[3].pos.x = 30;
	page[3].buttons[3].pos.y = 10;
	page[3].buttons[3].bg.w = 105;
	page[3].buttons[3].bg.h =  40;
	page[3].buttons[3].bg.x = 604;
	page[3].buttons[3].bg.y = 920;
	page[3].buttons[3].hv.w = 128;
	page[3].buttons[3].hv.h =  40;
	page[3].buttons[3].hv.x = 604;
	page[3].buttons[3].hv.y = 920;
	page[3].buttons[3].hover = false;

	page[4].buttons[0].pos.x = 706;
	page[4].buttons[0].pos.y = 536;
	page[4].buttons[0].bg.w = 84;
	page[4].buttons[0].bg.h =  64;
	page[4].buttons[0].bg.x = 716;
	page[4].buttons[0].bg.y = 1112;
	page[4].buttons[0].hv.w = 84;
	page[4].buttons[0].hv.h =  64;
	page[4].buttons[0].hv.x = 716;
	page[4].buttons[0].hv.y = 1176;
	page[4].buttons[0].hover = false;

	page[4].imgs[0].pos.x = 30;
	page[4].imgs[0].pos.y = 10;
	page[4].imgs[0].bg.w = 128;
	page[4].imgs[0].bg.h = 40;
	page[4].imgs[0].bg.x = 604;
	page[4].imgs[0].bg.y = 920;

	page[5].imgs[0].pos.x = 98;
	page[5].imgs[0].pos.y = 30;
	page[5].imgs[0].bg.w = 604;
	page[5].imgs[0].bg.h = 320;
	page[5].imgs[0].bg.x = 0;
	page[5].imgs[0].bg.y = 920;

	page[5].buttons[0].pos.x = 706;
	page[5].buttons[0].pos.y = 536;
	page[5].buttons[0].bg.w = 84;
	page[5].buttons[0].bg.h =  64;
	page[5].buttons[0].bg.x = 716;
	page[5].buttons[0].bg.y = 1112;
	page[5].buttons[0].hv.w = 84;
	page[5].buttons[0].hv.h =  64;
	page[5].buttons[0].hv.x = 716;
	page[5].buttons[0].hv.y = 1176;
	page[5].buttons[0].hover = false;

	// Définir les Sliders
	Sliders[0].pos.x = 236;
	Sliders[0].pos.y = 360;
	strcpy(Sliders[0].label, "Players");
	Sliders[0].value = 2;
	Sliders[0].max = 4;
	Sliders[0].min = 2;
	Sliders[0].hover = false;

	Sliders[1].pos.x = 236;
	Sliders[1].pos.y = 424;
	strcpy(Sliders[1].label, "Width");
	Sliders[1].value = 4;
	Sliders[1].max = 10;
	Sliders[1].min = 4;
	Sliders[1].hover = false;

	Sliders[2].pos.x = 236;
	Sliders[2].pos.y = 488;
	strcpy(Sliders[2].label, "Height");
	Sliders[2].value = 4;
	Sliders[2].max = 7;
	Sliders[2].min = 4;
	Sliders[2].hover = false;

	// Définir des constantes utilisées pour dessiner les Sliders
	Sliderbg.x = 220;
	Sliderbg.y = 600;
	Sliderbg.w = 448;
	Sliderbg.h = 32;

	Sliderbtn.x = 128;
	Sliderbtn.y = 760;
	Sliderbtn.w = 46;
	Sliderbtn.h = 32;

	Sliderbtnh.x = 128;
	Sliderbtnh.y = 728;
	Sliderbtnh.w = 46;
	Sliderbtnh.h = 32;

	// Initialiser les strucures des inputs
	for ( i = 0; i < 7; i++ ) {
		inputs[i].pos.y = 100 + i*64;
		inputs[i].pos.x = 110;
		inputs[i].pos.w = 580;
		inputs[i].pos.h = 64;
		inputs[i].cursor = 0;
		inputs[i].focus = false;
		strcpy(inputs[i].value,"");
	}
}

// Dessiner le cadre de la table
void drawBorder() {
	int i,j,sx,sy;
	SDL_Rect pos,img;
	sx = 400 - (game.width*64 + 64)/2;
	sy = 300 - (game.height*64 + 64)/2 + 40;
	for ( i = 0; i <= game.height+1; i++ ) {
		for ( j = 0; j <= game.width+1; j++ ) {
			//top,left corner
			if ( i == 0 && j == 0) {
				pos.x = sx;
				pos.y = sy;
				img.w = 32;
				img.h = 32;
				img.x = 0;
				img.y = 600;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//top,right corner
			if ( i == 0 && j == game.width+1) {
				pos.x = sx + 32 + 64*(j-1);
				pos.y = sy;
				img.w = 32;
				img.h = 32;
				img.x = 96;
				img.y = 600;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//bottom,left corner
			if ( i == game.height+1 && j == 0) {
				pos.x = sx;
				pos.y = sy + game.height*64 + 32;
				img.w = 32;
				img.h = 32;
				img.x = 0;
				img.y = 696;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//bottom,right corner
			if ( i == game.height+1 && j == game.width+1) {
				pos.x = sx + 32 + 64*game.width;
				pos.y = sy + game.height*64 + 32;
				img.w = 32;
				img.h = 32;
				img.x = 96;
				img.y = 696;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//top
			if ( i == 0 && j!=0 && j!=game.width+1 ) {
				pos.x = sx + 32 + 64*(j-1);
				pos.y = sy;
				img.w = 64;
				img.h = 32;
				img.x = 32;
				img.y = 600;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//bottom
			if ( i == game.height+1 && j!=0 && j!=game.width+1 ) {
				pos.x = sx + 32 + 64*(j-1);
				pos.y = sy + game.height*64 + 32;
				img.w = 64;
				img.h = 32;
				img.x = 32;
				img.y = 696;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//left
			if ( j==0 && i!=0 && i!=game.height+1 ) {
				pos.x = sx;
				pos.y = sy + 32 + 64*(i-1);
				img.w = 32;
				img.h = 64;
				img.x = 0;
				img.y = 632;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
			//right
			if ( j==game.width+1 && i!=0 && i!=game.height+1 ) {
				pos.x = sx + 32 + 64*game.width;
				pos.y = sy + 32 + 64*(i-1);
				img.w = 32;
				img.h = 64;
				img.x = 96;
				img.y = 632;
				SDL_BlitSurface(s, &img, screen, &pos);
			}
		}
	}
}

// Dessiner les cases de la table
void drawBoard() {
	int i,j,sx,sy;
	SDL_Rect pos,img;
	sx = 400 - (game.width*64 + 64)/2;
	sy = 300 - (game.height*64 + 64)/2 + 40;
	img.w = 64;
	img.h = 64;
	for ( i = 0; i < game.width; i++ ) {
		for ( j = 0; j < game.height; j++ ) {
			drawCell(i, j);
		}
	}
	for ( i = 0; i < game.numplayers; i++ ) {
		drawPlayer(i);
	}
}

// Dessiner une seule case
void drawCell(int i, int j) {
	int sx,sy;
	SDL_Rect pos,img;
	sx = 400 - (game.width*64 + 64)/2;
	sy = 300 - (game.height*64 + 64)/2 + 40;
	img.w = 64;
	img.h = 64;
	img.y = 728;
	if ( game.board[i][j].existe ) img.x = 64;
	else img.x = 0;
	if ( game.board[i][j].hover ) {
		img.y = 632;
		img.x = 32;
	}
	pos.x = sx + 32 + 64*i;
	pos.y = sy + 32 + 64*j;
	SDL_BlitSurface(s, &img, screen, &pos);
}

// Dessiner les pions des joueurs
void drawPlayer(int i) {
	int sx,sy;
	SDL_Rect pos,img;
	sx = 400 - (game.width*64 + 64)/2;
	sy = 300 - (game.height*64 + 64)/2 + 40;
	if ( i == 0 || i == 1 ) img.y = 792;
	else  img.y = 856;
	if ( i == 1 || i == 3 ) img.x = 64;
	else  img.x = 0;
	pos.x = sx + 32 + 64*game.players[i].x;
	pos.y = sy + 32 + 64*game.players[i].y;
	img.w = 64;
	img.h = 64;
	SDL_BlitSurface(s, &img, screen, &pos);
}

// Dessiner la structure Rect (une image)
void drawRect(Rect rect, bool first) {
	SDL_Rect bg;
	if ( !first ) {
		bg.x = rect.pos.x;
		bg.y = rect.pos.y;
		bg.w = rect.bg.w;
		bg.h = rect.bg.h;
		SDL_BlitSurface(s, &bg, screen, &rect.pos); // Draw a sub background
	}
	SDL_BlitSurface(s, &rect.bg, screen, &rect.pos); // Draw background
}

// Dessiner la structure Button (dans les différentes états)
void drawButton(Button button, bool first) {
	SDL_Rect bg;
	if ( !first ) {
		bg.x = button.pos.x;
		bg.y = button.pos.y;
		bg.w = button.bg.w;
		bg.h = button.bg.h;
		SDL_BlitSurface(s, &bg, screen, &button.pos); // Draw a sub background
	}
	if ( button.hover ) {
		SDL_BlitSurface(s, &button.hv, screen, &button.pos); // Draw background in hover case
	}
	else {
		SDL_BlitSurface(s, &button.bg, screen, &button.pos); // Draw background
	}	
}

// Dessiner un Slider
void drawSlider( Slider slider, bool first ) {
	SDL_Surface * text;
	SDL_Color fgcolor;
	SDL_Rect bg,pos,post;
	char str[2];
	bg.x = slider.pos.x - 21;
	bg.y = slider.pos.y - 4;
	bg.w = 560;
	bg.h = 40;
	fgcolor.r = 0;
	fgcolor.g = 0;
	fgcolor.b = 0;
	pos.x = slider.pos.x + (slider.value - slider.min) * 448 / (slider.max-slider.min) - 21;
	pos.y = slider.pos.y;
	SDL_BlitSurface(s, &bg, screen, &bg); // Draw a sub background
	if ( first ) {
		post.x = 40;
		post.y = slider.pos.y - 10;
		text = TTF_RenderText_Blended(fontb, slider.label, fgcolor);
		SDL_BlitSurface(text, NULL, screen, &post);
	}
	SDL_BlitSurface(s, &Sliderbg, screen, &slider.pos); // Draw line
	if ( slider.hover ) {
		SDL_BlitSurface(s, &Sliderbtn, screen, &pos); // Draw button in hover case
	}
	else {
		SDL_BlitSurface(s, &Sliderbtnh, screen, &pos); // Draw button
	}
	sprintf(str,"%d",slider.value);
	post.x = slider.pos.x + 480;
	post.y = slider.pos.y - 10;
	text = TTF_RenderText_Blended(font, str, fgcolor);
	SDL_BlitSurface(text, NULL, screen, &post);
}

/*extraire une partie d'une chaine de caracteres (utilisée pour calculer la longueure d'une portion de
 caracteres pour placer le curseur)*/
char * substring(char *string, int position, int length) {
	char *pointer;
	int c;
	pointer = malloc(length+1);
	for( c = 0 ; c < position -1 ; c++ ) 
		string++; 
	for( c = 0 ; c < length ; c++ ) {
		*(pointer+c) = *string;      
		string++;   
	}
	*(pointer+c) = '\0';
	return pointer;
}
// Dessiner un champ (Input)
void drawInput(int i) {
	SDL_Rect img,pos;
	SDL_Surface * text;
	int w,h;
	SDL_Color fgcolor,fg2color;
	// Blanc
	fgcolor.r = 255;
	fgcolor.g = 255;
	fgcolor.b = 255;
	// Jaune
	fg2color.r = 255;
	fg2color.g = 190;
	fg2color.b = 0;
	// Dessiner une portion du Background
	img.x = inputs[i].pos.x;
	img.y = inputs[i].pos.y;
	img.w = 580;
	img.h = 64;
	SDL_BlitSurface(s, &img, screen, &inputs[i].pos);
	// Dessiner le corps du champ
	img.x = 220;
	img.y = 856;
	SDL_BlitSurface(s, &img, screen, &inputs[i].pos);
	pos.x = 130;
	pos.y = 113 + i*64;
	if ( inputs[i].focus ) {
		// Dessiner le text en jaune
		TTF_SizeText(font, substring( inputs[i].value, 0, inputs[i].cursor), &w, &h);
		text = TTF_RenderText_Blended(font, inputs[i].value, fg2color);
		SDL_BlitSurface(text, NULL, screen, &pos);
		// Placer le curseur
		pos.x = 130 + w;
		pos.y = 117 + i*64;
		pos.w = 2;
		pos.h = h - 9;
		SDL_FillRect(screen, &pos, 0xFFFFFF);
	}
	else {
		// Dessiner le text en blanc
		text = TTF_RenderText_Blended(font, inputs[i].value, fgcolor);
		SDL_BlitSurface(text, NULL, screen, &pos);
	}
	SDL_Flip(screen);
}

// Dessiner une page pour la premiere fois
void firstDraw() {
	int i;
	DIR * dir;
	struct dirent * ent;
	SDL_Rect pos,img,post;
	SDL_Surface * text;
	SDL_Color fgcolor,fg2color;
	fgcolor.r = 255;
	fgcolor.g = 255;
	fgcolor.b = 255;
	fg2color.r = 0;
	fg2color.g = 0;
	fg2color.b = 0;
	dir = opendir("games");
	// Dessiner l'arrier-plan
	pos.x = 0;
	pos.y = 0;
	img.x = 0;
	img.y = 0;
	img.w = 800;
	img.h = 600;
	SDL_BlitSurface(s, &img, screen, &pos);
	// Dessiner les deux buttons min & close
	// Fermer
	SDL_BlitSurface(s, &close.bg, screen, &close.pos);	
	// Reduire
	SDL_BlitSurface(s, &min.bg, screen, &min.pos);

	// Dessiner la page acctuelle
	// Dessiner les images
	for ( i = 0; i < page[current].numi; i++ ) {
		drawRect(page[current].imgs[i],true);	
	}
	//Dessiner les bouttons
	for ( i = 0; i < page[current].numb; i++ ) {
		drawButton(page[current].buttons[i],true);
	}
	if ( current == 1 ) { // New Game
		drawSlider(Sliders[0], true);
		drawSlider(Sliders[1], true);
		drawSlider(Sliders[2], true);
	}
	if ( current == 3 ) { // Le jeu
		drawBorder();
		drawBoard();
	}
	if ( current == 2 ) {
		pos.x = 110;
		img.x = 220;
		img.y = 856;
		img.w = 580;
		img.h = 64;
		post.x = 130;
		for ( i = 0; i < 7; i++ ) {
			inputs[i].cursor = 0;
			inputs[i].focus = false;
			strcpy(inputs[i].value,"");
		}
		
		i = 0;
		char *txt;
		while ((ent = readdir(dir)) != NULL) {
			if ( ent->d_name[0] != '.' && i < 7 ) {
				pos.y = 100 + i*64;
				post.y = 110 + i*64;
				txt = substring( ent->d_name, 0, strlen(ent->d_name) - 4 );
				strcpy(inputs[i].value,txt);
				SDL_BlitSurface(s, &img, screen, &pos);
				text = TTF_RenderText_Blended(font, txt, fgcolor);
				SDL_BlitSurface(text, NULL, screen, &post);
				//files[i] = (char *) malloc(sizeof(char)*strlen(ent->d_name));
				//strcpy(files[i],ent->d_name);
    			i++;
    		}
  		}
		closedir(dir);
	}
	if ( current == 4 ) {
		for ( i = 0; i < 7; i++ ) {
			inputs[i].cursor = 0;
			inputs[i].focus = false;
			strcpy(inputs[i].value,"");
		}
		i = 0;
		char *txt;
		while ((ent = readdir(dir)) != NULL) {
			if ( ent->d_name[0] != '.' && i < 7 ) {
				txt = substring( ent->d_name, 0, strlen(ent->d_name) - 4 );
				strcpy(inputs[i].value,txt);
				inputs[i].cursor = strlen(txt);
    			i++;
    		}
  		}

  		for ( i = 0; i < 7; i++ )	drawInput(i);
		closedir(dir);
	}
	if ( current == 5 ) {
		post.x = 220;
		post.y = 350;
		text = TTF_RenderText_Blended(font, "isola V 2.1 realise par :", fg2color);
		SDL_BlitSurface(text, NULL, screen, &post);
		post.x = 160;
		post.y = 390;
		text = TTF_RenderText_Blended(font, "Ben Hammou Amine et Zoli Issam", fg2color);
		SDL_BlitSurface(text, NULL, screen, &post);
		post.x = 270;
		post.y = 430;
		text = TTF_RenderText_Blended(font, "ENSIAS B3 2012", fg2color);
		SDL_BlitSurface(text, NULL, screen, &post);
	}
    SDL_Flip(screen);
}

void drawPM(int xi, int yi, int x, int y, int i) { // Dessiner un joueur en train de se déplacer
	int sx,sy,c,pasx,pasy,delay;
	SDL_Rect pos,img;
	sx = 400 - (game.width*64 + 64)/2;
	sy = 300 - (game.height*64 + 64)/2 + 40;
	if ( i == 0 || i == 1 ) img.y = 792;
	else  img.y = 856;
	if ( i == 1 || i == 3 ) img.x = 64;
	else  img.x = 0;
	pos.x = sx + 32 + 64*xi;
	pos.y = sy + 32 + 64*yi;
	img.w = 64;
	img.h = 64;
	c = 0;
	delay = 20;
	if ( x == xi ) pasx = 0;
	else {
		if ( x > xi ) pasx = 4;
		else pasx = -4;
	}
	if ( y == yi ) pasy = 0;
	else {
		if ( y > yi ) pasy = 4;
		else pasy = -4;
	}
	while ( c <= 64 ) {
		if ( x != xi ) pos.x = pos.x + pasx;
		if ( y != yi ) pos.y = pos.y + pasy;
		drawCell(xi,yi);
		if ( y != yi ) {
			drawCell(xi,y); 
			/* Si la case est occupée par un joueur alors il faut le dessiner*/
			drawOthers(xi,y);	
		} 
		if ( x != xi ) {
			drawCell(x,yi); 
			drawOthers(x,yi);	
		}
		drawCell(x,y);
		SDL_BlitSurface(s, &img, screen, &pos);
		SDL_Flip(screen);
		SDL_Delay(delay);
		c = c + 4;
	}
	PlayMusic(0);		
}

void drawOthers(int i,int j){
	int k;
	if(game.board[i][j].occupied){
		for(i=0;i<game.numplayers;i++){
			if(i != game.turn)
				drawPlayer(i);
		}
	}
}

void drawHover(int x, int y){ //Actualiser le champ hover des cases
	int i,j,w,h;
	w = game.width;
	h = game.height;
	for(i=x-1;i<x+2;i++){
		for(j=y-1;j<y+2;j++) {
			if(i>=0 && i<w && j<h && j>=0 && !game.board[i][j].occupied) drawCell(i,j);
		}
	}
}