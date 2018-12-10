#include "fwunit.hpp"

FwUnit::FwUnit(std::string name, std::string shortsign)
: _name(name)
, _shortsign(shortsign)
{

}

std::string FwUnit::name() const
{
    return _name;
}

void FwUnit::setName(const std::string &name)
{
    _name = name;
}

std::vector<Adf> FwUnit::members() const
{
    return _members;
}

void FwUnit::setMembers(const std::vector<Adf> &members)
{
    _members = members;
}

const std::vector<Event *> &FwUnit::events() const
{
    return _events;
}

void FwUnit::addEvents(Event *events)
{
    _events.push_back(events);
}
