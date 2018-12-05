#include "bulk.h"
#include <fstream>
#include <iostream>

int main (int, char**)
{
    ImpBulk *blk = new Bulk();

    BulkController ctrl(blk, 3);

    std::string cmd;
    std::ifstream input;
    input.open("/dev/stdin", std::ios_base::in);

    while (!input.eof())
    {
        input >> cmd;

        if (!cmd.empty())
            ctrl.getString(cmd);

    }


    return 0;
}
