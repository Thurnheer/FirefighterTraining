#ifndef FWDRILLTYPE_HPP
#define FWDRILLTYPE_HPP

#include <cstdint>
#include "qsqltablemodel.h"
#include "QDateTime"

class FwDrillTypeDb
{
public:
    FwDrillTypeDb();

private:
    QSqlTableModel _model;
    uint32_t _highestId;
    std::string _tableName;
    std::string _drillName;
    QDateTime _startTime;
    QDateTime _endTime;
};

#endif // FWDRILLTYPE_HPP
