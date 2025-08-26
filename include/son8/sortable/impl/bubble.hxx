#ifndef SON8_SORTABLE_IMPL_BUBBLE_HXX
#define SON8_SORTABLE_IMPL_BUBBLE_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

namespace son8::sortable {

    template< typename Type >
    void bubble( Range< Type > range ) {
        auto last = range.end( ) - 1;
        for ( auto itL = range.beg( ); itL < last; ++itL ) {
            for ( auto itR = last; itR > itL; --itR ) {
                if ( compare( itR, itL ) ) swap( itR, itL );
            }
        }
    }

} // namespace son8::sortable

#endif//SON8_PATH_FILE_NAME_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
