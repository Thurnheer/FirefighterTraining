#include "drillparser.hpp"
#include "xlsxdocument.h"

IO::DrillParser::DrillParser(QXlsx::Document& document)
: document_(document)
{
    document.selectSheet("Themen");
}

void IO::DrillParser::pumpAllDrills(QVector<QRegularExpression> namesToFind, pipe<RawDrill> &out)
{

}
