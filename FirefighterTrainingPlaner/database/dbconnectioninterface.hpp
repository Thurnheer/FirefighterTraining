#ifndef DBCONNECTION_HPP
#define DBCONNECTION_HPP

#include "dbtabledefinition.hpp"
#include "QString"

class DbConnectionInterface
{
public:
    DbConnectionInterface();
    virtual ~DbConnectionInterface();

    virtual QString getConnection() = 0;
};

#endif // DBCONNECTION_HPP
