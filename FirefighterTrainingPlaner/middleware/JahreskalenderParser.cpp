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
