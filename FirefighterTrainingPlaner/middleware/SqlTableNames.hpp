#ifndef SQLTABLENAMES_HPP
#define SQLTABLENAMES_HPP


#include <QString>
#include <map>

class Event;

class EventDataBase
{
public:
    QList<Event*> getAllEvents();
    QList<Event*> getEvents(QString index, const QString& additionSearchTag);
    void query(QList<Event *> &events, const QString& queryString);
    void getEventDescription(Event &event);

private:

};

#endif // SQLTABLENAMES_HPP
