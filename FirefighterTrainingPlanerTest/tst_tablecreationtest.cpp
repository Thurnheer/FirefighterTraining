#include "autotest.hpp"
#include "tst_tablecreationtest.hpp"
#include "dbtabledefinition.hpp"
#include "boost/fusion/include/define_struct.hpp"

BOOST_FUSION_DEFINE_STRUCT(
    (TST), TestTable,
    (SQL::TABLENAME, Event)
    (SQL::ID, id)
    (SQL::TEXT, name)
    (SQL::INTEGER, einteilung)
    (SQL::TEXT, einteilungsindex)
    (SQL::INTEGER, uebungsnr)
    (SQL::DATE, startDate)
    (SQL::INTEGER, startTime)
    (SQL::DATE, endDate)
    (SQL::INTEGER, endTime)
    (SQL::TEXT, uuid)
)

BOOST_FUSION_DEFINE_STRUCT(
    (TST), RelationTable,
    (SQL::TABLENAME, Relation)
    (SQL::ID, id)
    (SQL::TEXT, name)
    (TST::TestTable, Event)
)

TableCreationTest::TableCreationTest()
{

}

void TableCreationTest::createSimpleTable()
{
    const QString EXPECTED("create table Event ( id INTEGER PRIMARY KEY, name TEXT, einteilung INT, einteilungsindex TEXT, uebungsnr INT, startDate DATE, startTime INT, endDate DATE, endTime INT, uuid TEXT)");
    TST::TestTable t;

    const QString result(createTableName(t).c_str());
    QCOMPARE(result, EXPECTED);
}

void TableCreationTest::createLinkedTable()
{
    const QString EXPECTED("create table Relation ( id INTEGER PRIMARY KEY, name TEXT, testTable INTEGER REFERENCES Testtable(id))");
    TST::RelationTable r;

    const QString result(createTableName(r).c_str());
//    QCOMPARE(result, EXPECTED);
}

DECLARE_TEST(TableCreationTest)
