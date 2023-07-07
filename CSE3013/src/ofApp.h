/*

	ofxWinMenu basic example - ofApp.h

	Copyright (C) 2016-2017 Lynn Jarvis.

	http://www.spout.zeal.co

	=========================================================================
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	=========================================================================
*/

	#pragma once

#include "ofMain.h"
#include "ofxWinMenu.h" // Menu addon
#include <time.h>
#include <stdlib.h>

#define MIN(a, b) ((a)>(b)?(b):(a))
#define MAX(a, b) ((a)<(b)?(b):(a))
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
using dd = pair<int, int >;
#define NAMELEN 16

typedef struct Node_* ptr;
typedef struct Node_ {
	char name[NAMELEN];
	int score;
	ptr next;
} Node;



class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key); // Traps escape key if exit disabled
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		bool readFile();
		void freeMemory();
		bool DFS();
		void dfsdraw();
		bool BFS();
		void bfsdraw();
		int HEIGHT;//미로의 높이
		int WIDTH;//미로의 너비
		char** input;//텍스트 파일의 모든 정보를 담는 이차원 배열이다.
		int** visited;//방문여부를 저장할 포인
		int maze_col;//미로칸의 열의 인덱스를 가리킨다.
		int maze_row;//미로칸의 행의 인덱스를 가리킨다.
		int k;
		int isOpen; //파일이 열렸는지를 판단하는 변수. 0이면 안열렸고 1이면 열렸다.
		int isDFS;//DFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		int isBFS;//BFS함수를 실행시켰는지 판단하는 변수. 0이면 실행안했고 1이면 실행했다.
		// Menu
		ofxWinMenu * menu; // Menu object
		void appMenuFunction(string title, bool bChecked); // Menu return function
		int **hor;
		int **ver;
		vector<pair<dd, dd>>DFS1, DFS2;
		vector<pair<dd, dd>>BFS1, BFS2;
		vector<pair<int, int>>land;
		int curx, cury;

		// Used by example app
		ofTrueTypeFont myFont;
        ofImage myImage;
		float windowWidth, windowHeight;
		HWND hWnd; // Application window
		HWND hWndForeground; // current foreground window
		int start_flag;
		int game_over;
		void makemine();
		// Example menu variables
		bool bShowInfo;
		bool bFullscreen;
		bool bTopmost;
		bool isdfs;
		// Example functions
 		void doFullScreen(bool bFull);
		void doTopmost(bool bTop);
		bool visit_flag(int hei, int wid, int dir);
		bool isvisit(int hei, int wid, int dir);
		int mine;
		int dirx[4] = { -1,0,1,0 };
		int diry[4] = { 0,1,0,-1 };
		int x, y;
		int trie;
		int life;
		int length;
		int isdone;
		int *mvisit;
		time_t new_time, old_time;
		int delay;
		int print_time;
		int success=0;
		void result();
		int scoresum;


		void createRankList();
		void Rank();
		void newRank(int score);
		
		//head = NULL;

		int rankNum = 0;
		int comp(int n1, int n2);
		Node* head;
		int draw_flag = 0;


};
