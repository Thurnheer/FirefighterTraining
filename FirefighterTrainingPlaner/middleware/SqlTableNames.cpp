#include "SqlTableNames.hpp"

#include "event.h"

#include <QSqlQuery>
#include <QVariant>


//------------------------------------------------------------------------------------------------
//
QList<Event*> EventDataBase::getAllEvents()
{
    QList<Event*> events;
    query(events, QString::fromLatin1("SELECT * FROM Event LEFT JOIN Drill ON (Event.category = Drill.category AND Event.uebungsnr = Drill.uebungsnr) ORDER by startDate"));

    return events;
}

//------------------------------------------------------------------------------------------------
//
void EventDataBase::query(QList<Event*>& events, const QString &queryString)
{

    QSqlQuery query(queryString);
    if (!query.exec())
        qFatal("Query failed");
//   qDebug() << query.executedQuery();

    while (query.next()) {
        Event *event = new Event();
        event->setName(query.value("name").toString());
        event->setCategory(query.value("category").toInt());
        event->setDrillNumber(query.value("uebungsnr").toInt());
        event->setUuid(query.value("uuid").toString());
        event->setDescription(query.value("description").toString());

        QDateTime startDate;
        startDate.setDate(query.value("startDate").toDate());
        startDate.setTime(QTime(0, 0).addSecs(query.value("startTime").toInt()));
        event->setStartDate(startDate);

        QDateTime endDate;
        endDate.setDate(query.value("endDate").toDate());
        endDate.setTime(QTime(0, 0).addSecs(query.value("endTime").toInt()));
        event->setEndDate(endDate);

        events.append(event);
    }
}

//------------------------------------------------------------------------------------------------
//
void EventDataBase::getEventDescription(Event &event)
{
    QSqlQuery query;
    int index = event.name().lastIndexOf(QRegExp("\\d"));
    if(index > 0)
    {
/*        QString number = event.name().at(index);
        QString tablename = m_tableNames.m_tableNames[(SqlTableNames::DivisionT)event.drillNumber()];
        if(!tablename.isEmpty())
        {
            QString queryStr(QString::fromLatin1("SELECT * FROM %1 WHERE number == %2").arg(tablename, number));
            if(query.exec(queryStr))
            {
                query.next();
                event.setDescription(query.value("description").toString());
            }
        }*/
    }
}

