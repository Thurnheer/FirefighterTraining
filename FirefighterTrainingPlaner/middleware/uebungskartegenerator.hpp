#ifndef UEBUNGSKARTEGENERATOR_HPP
#define UEBUNGSKARTEGENERATOR_HPP

#include "SqlTableNames.hpp"

class QString;

class UebungsKarteGenerator
{
public:
    UebungsKarteGenerator();

    //void generateUebungskarte(const QString &path);

private:
    EventDataBase   m_database;


};

#endif // UEBUNGSKARTEGENERATOR_HPP
