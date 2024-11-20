#include "iGraphics.h"
#include <stdlib.h>
 
// Screen dimensions
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
 
// Bird properties
#define BIRD_WIDTH 20
#define BIRD_HEIGHT 20
#define BIRD_X 50
int bird_y = 300;
int bird_velocity = 0;
#define GRAVITY 2
#define FLAP_STRENGTH -10
 
// Pipe properties
#define PIPE_WIDTH 70
#define PIPE_GAP 200
int pipe_x[2] = {SCREEN_WIDTH, SCREEN_WIDTH + 200};
int pipe_height[2];
#define PIPE_VELOCITY 3
 
// Game state
int score = 0;
int gameOver = 0;
 
// Function to reset pipes and bird position
void resetGame() {
    bird_y = 300;
    bird_velocity = 0;
    score = 0;
    gameOver = 0;
    pipe_x[0] = SCREEN_WIDTH;
    pipe_x[1] = SCREEN_WIDTH + 200;
    for (int i = 0; i < 2; i++) {
        pipe_height[i] = rand() % 300 + 150; // Random height
    }
}
 
// Function to check collisions
int checkCollision() {
    if (bird_y <= 0 || bird_y + BIRD_HEIGHT >= SCREEN_HEIGHT) {
        return 1; // Collision with top or bottom
    }
    for (int i = 0; i < 2; i++) {
        if (pipe_x[i] < BIRD_X + BIRD_WIDTH && pipe_x[i] + PIPE_WIDTH > BIRD_X) {
            if (bird_y < pipe_height[i] || bird_y + BIRD_HEIGHT > pipe_height[i] + PIPE_GAP) {
                return 1; // Collision with pipe
            }
        }
    }
    return 0;
}
 
// iDraw function to draw the game
void iDraw() {
    iClear();
    if (gameOver) {
        iSetColor(255, 0, 0);
        iText(150, 300, "Game Over!", GLUT_BITMAP_HELVETICA_18);
        iText(150, 270, "Press 'R' to Restart", GLUT_BITMAP_HELVETICA_18);
        return;
    }
 
    // Draw bird
    iSetColor(0, 255, 0);
    iFilledRectangle(BIRD_X, bird_y, BIRD_WIDTH, BIRD_HEIGHT);
 
    // Draw pipes
    iSetColor(0, 0, 0);
    for (int i = 0; i < 2; i++) {
        iFilledRectangle(pipe_x[i], 0, PIPE_WIDTH, pipe_height[i]);                          // Upper pipe
        iFilledRectangle(pipe_x[i], pipe_height[i] + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT); // Lower pipe
    }
 
    // Display score
    iSetColor(0, 0, 0);
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);
    iText(10, 570, scoreText, GLUT_BITMAP_HELVETICA_18);
}
 
// iKeyboard function to handle key events
void iKeyboard(unsigned char key) {
    if (key == ' ') {
        bird_velocity = FLAP_STRENGTH; // Flap the bird
    } else if (key == 'r' && gameOver) {
        resetGame();
    }
}
 
// iSpecialKeyboard function for special keys
void iSpecialKeyboard(unsigned char key) {}
 
// iMouse function (not used but required)
void iMouseMove(int mx, int my) {}
 
// Game update logic
void updateGame() {
    if (gameOver) return;
 
    bird_velocity += GRAVITY; // Apply gravity
    bird_y += bird_velocity;
 
    // Move pipes
    for (int i = 0; i < 2; i++) {
        pipe_x[i] -= PIPE_VELOCITY;
 
        if (pipe_x[i] + PIPE_WIDTH < 0) { // Reset pipe position after it goes out of the screen
            pipe_x[i] = SCREEN_WIDTH;
            pipe_height[i] = rand() % 300 + 150; // Generate new random height
            score++;
        }
    }
 
    // Check for collisions
    if (checkCollision()) {
        gameOver = 1;
    }
}
 
int main() {
    // Initialize pipe heights
    for (int i = 0; i < 2; i++) {
        pipe_height[i] = rand() % 300 + 150;
    }
 
    iSetTimer(20, updateGame); // Update game every 20 ms
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
    return 0;
}