#ifndef SON8_SORTABLE_IMPL_QUICK_HXX
#define SON8_SORTABLE_IMPL_QUICK_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

#include <cassert>

namespace son8::sortable {
    // TODO: improve partition logic and behavior, remove itL,itR pivot checks (self comparison avoidance)
    template< typename Type >
    void quick( Range< Type > range ) {
        static auto partition = []( Range< Type > p_range ) -> Type* {
            auto d = p_range.end( ) - p_range.beg( );
            auto pivot = p_range.beg( );
            auto itL = p_range.beg( );
            auto itR = p_range.end( ) - 1;
            if ( d == 2 && --d && compare( itR, itR - 1 ) ) swap( itR, itR - 1 );
            --d;
            while ( d ) {
                while ( itL <= itR && itL != pivot && compare( itL, pivot ) ) ++itL;
                while ( itL <= itR && itR != pivot && compare( pivot, itR ) ) --itR;
                if ( itL >= itR ) return itR + 1;
                swap( itL++, itR-- );
            }

            return nullptr;
        };

        auto pivot = partition( range );
        if ( pivot == nullptr ) return;
        quick( Range{ range.beg( ), pivot } );
        quick( Range{ pivot, range.end( ) } );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_IMPL_QUICK_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
