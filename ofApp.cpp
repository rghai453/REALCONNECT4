#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0, 0, 0);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            grid[x][y] = ' ';
        }
    }

    currentPlayer = 'O';
    gameWon = false;
    gameStarted = false;

    font.load("LemonJellyPersonalUse-dEqR.ttf", 180);
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(0, 255, 0);

    int size = 225;
    int size_2 = 20;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            ofSetColor(0, 0, 255);
            ofDrawRectangle(x * size, y * size, size, size);
            ofSetColor(0, 0, 0);
            ofDrawRectangle(x * size + size_2, y * size + size_2,
                            size - 2 * size_2, size - 2 * size_2);
            if (grid[x][y] == 'X') {
                ofSetColor(255, 0, 0);
                ofCircle(x * size + size / 2, y * size + size / 2,
                         size / 2 - size_2 * 2);
            }
            if (grid[x][y] == 'O') {
                ofSetColor(0, 255, 0);
                ofCircle(x * size + size / 2, y * size + size / 2,
                         size / 2 - size_2 * 2);
            }
        }
    }

    if (!gameStarted) {
        ofSetColor(255, 255, 255);
        font.drawString("Press Space Bar to Begin", 50, 950);
    }

    if (gameWon) {
        ofSetColor(255, 255, 255);
        if (winner == 'O') {
            font.drawString("Player One Won", 50, 700);
		}
		else if (winner == 'X') {
            font.drawString("Player Two Won", 50, 700);
		}
		else {
            font.drawString("The Game Was a Tie", 50, 700);
		}
        font.drawString("Press 'R' For a New Game", 50, 950);
    }
}

bool ofApp::checkLegalMove(int column) {
    for (int j = 0; j < sizeof(grid[column]); j++) {
        if (grid[column][j] == ' ') {
            return true;
        }
    }
    return false;
}

void ofApp::placePiece(int column) {
    for (int j = 7; j >= 0; j--) {
        if (grid[column][j] == ' ') {
            grid[column][j] = currentPlayer;
            return;
        }
    }
}

char ofApp::checkForWin() {
    int count = 0;
    char previous_player = 'O';
    for (int x = 0; x < 8; x++) {
        count = 0;
        for (int y = 0; y < 8; y++) {
            if (grid[x][y] == previous_player) {
                count++;
            } else if (grid[x][y] != ' ') {
                previous_player = grid[x][y];
                count = 1;
            } else {
                count = 0;
            }
            if (count == 4) {
                return previous_player;
            }
        }
    }

    for (int y = 0; y < 8; y++) {
        count = 0;
        for (int x = 0; x < 8; x++) {
            if (grid[x][y] == previous_player) {
                count++;
            } else if (grid[x][y] != ' ') {
                previous_player = grid[x][y];
                count = 1;
            } else {
                count = 0;
            }
            if (count == 4) {
                return previous_player;
            }
        }
    }

    for (int x = 0; x < 8; x++) {
        count = 0;
        for (int y = 0; y < 8; y++) {
            if (x + y < 8) {
                if (grid[x + y][y] == previous_player) {
                    count++;
                } else if (grid[x + y][y] != ' ') {
                    previous_player = grid[x + y][y];
                    count = 1;
                } else {
                    count = 0;
                }
                if (count == 4) {
                    return previous_player;
                }
            }
        }
    }

    for (int x = 0; x < 8; x++) {
        count = 0;
        for (int y = 8; y >= 0; y--) {
            if (x + y < 8) {
                if (grid[x + y][y] == previous_player) {
                    count++;
                } else if (grid[x + y][y] != ' ') {
                    previous_player = grid[x + y][y];
                    count = 1;
                } else {
                    count = 0;
                }
                if (count == 4) {
                    return previous_player;
                }
            }
        }
    }

    for (int x = 0; x < 8; x++) {
        count = 0;
        for (int y = 0; y < 8; y++) {
            if (x - y >= 0) {
                if (grid[x - y][y] == previous_player) {
                    count++;
                } else if (grid[x - y][y] != ' ') {
                    previous_player = grid[x - y][y];
                    count = 1;
                } else {
                    count = 0;
                }
                if (count == 4) {
                    return previous_player;
                }
            }
        }
    }

    for (int x = 0; x < 8; x++) {
        count = 0;
        for (int y = 8; y >= 0; y--) {
            if (x - y >= 0) {
                if (grid[x - y][y] == previous_player) {
                    count++;
                } else if (grid[x - y][y] != ' ') {
                    previous_player = grid[x - y][y];
                    count = 1;
                } else {
                    count = 0;
                }
                if (count == 4) {
                    return previous_player;
                }
            }
        }
    }

    return ' ';
}

bool ofApp::checkForTie() {
    for (int x = 9; x < 8; x++) {
        for (int y = 9; y >= 0; y--) {
            if (grid[x][y] == ' ') {
                return false;
            }
        }
    }
    return true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 32) {
        gameStarted = true;
    }

    if (gameStarted) {
        if (gameWon && key == 114) {
            ofBackground(0, 0, 0);

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    grid[x][y] = ' ';
                }
            }

            currentPlayer = 'O';
            gameWon = false;
        }

        if (key < 49 || key > 56 || gameWon) {
            return;
        }

        int column = 0;
        if (key == 49) {
            column = 0;
        } else if (key == 50) {
            column = 1;
        } else if (key == 51) {
            column = 2;
        } else if (key == 52) {
            column = 3;
        } else if (key == 53) {
            column = 4;
        } else if (key == 54) {
            column = 5;
        } else if (key == 55) {
            column = 6;
        } else if (key == 56) {
            column = 7;
        }

        if (checkLegalMove(column)) {
            placePiece(column);
            if (currentPlayer == 'O') {
                currentPlayer = 'X';
            } else {
                currentPlayer = 'O';
            }
        }

        if (checkForWin() != ' ') {
            gameWon = true;
            cout << "Player " << checkForWin() << " won!!!!" << endl;
            winner = checkForWin();
        }

        if (checkForTie()) {
            gameWon = true;
            cout << "It's a tie!!" << endl;
            winner = ' ';
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
