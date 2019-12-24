#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include "ImportExport/calendarparser.hpp"
#include "ImportExport/drillparser.hpp"
#include <vector>
#include <memory>


void convert(pipe<IO::RawEvent>& in);

void save(pipe<RawDrill>& in);

#endif // CONVERTER_HPP
