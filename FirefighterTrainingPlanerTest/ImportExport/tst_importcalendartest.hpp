#ifndef TST_IMPORTCALENDARTEST_HPP
#define TST_IMPORTCALENDARTEST_HPP

#include "QtTest"
#include "QCoreApplication"

class CalendarLayoutTest : public QObject
{
    Q_OBJECT

private slots:
    void getMonthRange_seventhJanuary_RangeSevenThree() const;
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
};

#endif // TST_IMPORTCALENDARTEST_HPP
