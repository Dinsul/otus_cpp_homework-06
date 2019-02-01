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

    ImpBulk *blk = new Bulk();

    BulkController ctrl(blk, commandsCount);

    std::string cmd;
    cmd.clear();

    for(std::string line; std::getline(std::cin, line);)
    {
        ctrl.addString(line);
    }

    ctrl.flush();

    delete blk;

    return 0;
}