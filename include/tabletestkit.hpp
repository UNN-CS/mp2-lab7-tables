#pragma once

#include <vector>
#include <fstream>

#include "tsorttable.hpp"
#include "tbalancetree.hpp"
#include "tarrayhash.hpp"
#include "tlisthash.hpp"
#include "ttabrecord.hpp"
#include "interface.hpp"

class TableTestKit
{
private:
    Interface mainUI;
    std::ifstream in;

    void EfficiencyTests();
    void GoogleTests(int argc, char **argv);
public:
    void StartKit(int argc, char **argv);
};
