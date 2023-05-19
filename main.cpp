#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include "MMSystem.h"
#include <ctime>

using namespace std;

HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO info;
COORD coord;
int CordY, menu = 0;
bool progRun = true;
string frameLine;


// -----===== Jedyny i najlepszy film =====-----

int catDance () {
	int timespace = 0, time = 0, colorCount = 0, timeVar[3], musicTimeVar[3] = {0, 0, 0}, colorSwitch;
	clock_t waiter;
	
	HANDLE wHnd = GetStdHandle (STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = {0, 0, 152, 50};
	SetConsoleWindowInfo (wHnd, 1, & windowSize);
	
	// Muzyka
	PlaySound(TEXT ("music.wav"), NULL, SND_ASYNC);
	musicTimeVar[0] = clock();
	
	// Pêtla filmu 
	while (true) {
		
		// nutka
		musicTimeVar[1] = clock();
		musicTimeVar[2] = musicTimeVar[1] - musicTimeVar[0];
		if (musicTimeVar[2] >= 114000) {
			PlaySound(TEXT ("music.wav"), NULL, SND_ASYNC);
			musicTimeVar[0] = musicTimeVar[1];
		}
		
		
		
		fstream f ("Frames.txt", ios::in);
		for (int j = 0; j < 23; j++) {
			
			timeVar[0] = clock();
			
			// kolorki
			if (j == 0 || j == 12) {
				colorCount++;
				colorCount %= 9;
				
				switch (colorCount) {
					case 0:
						system ("color 1");
						break;
					case 1:
						system ("color 9");
						break;
					case 2:
						system ("color b");
						break;
					case 3:
						system ("color 2");
						break;
					case 4:
						system ("color 6");
						break;
					case 5:
						system ("color 4");
						break;
					case 6:
						system ("color c");
						break;
					case 7:
						system ("color d");
						break;
					case 8:
						system ("color 5");
						break;
				}
			}
			
			CordY = 0;
			for (int k = 0; k < 30; k++) {				
				
				GetConsoleCursorInfo(out, &info);
				info.bVisible = false;
				SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
				
				getline (f, frameLine);
				coord.X = 1;
				coord.Y = CordY;
				SetConsoleCursorPosition(GetStdHandle (STD_OUTPUT_HANDLE), coord);
				CordY++;
				cout << "\r" << frameLine << "\n";
			}
			
			timespace++;
			timespace %= 8;
			
			time = 30;
			//if (timespace == 0 || timespace == 1 || timespace == 2) time++;
			
			timeVar[1] = clock();
			timeVar[2] = timeVar[1] - timeVar[0];
			timeVar[2] = time - timeVar[2];
			if (timeVar[2] < 0) timeVar[2] = 0;
			Sleep (timeVar[2]);
		}
		f.close();
	}
}



void set_console_size() {
     HANDLE hOut;
     SMALL_RECT DisplayArea = {0, 0, 0, 0};
     //set x and y to whatever ye' want
     int x = 91;
     int y = 30;

     hOut = GetStdHandle(STD_OUTPUT_HANDLE);
     DisplayArea.Right  = x;
     DisplayArea.Bottom = y;

     SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}




// -----===== Int Main =====-----

int main () {
    cout.tie(0);
    system ("Cat vibing to Lady hear me tonight");
    
    GetConsoleCursorInfo(out, &info);
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    
    set_console_size();
	catDance();
}
