#ifndef FWUNIT_HPP
#define FWUNIT_HPP

#include "adf.hpp"
#include "drilltype.hpp"
#include "event.h"
#include <vector>
#include <string>

class FwUnit
{
public:
    FwUnit(std::string name, std::string shortsign);

    std::string name() const;
    void setName(const std::string &name);

    std::vector<Adf> members() const;
    void setMembers(const std::vector<Adf> &members);

    std::vector<Event *> const& events() const;
    void addEvents(Event * events);

private:
    std::string _name;
    std::string _shortsign;
    std::vector<Adf> _members;
    std::vector<Event*> _events;
};

#endif // FWUNIT_HPP
