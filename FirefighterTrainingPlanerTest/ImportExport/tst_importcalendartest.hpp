#ifndef TST_IMPORTCALENDARTEST_HPP
#define TST_IMPORTCALENDARTEST_HPP

#include "QtTest"
#include "QCoreApplication"

class ImportCalendarTest : public QObject
{
    Q_OBJECT
public:
    ImportCalendarTest();

private slots:
    void getYear_Jahreskalender2019FWBAH_2019() const;
};

#endif // TST_IMPORTCALENDARTEST_HPP
