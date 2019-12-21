#ifndef CALENDERPARSERTEST_HPP
#define CALENDERPARSERTEST_HPP

#include "QtTest"
#include "QObject"

class calenderparsertest : public QObject
{
    Q_OBJECT
private slots:
    void filterForNames_ZugMdAs_seperated() const;
};

#endif // CALENDERPARSERTEST_HPP
