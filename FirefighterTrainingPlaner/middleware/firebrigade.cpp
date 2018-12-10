#include "firebrigade.hpp"
#include "init.hpp"

FireBrigade::FireBrigade()
{
    initFwBAH(*this);
}

Adf FireBrigade::commander() const
{
    return _commander;
}

void FireBrigade::setCommander(const Adf &commander)
{
    _commander = commander;
}

Adf FireBrigade::vicecommander() const
{
    return _vicecommander;
}

void FireBrigade::setVicecommander(const Adf &vicecommander)
{
    _vicecommander = vicecommander;
}

Adf FireBrigade::chiefOfTraining() const
{
    return _chiefOfTraining;
}

void FireBrigade::setChiefOfTraining(const Adf &chiefOfTraining)
{
    _chiefOfTraining = chiefOfTraining;
}

Adf FireBrigade::matierialWard() const
{
    return _materialWard;
}

void FireBrigade::setMatierialWard(const Adf &matierialWard)
{
    _materialWard = matierialWard;
}

std::vector<FwUnit>const & FireBrigade::units() const
{
    return _units;
}

void FireBrigade::addUnit(FwUnit units)
{
    _units.emplace_back(units);
}

const std::vector<Drilltype> &FireBrigade::drilltypes() const
{
    return _drilltypes;
}

void FireBrigade::setDrilltypes(const Drilltype &drilltypes)
{
    _drilltypes.push_back(drilltypes);
}
