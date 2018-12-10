#include "SqlTableNames.hpp"

#include "event.h"

#include <QSqlQuery>
#include <QVariant>


const QString SqlTableNames::ZUG("Zug");
const QString SqlTableNames::MASCHINISTEN("Maschinisten");
const QString SqlTableNames::ATEMSCHUTZ("Atemschutz");
const QString SqlTableNames::KOMMANDOZUG("Kommandozug");
const QString SqlTableNames::PIKETTZUG("Pikettzug");
const QString SqlTableNames::ABSTURZ("Abst");
const QString SqlTableNames::KADER("Kader");
const QString SqlTableNames::UOF("Unteroffiziere");
const QString SqlTableNames::OFF("Offiziere");
const QString SqlTableNames::ZUGFUEHRER("Zugführer");
const QString SqlTableNames::SPEZIALISTEN("Spezialisten");

SqlTableNames::SqlTableNames()
{
    m_tableNames[eZug] = ZUG;
    m_tableNames[eMaschinistenHRB] = MASCHINISTEN;
    m_tableNames[eAtemschutz] = ATEMSCHUTZ;
    m_tableNames[eKommandoZug] = KOMMANDOZUG;
    m_tableNames[ePikettzug] = PIKETTZUG;
    m_tableNames[eAbsturzsicherung] = ABSTURZ;
    m_tableNames[eKader] = KADER;
    m_tableNames[eUof] = UOF;
    m_tableNames[eOff] = OFF;
    m_tableNames[eZugfuehrer] = ZUGFUEHRER;
    m_tableNames[eSpezialisten] = SPEZIALISTEN;
}

SqlTableNames::~SqlTableNames()
{

}






//------------------------------------------------------------------------------------------------
//
QList<Event*> EventDataBase::getAllEvents()
{
    QList<Event*> events;
    query(events, QString::fromLatin1("SELECT * FROM Event ORDER by startDate"));

    return events;
}

//------------------------------------------------------------------------------------------------
//
QList<Event*> EventDataBase::getEvents(SqlTableNames::DivisionT division, QString index, const QString &additionSearchTag)
{
    QList<Event*> events;
    QString queryStr("SELECT * FROM Event WHERE einteilung = ");
    queryStr +=  QString::number(division);
    if(!index.isEmpty())
    {
        queryStr += " AND einteilungsindex = '";
        queryStr += index.trimmed() + "'";
    }
    if(!additionSearchTag.isEmpty())
    {
        QString ast(additionSearchTag);
        ast.insert(0,"\'%");
        ast.append("%\'");
        queryStr += " OR name LIKE ";
        queryStr += ast;
    }
    query(events, queryStr);
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
        event->setUuid(query.value("uuid").toString());
        event->setEventType(query.value("einteilung").toInt());
        getEventDescription(*event);

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
        QString number = event.name().at(index);
        QString tablename = m_tableNames.m_tableNames[(SqlTableNames::DivisionT)event.eventType()];
        if(!tablename.isEmpty())
        {
            QString queryStr(QString::fromLatin1("SELECT * FROM %1 WHERE number == %2").arg(tablename, number));
            if(query.exec(queryStr))
            {
                query.next();
                event.setDescription(query.value("description").toString());
            }
        }
    }
}

//------------------------------------------------------------------------------------------------
//
QString EventDataBase::getTableName(SqlTableNames::DivisionT division)
{
    return m_tableNames.m_tableNames[division];
}

