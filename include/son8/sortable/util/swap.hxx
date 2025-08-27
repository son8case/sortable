#ifndef SON8_SORTABLE_UTIL_SWAP_HXX
#define SON8_SORTABLE_UTIL_SWAP_HXX

#include <son8/sortable/util/assign.hxx>

#include <utility>

namespace son8::sortable {

    template< typename Type >
    void swap( Type &lhs, Type &rhs ) {
        Type tmp = std::move( lhs );
        assign( lhs, std::move( rhs ) );
        assign( rhs, std::move( tmp ) );
    }

    template< typename Type >
    void swap( Type *lhs, Type *rhs ) {
        Type temp = std::move( *lhs );
        assign( *lhs, std::move( *rhs ) );
        assign( *rhs, std::move( temp ) );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_SWAP_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
