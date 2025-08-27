#ifndef SON8_SORTABLE_IMPL_BUBBLE_HXX
#define SON8_SORTABLE_IMPL_BUBBLE_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

namespace son8::sortable {

    template< typename Type >
    void bubble( Range< Type > range ) {
        auto first = range.beg( );
        auto last = range.end( ) - 1;
        for ( auto itL = first; itL < last; ++itL ) {
            bool swapped = false;
            for ( auto itR = first; itR < last - ( itL - first ); ++itR ) {
                if ( compare( itR + 1, itR ) ) {
                    swap( itR + 1, itR );
                    swapped = true;
                }
            }
            if ( !swapped ) break;
        }
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_IMPL_BUBBLE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
