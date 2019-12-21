#ifndef IO_CELL_HPP
#define IO_CELL_HPP

#include <QColor>
#include <string>
#include "xlsxcell.h"

namespace IO {

class Cell
{
public:
    Cell();
    Cell(QXlsx::Cell const* const qcell);
    QColor backgroundColor() const;
    QColor textColor() const;
    std::string text() const;
    int textSize() const;
    bool bold() const;
private:
    QColor backgroundColor_;
    QColor textColor_;
    std::string text_;
    int textSize_;
    bool bold_;
};


} // namespace IO

#endif // IO_CELL_HPP
