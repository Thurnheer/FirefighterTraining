#include "calendarparser.hpp"
#include "xlsxdocument.h"
#include "calendarlayout.hpp"

constexpr std::array<IO::Range, IO::CalendarLayout::NUMMONTH> IO::CalendarLayout::months; // declaration for external linkage
constexpr IO::Range IO::CalendarLayout::EVENT; // declaration for external linkage

IO::CalendarParser::CalendarParser(const QXlsx::Document &document)
: document_(document)
{
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

std::vector<QXlsx::Cell const*> IO::CalendarParser::cellsFromDate(const QDate& date) const
{
    std::vector<QXlsx::Cell const*> events;
    events.reserve(2);
    IO::Range event = IO::CalendarLayout::getMonthRange(date.day(), date.month());
    for(int i = 0; i < event.length; i++)
    {
        if(QXlsx::Cell const* c = document_.cellAt(event.startRow, event.startCol + i))
        {
            events.push_back(c);
        }
    }
    return events;
}

QList<QXlsx::CellRange> IO::CalendarParser::getCellRange() const
{
    if(QXlsx::Worksheet* ws = document_.currentWorksheet())
    {
        return ws->mergedCells();
    }
    return  QList<QXlsx::CellRange>();
}
