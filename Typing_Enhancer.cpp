#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

char keys[10];	
int keyPos[10][2];	
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void drawBorder(){  
	for(int i=0; i<SCREEN_WIDTH; i++){ 
		gotoxy(i,SCREEN_HEIGHT); cout<<"?";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"?";
		gotoxy(SCREEN_WIDTH,i); cout<<"?";
	}
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(WIN_WIDTH,i); cout<<"?";
	}
}

void genAlphabet(int ind){
	keys[ind] = 65+rand()%25;   
	keyPos[ind][0] = 2 + rand()%(WIN_WIDTH-2);
	keyPos[ind][1] = 1;
}
void drawAlphabet(int ind){
	if( keyPos[ind][0] != 0 ){
		gotoxy(keyPos[ind][0], keyPos[ind][1]);   cout<<keys[ind];  
	} 
}
void eraseAlphabet(int ind){
	if( keyPos[ind][0] != 0 ){
		gotoxy(keyPos[ind][0], keyPos[ind][1]);   cout<<" ";  
	}
}
void resetAlphabet(int ind){
	eraseAlphabet(ind);
	genAlphabet(ind);
}

void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\t  Your final Score : "<<score<<endl;
	cout<<"\n\t\tPress any key to go back to menu.";
	getch();
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}

void instructions(){
	
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n On Left side you will see falling characters ";
	cout<<"\n You have to keep them away from touching floor";
	cout<<"\n Press respective key from keyboard to keep playing";
	cout<<"\n\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	getch();
}

void play(){
	score = 0;
	for(int i=0; i<10; i++){
		keyPos[i][0] = keyPos[i][1] = 1;	
	}
	 
	system("cls"); 
	drawBorder(); 
	updateScore();
	
	for(int i=0; i<10; i++)
		genAlphabet(i); 
	
	gotoxy(WIN_WIDTH + 5, 2);cout<<"Typing Enhancer";
	gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
	gotoxy(WIN_WIDTH + 6, 6);cout<<"----------";
	
	gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
	
	while(1){
		if(kbhit()){
			char ch = getch();
			for(int i=0; i<10; i++){
				if( ch == keys[i] || ch-32 == keys[i] ){
					resetAlphabet(i);
					score++;
					updateScore();
				}
			}
			if(ch==27){
				break;
			}
		} 
		
		for(int i=0; i<10; i++)
			drawAlphabet(i);  
			
		Sleep(300); 
		
		for(int i=0; i<10; i++){
			eraseAlphabet(i);  
			keyPos[i][1] += 1;
			if( keyPos[i][1] > SCREEN_HEIGHT ){
				gameover();
				return;
			}
		}
	}
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |     TYPING  ENHANCER   | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<endl<<"\t\t1. Start Game"<<endl;
		gotoxy(10,10); cout<<endl<<"\t\t2. Instructions"<<endl;	 
		gotoxy(10,11); cout<<endl<<"\t\t3. Quit"<<endl;
		gotoxy(10,13); cout<<endl<<"\t\tSelect option: "<<endl;
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
		
	}while(1);
	
	return 0;
}
