#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include "structs.h"
#include "methods.h"
#include "draw.h"
#include "save.h"

//lancer un effet sonore 
void PlayMusic(int i) {
	Mix_Chunk *sound = NULL;
	int channel = 0;
	switch(i) {
		case 0 : sound = Mix_LoadWAV("res/move.wav"); break;
		case 1 : sound = Mix_LoadWAV("res/click.wav"); break;
		case 2 : sound = Mix_LoadWAV("res/win.wav"); break;
	}
	channel = Mix_PlayChannel(-1, sound, 0);
	while ( Mix_Playing(channel) != 0 );
 	Mix_FreeChunk(sound);
}

bool IsHovered(int x, int y, Button b) {
	if ( x >= b.pos.x && x <= (b.pos.x + b.bg.w) && y >= b.pos.y && y <= (b.pos.y + b.bg.h) ) {
		drawButton(b,false);
		return true;
	}
	else
	{
		return false;	
	}
}

void updateHover(int x, int y, Button *b, bool *in, bool *out)
{

	bool mousein = ( x >= (*b).pos.x && x <= ((*b).pos.x + (*b).bg.w) && y >= (*b).pos.y && y <= ((*b).pos.y + (*b).bg.h));
	if( !(*in) && !(*out)){
		// No Button is updated yet
		if(mousein && !((*b).hover)){
			*in = true;
			(*b).hover = true;
			drawButton(*b, false);
		}
		if(!mousein && (*b).hover){
			*out = true;
			(*b).hover = false;
			drawButton(*b, false);
		}
	}else{
		if(*in){
			// Button was hovered and updated
			if(!mousein && (*b).hover){
				*out = true;
				(*b).hover = false;
				drawButton(*b, false);
			}
		}else{
			// Button was hovered out and updated
			if(mousein && !((*b).hover)){
				*in = true;
				(*b).hover = true;
				drawButton(*b, false);
			}
		}
	}
}

//traiter l'evenement
void eventHandler( SDL_Event event ) {
    int i,x,y;
    bool in = false, out = false;
    switch ( event.type ) {
    	case SDL_QUIT :
    		game.play = false;
    	break;
    	case SDL_MOUSEMOTION :
    		cmm++;
    		if ( cmm % 2 == 0 ) {
	    		x = event.button.x;
	    		y = event.button.y;
	    		// Gerer les Hovers
	    		updateHover(x,y,&close,&in,&out);
	    		updateHover(x,y,&min,&in,&out);
				for ( i = 0 ; i < page[current].numb ; i++ )
	    			updateHover(x,y,&page[current].buttons[i],&in,&out);	    			
	    	}
    	break;
    	case SDL_MOUSEBUTTONDOWN : // Lorsque un boutton de la souris est clickee
    		if ( event.button.button == SDL_BUTTON_LEFT ) { // Si c'est le boutton gauche
    			click(event); // Traiter le click de chaque boutton de la page acctuelle
    		}
    	break;
    }
}

bool inSlider(int mx,int my,int id){
	int x,y,w,h;
	x = Sliders[id].pos.x;
	y = Sliders[id].pos.y;
	w = 480;
	h = 32;
	if(mx >= x && mx <= x+w && my >= y && my <= y+h) 
		return true;
	else 
		return false;
}

void handleSlider(int id, SDL_Event se) {
	//printf("s%d clicked !\n",id );
	int mx,x,w,min;
	min = Sliders[id].min;
	float l;
	l = (Sliders[id].max - min) / 448.0;
	x = Sliders[id].pos.x;
	w = 480;
	mx = se.button.x;
	Sliders[id].hover = true;
	Sliders[id].value = min + (mx - x + 21) * l; 
    drawSlider(Sliders[id],false);
    SDL_Flip(screen);
	do {
		SDL_WaitEvent(&se);
		if ( se.type == SDL_MOUSEMOTION ) {
		    mx = se.button.x;    
        	if ( mx >= x && mx <= x+w ){
        		Sliders[id].value = min + (mx - x + 21) * l; 
        		drawSlider(Sliders[id],false);
        		SDL_Flip(screen);
        		//printf("s%d moved to mx:%d min:%d max:%d l:%.2f val:%d\n",id,mx,min,Sliders[id].max,l,Sliders[id].value);
        	}
        }
	} while(se.type != SDL_MOUSEBUTTONUP);
	Sliders[id].hover = false;
    drawSlider(Sliders[id],false);
    SDL_Flip(screen);
}

void handleInput(int id)
{
	char c, initVal[50];
	int i,l;
	bool v,e;
	SDL_Event ie;
	SDLMod mod;

	// Si la zone contien déjà du texte alors il doit etre écrasée !
	if( strcmp(inputs[id].value,"") != 0 ){
		e = true;
		strcpy(initVal,inputs[id].value);
		printf("%s\n",initVal);
	}else
		e = false;

	do{
		SDL_WaitEvent(&ie);
		mod = SDL_GetModState();
		if(mod == KMOD_LSHIFT || mod == KMOD_RSHIFT) 
			v = true;
		else
			v = false;
		switch(ie.type)
		{
			case SDL_KEYDOWN :
				c = '/';
				switch(ie.key.keysym.sym)
				{
					case SDLK_BACKSPACE : //delete !!
					if(inputs[id].cursor>0){
						i = inputs[id].cursor - 1;
						l = strlen(inputs[id].value);
						while(i<l){
							inputs[id].value[i] = inputs[id].value[i+1];
							i ++;
						}
						inputs[id].cursor -- ;
					}
					break;
					case SDLK_RIGHT : // Move cursor right !
						if(inputs[id].cursor < strlen(inputs[id].value)) inputs[id].cursor ++ ;	
					break;
					case SDLK_LEFT : // Move cursor left !
						if(inputs[id].cursor > 0) inputs[id].cursor -- ;
					break;
					case SDLK_ESCAPE : // Revenir !
						current = 3; //revenir la page du jeu
						firstDraw();
						return;
					break;
					case SDLK_RETURN : // 
						Save(inputs[id].value);
						if(e){
							remove(getPath(initVal));	
						} 
						
						current = 3; //revenir la page du jeu
						firstDraw();
						return ;		
					break;
					case SDLK_a : if(v) c = 'A'; else c = 'a'; break;
					case SDLK_b : if(v) c = 'B'; else c = 'b'; break;
					case SDLK_c : if(v) c = 'C'; else c = 'c'; break;
					case SDLK_d : if(v) c = 'D'; else c = 'd'; break;
					case SDLK_e : if(v) c = 'E'; else c = 'e'; break;
					case SDLK_f : if(v) c = 'F'; else c = 'f'; break;
					case SDLK_g : if(v) c = 'G'; else c = 'g'; break;
					case SDLK_h : if(v) c = 'H'; else c = 'h'; break;
					case SDLK_i : if(v) c = 'I'; else c = 'i'; break;
					case SDLK_j : if(v) c = 'J'; else c = 'j'; break;
					case SDLK_k : if(v) c = 'K'; else c = 'k'; break;
					case SDLK_l : if(v) c = 'L'; else c = 'l'; break;
					case SDLK_m : if(v) c = 'M'; else c = 'm'; break;
					case SDLK_n : if(v) c = 'N'; else c = 'n'; break;
					case SDLK_o : if(v) c = 'O'; else c = 'o'; break;
					case SDLK_p : if(v) c = 'P'; else c = 'p'; break;
					case SDLK_q : if(v) c = 'Q'; else c = 'q'; break;
					case SDLK_r : if(v) c = 'R'; else c = 'r'; break;
					case SDLK_s : if(v) c = 'S'; else c = 's'; break;
					case SDLK_t : if(v) c = 'T'; else c = 't'; break;
					case SDLK_u : if(v) c = 'U'; else c = 'u'; break;
					case SDLK_v : if(v) c = 'V'; else c = 'v'; break;
					case SDLK_w : if(v) c = 'W'; else c = 'w'; break;
					case SDLK_x : if(v) c = 'X'; else c = 'x'; break;
					case SDLK_y : if(v) c = 'Y'; else c = 'y'; break;
					case SDLK_z : if(v) c = 'Z'; else c = 'z'; break;
					case SDLK_UNDERSCORE : c = '_'; break;
					case SDLK_LEFTPAREN : c = '('; break;
					case SDLK_RIGHTPAREN : c = ')'; break;
					case SDLK_SPACE : c = ' '; break;
					case SDLK_MINUS : c = '-'; break;
					case SDLK_PERIOD : c = '.'; break;
					//...
				}
				if(c!='/')
				{
					i = strlen(inputs[id].value) + 1;
					l = inputs[id].cursor;
					while(i>l){
						inputs[id].value[i] = inputs[id].value[i-1] ;
						i--;
					}
					inputs[id].value[i] = c;
					inputs[id].cursor ++; 
				}
			break;
			case SDL_MOUSEBUTTONDOWN :
				inputs[id].focus = false;
				firstDraw();
			break;
		}
		drawInput(id);
	}while(inputs[id].focus);
	drawInput(id);
}

void click(SDL_Event e2)
{
	int mx, my,a,b, x0, y0;
	mx = e2.button.x;
	my = e2.button.y;
	// Le boutton clicke a surement hover=true
	// La boutton Close :
	if ( close.hover ) {
	 	game.play = false ; // Arreter le jeu !
	}	 
	// La boutton minimiser :
	if ( min.hover ) {
	 	 SDL_WM_IconifyWindow(); // minimiser la fenetre
	}
	// Determiner la page courente !
	switch( current ) {
		case 0 : // La page d'acceuil 
			if ( page[0].buttons[0].hover ) {
				current = 1 ; // New Game
				firstDraw();
			}
			if ( page[0].buttons[1].hover ) {
				current = 2 ; // Load Game
				firstDraw();
			}
			if ( page[0].buttons[2].hover ) {
				current = 5 ; // About
				firstDraw();
			}
		break;

		case 1 : // La page de New Game
			// Traitement des sliders 
				//Player's Slider
				if(inSlider(mx,my,0)){
					handleSlider(0,e2);
				}
				// Width's Slider
				if(inSlider(mx,my,1)){
					handleSlider(1,e2);
				}
				// Height's Slider
				if(inSlider(mx,my,2)){
					handleSlider(2,e2);
				}
			// Traitement des button
			if(page[1].buttons[0].hover ) {
				// Boutton : Next
				game.width = Sliders[1].value;
				game.height = Sliders[2].value;
				NewGame();
				current = 3; // Aller a la page du jeu
				firstDraw();
			}
			
			if(page[1].buttons[1].hover ) {
				// Boutton : Back
				current = 0; // Aller a la page d'acceuil
				firstDraw();
			}
		break;

		case 2 : // la page Load Game
			if(page[2].buttons[0].hover ) {
				// Boutton : Back
				current = 0; // Aller a la page d'acceuil
				firstDraw();
			}
			// On doit savoir le nom du fichier clicke pour pouvoir le charger
			// La zone est telque x entre 110 et 690 ; 
			// y entre 100 et 100+n*64 avec n le nombre de fichiers
			// n maximal est 7
			if(mx > 110 && mx < 690 && my > 100 && my < (100+7*64) ){
				a = (my - 100) / 64; // inputs[a].value est le nom qui a ete clique
				if(strcmp(inputs[a].value,"") != 0){
					Load(getPath(inputs[a].value));
					current = 3;
					firstDraw();					
				}
			}
		break;

		case 3 : // La page du jeu
			//History buttons
			if(page[3].buttons[0].hover){
				// le boutton Back
				if(isPrev()){
					Prev();
					drawBoard();	
				}
			}
			
			if(page[3].buttons[1].hover){
				// le boutton Next
				if(isNext()){
					Next();
					drawBoard();	
				}
			}

			// Save Button
			if(page[3].buttons[2].hover){
				if(game.history!=NULL){
					current = 4;
					firstDraw();
				}
			}

			// New Game
			if(page[3].buttons[3].hover){
				current = 1;
				firstDraw();
			}

			//Les cliques sur la zone des cases :
 			 // Determiner les indices de la case clickee ; si jamais !
			x0 = 400 - (game.width*64 + 64)/2 + 32;
			y0 = 300 - (game.height*64 + 64)/2 + 40 + 32;


			if(mx >= x0 && mx < (x0 + 64 * game.width) && my >= y0 && my < (y0 + 64 * game.height)){
				// Le click est dans la zone les cases
				a = (mx - x0) / 64 ; // division entiere
				b = (my - y0) / 64 ;
				// C'est la case board[a][b] qui s'est cliquee !

				switch(game.step){
					case 0 :
						if(game.board[a][b].hover){
							// Le joueur peut se déplacer vers cette case 
							x0 = game.players[game.turn].x;
							y0 = game.players[game.turn].y;
							drawPM(x0,y0,a,b,game.turn);
							pMove(a,b,game.turn);
							drawHover(x0,y0);
							drawCell(game.players[game.turn].x,game.players[game.turn].y);
							drawPlayer(game.turn);
						}
					break;
					case 1 :
						if ( game.board[a][b].existe && !game.board[a][b].occupied ) {
							Remove(a,b);
							drawCell(a,b);
							PlayMusic(1);
							if ( checkWin() ) {
								PlayMusic(2);
								current = 0;
								firstDraw();
							}
							else {
								x0 = game.players[game.turn].x;
								y0 = game.players[game.turn].y;
								SetHover(x0,y0);
								drawHover(game.players[game.turn].x,game.players[game.turn].y);
								drawPlayer(game.turn);
							}
						}
					break;
				}
			}
		break;

		case 4 : // La page de sauvegarde !!
			if(page[4].buttons[0].hover ) {
				// Boutton : Back
				current = 3; //revenir la page du jeu
				firstDraw();
			}

			if(mx > 110 && mx < 690 && my > 100 && my < (100+7*64) ){
				a = (my - 100) / 64; // inputs[a] est la zone de texte cliquee
				inputs[a].focus = true ;
				drawInput(a);
				handleInput(a);
			} 
		break;
		case 5 : // La page de About !!
			if(page[5].buttons[0].hover ) {
				current = 0; //revenir la page du jeu
				firstDraw();
			}
		break;
	}
}