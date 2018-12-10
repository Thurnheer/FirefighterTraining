#include "IcalGenerator.hpp"
#include "QFile"
#include "QDateTime"
#include "QDate"
#include "QSqlQuery"
#include "QDebug"

const QString IcalGenerator::ENDING(".ics");

const QString IcalGenerator::STARTCALENDAR("BEGIN:VCALENDAR");
const QString IcalGenerator::PRODID("PRODID:-//Christoph Thurnheer//Ihre Feuerwehr 1.0//EN");
const QString IcalGenerator::ICALVERSION("VERSION:2.0");
const QString IcalGenerator::TIMEZONE("BEGIN:VTIMEZONE\nTZID:W. Europe Standard Time\nBEGIN:STANDARD\nDTSTART:16011028T030000\nRRULE:FREQ=YEARLY;BYDAY=-1SU;BYMONTH=10\nTZOFFSETFROM:+0200\nTZOFFSETTO:+0100\nEND:STANDARD\nBEGIN:DAYLIGHT\nDTSTART:16010325T020000\nRRULE:FREQ=YEARLY;BYDAY=-1SU;BYMONTH=3\nTZOFFSETFROM:+0100\nTZOFFSETTO:+0200\nEND:DAYLIGHT\nEND:VTIMEZONE");
const QString IcalGenerator::ENDCALENDAR("END:VCALENDAR");
const QString IcalGenerator::STARTEVENT("BEGIN:VEVENT");
const QString IcalGenerator::ENDEVENT("END:VEVENT");
const QString IcalGenerator::CREATED("CREATED:");
const QString IcalGenerator::CLASS("CLASS:");
const QString IcalGenerator::ENDDATETIME("DTEND;TZID=\"W. Europe Standard Time\":");
const QString IcalGenerator::STARTDATETIME("DTSTART;TZID=\"W. Europe Standard Time\":");
const QString IcalGenerator::ENDONLYDATE("DTEND;VALUE=DATE:");
const QString IcalGenerator::STARTONLYDATE("DTSTART;VALUE=DATE:");
const QString IcalGenerator::LASTMODIFIED("LAST-MODIFIED:");
const QString IcalGenerator::PRIORITY("PRIORITY:");
const QString IcalGenerator::SEQUENCE("SEQUENCE:");
const QString IcalGenerator::TIMESTAMP("DTSTAMP:");
const QString IcalGenerator::SUMMARY("SUMMARY;LANGUAGE=de_ch:");
const QString IcalGenerator::LOCATION("LOCATION:");
const QString IcalGenerator::TRANSPARENT("TRANSP:OPAQUE");
const QString IcalGenerator::UID("UID:");
const QString IcalGenerator::DESCRIPTION("DESCRIPTION:");

//------------------------------------------------------------------------------------------------
//
IcalGenerator::IcalGenerator(QObject *parent) : QObject(parent)
{

}

//------------------------------------------------------------------------------------------------
//
IcalGenerator::~IcalGenerator()
{

}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::generateCalendar(const QUrl &path)
{
    QString ending(path.toLocalFile());
    if(ending.isEmpty())
    {
        return;
    }
    if(ending.endsWith(ENDING, Qt::CaseInsensitive))
    {
        ending.replace(ending.length()-4, 4, ENDING);
    }
    else
    {
        ending += ENDING;
    }
    QList<Event*> events = m_database.getAllEvents();
    // write all events to one calendar
    QString allEvents(ending);
    allEvents.insert(ending.lastIndexOf("."), "_alleTermine");
    writeCalendar(allEvents, events);
    qDeleteAll(events);

    generateAllCalendars(ending);

}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::generateAllCalendars(const QString& fileName)
{
    generateAllCalendars(fileName, SqlTableNames::eZug, " 1", "Hauptübung");
    generateAllCalendars(fileName, SqlTableNames::eZug, " 2", "Hauptübung");
    generateAllCalendars(fileName, SqlTableNames::eZug, " 3", "Hauptübung");
    generateAllCalendars(fileName, SqlTableNames::eMaschinistenHRB, " A", "Fahrertag");
    generateAllCalendars(fileName, SqlTableNames::eMaschinistenHRB, " B", "Fahrertag");
    generateAllCalendars(fileName, SqlTableNames::eMaschinistenHRB, " C", "Fahrertag");
    generateAllCalendars(fileName, SqlTableNames::eAtemschutz, " A", "Atemschutztag");
    generateAllCalendars(fileName, SqlTableNames::eAtemschutz, " B", "Atemschutztag");
    generateAllCalendars(fileName, SqlTableNames::eAtemschutz, " C", "Atemschutztag");
    generateAllCalendars(fileName, SqlTableNames::eKommandoZug, "", "Hauptübung");
    generateAllCalendars(fileName, SqlTableNames::ePikettzug);
    generateAllCalendars(fileName, SqlTableNames::eAbsturzsicherung);
    generateAllCalendars(fileName, SqlTableNames::eKader);
    generateAllCalendars(fileName, SqlTableNames::eUof);
    generateAllCalendars(fileName, SqlTableNames::eOff);
    generateAllCalendars(fileName, SqlTableNames::eZugfuehrer);
    generateAllCalendars(fileName, SqlTableNames::eSpezialisten);

    m_ubungskarte.generateUebungskarte(fileName);
}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::generateAllCalendars(QString fileName, SqlTableNames::DivisionT division, const QString &index, const QString &additionSearchTag)
{
    QList<Event*> event = m_database.getEvents(division, index, additionSearchTag);
    fileName.insert(fileName.lastIndexOf("."), "_" + m_database.getTableName(division) + index);
    writeCalendar(fileName, event);
    qDeleteAll(event);
}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::writeCalendar(QString fileName, const QList<Event*>& event)
{
    QFile calendar(fileName);
    calendar.open(QFile::WriteOnly | QIODevice::Text);
    QTextStream out(&calendar);
    writeHeader(out);
    writeEvent(out, event);
    writeFooter(out);
    out.flush();
    calendar.flush();
    calendar.close();
}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::writeHeader(QTextStream& stream)
{
    stream << STARTCALENDAR << endl;
    stream << PRODID << endl;
    stream << ICALVERSION << endl;
    stream << TIMEZONE << endl;
}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::writeEvent(QTextStream &stream, const QList<Event*> &event)
{
    QList<Event*>::const_iterator it = event.begin();
    for(;it != event.end();++it)
    {
        writeEvent(stream, **it);
    }
}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::writeEvent(QTextStream &stream, const Event& event)
{
    QDate currentDate = QDate::currentDate();
    QDateTime currentTime = QDateTime::currentDateTime();
    stream << STARTEVENT << endl;
    stream << TIMESTAMP << currentDate.toString("yyyyMMdd") << "T";
    stream << currentTime.time().toString("hhmmss") << "Z" << endl;
    stream << CREATED << currentDate.toString("yyyyMMdd") << "T";
    stream << currentTime.time().toString("hhmmss") << "Z" << endl;
    stream << UID << event.uuid() << endl;
    stream << LASTMODIFIED << currentDate.toString("yyyyMMdd") << "T";
    stream << currentTime.time().toString("hhmmss") << "Z" << endl;
    stream << SUMMARY << event.name() << endl;
    if(!event.location().isEmpty())
    {
        stream << LOCATION << event.location() << endl;
    }
    if(!event.description().isEmpty())
    {
        stream << DESCRIPTION << event.description() << endl;
    }
    stream << PRIORITY << "5" << endl;
    if(event.startDate().time() == QTime(0,0,1)
       && event.endDate().time() == QTime(23, 59, 59))
    {
        stream << STARTONLYDATE << event.startDate().toString("yyyyMMdd") << endl;
        stream << ENDONLYDATE << event.endDate().addDays(1).toString("yyyyMMdd") << endl;
    }
    else
    {
        stream << STARTDATETIME << event.startDate().toString("yyyyMMdd") << "T" << event.startDate().time().toString("hhmmss") << endl;
        stream << ENDDATETIME << event.endDate().toString("yyyyMMdd") << "T" << event.endDate().time().toString("hhmmss") << endl;
    }
    stream << TRANSPARENT << endl;
    stream << ENDEVENT << endl;
}

//------------------------------------------------------------------------------------------------
//
void IcalGenerator::writeFooter(QTextStream &stream)
{
    stream << ENDCALENDAR;
}

