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

//------------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------------
//
JahreskalenderParser::JahreskalenderParser(QObject *parent)
: QObject(parent)
, m_currentDivision(SqlTableNames::eZug)
{
}

//------------------------------------------------------------------------------------------------
//
JahreskalenderParser::~JahreskalenderParser()
{

}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseEvents(QXlsx::Document const& xlsx, QVector<QRegularExpression> names, SqlTableNames::DivisionT eventType)
{

    IO::CalendarParser parser(xlsx, times);
    pipe<IO::RawEvent> zugevents;
    pipe<IO::RawEvent> events;
    parser.pumpAllEvents(names, zugevents);
    parser.setEventType(zugevents, eventType, events);
    convert(events);
}

void JahreskalenderParser::importCalendar(const QUrl& path)
{

    QXlsx::Document xlsx(path.toLocalFile());

    parseEvents(xlsx, exerciseZug1, SqlTableNames::eZug);
    parseEvents(xlsx, exerciseZug2, SqlTableNames::eZug);
    parseEvents(xlsx, exerciseZug3, SqlTableNames::eZug);
    parseEvents(xlsx, exerciseKommandoZug, SqlTableNames::eKommandoZug);
    parseEvents(xlsx, exerciseMaschA, SqlTableNames::eMaschinistenHRB);
    parseEvents(xlsx, exerciseMaschB, SqlTableNames::eMaschinistenHRB);
    parseEvents(xlsx, exerciseMaschC, SqlTableNames::eMaschinistenHRB);
    parseEvents(xlsx, exerciseAsA, SqlTableNames::eAtemschutz);
    parseEvents(xlsx, exerciseASB, SqlTableNames::eAtemschutz);
    parseEvents(xlsx, exerciseAsC, SqlTableNames::eAtemschutz);
    parseEvents(xlsx, exerciseAbsturz, SqlTableNames::eAbsturzsicherung);
    parseEvents(xlsx, exercisePiketzug, SqlTableNames::ePikettzug);
    parseEvents(xlsx, exerciseKader, SqlTableNames::eKader);
    parseEvents(xlsx, exerciseUof, SqlTableNames::eUof);
    parseEvents(xlsx, exerciseOff, SqlTableNames::eOff);
    parseEvents(xlsx, exerciseZugfuehrer, SqlTableNames::eZugfuehrer);
    parseEvents(xlsx, exerciseSpezialisten, SqlTableNames::eSpezialisten);
    parseEvents(xlsx, sonstiges, SqlTableNames::eSonstiges);

    emit parsed();
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
            generateDrillTable(name);
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
void JahreskalenderParser::generateDrillTable(const QString &tablename)
{
    QSqlQuery query;
    if(tablename.startsWith(SqlTableNames::ZUG, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::eZug;
        QString queryStr(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::ZUG));
        if (!query.exec(queryStr))
        {
            qDebug() << query.lastError();
        }
    }
    else if(tablename.contains(SqlTableNames::MASCHINISTEN, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::eMaschinistenHRB;
        query.exec(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::MASCHINISTEN));
    }
    else if(tablename.contains(SqlTableNames::ATEMSCHUTZ, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::eAtemschutz;
        query.exec(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::ATEMSCHUTZ));
    }
    else if(tablename.contains(SqlTableNames::KOMMANDOZUG, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::eKommandoZug;
        query.exec(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::KOMMANDOZUG));
    }
    else if(tablename.contains(SqlTableNames::PIKETTZUG, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::ePikettzug;
        query.exec(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::PIKETTZUG));
    }
    else if(tablename.contains(SqlTableNames::ABSTURZ, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::eAbsturzsicherung;
        query.exec(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::ABSTURZ));
    }
    else if(tablename.contains(SqlTableNames::KADER, Qt::CaseInsensitive))
    {
        m_currentDivision = SqlTableNames::eKader;
        query.exec(QString::fromLatin1("create table %1 (number INT, category TEXT, teacher TEXT, description TEXT)").arg(SqlTableNames::KADER));
    }
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
    if(!m_tableNames.m_tableNames[m_currentDivision].isEmpty())
    {

        QString queryString(QString::fromLatin1("insert into %1 values('%2', '%3', '%4', '%5')").arg(m_tableNames.m_tableNames[m_currentDivision], QString::number(number),
                                                                                                     category, teacher,description));
        if (!query.exec(queryString))
        {
            qDebug() << query.lastError();
        }
    }
}
