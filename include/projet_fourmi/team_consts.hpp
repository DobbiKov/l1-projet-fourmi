#ifndef TEAM_CONSTS_HPP
#define TEAM_CONSTS_HPP

#include <vector>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/coord.hpp>

const int NUMBER_OF_COLONIES = 4;

const int TEAMS_COLORS[NUMBER_OF_COLONIES][3] = {
    {255, 0, 0},
    {0, 0, 255},
    {255, 0, 255},
    {0, 255, 0},
};

const vector<vector<Coord>> NIDS_COORDS = {{
    {
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    },
    {
        Coord(21, 5),
        Coord(21, 6),
        Coord(22, 5),
        Coord(22, 6)
    },
    {
        Coord(12, 18),
        Coord(12, 19),
        Coord(13, 18),
        Coord(13, 19)
    },
    {
        Coord(40, 25),
        Coord(40, 26),
        Coord(41, 25),
        Coord(41, 26)
    },
    }};

#endif