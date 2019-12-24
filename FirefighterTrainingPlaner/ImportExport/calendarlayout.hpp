#ifndef CALENDARLAYOUT_HPP
#define CALENDARLAYOUT_HPP

#include "rangedefinition.hpp"
#include <array>
#include <tuple>

namespace IO
{

enum class Category {
    unknown = 0,
    zug,
    masch,
    as,
    kommando,
    piket,
    absturz
};

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

static constexpr std::array<std::tuple<Cell, int, Category>, 6> DrillTable
{{
    {Cell{ 5,  3}, 10, Category::zug},
    {Cell{18,  3}, 6, Category::masch},
    {Cell{27,  3}, 4, Category::as},
    {Cell{34,  3}, 10, Category::kommando},
    {Cell{47,  3}, 2, Category::piket},
    {Cell{52,  3}, 2, Category::absturz}
}};

}
#endif // CALENDARLAYOUT_HPP
