#ifndef DRILLPARSER_HPP
#define DRILLPARSER_HPP

#include "QVector"
#include "QRegularExpression"
#include "pipe.hpp"

namespace QXlsx {
    class Document;
}

struct RawDrill {
    QString teacher;
    QString description;
    int number;
};

namespace IO {


class DrillParser
{
public:
    DrillParser(QXlsx::Document &document);
    void pumpAllDrills(QVector<QRegularExpression> namesToFind, pipe<RawDrill>& out);

private:
    QXlsx::Document& document_;
};

}

#endif // DRILLPARSER_HPP
