#ifndef SQLTABLENAMES_HPP
#define SQLTABLENAMES_HPP


#include <QString>
#include <map>

class SqlTableNames
{
public:
    SqlTableNames();
    ~SqlTableNames();

    enum DivisionT
    {
        eUnknown,
        eZug,
        eMaschinistenHRB,
        eAtemschutz,
        eKommandoZug,
        ePikettzug,
        eAbsturzsicherung,
        eKader,
        eUof,
        eOff,
        eZugfuehrer,
        eSpezialisten
    };


    std::map<DivisionT, QString> m_tableNames;

    static const QString ZUG;
    static const QString MASCHINISTEN;
    static const QString ATEMSCHUTZ;
    static const QString KOMMANDOZUG;
    static const QString PIKETTZUG;
    static const QString ABSTURZ;
    static const QString KADER;
    static const QString UOF;
    static const QString OFF;
    static const QString ZUGFUEHRER;
    static const QString SPEZIALISTEN;

};

class Event;

class EventDataBase
{
public:
    QList<Event*> getAllEvents();
    QList<Event*> getEvents(SqlTableNames::DivisionT division, QString index, const QString& additionSearchTag);
    void query(QList<Event *> &events, const QString& queryString);
    void getEventDescription(Event &event);

    QString getTableName(SqlTableNames::DivisionT division);

private:

    SqlTableNames m_tableNames;

};

#endif // SQLTABLENAMES_HPP
