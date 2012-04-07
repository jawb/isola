typedef struct Button {
	SDL_Rect pos;
	SDL_Rect bg;
	SDL_Rect hv;
	bool hover;
} Button;

typedef struct Slider {
	SDL_Rect pos;
	char label[30];
	int value;
	int max;
	int min;
	bool hover;
} Slider;

typedef struct Input {
	SDL_Rect pos;
	int cursor;
	char value[50];
	bool focus;
} Input;

typedef struct Rect {
	SDL_Rect pos;
	SDL_Rect bg;
} Rect;

typedef struct Page {
	int numb;
	int numi;
	Button * buttons;
	Rect * imgs;
} Page;

Button close, min;
Input inputs[7];
Page page[6];
SDL_Rect Sliderbg,Sliderbtn,Sliderbtnh;
Slider Sliders[3];
char * files[7];
//SDL_Color black;

void eventHandler(SDL_Event);
void quit();
bool IsHovered(int, int, Button);
void click();
void updateHover(int , int , Button*, bool *, bool *);
bool inSlider(int ,int ,int );
void handleSlider(int , SDL_Event );

void PlayMusic(int);
void InitDraw();
void drawBorder();
void drawBoard();
void drawCell(int, int);
void drawPlayer(int);
void drawRect(Rect , bool);
void drawButton(Button, bool);
void drawSlider(Slider, bool); 
void drawHover(int,int);
void firstDraw();
void drawInput(int);
char * substring(char *, int , int );
void drawPM(int , int , int , int , int );
void drawOthers(int i,int j);