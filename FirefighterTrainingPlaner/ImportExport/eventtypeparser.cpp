#include "eventtypeparser.hpp"
#include "xlsxdocument.h"

IO::EventTypeParser::EventTypeParser(QXlsx::Document &document)
: document_(document)
{

}

std::vector<IO::EventDescriptionLayout::Layout> IO::EventTypeParser::pumpDescriptions()
{
    std::vector<IO::EventDescriptionLayout::Layout> v;
    v.reserve(64);
    document_.selectSheet(QString(IO::EventDescriptionLayout::WORKSHEETNAME.c_str()));
    for (auto& i : EventDescriptionLayout::allUnits()) {
        for(uint32_t j = 1; j <= std::get<1>(i); j++)
        {
            Range description = IO::EventDescriptionLayout::training(std::get<0>(i), j);
            EventDescriptionLayout::Layout l;
            std::get<0>(l) = document_.read(description.startRow, description.startCol).toString().toStdString();
            std::get<1>(l) = document_.read(description.startRow, description.startCol + 1).toString().toStdString();
            std::get<2>(l) = document_.read(description.startRow, description.startCol + 2).toString().toStdString();
            v.emplace_back(l);
        }
    }
    return v;
}
