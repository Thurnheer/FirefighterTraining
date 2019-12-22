#include "tst_importcalendartest.hpp"
#include "autotest.hpp"
#include "xlsxdocument.h"
#include "xlsxcellrange.h"
#include "calendarparser.hpp"
#include <QVariant>
#include "../middleware/Names.hpp"

ImportCalendarTest::ImportCalendarTest()
{

}

void ImportCalendarTest::getYear_Jahreskalender2019FWBAH_2019() const
{
    QXlsx::Document testDoc;
    testDoc.write("A1", "Jahreskalender 2019 FW B-A-H");

    IO::CalendarParser parser(testDoc, times);

    QCOMPARE(parser.getYear(), 2019);
}



DECLARE_TEST(ImportCalendarTest)
