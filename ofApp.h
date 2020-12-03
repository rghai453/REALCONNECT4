#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        bool checkLegalMove(int column);
        void placePiece(int column);
        char checkForWin();
        bool checkForTie();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		char grid[8][8];
        char currentPlayer;
		bool gameWon;
        bool gameStarted;
        ofTrueTypeFont font;
        char winner;
		
};
