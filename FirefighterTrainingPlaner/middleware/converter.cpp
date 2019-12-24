#include "converter.hpp"
#include "qdatetime.h"
#include "qsqlquery.h"
#include "QString"

void convert(pipe<IO::RawEvent>& in) {
    IO::RawEvent event;
    do {
        in >> event;
        if(event.date() > IO::ENDEVENT.date()) {
            Event qtEvent;
            qtEvent.setName(event.name());
            qtEvent.setUuid(event.uuid.toString());
            qtEvent.setDrillNumber(event.drillNumber);
            qtEvent.setCategory(static_cast<int>(event.category));
            QDateTime starttime; starttime.setDate(event.date()); starttime.setTime(event.startTime);
            QDateTime endtime; endtime.setDate(event.date()); endtime.setTime(event.endTime);
            qtEvent.setStartDate(starttime);
            qtEvent.setEndDate(endtime);
            qtEvent.save();
        }
    } while (event.date() > IO::ENDEVENT.date());
}

void save(pipe<RawDrill>& in) {
    RawDrill drill;
    do {
        in >> drill;
        if(!drill.description.isEmpty()) {
            QSqlQuery query;
            // We store the time as seconds because it's easier to query.
            query.exec(QString::fromLatin1("insert into Drill values('%1', '%2', '%3', '%4')").arg(drill.description,
                                                                            QString::number(drill.number),
                                                                            QString::number(static_cast<int>(drill.category)),
                                                                            drill.teacher));
        }
    } while (!drill.description.isEmpty());
}
