#ifndef SON8_SORTABLE_IMPL_SELECTION_HXX
#define SON8_SORTABLE_IMPL_SELECTION_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

namespace son8::sortable {

    template< typename Type >
    void selection( Range< Type > range ) {
        for ( auto itL = range.beg(); itL != range.end(); ++itL ) {
            auto min_it = itL;
            for ( auto itR = itL + 1; itR != range.end(); ++itR ) {
                if ( compare( itR, min_it ) ) {
                    min_it = itR;
                }
            }
            if (min_it != itL) {
                swap( itL, min_it );
            }
        }
    }

}

#endif//SON8_SORTABLE_IMPL_SELECTION_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
