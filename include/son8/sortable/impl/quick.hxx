#ifndef SON8_SORTABLE_IMPL_QUICK_HXX
#define SON8_SORTABLE_IMPL_QUICK_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

#include <cassert>

namespace son8::sortable {
    // TODO: remove itL,itR pivot checks (self comparison avoidance)
    template< typename Type >
    class Partition_ final {
        using RangeType = Range< Type >;
        using PointerType = Type*;
        PointerType ltL, ltR, rtL, rtR;
    public:
        Partition_( RangeType range ) {
            assert( range.end( ) - range.beg( ) > 2 );
            auto pivot = range.beg( );
            auto itL = range.beg( ) ;
            auto itR = range.end( ) - 1;
            for (;/*_*/;) {
                while ( itL <= itR && itL != pivot && compare( itL, pivot ) ) ++itL;
                while ( itL <= itR && itR != pivot && compare( pivot, itR ) ) --itR;
                if ( itL >= itR ) break;
                swap( itL++, itR-- );
            }
            ltL = range.beg( );
            ltR = itR + 1;
            rtL = itR + 1;
            rtR = range.end( );
        }

        auto leftmost( ) const { return RangeType{ ltL, ltR }; }
        auto rightful( ) const { return RangeType{ rtL, rtR }; }

        bool is_last( ) const { return ltL == rtL && ltR == rtR; }

        Partition_( ) = delete;
        Partition_( Partition_ && ) = delete;
        auto &operator=( Partition_ && ) = delete;
    }; // class Partition_

    template< typename Type >
    void quick( Range< Type > range ) {
        auto d = range.end( ) - range.beg( );
        if ( d < 3) {
            if ( d == 2 && compare( range.beg( ) + 1, range.beg( ) ) ) swap( range.beg( ) + 1, range.beg( ) );
            return;
        }

        Partition_ p{ range };
        quick( p.leftmost( ) );
        quick( p.rightful( ) );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_IMPL_QUICK_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
