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

class CalendarLayout
{
private:
    static constexpr Range addDays(int const day, Range const month, Range const event)
    {
        return Range{month.startRow + day,
                     month.startCol + event.startCol - 1,
                     event.length};
    }

    static constexpr int NUMDAYS = 31;
    static constexpr int NUMMONTH = 12;
    static constexpr Range EVENT{3, 3, 2};

    static constexpr std::array<Range, NUMMONTH> months
    {{
         Range{  2,  1,  4},
         Range{  2,  5,  4},
         Range{  2,  9,  4},
         Range{  2, 13,  4},
         Range{  2, 17,  4},
         Range{  2, 21,  4},
         Range{ 35,  1,  4},
         Range{ 35,  5,  4},
         Range{ 35,  9,  4},
         Range{ 35, 13,  4},
         Range{ 35, 17,  4},
         Range{ 35, 21,  4},
    }};

public:
    //TODO do this at compiletime
    static constexpr Range getMonthRange(int day, int month){
        //static_assert (day <= NUMDAYS && day > 0, "A month has max 31 days");
        //static_assert (month <= NUMMONTH && month > 0, "no more than 12 month in a year");
        return CalendarLayout::addDays(day, months[month-1], EVENT);
    }
};

}
#endif // CALENDARLAYOUT_HPP
