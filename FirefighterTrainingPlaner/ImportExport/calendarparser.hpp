#ifndef CALENDARPARSER_HPP
#define CALENDARPARSER_HPP

#include "pipe.hpp"
#include "xlsxcell.h"
#include "xlsxcellrange.h"
#include <vector>
#include <array>

namespace QXlsx {
    class Document;
    class Cell;
}


namespace IO
{

class CalendarParser
{
public:
    CalendarParser(QXlsx::Document const& document);
    int getYear() const;

    void pumpAllEvents(pipe<QXlsx::Cell const*>& out);
    std::vector<QXlsx::Cell const*> cellsFromDate(const QDate &date) const;
    QList<QXlsx::CellRange> getCellRange() const;

private:
    QXlsx::Document const& document_;
};

}
#endif // CALENDARPARSER_HPP
