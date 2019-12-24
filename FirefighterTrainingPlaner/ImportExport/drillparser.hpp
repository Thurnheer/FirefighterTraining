#ifndef DRILLPARSER_HPP
#define DRILLPARSER_HPP

#include "QVector"
#include "QRegularExpression"
#include "pipe.hpp"
#include "calendarlayout.hpp"

namespace QXlsx {
    class Document;
}

struct RawDrill {
    QString teacher;
    QString description;
    IO::Category category;
    int number;
};

namespace IO {


class DrillParser
{
public:
    DrillParser(QXlsx::Document &document);
    void pumpAllDrills(pipe<RawDrill>& out) const;

    void pumpDrills(std::tuple<Cell, int, IO::Category> drills, pipe<RawDrill> &out) const;
private:
    QXlsx::Document& document_;
};

}

#endif // DRILLPARSER_HPP
