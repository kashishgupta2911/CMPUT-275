#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Cell intialisation
const char ALIVE = 'O'; 
const char DEAD = '.'; 

// Counts live neighbors of a cell
int count(char** grid, int row, int col, int rows, int columns) {
    int count = 0;
    // Loop over all neighbors
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int newRow = row + i;
            int newCol = col + j;
            // Count if neighbor is alive
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && grid[newRow][newCol] == ALIVE) {
                ++count;
            }
        }
    }
    return count; // Return count of live neighbors
}

// Updates the grid to the next generation
void new_grid(char** grid, int rows, int columns) {
    char** newGrid = new char*[rows]; // New grid for next generation

    // Initialize new grid with dead cells
    for (int i = 0; i < rows; ++i) {
        newGrid[i] = new char[columns];
        for (int j = 0; j < columns; ++j) {
            newGrid[i][j] = DEAD;
        }
    }

    // Apply rules to each cell
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            int liveNeighbors = count(grid, row, col, rows, columns);
            char currentState = grid[row][col];
            char& nextState = newGrid[row][col];

            // Apply Conway's Game of Life rules
            nextState = (currentState == ALIVE) ?
                        (liveNeighbors < 2 || liveNeighbors > 3) ? DEAD : ALIVE :
                        (liveNeighbors == 3) ? ALIVE : DEAD;
        }
    }

    // Copy new grid to original grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = newGrid[i][j];
        }
    }

    // Deallocate new grid
    for (int i = 0; i < rows; ++i) {
        delete[] newGrid[i];
    }
    delete[] newGrid;
}

// Prints the grid
void print_grid(char** grid, int rows, int columns) {
    // Print top border
    for (int i = 0; i < columns; ++i) {
        cout << '|';
    }
    cout << endl;

    // Print cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << grid[i][j];
        }
        cout << endl;
    }

    // Print bottom border
    for (int i = 0; i < columns; ++i) {
        cout << '|';
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    int rows = 0;
    int columns = 0;
    char** grid = nullptr;
    string line;

    // Read grid size
    while (getline(cin, line)) {
        if (line == "x") break;
        stringstream ss(line);
        char cell;
        int j = 0;
        while (ss >> cell) {
            if (columns == 0) ++columns;
            ++j;
        }
        columns = j;
        ++rows;
    }

    // Allocate grid
    grid = new char*[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[columns];
    }

    // Reset input stream
    cin.clear();
    cin.seekg(0, ios::beg);

    // Read grid
    rows = 0;
    while (getline(cin, line)) {
        if (line == "x") break;
        stringstream ss(line);
        int j = 0;
        char cell;
        while (ss >> cell) {
            grid[rows][j] = cell;
            ++j;
        }
        ++rows;
    }

    // Handle commands
    char command;
    while (cin >> command) {
        if (command == 'p') {
            print_grid(grid, rows, columns); // Print command
        } else if (command == 's') {
            new_grid(grid, rows, columns); // Step command
        }
    }

    // Deallocate grid
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
