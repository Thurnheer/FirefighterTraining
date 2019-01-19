#ifndef TESTCALENDARLAYOUT_HPP
#define TESTCALENDARLAYOUT_HPP

#include "QtTest"
#include <QObject>

class TestCalendarLayout : public QObject
{
    Q_OBJECT

private slots:
    void testGetMonthRange_seventhJanuary_RangeSevenThree() const;
    void getMonthRange_18March_Range20_11() const;
    void getMonthRange_15July_Range50_3() const;
    void getMonthRange_31December_Range66_23() const;

};

#endif // TESTCALENDARLAYOUT_HPP
