#ifndef SON8_SORTABLE_UTIL_PRINT_HXX
#define SON8_SORTABLE_UTIL_PRINT_HXX

#include <son8/sortable/util/range.hxx>

#include <iostream>

namespace son8::sortable {

    template< typename Type >
    void print( Range< Type > range ) {
        Type *it = range.beg( );
        std::cout << "[ " << *it;
        while ( ++it < range.end( ) ) std::cout << ", " << *it;
        std::cout << " ]";
    }

    template< typename Type >
    void println( Range< Type > range ) {
        print( range );
        std::cout << std::endl;
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_PRINT_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
