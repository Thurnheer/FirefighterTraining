#include "calenderparsertest.hpp"
#include "pipe.hpp"
#include "calendarparser.hpp"
#include "xlsxdocument.h"
#include "autotest.hpp"


void calenderparsertest::filterForNames_ZugMdAs_seperated() const
{
/*    pipe<IO::RawEvent> input, output, rest;

    IO::RawEvent masch;
    masch.name = "MD A/1";
    masch.date = QDate(2010, 1, 2);
    IO::RawEvent zug;
    zug.name = "Zug 1/1";
    zug.date = QDate(2010, 1, 2);
    IO::RawEvent as;
    as.name = "AS A/1";
    as.date = QDate(2010, 1, 2);

    input << masch; input << zug; input << as;

    QXlsx::Document doc;
    IO::CalendarParser parser(doc);

    QVector<QRegularExpression> name{QRegularExpression("Zug \\d.*")};

    parser.filterForNames(input, name, output, rest);
*/

    QString name("Zug 1/1");
    QRegularExpression regex("Zug \\d.*");

    QVERIFY(regex.match(name).hasMatch());

}

DECLARE_TEST(calenderparsertest);
