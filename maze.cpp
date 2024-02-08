#include "maze.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <utility>
#include <set>

Maze::Maze(int seed, int y, int x, std::string fileName) {
    this->seed = seed;
    this->height = y;
    this->width = x;
    this->fileName = fileName;
    this->xloc = 0;
    this->yloc = 0;
    maze.resize(height);
    std::srand(seed);
    for (int i = 0; i < height; ++i) {
        maze[i].assign(width, 15);
    }
}

void Maze::generateMaze() {
    // Add current cells to visited stack
    visitedCells.push(std::make_pair(yloc,xloc));
    visitedCellsList.insert(std::make_pair(yloc,xloc));
    maze[0][0]=7;
    // While loop runs while there are still cells to visit
    while (!visitedCells.empty()) {
            // Find available neightbors
            // Check north and append if valid
        if (yloc-1 >= 0 && IsValid(yloc-1,xloc)) {
            neighbors.push_back(std::make_pair(yloc-1,xloc));
        }
        // Check south and append if valid
        if (yloc+1 < height && IsValid(yloc+1,xloc)) {
            neighbors.push_back(std::make_pair(yloc+1,xloc));
        }
        // Check east and append if valid
        if (xloc+1 < width && IsValid(yloc,xloc+1)) {
            neighbors.push_back(std::make_pair(yloc,xloc+1));
        }
        // Check west and append if valid
        if (xloc-1 >= 0 && IsValid(yloc,xloc-1)) {
            neighbors.push_back(std::make_pair(yloc,xloc-1));
        }

        if (!neighbors.empty()) {
            DeleteWall();
            visited++;
            std::cout << "Wall deleted" << std::endl;
            neighbors.clear();
        }
        else {
            visitedCells.pop();
            if(!visitedCells.empty()){
                yloc = visitedCells.top().first;
                xloc = visitedCells.top().second;
            }
        }
    }
    maze[height-1][width-1] -= 4;
}

bool Maze::IsValid(int y, int x) {
    return !(visitedCellsList.find(std::make_pair(y, x)) != visitedCellsList.end());
}


//function to delete a cells wall, original cell # is passed in and direction is 0=north 1=south 2=east 3=west
void Maze::DeleteWall() {
    int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
    std::pair<int, int> neigh = neighbors[idx];
    visitedCellsList.insert(std::make_pair(neigh.first,neigh.second));
    visitedCells.push(std::make_pair(neigh.first,neigh.second));
    int direction;
    int oppDirection;
    int dy = neigh.first - yloc;
    int dx = neigh.second - xloc;

    if (dx == 1) {
        direction = 1; // South
        oppDirection = 0;
    } else if (dx == -1) {
        direction = 0; // North
        oppDirection = 1;
    } else if (dy == 1) {
        direction = 2; // East
        oppDirection = 3;
    } else if (dy == -1) {
        direction = 3; // West
        oppDirection = 2;
    } else {
        // Invalid direction, do nothing
        return;
    }

    int num = maze[yloc][xloc]; // Gets 0-15 value for current cell
    std::bitset<4> binaryNum(num); //converts int to binary
    if(binaryNum.test(direction)){ 
        binaryNum.flip(direction);    //Deleted wall from passed in side 0n 1s 2e 3w
    }
    maze[yloc][xloc] = (int)(binaryNum.to_ulong());//Converts back to usable int

    num = maze[neigh.first][neigh.second]; // Gets 0-15 value for neighbor
    std::bitset<4> binaryNum2(num); //converts int to binary
    if(binaryNum2.test(oppDirection)) {
        binaryNum2.flip(oppDirection);    //Deleted wall from passed in side 0n 1s 2e 3w
    }
    maze[neigh.first][neigh.second] = (int)(binaryNum2.to_ulong());//Converts back to usable int

    yloc = neigh.first;
    xloc = neigh.second;
    
    std::cout << "Moved to the neighbor: " << yloc << "," << xloc << std::endl;
}

void Maze::PrintStuff() {
    std::ofstream outFile(fileName);
    if (!maze.empty() && maze.size() > 0 && maze[0].size() > 0) {
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[0].size(); j++)
            { outFile << maze[i][j]<<"\t"; }
            outFile << " " << std::endl;
}}outFile.close();}