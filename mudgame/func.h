typedef enum {
	empty, soup, water, map, gas_mask, radio, ax, book, checker_board, card, gun, flashlight, first_aid_kit, bottle, megaphone
}what;

typedef enum {
	LIVING_ROOM=1, BED_ROOM, DINING_ROOM, BATH_ROOM, SHELTER
}where;

unsigned _stdcall TimeCount();

void gotoxy(int x, int y);
void PrintfText(char* file_name, int cols, int lines);
void CursorView(bool show);
int PrintfItem(int item);
void PrintfPlace(int place);
void PrintfPlaceItem(where place, int plus_lines);
void SetColor(int color);
void PrintBag(int* pNitem, int plus_line);
void PrintMap(int cols, int lines, where place, int plus_line);
void PrintMyItem();

void ItemRandom();
void ItemChoice(int cols, int liens, int plus_line);
void ItemChoiceInPlace(int* pMybag, where place, int* pNitem, int cols, int lines, int plus_line);
void PutItemInShelter(int* pMybag, where place, int* pNitem, int cols, int lines, int plus_line);
void PrintHp(int hp);

void SortZero(where place);

void EventRandom(int* pHp, int plus_line);

void PrintfEvent(int number, int* pHp, int plus_line);

void PrintHp(int hp);

enum ColorType {
	BLACK,  	//0
	DarkBLUE,	//1
	DarkGreen,	//2
	DarkSkyBlue, //3
	DarkRed,  	//4
	DarkPurple,	//5
	DarkYellow,	//6
	GRAY,		//7
	DarkGray,	//8
	BLUE,		//9
	GREEN,		//10
	SkyBlue,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} COLOR;

/*
SetColor(BLACK); printf("BLACK\n");
	SetColor(DarkBLUE); printf("DarkBLUE\n");
	SetColor(DarkGreen); printf("DarkGreen\n");
	SetColor(DarkSkyBlue); printf("DarkSkyBlue\n");
	SetColor(DarkRed); printf("DarkRed\n");
	SetColor(DarkPurple); printf("DarkPurple\n");
	SetColor(DarkYellow); printf("DarkYellow\n");
	SetColor(GRAY); printf("GRAY\n");
	SetColor(DarkGray); printf("DarkGray\n");
	SetColor(BLUE); printf("BLUE\n");
	SetColor(GREEN); printf("GREEN\n");
	SetColor(SkyBlue); printf("SkyBlue\n");
	SetColor(RED); printf("RED\n");
	SetColor(PURPLE); printf("PURPLE\n");
	SetColor(YELLOW); printf("YELLOW\n");
	SetColor(WHITE); printf("WHITE\n");
*/

void DrawLines(int cols, int lines);
void DrawStart(int cols, int lines, int* pCL, int* pS, int plus_line);
void PrintHow(int cols, int lines, int plus_line);
void MenuChoice(int cols, int lines, int* pCL, int* pS, int plus_line);
int KeyControl();