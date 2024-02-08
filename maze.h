#include <vector>
#include <string>
#include <stack>
#include <utility>

#ifndef MYHEADER_H
#define MYHEADER_H

class Maze {
public:
    Maze(int seed, int rows, int cols);
    void generateMaze();
    void GetNeighbors(int xloc, int yloc);
    void DeleteWall();
    void PrintStuff();

private:
    int height;
	int width;
    int yloc;
	int xloc;
    int seed;
	int visited;
    int neighborCellNumber;

    int  m_nPathWidth;
    int  numberVisited;
    std::vector<std::vector<int> > maze;
    std::vector<std::pair<int, int> > neighbors;
    std::vector<std::pair<int, int> > unvisitedCells;
    std::stack<std::pair<int, int> > visitedCells;
};


#endif