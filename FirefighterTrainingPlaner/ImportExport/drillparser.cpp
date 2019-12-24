#include "drillparser.hpp"
#include "xlsxdocument.h"

IO::DrillParser::DrillParser(QXlsx::Document& document)
: document_(document)
{
    document.selectSheet("Themen");
}

void IO::DrillParser::pumpAllDrills(pipe<RawDrill> &out) const
{
    for(auto& i : DrillTable) {
        pumpDrills(i, out);
    }
}

void IO::DrillParser::pumpDrills(std::tuple<Cell, int, IO::Category> drills, pipe<RawDrill> &out) const
{
    for(int i = 0; i < std::get<1>(drills); i++) {
        const QXlsx::Cell* c = document_.cellAt(std::get<0>(drills).row + i, std::get<0>(drills).column);
        RawDrill drill;
        drill.number = i + 1;
        drill.category = std::get<2>(drills);
        drill.description = c->value().toString().trimmed();
        out << drill;
    }
}
