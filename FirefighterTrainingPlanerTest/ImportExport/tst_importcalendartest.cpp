#include "tst_importcalendartest.hpp"
#include "autotest.hpp"
#include "xlsxdocument.h"
#include "calendarparser.hpp"
#include <QVariant>

void CalendarLayoutTest::getMonthRange_seventhJanuary_RangeSevenThree() const
{
    const IO::Range EXPECTED{ 9, 3, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(7, 1);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{ 9, 3, 2} == IO::CalendarLayout::getMonthRange(7, 1), "The cell index is not correct");
}

void CalendarLayoutTest::getMonthRange_18March_Range20_11() const
{
    const IO::Range EXPECTED{ 20, 11, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(18, 3);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{20, 11, 2} == IO::CalendarLayout::getMonthRange(18, 3), "The cell index is not correct");
}

void CalendarLayoutTest::getMonthRange_15July_Range50_3() const
{
    const IO::Range EXPECTED{ 50, 3, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(15, 7);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{50, 3, 2} == IO::CalendarLayout::getMonthRange(15, 7), "The cell index is not correct");
}

void CalendarLayoutTest::getMonthRange_31December_Range66_23() const
{
    const IO::Range EXPECTED{ 66, 23, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(31, 12);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{66, 23, 2} == IO::CalendarLayout::getMonthRange(31, 12), "The cell index is not correct");
}

DECLARE_TEST(CalendarLayoutTest)

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

    std::vector<QXlsx::Cell*> const RESULT = parser.getDate(1, 1);
    QCOMPARE(2, RESULT.size());
    QCOMPARE(EVENT, RESULT.at(0)->value().toString().toStdString());

}

void ImportCalendarTest::getYear_Jahreskalender2019FWBAH_2019() const
{
    QXlsx::Document testDoc;
    testDoc.write("A1", "Jahreskalender 2019 FW B-A-H");

    IO::CalendarParser parser(testDoc);

    QCOMPARE(2019, parser.getYear());
}



DECLARE_TEST(ImportCalendarTest)
