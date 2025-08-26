#ifndef SON8_SORTABLE_IMPL_INSERTION_HXX
#define SON8_SORTABLE_IMPL_INSERTION_HXX

#include <son8/sortable/util/assign.hxx>
#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>

namespace son8::sortable {

    template< typename Type >
    void insertion( Range< Type > range ) {
        Type val;
        for ( auto itR = range.beg( ) + 1; itR < range.end( ); ++itR ) {
            assign( val, std::move( *itR ) );
            auto itL = itR;
            while ( --itL >= range.beg( ) ) {
                if ( compare( val, *itL ) ) assign( *( itL + 1 ), std::move( *itL ) );
                else break;
            }
            assign( *( itL + 1 ), std::move( val ) );
        }
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_IMPL_INSERTION_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
