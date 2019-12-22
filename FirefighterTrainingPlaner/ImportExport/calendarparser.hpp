#ifndef CALENDARPARSER_HPP
#define CALENDARPARSER_HPP

#include "pipe.hpp"
#include "xlsxcell.h"
#include "xlsxcellrange.h"
#include "QDate"
#include <vector>
#include <array>
#include "../middleware/event.h"
#include "../middleware/SqlTableNames.hpp"
#include "QUuid"
#include "QRegularExpression"

namespace QXlsx {
    class Document;
    class Cell;
}


namespace IO
{

struct RawEvent
{
    QString     name_;
    QString     name() const {return name_; }
    QColor      charColor;
    int         cellColor;
    QDate       date_;
    QDate       date() const { return date_; }
    QUuid       uuid;
    QString     location;
    QString     description;
    QTime       startTime;
    QTime       endTime;
    int         eventType;
};

struct EventTime
{
    QVector<QRegularExpression>  regex;
    QTime               starttime;
    QTime               endtime;
};

static const IO::RawEvent ENDEVENT{"EndEvent", QColor(), 0, QDate(2000, 1, 1), QUuid(), "", "", QTime(), QTime(), SqlTableNames::eUnknown};

class CalendarParser
{
public:
    CalendarParser(QXlsx::Document const& document, const QVector<IO::EventTime>& eventtimes);
    int getYear() const;

    void pumpAllEvents(QVector<QRegularExpression> namesToFind, pipe<RawEvent>& out);
    std::vector<QXlsx::Cell const*> cellsFromDate(const QDate &date) const;
    void pumpMonth(QDate monthToParse, pipe<std::tuple<QDate, const QXlsx::Cell*> > &out) const;
    void convert(pipe<std::tuple<QDate, const QXlsx::Cell*> > &in, pipe<RawEvent> &out) const;
    void splitCombinedEvents(pipe<RawEvent>& in, pipe<RawEvent>& out) const;
    void filterEmptyEvents(pipe<RawEvent>&in, pipe<RawEvent>& out) const;
    void filterForNames(pipe<RawEvent>&in, QVector<QRegularExpression> names, pipe<RawEvent>& filterout) const;
    void setEventType(pipe<RawEvent> &in, SqlTableNames::DivisionT division, pipe<RawEvent> &out) const;
    void setEventTime(pipe<RawEvent> &in, QVector<EventTime> time, pipe<RawEvent> &out) const;

private:
    QXlsx::Document const& document_;
    const QVector<IO::EventTime>& eventtimes_;

    pipe<std::tuple<QDate, QXlsx::Cell const*>> cells_;
    pipe<IO::RawEvent> rawEvents_;
    pipe<IO::RawEvent> eventsOnly_;
    pipe<IO::RawEvent> singleEvents_;
    pipe<IO::RawEvent> timedEvents_;
};

}
#endif // CALENDARPARSER_HPP
