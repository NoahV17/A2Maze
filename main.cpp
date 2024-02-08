#include "maze.h"
#include "maze.cpp"

int main(int argc, char* argv[]) {
            // Parse command-line args
    int seed = std::atoi(argv[1]);
    int rows = std::atoi(argv[2]);
    int cols = std::atoi(argv[3]);
    //std::string fname = argv[4];

            // Create Maze object
    Maze maze(seed, rows, cols);
    maze.generateMaze();
    maze.PrintStuff();
    return 0;
}