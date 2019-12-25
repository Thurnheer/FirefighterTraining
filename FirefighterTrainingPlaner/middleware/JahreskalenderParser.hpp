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
#include "../ImportExport/calendarlayout.hpp"

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

    // indicator words
    void parseEvents(const QXlsx::Document &xlsx, QVector<QRegularExpression> names);
    void parseDrills(QXlsx::Document &xlsx);
};

#endif // JAHRESKALENDERPARSER_HPP
