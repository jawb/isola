void StartGame ();
void PauseGame ();
void NewGame ();

//Handling history
void AddHistory();
void CleanHistory();
bool isNext();
bool isPrev();
void Next();
void Prev();
int Length();

//Abstraction layer
void pMove(int, int, int);
void Remove(int, int) ;
void NextTurn();

//Hover
void ResetHover(int, int);
void SetHover(int, int);
void CleanHover();

int Possibility(int);
bool CheckWin();