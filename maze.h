#include <vector>
#include <string>
#include <stack>
#include <utility>
#include <set>

#ifndef MYHEADER_H
#define MYHEADER_H

class Maze {
public:
    Maze(int seed, int height, int width, std::string fileName);
    void generateMaze();
    void DeleteWall();
    void PrintStuff();
    bool IsValid(int x, int y);

private:
    int height;
	int width;
    int yloc;
	int xloc;
    int seed;
	int visited;
    std::string fileName;
    std::vector<std::vector<int> > maze;
    std::vector<std::pair<int, int> > neighbors;
    std::set<std::pair<int, int> > visitedCellsList;
    std::stack<std::pair<int, int> > visitedCells;
};


#endif