#ifndef CELLFILTERS_HPP
#define CELLFILTERS_HPP

#include "pipe.hpp"
#include "QColor"
#include "QDate"
#include <tuple>

namespace QXlsx {
    class Cell;
}

namespace IO {

using EventCell = std::tuple<QDate, QXlsx::Cell const*>;

void filterEmpty(pipe<EventCell>& in, pipe<EventCell>& out);

void filterBackgroundColor(int const color, pipe<EventCell>& in, pipe<EventCell>& out);

void filterCellValueColor(QColor const color, pipe<EventCell>& in, pipe<EventCell>& out);

}

#endif // CELLFILTERS_HPP
