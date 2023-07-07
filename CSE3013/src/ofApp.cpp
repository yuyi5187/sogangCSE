/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

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

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;
//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();
	curx = 0; 
	cury = 0;
	trie= 0;
	Node* tmp2 = (Node*)malloc(sizeof(Node));
	strcpy(tmp2->name, "start");
	tmp2->score = -1;

	tmp2->next = NULL;
	head = tmp2;
	//free(tmp2);
} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Open") {
		readFile();
	}
	if(title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		//bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		doTopmost(bChecked);
		if (isdfs == true) {
			isdfs = false;
		}
		else
			if (isOpen)
			{
				DFS();
				bShowInfo = bChecked;
			}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		doTopmost(bChecked); // Use the checked value directly
		if (isBFS) {
			isBFS = 0;
		}
		else
			if (isOpen)
			{
				BFS();
			}
			else
				cout << "you must open file first" << endl;

	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {

}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(4);
	int i, j;

	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here

	if (isOpen) {
		length = 40;
		ofSetLineWidth(4);
		ofDrawLine(0, 0, length * WIDTH, 0);
		ofDrawLine(0, HEIGHT * length, length * WIDTH, length * HEIGHT);
		ofDrawLine(0, 0, 0, length * HEIGHT);
		ofDrawLine(length * WIDTH, 0, length * WIDTH, length * HEIGHT);
		for (int i = 0; i < HEIGHT; i++) {//wall_ver
			for (int j = 0; j < WIDTH - 1; j++) {
				if (ver[i][j] == 1) {
					ofDrawLine((j + 1) * length, i * length, (j + 1) * length, (i + 1) * length);
				}
			}
		}
		for (int i = 0; i < HEIGHT - 1; i++) {//wall_hor
			for (int j = 0; j < WIDTH; j++) {
				if (hor[i][j] == 1) {
					ofDrawLine(j * length, (i + 1) * length, (j + 1) * length, (i + 1) * length);
				}
			}
		}

	
	}
	if (game_over) {
		//게임 오버된 경우에는 결과를 출력하는 함수를 호출한다.
		result();
		//result_flag = 1;
		
		game_over = 0;
		
	}

	//처음에 생성된 지뢰를 그린다.
	if (draw_flag) {
		ofSetColor(0, 255, 255);
		for (int i = 0; i < mine; i++) {
			ofDrawCircle(land[i].first*length + length / 2, land[i].second*length + length / 2, 6);
		}
	}
	if (start_flag) {
	
		
		//게임이 시작되었다 사용자 위치, 밟은 지뢰 개수, 실패와 성공 여부를 계산한다.

		int check = 0;
		int stdou = mine;
		
		
		new_time = clock();
		//제한 시간이 지났는지 아닌지 체크한다.
		if (difftime(new_time, old_time) >= delay) {
			print_time = difftime(new_time, old_time);
			start_flag = 0;
			game_over = 1;
			draw_flag = 1;
			//success = 2;
			
		}
		    // 밟은 미로인지 아닌지 체크하고, 밟지 않았던 경우에는 새로 밟은 것이므로 trie를 증가한다.
			for (int i = 0; i < mine; i++) {
				int tmpx = land[i].first;
				int tmpy = land[i].second;
				if (curx == tmpx & cury == tmpy) {
					if (mvisit[i]) {
						continue;
					}
					check = 1;
					//stdou--;
					mvisit[i] = 1;
					trie++;
					break;
					//land.erase(land.begin() + 1);

				}
			}
			ofSetColor(0, 255, 255);

			//만약 미로를 밟았는데 life보다 trie가 남은 경우에는 시작점으로 사용자 위치를 초기화한다.
			if (check == 1 & trie <= life) {
				curx = 0;
				cury = 0;
				ofSetColor(255, 0, 0);
				//ofDrawCircle(curx*length + length / 2, cury*length + length / 2, 8);
			}

			//미로를 밟았는데 life를 모두 소진한 경우에는 게임이 종료된다.
			else if (check == 1 & trie > life) {
				ofSetColor(127, 127, 127);
				
				game_over = 1;
				draw_flag = 1;
				start_flag = 0;
				
				//isdone = 1;


			}
			//미로의 출구에 도달한 경우에는 사용자 점 색을 바꾸고 success를 1로 셋팅한다.
			else if (curx == WIDTH - 1 & cury == HEIGHT - 1) {
				ofSetColor(128, 255, 0);
				game_over = 1;
				draw_flag = 1;
				start_flag = 0;
				success = 1;
				//cout << "You win!" << endl;


			}
			//그냥 빈칸일 경우에 사용자 위치를 파란점으로 그린다.
			else {
				ofSetColor(0, 0, 255);
				//ofDrawCircle(curx*length + length / 2, cury*length + length / 2, 8);
			}

			ofDrawCircle(curx*length + length / 2, cury*length + length / 2, 8);

			
			


	}
	
	//if (isdone) {
	//	cout << "You lose" << endl;
	//}
	if (isdfs)
	{
		ofSetColor(200);
		ofSetLineWidth(4);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	if (isBFS)
	{
		ofSetColor(200);
		//ofSetColor(0, 162, 232);
		ofSetLineWidth(4);
		if (isOpen)
			bfsdraw();
		else
			cout << "You must open file first" << endl;
	}
	if (bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight() - 20);
	}

} // end Draw


void ofApp::makemine()
{
	//지뢰 생성, 시간제한, life를 초기화한다. 즉 게임의 초기 셋팅을 진행한다

	visited = (int**)malloc(sizeof(int*)*HEIGHT);
	for (int i = 0; i < HEIGHT; i++) {
		visited[i] = (int*)malloc(sizeof(int)*WIDTH);
		for (int j = 0; j < WIDTH; j++) {
			visited[i][j] = 0;
		}
	}
	cout << "-----------------------------------" << endl;
	cout << "Game Start!" << endl;
	cout << "-----------------------------------" << endl;
	
	
	int maze = (int)((HEIGHT-1) * (WIDTH-1));
	srand((unsigned)time(NULL));
	//랜덤으로 지뢰의 개수를 생성하여 mine에 저장한다.
	mine = MAX(HEIGHT, WIDTH);
	mine = (int) rand() % mine + mine/2;
	//제한 시간을 MIN macro를 이용해 정한다.
	delay = MIN(HEIGHT, WIDTH);
	cout << "The number of land mine is " << mine << endl;
	//지뢰를 밟을 수 있는 기회를 정한다.
	life = (mine / 2) - 1;
	cout << "You have " << life << " chance for challenge" << endl;
	cout << "You have " << delay << " second for challenge" << endl;
	delay = delay * 1000;

	//밟은 지뢰인지 아닌지 체크할 배열
	mvisit = (int*)malloc(sizeof(int*)*mine);
	for (int j = 0; j < mine; j++) {
		mvisit[j] = 0;
	}
	int m = mine;


	while (m>0) {
		//랜덤으로 좌표를 생성한다
		int mx = rand()% HEIGHT;
		int my = rand() % WIDTH;
		//시작점인지 체크한다
		if (mx == 0 || my == 0) {
			continue;
		}
		//미로 내부에 있는지 확인한다
		if (mx == HEIGHT-1 || my == WIDTH-1) {
			continue;
		}
		
		for (int i = 0; i < 4; i++) {
			//미로 내부 중 칸에 있는지 확인한다
			if (visit_flag(mx + dirx[i], my + diry[i], i)) {
				visited[mx + dirx[i]][my + diry[i]] = 1;
				//지뢰 좌표를 land에 저장한다.
				land.push_back({ mx + dirx[i], my + diry[i] });
				m--;
				break;
			}
		}
	}
	trie = 0;


	for (int i = 0; i < HEIGHT; i++) {
		free(visited[i]);
	}
	free(visited);
}

void ofApp::result()
{
	//게임 종료 후, 결과를 출력하는 함수

	print_time = (int)(print_time / 1000);
	cout << "-----------------------------------" << endl;
	cout << "Game End!" << endl;
	cout << "-----------------------------------" << endl;
	//성공한 경우에 점수를 출력한다
	if (success) {
		cout << "Success!" << endl;
		cout << print_time << " second is over" << endl;
		cout << "You met " << trie << " land mine "<<endl;
		scoresum = trie;
	}
	//실패한 경우에 점수를 출력한다 
	else {
		cout << "Fail!" << endl;
		cout << print_time << " second is over" << endl;
		cout << "You met " << trie <<" land mine " << endl;
		scoresum = 5*trie;
		//실패했는데 밟은 지뢰개수가 없을 경우에 score를 3으로 셋팅한다
		if (trie == 0) {
			scoresum = 3;
		}
	}
	
	newRank(scoresum);
}



void ofApp::Rank()
{
	
	//랭킹을 쭉 보여주는 함수

	Node* tmp;
	tmp = (ptr)malloc(sizeof(Node));
	tmp = head;
	char tmpn[NAMELEN];
	int tmps;
	int count = 1;
	cout << "-----------------------------------" << endl;
	cout << "Ranking" << endl;
	cout << "-----------------------------------" << endl;
	if (rankNum <= 0) {
		cout << "No rank in the list" << endl;
	}
	//cout << rankNum <<endl;
	//링크드 리스트를 돌면서 랭킹에 따라 사용자 이름과 점수를 출력한다
	tmp = tmp->next;
	while (tmp!= NULL) {
		
		cout<< "rank: "<< count<< "  user name: " << tmp->name << "  ||   score: " << tmp->score << endl;
		
		
		tmp = tmp->next;
		count++;
	}
	cout << "-----------------------------------" << endl;
}



void ofApp::newRank(int score)
{
	//새로운 랭킹 노드를 삽입하는 함수

	char nname[NAMELEN];
	cout << "You name: ";
	cin >> nname;
	int n;
	Node* tmp =(Node*)malloc(sizeof(Node));;
	tmp = head;
	//링크드 리스트를 돌면서 해당 score보다 점수가 더 큰 경우를 찾아서 멈춘다.
	while (tmp->next != NULL) {
		if (score >= tmp->next->score) {
			tmp = tmp->next;
		}
		else {
			break;
		}

	}
	Node* newNode = (ptr)malloc(sizeof(Node));
	strcpy(newNode->name, nname);
	newNode->score = score;

	newNode->next = tmp->next;
	tmp->next = newNode;

		


	
	rankNum++;
	cout << "-----------------------------------" << endl;
	//cout << rankNum;*/
}

int ofApp::comp(int n1, int n2)
{
	if (n1 < n2) {
		return 0;
	}
	return 1;
}

void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	// Escape key exit has been disabled but it can be checked here
	if (key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if (bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if (key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check mark because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if (key == 'f') {
		bFullscreen = !bFullscreen;
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

	if (key == 'd' or key == 'D') {
		draw_flag= 1;
		

	}

	

	if (key == 'q' || key == 'Q') {
		draw_flag = 0;
		start_flag = 0;
		cout << "Exit program!";
		_Exit(0);
	}


	if (key == 's' || key == 'S') {
		makemine();//지뢰 셋팅
		//createRankList();
		
		curx = 0;
		cury = 0;
		draw_flag = 0;
		start_flag = 1;
		//srand((unsigned)time(NULL));
		old_time = clock();
	}

	if (key == 'r' || key == 'R') {
		Rank();
	}
	

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_RIGHT) {
		if (isvisit(cury+dirx[1], curx+diry[1], 1)) {
			curx++;
		}
	}
	if (key == OF_KEY_LEFT) {
		if (isvisit(cury+dirx[3], curx+diry[3], 3)) {
			curx--;
		}
	}
	if (key == OF_KEY_UP){
		if (isvisit(cury+dirx[0], curx+diry[0], 0)) {
			cury--;
		}
	}
	if (key == OF_KEY_DOWN) {
		if (isvisit(cury+dirx[2], curx+diry[2], 2)) {
			cury++;
		}
	}


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile()
{
	start_flag = 0;
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		printf("file name is %s\n", fileName);
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(filePath);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			y = buffer.getLines().begin().asString().size();
			x = buffer.size() / (y + 1);
			WIDTH = y / 2;
			HEIGHT = x / 2;


			hor = (int**)malloc(sizeof(int*)*(HEIGHT - 1));
			for (int i = 0; i < HEIGHT - 1; i++) {
				hor[i] = (int*)malloc(sizeof(int)*WIDTH);
				for (int j = 0; j < WIDTH; j++) {
					hor[i][j] = 0;
				}
			}

			ver = (int **)malloc(sizeof(int*)*HEIGHT);
			for (int i = 0; i < HEIGHT; i++) {
				ver[i] = (int*)malloc(sizeof(int)*(WIDTH - 1));
				for (int j = 0; j < HEIGHT; j++) {
					ver[i][j] = 0;
				}
			}

			input = new char*[x];
			int c = 0;
			for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
				string line = *it;
				input[c] = new char[y + 1];
				strcpy(input[c], line.c_str());
				c++;
			}

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;
			for (int i = 1; i < x - 1; i++) {
				if (!input_flag) {//wall_ver
					for (int j = 2; j < y - 1; j += 2) {
						if (input[i][j] == '|') {
							ver[i / 2][(j - 1) / 2] = 1;
						}
						else {
							ver[i / 2][(j - 1) / 2] = 0;
						}
					}
					input_flag = 1;
				}
				else {//wall_hor
					for (int j = 1; j < y - 1; j += 2) {
						if (input[i][j] == '-') {
							hor[(i - 1) / 2][j / 2] = 1;
						}
						else {
							hor[(i - 1) / 2][j / 2] = 0;
						}
					}
					input_flag = 0;
				}
			}




			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;
			
			
			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			
		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
	
}
void ofApp::freeMemory() {
	for (int i = 0; i < HEIGHT * 2; i++) {
		free(input[i]);
	}
	free(input);

	for (int i = 0; i < HEIGHT; i++) {
		free(ver[i]);
	}
	free(ver);

	for (int i = 0; i < HEIGHT * 2 - 1; i++) {
		free(hor[i]);
	}
	free(hor);
	//TO DO
	// malloc한 memory를 free해주는 함수
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	visited = (int**)malloc(sizeof(int*)*HEIGHT);
	for (int i = 0; i < HEIGHT; i++) {
		visited[i] = (int*)malloc(sizeof(int)*WIDTH);
		for (int j = 0; j < WIDTH; j++) {
			visited[i][j] = 0;
		}
	}
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	stack<dd> st;
	DFS1.clear();
	st.push({ 0,0 });
	visited[0][0] = 1;


	while (!st.empty()) {
		int hei = st.top().first, wid = st.top().second;
		if (hei == HEIGHT - 1 && wid == WIDTH - 1) {
			break;
		}
		bool endPath = true;

		for (int i = 0; i < 4; i++) {
			if (visit_flag(hei + dirx[i], wid + diry[i], i)) {
				visited[hei + dirx[i]][wid + diry[i]] = 1;
				//cout <<" a";
				DFS1.push_back({ {hei,wid}, {hei + dirx[i], wid + diry[i]} });
				st.push({ hei + dirx[i], wid + diry[i] });
				endPath = false;
				break;
			}

		}

		if (endPath) {
			//cout << "b";
			st.pop();
		}
	}
	if (!st.empty()) {
		dd temp = st.top();
		st.pop();
		while (!st.empty()) {
			DFS2.push_back({ temp, st.top() });
			temp = st.top();
			st.pop();
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		 free(visited[i]);
	}
	free (visited);
	isdfs = true;
	return 0;
	
	
	
}





void ofApp::dfsdraw()
{
	float h1, h2, w1, w2;
	for (int i = 0; i < DFS1.size(); i++) {
		h1 = DFS1[i].first.first * length + (float)length / 2;
		w1 = DFS1[i].first.second * length + (float)length / 2;
		h2 = DFS1[i].second.first * length + (float)length / 2;
		w2 = DFS1[i].second.second * length + (float)length / 2;
		ofDrawLine(w1, h1, w2, h2);
	}
	ofSetColor(0, 162, 232);
	//ofSetColor(0,0,200);
	for (int i = 0; i < DFS2.size(); i++) {
		h1 = DFS2[i].first.first * length + (float)length / 2;
		w1 = DFS2[i].first.second * length + (float)length / 2;
		h2 = DFS2[i].second.first * length + (float)length / 2;
		w2 = DFS2[i].second.second * length + (float)length / 2;
		ofDrawLine(w1, h1, w2, h2);
	}
	ofSetColor(0, 162, 232);
	
	ofSetLineWidth(4);
	return;
	//TO DO 
	//DFS를 수행한 결과를 그린다. (3주차 내용)
}
bool ofApp::BFS() {
	visited = (int**)malloc(sizeof(int*)*HEIGHT);
	for (int i = 0; i < HEIGHT; i++) {
		visited[i] = (int*)malloc(sizeof(int)*WIDTH);
		for (int j = 0; j < WIDTH; j++) {
			visited[i][j] = 0;
		}
	}

	vector<vector<dd>> parent(HEIGHT, vector<dd>(WIDTH, { -1,-1 }));
	queue<dd> q;
	BFS1.clear();
	q.push({ 0,0 });
	visited[0][0] = 1;

	while (!q.empty()) {
		
		int hei = q.front().first, wid = q.front().second;
		if (hei == HEIGHT - 1 && wid == WIDTH - 1)
			break;
		for (int i = 0; i < 4; i++) {
			if (visit_flag(hei+dirx[i], wid+diry[i], i)) {//up
				visited[hei +dirx[i]][wid+diry[i]] = 1;
				BFS1.push_back({ {hei,wid},{hei +dirx[i],wid+diry[i]} });
				q.push({ hei +dirx[i],wid+diry[i] });
				parent[hei+dirx[i]][wid+diry[i]] = { hei,wid };
			}
		}
	
	
		q.pop();
		
	}

	for (int i = 0; i < HEIGHT; i++) {
		free(visited[i]);
	}
	free(visited);
	if (!q.empty()) {
		dd des = { 0,0 };
		dd start = parent[HEIGHT - 1][WIDTH - 1];
		dd end = { HEIGHT - 1,WIDTH - 1 };
		while (start != des) {
			BFS2.push_back({ start,end });
			end = start;
			start = parent[end.first][end.second];
		}
	}
	else {
		cout << "No Route\n";
		return false;
	}
	if (isdfs) isdfs = 0;
	isBFS = 1;
	return true;


}
void ofApp::bfsdraw() {
	float h1, h2, w1, w2;
	for (int i = 0; i < BFS1.size(); i++) {
	    h1 = BFS1[i].first.first * length + (float)length / 2;
	    w1 = BFS1[i].first.second * length + (float)length / 2;
		h2 = BFS1[i].second.first * length + (float)length / 2;
		w2 = BFS1[i].second.second * length + (float)length / 2;
		ofDrawLine(w1, h1, w2, h2);
	}

	ofSetColor(0, 162, 232);
	for (int i = 0; i < BFS2.size(); i++) {
		h1 = BFS2[i].first.first * length + (float)length / 2;
		w1 = BFS2[i].first.second * length + (float)length / 2;
		h2 = BFS2[i].second.first * length + (float)length / 2;
		w2 = BFS2[i].second.second * length + (float)length / 2;
		ofDrawLine(w1, h1, w2, h2);
	}

	ofSetColor(0, 162, 232);
	ofSetLineWidth(4);
	return;
}

bool ofApp::visit_flag(int h, int w, int dir)
{
	if (h < 0 || h >= HEIGHT)
		return false;
	if (w < 0 || w >= WIDTH)
		return false;
	if (visited[h][w] == true)
		return false;



	switch (dir) {
	case 0://up
		if (hor[h][w] == true)
			return false;
		break;
	case 1://right
		if (ver[h][w - 1] == true)
			return false;
		break;
	case 2://down
		if (hor[h - 1][w] == true)
			return false;
		break;
	case 3://left
		if (ver[h][w] == true)
			return false;
		break;
	default:
		break;
	}


	return true;
}

bool ofApp::isvisit(int h, int w, int dir)
{
	if (h < 0 || h >= HEIGHT)
		return false;
	if (w < 0 || w >= WIDTH)
		return false;

	switch (dir) {
	case 0://up
		if (hor[h][w] == true)
			return false;
		break;
	case 1://right
		if (ver[h][w - 1] == true)
			return false;
		break;
	case 2://down
		if (hor[h - 1][w] == true)
			return false;
		break;
	case 3://left
		if (ver[h][w] == true)
			return false;
		break;
	default:
		break;
	}


	return true;
}


