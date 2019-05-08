#include "io_cell.hpp"

IO::Cell::Cell()
: backgroundColor_(Qt::white)
, textColor_(Qt::black)
, text_()
, textSize_(8)
, bold_(false)
{

}

IO::Cell::Cell(QXlsx::Cell const* const qcell)
: backgroundColor_(qcell->format().hasFillData() ? qcell->format().fillIndex() : Qt::white)
, textColor_(qcell->format().fontColor())
, text_(qcell->value().toString().toStdString())
, textSize_(qcell->format().fontSize())
, bold_(qcell->format().fontBold())
{

}

QColor IO::Cell::backgroundColor() const {
    return backgroundColor_;
}

QColor IO::Cell::textColor() const {
    return textColor_;
}

std::string IO::Cell::text() const {
    return text_;
}

int IO::Cell::textSize() const {
    return textSize_;
}

bool IO::Cell::bold() const {
    return bold_;
}

