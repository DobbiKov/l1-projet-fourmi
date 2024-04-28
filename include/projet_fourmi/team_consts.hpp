#ifndef TEAM_CONSTS_HPP
#define TEAM_CONSTS_HPP

#include <vector>
#include <projet_fourmi/consts.hpp>
#include <projet_fourmi/coord.hpp>

const int NUMBER_OF_COLONIES = 3;

const int TEAMS_COLORS[NUMBER_OF_COLONIES][3] = {
    {255, 0, 0},
    {255, 255, 0},
    {255, 0, 255},
};

const vector<vector<Coord>> NIDS_COORDS = {{
    {
        Coord(4, 7),
        Coord(4, 8),
        Coord(5, 7),
        Coord(5, 8)
    },
    {
        Coord(8, 9),
        Coord(9, 9),
        Coord(8, 10),
        Coord(9, 10)
    },
    {
        Coord(12, 16),
        Coord(12, 17),
        Coord(13, 16),
        Coord(13, 17)
    },
    }};

#endif