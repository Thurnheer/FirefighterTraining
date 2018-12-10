#ifndef DBTABLEDEFINITION_HPP
#define DBTABLEDEFINITION_HPP

#include "string"
#include "boost/fusion/include/define_struct.hpp"
#include "boost/fusion/include/for_each.hpp"
#include "boost/fusion/include/zip.hpp"
#include "boost/fusion/include/transform.hpp"
#include "boost/fusion/include/algorithm.hpp"
#include "boost/mpl/range_c.hpp"

namespace SQL
{

struct TABLENAME
{
    inline static constexpr char value[] = " (";
};

struct ID
{
    inline static constexpr char value[] = " INTEGER PRIMARY KEY,";
};

struct INTEGER
{
    inline static constexpr char value[] = " INT,";
};

struct TEXT
{
    inline static constexpr char value[] = " TEXT,";
};

struct DATE
{
    inline static constexpr char value[] = " DATE,";
};

}

struct SqlWriter
{
    SqlWriter()
    : _str("create table")
    {

    }

    template<typename T>
    void operator()(T const &) const
    {
        _str += T::value;
    }

    void operator()(std::string const & val) const
    {
        _str += " " + val;
    }

    std::string getString() const
    {
        _str.back() = ')';
        return _str;
    }

private:
    mutable std::string _str;
};

template<class S>
auto combineWithNames(S const& s)
{
    typedef boost::mpl::range_c<int, 0, boost::fusion::result_of::size<S>::type::value> range;
    static auto names = boost::fusion::transform(range(), [](auto i)->std::string{
        return boost::fusion::extension::struct_member_name<S, i>::call();
    });
    return boost::fusion::zip(names, s);
}

template<typename T>
std::string createTableName(T const& val)
{
    SqlWriter w;
    auto withNames = boost::fusion::as_vector(combineWithNames(val));
    auto flat = boost::fusion::flatten<decltype(withNames)>(withNames);
    boost::fusion::for_each(flat, w);
    return w.getString();
}


#endif // DBTABLEDEFINITION_HPP
