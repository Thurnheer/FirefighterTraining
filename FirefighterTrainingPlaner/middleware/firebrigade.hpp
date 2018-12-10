#ifndef FIREBRIGADE_HPP
#define FIREBRIGADE_HPP

#include "adf.hpp"
#include "fwunit.hpp"
#include <vector>

class FireBrigade
{
public:
    FireBrigade();

    Adf commander() const;
    void setCommander(const Adf &commander);

    Adf vicecommander() const;
    void setVicecommander(const Adf &vicecommander);

    Adf chiefOfTraining() const;
    void setChiefOfTraining(const Adf &chiefOfTraining);

    Adf matierialWard() const;
    void setMatierialWard(const Adf &matierialWard);

    std::vector<FwUnit>const &units() const;
    void addUnit(FwUnit units);

    const std::vector<Drilltype>& drilltypes() const;
    void setDrilltypes(const Drilltype &drilltypes);

private:
    Adf _commander;
    Adf _vicecommander;
    Adf _chiefOfTraining;
    Adf _materialWard;
    std::vector<Drilltype> _drilltypes;
    std::vector<FwUnit> _units;
};

#endif // FIREBRIGADE_HPP
