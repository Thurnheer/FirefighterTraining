#ifndef TST_TABLECREATIONTEST_HPP
#define TST_TABLECREATIONTEST_HPP

#include <QtTest>
#include <QCoreApplication>

class TableCreationTest : public QObject
{
    Q_OBJECT
public:
    TableCreationTest();

private slots:
    void createSimpleTable();
    void createLinkedTable();
};

#endif // TST_TABLECREATIONTEST_HPP
