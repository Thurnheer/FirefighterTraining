#ifndef DRILLTYPE_HPP
#define DRILLTYPE_HPP

#include <string>
#include <QDateTime>

class Drilltype
{
public:
    Drilltype(std::string name, QDateTime startTime, QDateTime endTime);
    ~Drilltype();
    const std::string _name;
    const QDateTime _startTime;
    const QDateTime _endTime;

};

#endif // DRILLTYPE_HPP
