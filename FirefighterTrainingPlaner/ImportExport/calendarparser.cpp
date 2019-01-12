#include "calendarparser.hpp"
#include "xlsxdocument.h"

constexpr std::array<IO::Range, IO::CalendarLayout::NUMMONTH> IO::CalendarLayout::months; // declaration for external linkage
constexpr IO::Range IO::CalendarLayout::EVENT; // declaration for external linkage

IO::CalendarParser::CalendarParser(const QXlsx::Document &document)
: document_(document){

}

int IO::CalendarParser::getYear() const
{
    QRegExp regex("(\\d+)");
    QString value = document_.read(1, 1).toString();
    int pos = regex.indexIn(value);
    if(pos > -1)
        return regex.cap(1).toInt();
    return -1;
}

std::vector<QXlsx::Cell*> IO::CalendarParser::getDate(unsigned int day, unsigned int month) const
{
    std::vector<QXlsx::Cell*> events;
    events.reserve(2);
    IO::Range event = IO::CalendarLayout::getMonthRange(day, month);
    for(int i = 0; i < event.length; i++)
    {
        events.push_back(document_.cellAt(event.startRow, event.startCol + i));
    }
    return events;
}
