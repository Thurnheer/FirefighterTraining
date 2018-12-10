#ifndef TST_EVENTTEST_HPP
#define TST_EVENTTEST_HPP

#include "QtTest"
#include "QCoreApplication"

class EventTest : public QObject
{
    Q_OBJECT

public:
    EventTest();
    ~EventTest();

private slots:
    void test_case1();

};

#endif // TST_EVENTTEST_HPP
