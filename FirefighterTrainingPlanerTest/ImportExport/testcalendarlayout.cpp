#include "testcalendarlayout.hpp"
#include "calendarlayout.hpp"
#include "autotest.hpp"

void TestCalendarLayout::testGetMonthRange_seventhJanuary_RangeSevenThree() const
{
    const IO::Range EXPECTED{ 9, 3, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(7, 1);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{ 9, 3, 2} == IO::CalendarLayout::getMonthRange(7, 1), "The cell index is not correct");
}

void TestCalendarLayout::getMonthRange_18March_Range20_11() const
{
    const IO::Range EXPECTED{ 20, 11, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(18, 3);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{20, 11, 2} == IO::CalendarLayout::getMonthRange(18, 3), "The cell index is not correct");
}

void TestCalendarLayout::getMonthRange_15July_Range50_3() const
{
    const IO::Range EXPECTED{ 50, 3, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(15, 7);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{50, 3, 2} == IO::CalendarLayout::getMonthRange(15, 7), "The cell index is not correct");
}

void TestCalendarLayout::getMonthRange_31December_Range66_23() const
{
    const IO::Range EXPECTED{ 66, 23, 2};
    const IO::Range result = IO::CalendarLayout::getMonthRange(31, 12);
    QVERIFY(EXPECTED == result);
    static_assert(IO::Range{66, 23, 2} == IO::CalendarLayout::getMonthRange(31, 12), "The cell index is not correct");
}

DECLARE_TEST(TestCalendarLayout)
