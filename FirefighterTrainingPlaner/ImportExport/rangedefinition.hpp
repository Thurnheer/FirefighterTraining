#ifndef RANGEDEFINITION_HPP
#define RANGEDEFINITION_HPP

namespace IO {

struct Range
{
    int startRow;
    int startCol;
    int length;
};
static constexpr Range operator+(Range rhs, Range const& lhs){
    return Range{ rhs.startRow + lhs.startRow, rhs.startCol + lhs.startCol, rhs.length + lhs.length };
}

constexpr bool operator==(Range const& lhs, Range const& rhs)
{
    return lhs.startRow == rhs.startRow && lhs.startCol == rhs.startCol && lhs.length == rhs.length;
}

}

#endif // RANGEDEFINITION_HPP
