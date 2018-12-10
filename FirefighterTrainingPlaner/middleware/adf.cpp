#include "adf.hpp"

Adf::Adf()
{

}

std::string Adf::name() const
{
    return _name;
}

void Adf::setName(const std::string &name)
{
    _name = name;
}

std::string Adf::surname() const
{
    return _surname;
}

void Adf::setSurname(const std::string &surname)
{
    _surname = surname;
}

std::string Adf::email() const
{
    return _email;
}

void Adf::setEmail(const std::string &email)
{
    _email = email;
}

std::string Adf::mobilePhone() const
{
    return _mobilePhone;
}

void Adf::setMobilePhone(const std::string &mobilePhone)
{
    _mobilePhone = mobilePhone;
}

std::string Adf::workPhone() const
{
    return _workPhone;
}

void Adf::setWorkPhone(const std::string &workPhone)
{
    _workPhone = workPhone;
}

std::string Adf::adress() const
{
    return _adress;
}

void Adf::setAdress(const std::string &adress)
{
    _adress = adress;
}

Dienstgrad Adf::grad() const
{
    return _grad;
}

void Adf::setGrad(const Dienstgrad &grad)
{
    _grad = grad;
}
