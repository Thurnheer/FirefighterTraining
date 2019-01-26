#ifndef EVENTTYPEPARSER_HPP
#define EVENTTYPEPARSER_HPP

#include "eventdescriptionlayout.hpp"
#include <vector>

namespace QXlsx {
    class Document;
}

namespace IO {

class EventTypeParser
{
public:
    EventTypeParser(QXlsx::Document& document);
    std::vector<EventDescriptionLayout::Layout> pumpDescriptions();

private:
    QXlsx::Document& document_;
};

}

#endif // EVENTTYPEPARSER_HPP
