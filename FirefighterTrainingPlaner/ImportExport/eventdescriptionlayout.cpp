#include "eventdescriptionlayout.hpp"

constexpr IO::Range IO::EventDescriptionLayout::TITLE;
constexpr IO::Range IO::EventDescriptionLayout::ZUG;
constexpr IO::Range IO::EventDescriptionLayout::MD;
constexpr IO::Range IO::EventDescriptionLayout::AS;
constexpr IO::Range IO::EventDescriptionLayout::KOMMANDOZUG;
constexpr IO::Range IO::EventDescriptionLayout::PIKETZUG;
constexpr IO::Range IO::EventDescriptionLayout::ABSTURZSICHERUNG;
constexpr IO::Range IO::EventDescriptionLayout::KADERTAGE ;

constexpr IO::Range IO::EventDescriptionLayout::LAYOUT;
constexpr IO::Range IO::EventDescriptionLayout::SPACE;
constexpr std::array<std::pair<IO::Range, uint32_t>, 7> IO::EventDescriptionLayout::allUnits_;

const std::string IO::EventDescriptionLayout::WORKSHEETNAME("Themen");
