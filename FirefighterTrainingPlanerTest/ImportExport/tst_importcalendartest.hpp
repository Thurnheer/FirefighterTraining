#ifndef TST_IMPORTCALENDARTEST_HPP
#define TST_IMPORTCALENDARTEST_HPP

#include "QtTest"
#include "QCoreApplication"

class TestCalendarLayout : public QObject
{
    Q_OBJECT

private slots:
    void testGetMonthRange_seventhJanuary_RangeSevenThree() const;
    void getMonthRange_18March_Range20_11() const;
    void getMonthRange_15July_Range50_3() const;
    void getMonthRange_31December_Range66_23() const;

};

class ImportCalendarTest : public QObject
{
    Q_OBJECT
public:
    ImportCalendarTest();

private slots:
    void getYear_Jahreskalender2019FWBAH_2019() const;
    void getDate__1_1_Neujahrsapero__cellNeujahrsapero() const;
    void getDate_FileJahresKalender2019_Zug1_1() const;
    void getDate_FileJahresKalender2019_EmptyConcatenatedCell() const;
};

#endif // TST_IMPORTCALENDARTEST_HPP
