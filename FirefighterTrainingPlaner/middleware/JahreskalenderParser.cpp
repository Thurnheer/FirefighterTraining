#include "JahreskalenderParser.hpp"
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QUuid>
#include "xlsxformat.h"
#include "xlsxcolor_p.h"

//------------------------------------------------------------------------------------------------
//
const QString JahreskalenderParser::TAG("tag");
const QString JahreskalenderParser::BRANDHAUS("brandhaus");

//------------------------------------------------------------------------------------------------
//
JahreskalenderParser::JahreskalenderParser(QObject *parent)
: QObject(parent)
, m_currentDivision(SqlTableNames::eZug)
{
    m_indicatorWords.push_back(TAG);
    m_indicatorWords.push_back(BRANDHAUS);
}

//------------------------------------------------------------------------------------------------
//
JahreskalenderParser::~JahreskalenderParser()
{

}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::importCalendar(const QUrl& path)
{

    QXlsx::Document xlsx(path.toLocalFile());
    xlsx.selectSheet("Themen");
    importDrills(xlsx);
    importCourse(xlsx);
    xlsx.selectSheet("Farbcode");
    getEventColors(xlsx);
    xlsx.selectSheet("Kalender 2019");
    importEvents(xlsx);
    emit parsed();
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::getEventColors(const QXlsx::Document &xlsx)
{
    int row = 2;
    int col = 1;
    QString name;
    do
    {
        name = xlsx.read(row, col).toString();
        QXlsx::Cell* cell = xlsx.cellAt(row, col+1);
        if(cell && cell->format().hasFillData())
        {
            m_colorIndexMap.push_back(cell->format().fillIndex());
        }
        ++row;
    }
    while(!name.isEmpty());
}

//------------------------------------------------------------------------------------------------
//
bool JahreskalenderParser::hasColor(int color)
{
    for(size_t i = 0; i < m_colorIndexMap.size(); ++i)
    {
        if(m_colorIndexMap[i] == color)
            return true;
    }
    return false;
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::importEvents(const QXlsx::Document& xlsx)
{
    for(int ii = 0; ii < 12; ++ii)
    {
        int i = ii % 6;
        int k = 0;
        if(ii >= 6)
        {
            k = 33;
        }
        for(int j = 3+k; j < 34+k; ++j)
        {
            QString name = xlsx.read(j, i*4+3).toString();
            if(!name.isEmpty())
            {
                if(xlsx.cellAt(j, i*4+3))
                {
                    QXlsx::Format format = xlsx.cellAt(j, i*4+3)->format();
                    format.formatKey();
                    if(format.hasFillData() && hasColor(format.fillIndex()))
                    {
                        parseEvent(name, QDate(2019,ii+1, j-k-2));
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseEvent(const QString &name, const QDate &inDate)
{
    QStringList events = name.split("//", QString::SkipEmptyParts);
    QStringList::iterator it;
    for(it = events.begin();it != events.end(); ++it)
    {
        if((*it).contains("A/B/C", Qt::CaseInsensitive))
        {
            (*it).replace((*it).indexOf("A/B/C"),5,"a-c");
        }
        if((*it).contains("MD alle", Qt::CaseInsensitive) || (*it).contains("a-c", Qt::CaseInsensitive) || (*it).contains("MD Parkdienst", Qt::CaseInsensitive))
        {
            int start = (*it).indexOf(" ");
            int len = (*it).length() - start;
            if(!(*it).contains("MD Parkdienst", Qt::CaseInsensitive))
            {
                len   = (*it).lastIndexOf(QRegExp("(\\d+)")) - start;
            }
            else
            {
                (*it) += "3";
            }
            (*it).replace(start, len, " A/");
            generateEvent(*it, inDate);
            (*it).replace((*it).lastIndexOf("A"), 1, "B");
            generateEvent(*it, inDate);
            (*it).replace((*it).lastIndexOf("B"), 1, "C");
            generateEvent(*it, inDate);
        }
        else if((*it).contains("alle", Qt::CaseInsensitive))
        {
            int start = 0;
            int len   = (*it).lastIndexOf(QRegExp("(\\d+)")) - start;
            (*it).replace(start, len, "Zug 1/");
            generateEvent(*it, inDate);
            (*it).replace((*it).lastIndexOf("Zug 1"), 5, "Zug 2");
            generateEvent(*it, inDate);
            (*it).replace((*it).lastIndexOf("Zug 2"), 5, "Zug 3");
            generateEvent(*it, inDate);
            (*it).replace((*it).lastIndexOf("Zug 3/"), 6, "K-Zug ");
            generateEvent(*it, inDate);
        }
        else
        {
            generateEvent(*it, inDate);
        }
    }
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::generateEvent(const QString &name, const QDate &inDate)
{
    Event event;
    event.setName(name);
    event.setUuid(QUuid::createUuid().toString());
    setEventType(event);
    setEventStartEndTime(event, inDate);
    event.save();
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::setEventType(Event &event)
{
    if(event.name().startsWith("Zug") && !event.name().startsWith("Zugsr", Qt::CaseInsensitive) && !event.name().contains("Zugführer", Qt::CaseInsensitive))
    {
        event.setEventType(SqlTableNames::eZug);
    }
    else if(event.name().contains("MD", Qt::CaseSensitive) ||
            event.name().contains("Masch", Qt::CaseSensitive) ||
            event.name().contains("Fahrer", Qt::CaseSensitive))
    {
        event.setEventType(SqlTableNames::eMaschinistenHRB);
    }
    else if(event.name().contains("AS", Qt::CaseSensitive))
    {
        event.setEventType(SqlTableNames::eAtemschutz);
    }
    else if(event.name().contains("K-Zug", Qt::CaseSensitive))
    {
        event.setEventType(SqlTableNames::eKommandoZug);
    }
    else if(event.name().contains("Piket", Qt::CaseSensitive))
    {
        event.setEventType(SqlTableNames::ePikettzug);
    }
    else if(event.name().contains("Abst", Qt::CaseSensitive))
    {
        event.setEventType(SqlTableNames::eAbsturzsicherung);
    }
    else if(event.name().contains("Kader", Qt::CaseSensitive) || event.name().contains("Zugsrapport"))
    {
        event.setEventType(SqlTableNames::eKader);
    }
    else if(event.name().contains("UOF", Qt::CaseInsensitive))
    {
        event.setEventType(SqlTableNames::eUof);
    }
    else if(event.name().contains("Off", Qt::CaseInsensitive) || event.name().contains("was ist neu", Qt::CaseInsensitive))
    {
        event.setEventType(SqlTableNames::eOff);
    }
    else if(event.name().contains("Jahresplanung", Qt::CaseInsensitive) || event.name().contains("Zugführer", Qt::CaseInsensitive))
    {
        event.setEventType(SqlTableNames::eZugfuehrer);
    }
    else if(event.name().contains("Spezialisten", Qt::CaseSensitive))
    {
        event.setEventType(SqlTableNames::eSpezialisten);
    }
    else
    {
        event.setEventType(SqlTableNames::eUnknown);
    }
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::setEventStartEndTime(Event &event, const QDate &dateWithoutTime)
{
    QDateTime date;
    date.setDate(dateWithoutTime);
    QStringList::iterator it;
    QSqlQuery query;
    int index = event.name().lastIndexOf(QRegExp("\\d"));
    QString category;
    if(index > 0)
    {
        QString number = event.name().at(index);
        QString tablename = m_tableNames.m_tableNames[(SqlTableNames::DivisionT)event.eventType()];
        if(!tablename.isEmpty())
        {
            if(query.exec(QString::fromLatin1("SELECT * FROM %1 WHERE number == %2").arg(tablename, number)))
            {
                query.next();
                category = query.value("category").toString();
            }
        }
    }

    for(it = m_indicatorWords.begin(); it != m_indicatorWords.end(); ++it)
    {
        if(category.contains(*it, Qt::CaseInsensitive) || event.name().contains(*it, Qt::CaseInsensitive)
                || dateWithoutTime.dayOfWeek() == 6/*Saturday*/)
        {
            date.setTime(QTime(0, 0, 1));
            event.setStartDate(date);
            date.setTime(QTime(23, 59, 59));
            event.setEndDate(date);
            return;
        }
    }
    if(event.eventType() == m_tableNames.eAtemschutz)
    {
        date.setTime(QTime(19, 15));
        event.setStartDate(date);
        date.setTime(QTime(22, 15));
        event.setEndDate(date);
        return;
    }
    date.setTime(QTime(19, 15));
    event.setStartDate(date);
    date.setTime(QTime(21, 15));
    event.setEndDate(date);
    if(event.name().contains("Hauptübung"))
    {
        date.setTime(QTime(18,00));
        event.setStartDate(date);
        date.setTime(QTime(23,00));
        event.setEndDate(date);
    }
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
QString JahreskalenderParser::getDrillTeacher(QString &toParse)
{
    return "";
}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseDrill(int number, const QString& category, const QString& drillDescription)
{
    QSqlQuery query;
    QString teacher;
    QString description = drillDescription;
    teacher = getDrillTeacher(description);
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

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::importCourse(const QXlsx::Document &xlsx)
{

}

//------------------------------------------------------------------------------------------------
//
void JahreskalenderParser::parseCourse()
{

}
