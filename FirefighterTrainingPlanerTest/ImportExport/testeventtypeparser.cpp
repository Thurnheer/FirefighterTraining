#include "testeventtypeparser.hpp"
#include "autotest.hpp"
#include "QString"
#include "xlsxdocument.h"
#include "eventtypeparser.hpp"

TestEventTypeParser::TestEventTypeParser(QObject *parent) : QObject(parent)
{

}

void TestEventTypeParser::testPumpDescription() const
{
    IO::EventDescriptionLayout::Layout const EXPECTED { "1", "Schule", "Sanitätsdienst // Rettungsgeräte"};
    QXlsx::Document d(QString(AutoTest::inputPath() + "Jahreskalender 2019.xlsx"));

    IO::EventTypeParser p(d);
    std::vector<IO::EventDescriptionLayout::Layout> v = p.pumpDescriptions();

    QCOMPARE(v[21], EXPECTED);
}

DECLARE_TEST(TestEventTypeParser);
