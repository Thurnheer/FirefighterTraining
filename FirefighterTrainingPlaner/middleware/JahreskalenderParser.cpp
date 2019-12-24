#include "JahreskalenderParser.hpp"
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QUuid>
#include "xlsxformat.h"
#include "xlsxcolor_p.h"
#include "../ImportExport/calendarparser.hpp"
#include "pipe.hpp"
#include "QStringList"
#include "QVector"
#include "converter.hpp"
#include "Names.hpp"
#include <utility>
#include "ImportExport/calendarlayout.hpp"
#include "ImportExport/drillparser.hpp"

static const std::pair<QVector<QRegularExpression>, IO::Category> catZug {{zug1, zug2, zug3, hauptuebung, exerciseAll}, IO::Category::zug};
static const std::pair<QVector<QRegularExpression>, IO::Category> catMasch {{maschA, maschB, maschC, fahrertag, parkdienst}, IO::Category::masch};
static const std::pair<QVector<QRegularExpression>, IO::Category> catAs {{atemschutzA, atemschutzB, atemschutzC, brandhaus}, IO::Category::as};
static const std::pair<QVector<QRegularExpression>, IO::Category> catKommando {exerciseKommandoZug, IO::Category::kommando};
static const std::pair<QVector<QRegularExpression>, IO::Category> catPiket {exercisePiketzug, IO::Category::piket};
static const std::pair<QVector<QRegularExpression>, IO::Category> catAbsturz {exerciseAbsturz, IO::Category::absturz};

//------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------
//
JahreskalenderParser::JahreskalenderParser(QObject *parent)
: QObject(parent)
{
}

//------------------------------------------------------------------------------------------------
//
JahreskalenderParser::~JahreskalenderParser()
{

}

void JahreskalenderParser::importCalendar(const QUrl& path)
{

    QXlsx::Document xlsx(path.toLocalFile());

    parseEvents(xlsx, allEvents);
    parseDrills(xlsx);

    emit parsed();
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseEvents(QXlsx::Document const& xlsx, QVector<QRegularExpression> names)
{

    IO::CalendarParser parser(xlsx, times);
    pipe<IO::RawEvent> events;
    pipe<IO::RawEvent> e1;
    pipe<IO::RawEvent> e2;
    pipe<IO::RawEvent> e3;
    pipe<IO::RawEvent> e4;
    pipe<IO::RawEvent> e5;
    pipe<IO::RawEvent> e6;
    parser.pumpAllEvents(names, e1);
    parser.setCategory(e1, catZug, e2);
    parser.setCategory(e2, catMasch, e3);
    parser.setCategory(e3, catAs, e4);
    parser.setCategory(e4, catKommando, e5);
    parser.setCategory(e5, catPiket, e6);
    parser.setCategory(e6, catAbsturz, events);
    convert(events);
}

void JahreskalenderParser::parseDrills(QXlsx::Document& xlsx) {
    IO::DrillParser parser(xlsx);
    pipe<RawDrill> drills;
    parser.pumpAllDrills(drills);
    drills << RawDrill();
    save(drills);
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::importDrills(const QXlsx::Document &xlsx)
{
    for(int j = 3; j < 70; ++j)
    {
        QString name = xlsx.read(j, 1).toString();
        QString category = xlsx.read(j, 2).toString();
        QString description = xlsx.read(j, 3).toString();
        if(!name.isEmpty() && (category.isEmpty() || category.contains(QRegExp("( +)"))))
        {
           // generateDrillTable(name);
        }
        else if(!name.isEmpty() && !category.isEmpty())
        {
            QStringList::iterator it;
            QStringList numbers = getCompositedDrills(name);
            for(it = numbers.begin(); it != numbers.end(); ++it)
            {
                bool ok = false;
                int number = it->toInt(&ok);
                if(ok)
                {
                    parseDrill(number, category, description);
                }
            }
        }
    }
}

//------------------------------------------------------------------------------------------------
//
QStringList JahreskalenderParser::getCompositedDrills(const QString &name)
{
    return name.split("+", QString::SkipEmptyParts);

}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseDrill(int number, const QString& category, const QString& drillDescription)
{
    QSqlQuery query;
    QString teacher;
    QString description = drillDescription;
    //teacher = getDrillTeacher(description);
    if(teacher.isEmpty())
    {
        teacher = " ";
    }
/*    if(!m_tableNames.m_tableNames[m_currentDivision].isEmpty())
    {

        QString queryString(QString::fromLatin1("insert into %1 values('%2', '%3', '%4', '%5')").arg(m_tableNames.m_tableNames[m_currentDivision], QString::number(number),
                                                                                                     category, teacher,description));
        if (!query.exec(queryString))
        {
            qDebug() << query.lastError();
        }
    }*/
}
