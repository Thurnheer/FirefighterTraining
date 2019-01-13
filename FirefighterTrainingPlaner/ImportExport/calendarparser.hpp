#ifndef CALENDARPARSER_HPP
#define CALENDARPARSER_HPP

#include "pipe.hpp"
#include "xlsxcell.h"
#include <vector>
#include <array>

namespace QXlsx {
    class Document;
    class Cell;
}


namespace IO
{

enum class Month
{
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    November,
    December
};

struct Range
{
    int startRow;
    int startCol;
    int length;
};

constexpr bool operator==(Range const& lhs, Range const& rhs)
{
    return lhs.startRow == rhs.startRow && lhs.startCol == rhs.startCol && lhs.length == rhs.length;
}

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

class CalendarParser
{
public:
    CalendarParser(QXlsx::Document const& document);
    int getYear() const;

    std::vector<QXlsx::Cell const*> getDate(unsigned int day, unsigned int month) const;

private:
    QXlsx::Document const& document_;
};

[[noreturn]] inline void filterColor(pipe<QXlsx::Cell*>& in, pipe<QXlsx::Cell*>& out)
{
    for(QXlsx::Cell* cell; ; )
    {
        in >> cell;
        if(cell->format().fillIndex() == 100)
        {
            out << cell;
        }
    }
}

}
#endif // CALENDARPARSER_HPP
