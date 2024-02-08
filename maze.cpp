#include "maze.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <utility>

Maze::Maze(int seed, int y, int x) {
    this->seed = seed;
    this->height = y;
    this->width = x;
    this->xloc = 0;
    this->yloc = 0;
    maze.resize(height);
    std::srand(seed);
    for (int i = 0; i < height; ++i) {
        maze[i].assign(width, 15);
    }
    
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++) {
           unvisitedCells.push_back(std::make_pair(i,j));
            
        }
    }
    visitedCells.push(std::make_pair(xloc,yloc));
}

void Maze::generateMaze() {
    // Add current cells to visited stack

    // Mark this cell as visited by taking it out of the unvisitedCells vector
    for(int i = 0; i < unvisitedCells.size(); i++){
        if (unvisitedCells[i].first == xloc && unvisitedCells[i].second == yloc){
            unvisitedCells[i] = std::make_pair(height+2,width+2);
            break;
        }
    }

    // While loop runs while there are still cells to visit
    while (!unvisitedCells.empty() && visited < height*width-1) {
        // Find available neightbors
        GetNeighbors(xloc,yloc);
        
        DeleteWall();
        //std::cout << "visited: " << std::to_string(visitedCells.size()) << " | unvisited: " << std::to_string(unvisitedCells.size()) << std::endl;
    }
}

void Maze::GetNeighbors(int xloc, int yloc) {
    neighbors.clear();
    // Check north and append if valid
    for(int i = 0; i < unvisitedCells.size(); i++){
        if ((yloc-1 >= 0) && (unvisitedCells[i].first == xloc) && (unvisitedCells[i].second == yloc-1)) {
            neighbors.push_back(std::make_pair(xloc,yloc-1));
        }
    }
    // Check south and append if valid
    for(int i = 0; i < unvisitedCells.size(); i++){
        if ((yloc+1 <= height) && (unvisitedCells[i].first == xloc) && (unvisitedCells[i].second == yloc+1)) {
            neighbors.push_back(std::make_pair(xloc,yloc+1));
        }
    }
    // Check east and append if valid
    for(int i = 0; i < unvisitedCells.size(); i++){
        if ((xloc+1 <= width) && (unvisitedCells[i].first == xloc+1) && (unvisitedCells[i].second == yloc)) {
            neighbors.push_back(std::make_pair(xloc+1,yloc));
        }
    }
    // Check west and append if valid
    for(int i = 0; i < unvisitedCells.size(); i++){
        if ((xloc-1 >= 0) && (unvisitedCells[i].first == xloc-1) && (unvisitedCells[i].second == yloc)) {
            neighbors.push_back(std::make_pair(xloc-1,yloc));
        }
    }
    if (neighbors.size() < 1) {
        visitedCells.pop();
    }
    else {visited++;}
}

//function to delete a cells wall, original cell # is passed in and direction is 0=north 1=south 2=east 3=west
void Maze::DeleteWall() {
    int idx = std::rand() / ((RAND_MAX + 1u) / neighbors.size());
    std::pair<int, int> neighborCell = neighbors[idx];
    int direction;
    int oppDirection;
    int dx = neighborCell.first - xloc;
    int dy = neighborCell.second - yloc;

    if (dx == 1) {
        direction = 2; // East
        oppDirection = 3;
    } else if (dx == -1) {
        direction = 3; // West
        oppDirection = 2;
    } else if (dy == 1) {
        direction = 1; // South
        oppDirection = 0;
    } else if (dy == -1) {
        direction = 0; // North
        oppDirection = 1;
    } else {
        // Invalid direction, do nothing
        return;
    }

    int num = maze[xloc][yloc]; // Gets 0-15 value for current cell
    std::bitset<4> binaryNum(num); //converts int to binary
    binaryNum.flip(direction);    //Deleted wall from passed in side 0n 1s 2e 3w
    maze[xloc][yloc] = (int)(binaryNum.to_ulong());//Converts back to usable int

    num = maze[neighborCell.first][neighborCell.second]; // Gets 0-15 value for neighbor
    std::bitset<4> binaryNum2(num); //converts int to binary
    binaryNum.flip(oppDirection);    //Deleted wall from passed in side 0n 1s 2e 3w
    maze[neighborCell.first][neighborCell.second] = (int)(binaryNum.to_ulong());//Converts back to usable int

    xloc = neighborCell.first;
    yloc = neighborCell.second;
    std::cout << "Moved to the neighbor: " << yloc << xloc << std::endl;
}

void Maze::PrintStuff() {
    if (!maze.empty() && maze.size() > 0 && maze[0].size() > 0) {
        for (int i = 0; i < maze.size(); i++)
        {
            for (int j = 0; j < maze[0].size(); j++)
            {
                std::cout << maze[i][j];
                std::cout << " ";
            }
            std::cout << " " << std::endl;
        }
        
    } else {
        std::cout << "Maze is not properly initialized or indices are out of bounds." << std::endl;
    }
}