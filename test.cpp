#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>

#define screenwidth 800
#define screenheight 600

// Pac-Man variables
int pacmanX = 400, pacmanY = 300; // Initial position of Pac-Man
int pacmanSize = 30; // Size of Pac-Man
int pacmanSpeed = 10; // Pac-Man's movement speed
int pacmanDirection = 0; // Direction (0: Right, 1: Down, 2: Left, 3: Up)

// Maze layout (1 represents a wall, 0 represents an empty space)
int maze[20][20];

// Function to initialize the maze
void initMaze() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0 || j == 0 || i == 19 || j == 19) {
                maze[i][j] = 1; // walls around the border
            } else {
                maze[i][j] = 0; // empty space
            }
        }
    }

    // Example walls inside the maze
    maze[5][5] = 1;
    maze[6][5] = 1;
    maze[7][5] = 1;
    maze[8][5] = 1;
}

// Function to draw the Pac-Man character (using an arc for the mouth)
void drawPacman() {
    int mouthAngle = 45; // The angle for Pac-Man's mouth

    iSetColor(255, 255, 0); // Set color for Pac-Man (yellow)
    iFilledArc(pacmanX, pacmanY, pacmanSize, pacmanSize, mouthAngle * pacmanDirection, 360 - mouthAngle * pacmanDirection);
}

// Function to move Pac-Man based on the arrow key input
void movePacman() {
    if (pacmanDirection == 0) {
        pacmanX += pacmanSpeed; // Move to the right
    } else if (pacmanDirection == 1) {
        pacmanY -= pacmanSpeed; // Move down
    } else if (pacmanDirection == 2) {
        pacmanX -= pacmanSpeed; // Move left
    } else if (pacmanDirection == 3) {
        pacmanY += pacmanSpeed; // Move up
    }
}

// Function to handle keyboard input
void iKeyboard(unsigned char key) {
    if (key == 'd' || key == 'D') { // Move right
        pacmanDirection = 0;
    }
    if (key == 's' || key == 'S') { // Move down
        pacmanDirection = 1;
    }
    if (key == 'a' || key == 'A') { // Move left
        pacmanDirection = 2;
    }
    if (key == 'w' || key == 'W') { // Move up
        pacmanDirection = 3;
    }
}

// Function to handle special keyboard input (arrow keys)
void iSpecialKeyboard(unsigned char key) {
    if (key == GLUT_KEY_RIGHT) { // Move right
        pacmanDirection = 0;
    }
    if (key == GLUT_KEY_DOWN) { // Move down
        pacmanDirection = 1;
    }
    if (key == GLUT_KEY_LEFT) { // Move left
        pacmanDirection = 2;
    }
    if (key == GLUT_KEY_UP) { // Move up
        pacmanDirection = 3;
    }
}

// Function to draw the maze
void drawMaze() {
    int mazeX, mazeY;
    iSetColor(0, 0, 255); // Set color for walls (blue)
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (maze[i][j] == 1) {
                mazeX = j * 40;
                mazeY = i * 40;
                iFilledRectangle(mazeX, mazeY, 40, 40); // Draw a wall
            }
        }
    }
}

// Function to check if Pac-Man collides with a wall
int checkCollision() {
    int mazeX = pacmanX / 40;
    int mazeY = pacmanY / 40;

    if (maze[mazeY][mazeX] == 1) { // Wall collision
        return 1;
    }
    return 0;
}

// Function to render the game screen
void iDraw() {
    iClear(); // Clear the screen

    drawMaze(); // Draw the maze
    drawPacman(); // Draw Pac-Man

    movePacman(); // Move Pac-Man

    // Check for collision with walls
    if (checkCollision()) {
        pacmanX -= pacmanSpeed; // Undo movement if there's a collision
        pacmanY -= pacmanSpeed;
    }
}

int main() {
    iInitialize(screenwidth, screenheight, "Pac-Man");

    initMaze(); // Initialize the maze

    iStart(); // Start the game
    return 0;
}
