#include "calendarparser.hpp"
#include "xlsxdocument.h"
#include "calendarlayout.hpp"
#include <tuple>

constexpr std::array<IO::Range, IO::CalendarLayout::NUMMONTH> IO::CalendarLayout::months; // declaration for external linkage
constexpr IO::Range IO::CalendarLayout::EVENT; // declaration for external linkage

IO::CalendarParser::CalendarParser(const QXlsx::Document &document, const QVector<EventTime> &eventtimes)
: document_(document)
, eventtimes_(eventtimes)
{
}

int IO::CalendarParser::getYear() const
{
    QRegExp regex("(\\d+)");
    QString value = document_.read(1, 1).toString();
    int pos = regex.indexIn(value);
    if(pos > -1)
        return regex.cap(1).toInt();
    return -1;
}

void IO::CalendarParser::pumpAllEvents(QVector<QRegularExpression> namesToFind, pipe<RawEvent> &out)
{
    for(int i = 1; i < 13; i++) {
        QDate d(getYear(), i, 1);
        pumpMonth(d, cells_);
    }
    cells_ << std::make_tuple(IO::ENDEVENT.date, nullptr);
    convert(cells_, rawEvents_);
    filterEmptyEvents(rawEvents_, eventsOnly_);
    splitCombinedEvents(eventsOnly_, singleEvents_);
    setEventTime(singleEvents_, eventtimes_, timedEvents_);
    filterForNames(timedEvents_, namesToFind, out);
}

std::vector<QXlsx::Cell const*> IO::CalendarParser::cellsFromDate(const QDate& date) const
{
    std::vector<QXlsx::Cell const*> events;
    events.reserve(2);
    IO::Range event = IO::CalendarLayout::getMonthRange(date.day(), date.month());
    for(int i = 0; i < event.length; i++)
    {
        if(QXlsx::Cell const* c = document_.cellAt(event.startRow, event.startCol + i))
        {
            events.push_back(c);
        }
    }
    return events;
}

void IO::CalendarParser::pumpMonth(QDate monthToParse, pipe<std::tuple<QDate, const QXlsx::Cell *> > &out) const
{
    monthToParse.setDate(monthToParse.year(), monthToParse.month(), 1);
    QDate date(monthToParse);
    const Cell excel = MonthBegining[monthToParse.month() - 1];
    for(int i = 0; i < monthToParse.daysInMonth(); i++)
    {
        out << std::make_tuple(date, document_.cellAt(excel.row + i, excel.column));
        date = date.addDays(1);
    }
}

void IO::CalendarParser::convert(pipe<std::tuple<QDate, const QXlsx::Cell *> > &in, pipe<RawEvent> &out) const
{
    RawEvent event;
    std::tuple<QDate, const QXlsx::Cell*> data;
    do {
        in >> data;
        event.date = std::get<0>(data);
        const QXlsx::Cell* cell = std::get<1>(data);
        if(cell) {
            event.name = cell->value().toString();
            event.cellColor = cell->format().fillIndex();
            event.charColor = cell->format().fontColor();
            event.uuid = QUuid::createUuid();
            out << event;
        }
    } while(std::get<0>(data) > ENDEVENT.date);
    out << ENDEVENT;
}

void IO::CalendarParser::splitCombinedEvents(pipe<IO::RawEvent> &in, pipe<IO::RawEvent> &out) const
{
    RawEvent event;
    do {
        in >> event;
        QStringList names = event.name.split("//", QString::SkipEmptyParts);
        for(auto i : names)
        {
            RawEvent splitedEvent = event;
            splitedEvent.name = i;
            out << splitedEvent;
        }
    } while(event.date > ENDEVENT.date);
}

void IO::CalendarParser::filterEmptyEvents(pipe<IO::RawEvent> &in, pipe<IO::RawEvent> &out) const
{
    RawEvent event;
    do {
        in >> event;
        if(!event.name.isEmpty()) {
            out << event;
        }
    } while (event.date > ENDEVENT.date);
}

void IO::CalendarParser::filterForNames(pipe<IO::RawEvent> &in, QVector<QRegularExpression> names, pipe<IO::RawEvent> &filterout) const
{
    RawEvent event;
    do {
        in >> event;
        if(isValid(names, event.name))
        {
            filterout << event;
        }
    } while (event.date > ENDEVENT.date);
    filterout << ENDEVENT;
}

void IO::CalendarParser::setEventType(pipe<RawEvent> &in, SqlTableNames::DivisionT division, pipe<RawEvent> &out) const
{
    RawEvent event;
    do {
        in >> event;
        event.eventType = division;
        out << event;
    } while (event.date > ENDEVENT.date);
}

void IO::CalendarParser::setEventTime(pipe<IO::RawEvent> &in, QVector<IO::EventTime> time, pipe<IO::RawEvent> &out) const
{
    RawEvent event;
    do {
        in >> event;
        for(auto j : time) {
            for(auto i : j.regex) {
                if(i.match(event.name).hasMatch())
                {
                    event.startTime = j.starttime;
                    event.endTime = j.endtime;
                    break;
                }
            }
        }
        out << event;
    } while (event.date > ENDEVENT.date);
}

bool IO::CalendarParser::isValid(const QVector<QRegularExpression> &regex, const QString &name) const
{
    for(auto r : regex) {
        if(r.match(name).hasMatch()) {
            return true;
        }
    }
    return false;
}
