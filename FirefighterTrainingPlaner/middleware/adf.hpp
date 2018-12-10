#ifndef ADF_HPP
#define ADF_HPP

#include <cstdint>
#include <string>
#include "firefighter.hpp"

class Adf
{
public:
    Adf();

    std::string name() const;
    void setName(const std::string &name);

    std::string surname() const;
    void setSurname(const std::string &surname);

    std::string email() const;
    void setEmail(const std::string &email);

    std::string mobilePhone() const;
    void setMobilePhone(const std::string &mobilePhone);

    std::string workPhone() const;
    void setWorkPhone(const std::string &workPhone);

    std::string adress() const;
    void setAdress(const std::string &adress);

    Dienstgrad grad() const;
    void setGrad(const Dienstgrad &grad);

private:
    std::string _name;
    std::string _surname;
    std::string _email;
    std::string _mobilePhone;
    std::string _workPhone;
    std::string _adress;
    Dienstgrad _grad;
};

#endif // ADF_HPP
