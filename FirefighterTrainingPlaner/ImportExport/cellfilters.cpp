#include "cellfilters.hpp"
#include "xlsxcell.h"


void IO::filterBackgroundColor(int const color, pipe<EventCell>& in, pipe<EventCell>& out)
{
    EventCell cell { { 1979, 2, 6}, { nullptr } };
    do
    {
        in >> cell;
        if(std::get<1>(cell)->format().fillIndex() == color)
        {
            out << cell;
        }
    }
    while(std::get<1>(cell) != nullptr);
}

void IO::filterEmpty(pipe<EventCell>& in, pipe<EventCell>& out)
{
    EventCell cell { { 1979, 2, 6}, { nullptr } };
    do
    {
        in >> cell;
        if(!std::get<1>(cell)->value().toString().isEmpty())
        {
            out << cell;
        }
    }
    while ( std::get<1>(cell) != nullptr);
}

void IO::filterCellValueColor(QColor const color, pipe<EventCell>& in, pipe<EventCell>& out)
{
    EventCell cell { { 1979, 2, 6}, { nullptr } };
    do
    {
        in >> cell;
        if(std::get<1>(cell)->format().fontColor() == color)
        {
            out << cell;
        }
    }
    while(std::get<1>(cell) != nullptr);
}
