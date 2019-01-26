#ifndef EVENTDESCRIPTIONLAYOUT_HPP
#define EVENTDESCRIPTIONLAYOUT_HPP

#include "rangedefinition.hpp"
#include <array>
#include <tuple>
#include <string>

namespace IO {

class EventDescriptionLayout
{
private:
    static constexpr Range TITLE{ 1, 1, 1};
    static constexpr Range ZUG{ 3, 1, 1};
    static constexpr Range MD{ 16, 1, 1};
    static constexpr Range AS{ 25, 1, 1};
    static constexpr Range KOMMANDOZUG{ 32, 1, 1};
    static constexpr Range PIKETZUG { 45, 1, 1};
    static constexpr Range ABSTURZSICHERUNG{ 50, 1, 1};
    static constexpr Range KADERTAGE { 55, 1, 1};

    static constexpr Range LAYOUT{ 0, 0, 3};
    static constexpr Range SPACE{ 1, 0, 0};

    static constexpr uint32_t ZUG_TRAININGS = 10;
    static constexpr uint32_t MD_TRAININGS = 6;
    static constexpr uint32_t AS_TRAININGS = 5;
    static constexpr uint32_t KOMMANDOZUGTRAININGS = 10;
    static constexpr uint32_t PIKETZUGTRAININGS = 2;
    static constexpr uint32_t ABSTURZSICHERUNGSTRAININGS = 2;

    static constexpr std::array<std::pair<Range, uint32_t>, 7> allUnits_{{
        {ZUG, ZUG_TRAININGS},
        {MD, MD_TRAININGS},
        {AS, AS_TRAININGS},
        {KOMMANDOZUG, KOMMANDOZUGTRAININGS},
        {PIKETZUG, PIKETZUGTRAININGS},
        {ABSTURZSICHERUNG, ABSTURZSICHERUNGSTRAININGS},
        {KADERTAGE, 0}
    }};
public:

    using  Layout = std::tuple<std::string, std::string, std::string>;
    static const std::string WORKSHEETNAME;

    static constexpr Range training(Range fwUnit, int trainingsNr)
    {
        return  fwUnit + SPACE + Range{ trainingsNr, 0, 0};
    }

    static constexpr std::array<std::pair<Range, uint32_t>, 7> allUnits() { return allUnits_; }
};
}

#endif // EVENTDESCRIPTIONLAYOUT_HPP
