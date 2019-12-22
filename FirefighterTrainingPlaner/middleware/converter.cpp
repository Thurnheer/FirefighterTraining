#include "converter.hpp"
#include "qdatetime.h"

void convert(pipe<IO::RawEvent>& in) {
    IO::RawEvent event;
    do {
        in >> event;
        if(event.date() > IO::ENDEVENT.date()) {
            Event qtEvent;
            qtEvent.setName(event.name());
            qtEvent.setUuid(event.uuid.toString());
            qtEvent.setDrillNumber(event.drillNumber);
            QDateTime starttime; starttime.setDate(event.date()); starttime.setTime(event.startTime);
            QDateTime endtime; endtime.setDate(event.date()); endtime.setTime(event.endTime);
            qtEvent.setStartDate(starttime);
            qtEvent.setEndDate(endtime);
            qtEvent.save();
        }
    } while (event.date() > IO::ENDEVENT.date());
}
