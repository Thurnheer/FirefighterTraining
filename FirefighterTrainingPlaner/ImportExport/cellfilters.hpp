#ifndef CELLFILTERS_HPP
#define CELLFILTERS_HPP

#include "xlsxcell.h"
#include "pipe.hpp"

inline void filterEmpty(pipe<QXlsx::Cell const*> in, pipe<QXlsx::Cell const*> out)
{
    QXlsx::Cell const* cell = nullptr;
    do
    {
        in >> cell;
        if(!cell->value().toString().isEmpty())
        {
            out << cell;
        }
    }
    while ( cell != nullptr);
}

inline void filterBackgroundColor(int const color, pipe<QXlsx::Cell const*>& in, pipe<QXlsx::Cell const*>& out)
{
    QXlsx::Cell const* cell = nullptr;
    do
    {
        in >> cell;
        if(cell->format().fillIndex() == color)
        {
            out << cell;
        }
    }
    while(cell != nullptr);
}

inline void filterCellValueColor(QColor const color, pipe<QXlsx::Cell const*>& in, pipe<QXlsx::Cell const*>& out)
{
    QXlsx::Cell const* cell = nullptr;
    do
    {
        in >> cell;
        if(cell->format().fontColor() == color)
        {
            out << cell;
        }
    }
    while(cell != nullptr);
}

#endif // CELLFILTERS_HPP
