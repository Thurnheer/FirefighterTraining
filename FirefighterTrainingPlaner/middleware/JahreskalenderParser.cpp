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

    emit parsed();
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseEvents(QXlsx::Document const& xlsx, QVector<QRegularExpression> names)
{

    IO::CalendarParser parser(xlsx, times);
    pipe<IO::RawEvent> events;
    parser.pumpAllEvents(names, events);
    convert(events);
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
