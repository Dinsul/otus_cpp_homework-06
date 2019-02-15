#include "bulk.h"
#include <fstream>
#include <iostream>

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "usage: bulk N\n\tN - number of commands in bulk." << std::endl;

        return 1;
    }

    int commandsCount = atoi(argv[1]);

    Bulk   blk;
    Worker wrk;

    BulkController ctrl(commandsCount, blk, wrk);

    std::string cmd;
    cmd.clear();

    for(std::string line; std::getline(std::cin, line);)
    {
        ctrl.addString(line);
    }

    ctrl.flush();

    return 0;
}
