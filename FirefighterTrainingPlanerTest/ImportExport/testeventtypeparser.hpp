#ifndef TESTEVENTTYPEPARSER_HPP
#define TESTEVENTTYPEPARSER_HPP

#include "QtTest"
#include <QObject>

class TestEventTypeParser : public QObject
{
    Q_OBJECT
public:
    explicit TestEventTypeParser(QObject *parent = nullptr);

private slots:
    void testPumpDescription() const;

};

#endif // TESTEVENTTYPEPARSER_HPP
