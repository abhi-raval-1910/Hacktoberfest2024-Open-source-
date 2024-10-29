#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 21;     // Width of the maze (odd number)
const int HEIGHT = 11;    // Height of the maze (odd number)

vector<vector<char>> maze(HEIGHT, vector<char>(WIDTH, '#'));

struct Cell {
    int x, y;
    Cell(int _x, int _y) : x(_x), y(_y) {}
};

// Directions for moving in the maze
const vector<Cell> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};

// Function to print the maze
void printMaze() {
    for (const auto& row : maze) {
        for (char cell : row) cout << cell;
        cout << endl;
    }
}

// Check if the cell is within the maze boundaries
bool isValid(int x, int y) {
    return x > 0 && x < HEIGHT - 1 && y > 0 && y < WIDTH - 1;
}

// Recursive DFS algorithm to generate the maze
void generateMaze(int x, int y) {
    maze[x][y] = ' ';  // Mark current cell as a path
    random_shuffle(directions.begin(), directions.end()); // Shuffle directions for randomness
    
    for (const Cell& dir : directions) {
        int nx = x + dir.x, ny = y + dir.y;  // New cell
        int mx = x + dir.x / 2, my = y + dir.y / 2;  // Middle cell between current and new
        
        // Check if the new cell is a valid and unvisited cell
        if (isValid(nx, ny) && maze[nx][ny] == '#') {
            maze[mx][my] = ' ';  // Carve a path
            generateMaze(nx, ny);  // Recursively visit the new cell
        }
    }
}

int main() {
    srand(time(0));
    
    // Starting position
    int startX = 1, startY = 1;
    maze[startX][startY] = 'S';  // Start point
    maze[HEIGHT - 2][WIDTH - 2] = 'E';  // End point
    
    generateMaze(startX, startY);
    printMaze();
    
    return 0;
}
