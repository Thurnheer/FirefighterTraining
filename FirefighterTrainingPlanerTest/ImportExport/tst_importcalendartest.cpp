#include "tst_importcalendartest.hpp"
#include "autotest.hpp"
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "calendarparser.hpp"
#include <QVariant>

ImportCalendarTest::ImportCalendarTest()
{

}

void ImportCalendarTest::getDate__1_1_Neujahrsapero__cellNeujahrsapero() const
{
    const std::string EVENT("Neujahrsapéro");
    QXlsx::Document testDoc;
    testDoc.write("A2", "Januar");
    testDoc.write("A3", "1");
    testDoc.write("B3", "Di");
    testDoc.write("C3", QVariant(EVENT.c_str()));

    IO::CalendarParser parser(testDoc);

    QDate date(2019, 1, 1);
    std::vector<QXlsx::Cell const*> const RESULT = parser.cellsFromDate(date);
    QCOMPARE(RESULT.size(), 1);
    QCOMPARE(RESULT.at(0)->value().toString().toStdString(), EVENT);

}

void ImportCalendarTest::getYear_Jahreskalender2019FWBAH_2019() const
{
    QXlsx::Document testDoc;
    testDoc.write("A1", "Jahreskalender 2019 FW B-A-H");

    IO::CalendarParser parser(testDoc);

    QCOMPARE(parser.getYear(), 2019);
}

void ImportCalendarTest::getDate_FileJahresKalender2019_Zug1_1() const
{
    QXlsx::Document t(QString(AutoTest::inputPath() + "Jahreskalender 2019.xlsx"));

    IO::CalendarParser p(t);
    const int year = p.getYear();
    QCOMPARE(2019, year);
    QDate date(year, 1, 28);
    std::vector<QXlsx::Cell const*> const Result = p.cellsFromDate(date);
    QXlsx::Format f = Result[0]->format();
    std::string v(Result.at(0)->value().toString().toStdString());
    std::string vv(Result.at(1)->value().toString().toStdString());

    QCOMPARE(v, "Zug 1/1");
    QCOMPARE(vv, "Ferien");
}

void ImportCalendarTest::getDate_FileJahresKalender2019_EmptyConcatenatedCell() const
{
    QXlsx::Document t(QString(AutoTest::inputPath() + "Jahreskalender 2019.xlsx"));

    IO::CalendarParser p(t);
    const int year = p.getYear();
    QCOMPARE(2019, year);
    QDate date(year, 1, 29);
    std::vector<QXlsx::Cell const*> const Result = p.cellsFromDate(date);
    std::string v(Result.at(0)->value().toString().toStdString());
    std::string vv(Result.at(1)->value().toString().toStdString());

    QVERIFY(v.empty());
    QVERIFY(vv.empty());
}



DECLARE_TEST(ImportCalendarTest)
