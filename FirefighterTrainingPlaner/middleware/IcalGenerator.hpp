#ifndef ICALGENERATOR_HPP
#define ICALGENERATOR_HPP

#include <QObject>
#include <QString>
#include <QUrl>
#include <QList>
#include <QTextStream>
#include "event.h"
#include "SqlTableNames.hpp"
#include "uebungskartegenerator.hpp"
#include "pipe.hpp"

class IcalGenerator : public QObject
{
    Q_OBJECT
public:
    explicit IcalGenerator(QObject *parent = nullptr);
    ~IcalGenerator();

    Q_INVOKABLE void generateCalendars(const QUrl& path);


private:

    void generateCalendar(const QString& filePath, const QString &filename, const QVector<QRegularExpression> &regex, const QList<Event *> events);
    void writeCalendar(QString fileName, const QList<Event *> &event);
    void writeHeader(QTextStream& stream);
    void writeEvent(QTextStream& stream, const QList<Event *> &event);
    void writeEvent(QTextStream& stream, const Event &event);
    void writeFooter(QTextStream& stream);


    void convert(QList<Event*>const& events, pipe<Event *> &out) const;

    EventDataBase m_database;
    UebungsKarteGenerator m_ubungskarte;

    const static QString ENDING;

    // Header and Footer
    const static QString STARTCALENDAR;
    const static QString PRODID;
    const static QString ICALVERSION;
    const static QString TIMEZONE;
    const static QString ENDCALENDAR;

    // Event
    const static QString STARTEVENT;
    const static QString ENDEVENT;
    const static QString CREATED;
    const static QString CLASS;
    const static QString ENDDATETIME;
    const static QString STARTDATETIME;
    const static QString ENDONLYDATE;
    const static QString STARTONLYDATE;
    const static QString LASTMODIFIED;
    const static QString PRIORITY;
    const static QString SEQUENCE;
    const static QString TIMESTAMP;
    const static QString SUMMARY;
    const static QString LOCATION;
    const static QString TRANSPARENT;
    const static QString UID;
    const static QString DESCRIPTION;

    void convert(pipe<Event *> &in, QList<Event *> &events) const;
    QString generateFileName(const QString& filepath, const QString &filename);
};

#endif // ICALGENERATOR_HPP
