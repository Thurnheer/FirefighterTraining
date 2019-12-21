#ifndef JAHRESKALENDERPARSER_HPP
#define JAHRESKALENDERPARSER_HPP

#include <QObject>
#include <vector>
#include <map>
#include "event.h"
#include <QUrl>
#include "xlsxdocument.h"
#include "event.h"
#include "SqlTableNames.hpp"

class JahreskalenderParser : public QObject
{
    Q_OBJECT

public:
    JahreskalenderParser(QObject *parent = nullptr);
    virtual ~JahreskalenderParser();

    Q_INVOKABLE void importCalendar(const QUrl &path);

signals:
    void parsed();

private:

    void getEventColors(const QXlsx::Document &xlsx);
    bool hasColor(int color);

    void importEvents(const QXlsx::Document &xlsx);
    void parseEvent(const QString& name, const QDate& inDate);
    void generateEvent(const QString& name, const QDate& date);
    void setEventType(Event& event);
    void setEventStartEndTime(Event& event, const QDate &dateWithoutTime);

    void importDrills(const QXlsx::Document& xlsx);
    void parseDrill(int number, const QString &category, const QString &drillDescription);
    void generateDrillTable(const QString& tablename);
    QStringList getCompositedDrills(const QString& name);
    QString getDrillTeacher(QString& toParse);

    void importCourse(const QXlsx::Document& xlsx);
    void parseCourse();

    std::vector<int> m_colorIndexMap;
    QStringList m_indicatorWords;
    SqlTableNames::DivisionT     m_currentDivision;
    SqlTableNames m_tableNames;


    // indicator words
    static const QString TAG;
    static const QString BRANDHAUS;
    void parseEvents(const QXlsx::Document &xlsx, QVector<QRegularExpression> names, SqlTableNames::DivisionT eventType);
};

#endif // JAHRESKALENDERPARSER_HPP
