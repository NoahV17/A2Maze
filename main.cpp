#include "maze.h"

int main(int argc, char* argv[]) {
            // Parse command-line args
    int seed = std::atoi(argv[1]);
    int height = std::atoi(argv[2]);
    int width = std::atoi(argv[3]);
    std::string fname = argv[4];

            // Create Maze object
    Maze maze(seed, height, width, fname);
    maze.generateMaze();
    maze.PrintStuff();
    return 0;
}