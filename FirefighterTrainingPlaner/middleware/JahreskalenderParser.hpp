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

    void importDrills(const QXlsx::Document& xlsx);
    void parseDrill(int number, const QString &category, const QString &drillDescription);
    void generateDrillTable(const QString& tablename);
    QStringList getCompositedDrills(const QString& name);

    SqlTableNames::DivisionT     m_currentDivision;
    SqlTableNames m_tableNames;


    // indicator words
    void parseEvents(const QXlsx::Document &xlsx, QVector<QRegularExpression> names);
};

#endif // JAHRESKALENDERPARSER_HPP
