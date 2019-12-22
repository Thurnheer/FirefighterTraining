#ifndef CALENDARLAYOUT_HPP
#define CALENDARLAYOUT_HPP

#include "rangedefinition.hpp"
#include <array>

namespace IO
{

static constexpr std::array<Cell, 12> MonthBegining
{{
    Cell{ 3,  3},
    Cell{ 3,  7},
    Cell{ 3, 11},
    Cell{ 3, 15},
    Cell{ 3, 19},
    Cell{ 3, 23},
    Cell{36,  3},
    Cell{36,  7},
    Cell{36, 11},
    Cell{36, 15},
    Cell{36, 19},
    Cell{36, 23}
}};

}
#endif // CALENDARLAYOUT_HPP
