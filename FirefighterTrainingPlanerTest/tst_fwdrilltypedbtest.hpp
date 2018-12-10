#ifndef TST_FWDRILLTYPETEST_HPP
#define TST_FWDRILLTYPETEST_HPP

#include <QtTest>
#include <QCoreApplication>

class DrilltypeDbTest : public QObject
{
    Q_OBJECT

public:
    DrilltypeDbTest();
    ~DrilltypeDbTest();

private slots:
    void test_case1();

};

#endif // TST_FWDRILLTYPETEST_HPP
