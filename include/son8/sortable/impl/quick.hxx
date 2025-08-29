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
        RangeType leftmost_, rightful_;
    public:
        Partition_( RangeType range ) : leftmost_{ range.beg( ), range.mid( ) }, rightful_{ range.mid( ), range.end( ) } {
            assert( range.end( ) - range.beg( ) > 2 );
            auto pivot = range.beg( );
            auto itL = range.beg( );
            auto itR = range.end( ) - 1;
            for (;/*_*/;) {
                while ( itL <= itR && itL != pivot && compare( itL, pivot ) ) ++itL;
                while ( itL <= itR && itR != pivot && compare( pivot, itR ) ) --itR;
                if ( itL >= itR ) break;
                swap( itL++, itR-- );
            }
            ++itR;
            leftmost_ = RangeType{ range.beg( ), itR };
            rightful_ = RangeType{ itR, range.end( ) };
            // TODO (in progress): fix unbalanced cases, when one split
            //      is significantly smaller than the other
            if ( range.size( ) > 8 ) {
                if ( rightful_.size( ) == 1 ) {
                    swap( leftmost_.beg( ), leftmost_.mid( ) );
                } else if ( leftmost_.size( ) == 1 ) {
                    for ( ; itR != rightful_.end( ) - 1; ++itR ) {
                        if ( compare( itR + 1, itR ) ) {
                            swap( rightful_.beg( ), rightful_.mid( ) );
                            return;
                        }
                    }
                    // REMINDER:
                    //      right split is already sorted
                    //      leftmost_ size = 1 means it is the smallest element
                    rightful_ = RangeType{ rightful_.end( ) - 1, rightful_.end( ) };
                }
            }
        }
        // accessors
        auto leftmost( ) const { return leftmost_; }
        auto rightful( ) const { return rightful_; }
        // deleted
        Partition_( ) = delete;
        Partition_( Partition_ && ) = delete;
        auto &operator=( Partition_ && ) = delete;
    }; // class Partition_

    template< typename Type >
    void quick( Range< Type > range ) {
        auto d = range.end( ) - range.beg( );
        if ( d < 3 ) {
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
