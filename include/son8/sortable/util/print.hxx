#ifndef SON8_SORTABLE_UTIL_PRINT_HXX
#define SON8_SORTABLE_UTIL_PRINT_HXX

#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/stat.hxx>

#include <iostream>

namespace son8::sortable {

    template< typename Type >
    void print( Range< Type > range, std::ostream &os = std::cout ) {
        Type *it = range.beg( );
        os << "[ " << *it;
        while ( ++it < range.end( ) ) os << ", " << *it;
        os << " ]";
    }

    template< typename Type >
    void println( Range< Type > range, std::ostream &os = std::cout ) {
        print( range, os );
        os << std::endl;
    }

    template< typename Type >
    std::ostream &operator<<( std::ostream &os, Range< Type > range ) {
        print( range, os );
        return os;
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_PRINT_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
