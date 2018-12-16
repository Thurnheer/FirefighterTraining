#ifndef DBTABLEDEFINITION_HPP
#define DBTABLEDEFINITION_HPP

#include "string"
#include "boost/fusion/include/define_struct.hpp"
#include "boost/fusion/include/for_each.hpp"
#include "boost/fusion/include/zip.hpp"
#include "boost/fusion/include/transform.hpp"
#include "boost/fusion/include/algorithm.hpp"
#include "boost/fusion/include/find.hpp"
#include "boost/mpl/range_c.hpp"
#include <utility>

namespace SQL
{

struct TABLENAME
{
    inline static constexpr char value[] = " (";
};

struct PRIMARY_KEY
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

template<typename T>
struct FOREIGN_KEY
{
    inline static constexpr char value[] = " FOREIGN KEY (";
};

}

template<class S>
auto combineWithNames(S const& s)
{
    typedef boost::mpl::range_c<int, 0, boost::fusion::result_of::size<S>::type::value> range;
    static auto names = boost::fusion::transform(range(), [](auto i)->std::string{
        return boost::fusion::extension::struct_member_name<S, i>::call();
    });
    return std::move(boost::fusion::zip(names, s));
}

template<class S>
auto appendNames(S const& s)
{
    auto withNames = boost::fusion::as_vector(combineWithNames(s));
    return std::move(boost::fusion::flatten(withNames));
}

struct SqlWriter
{
    explicit SqlWriter(std::string& str)
    : _str(str)
    {
        _str = "create table";
    }

    ~SqlWriter()
    {
        _str.back() = ')';
    }

    template<typename T>
    void operator()(SQL::FOREIGN_KEY<T> const & val)
    {
        _str += SQL::FOREIGN_KEY<T>::value;
        /*auto foreignTableKey = boost::fusion::find<SQL::PRIMARY_KEY>(val);
        auto withNames = boost::fusion::as_vector(combineWithNames(foreignTableKey));
        auto flat = boost::fusion::flatten<decltype(withNames)>(withNames);
        this->operator()(flat);*/
        _str += ")";
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

private:
    std::string& _str;
};

template<typename T>
std::string createTableName(T const& val)
{
    std::string sqlStr;
    SqlWriter w(sqlStr);
    auto withNames = boost::fusion::as_vector(combineWithNames(val));
    auto flat = boost::fusion::flatten<decltype(withNames)>(withNames);
    //auto withNames = appendNames(val);
    boost::fusion::for_each(flat, w);
    return sqlStr;
}


#endif // DBTABLEDEFINITION_HPP
