#ifndef SON8_SORTABLE_IMPL_QUICK_HXX
#define SON8_SORTABLE_IMPL_QUICK_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

#include <cassert>

namespace son8::sortable {

    template< typename Type >
    class Partition_ final {
        using RangeType = Range< Type >;
        using PointerType = Type *;
        PointerType beg_, mid_, end_;
        bool is_unbalanced( ) const {
            // smaller of two splits is less than one quarter of full size
            auto minsize = mid_ - beg_ < end_ - mid_ ? mid_ - beg_ : end_ - mid_;
            auto fullsize = end_ - beg_;
            return minsize < ( fullsize >> 2 );
        }
    public:
        // TODO: rewrite to more sane version
        Partition_( RangeType range ) : beg_{ range.beg( ) }, mid_{ range.end( ) - 1 }, end_{ range.end( ) } {
            assert( range.end( ) - range.beg( ) > 2 );
            auto pivot = range.beg( );
            for (;/*_*/;) {
                while ( beg_ <= mid_ && beg_ != pivot && compare( beg_, pivot ) ) ++beg_;
                while ( beg_ <= mid_ && mid_ != pivot && compare( pivot, mid_ ) ) --mid_;
                if ( beg_ >= mid_ ) break;
                swap( beg_++, mid_-- );
            }
            beg_ = range.beg( );
            ++mid_;
            // TODO (in progress): fix unbalanced cases, when one split
            //      is significantly smaller than the other
            if ( is_unbalanced( ) ) {
                if ( end_ - mid_ == 1 ) {
                    // right split is one element with maximum value, check if other is fully reversed
                    auto leftmost_ = leftmost( );
                    for ( auto it = leftmost_.beg( ) + 1; it != leftmost_.end( ); ++it ) {
                        if ( compare( it - 1, it ) ) {
                            swap( leftmost_.beg( ), it );
                            return;
                        }
                    }
                    // reverse left split and make it one element
                    while ( beg_ < mid_ - 1 ) swap( beg_++, --mid_ );
                    beg_ = mid_ - 1;
                } else if ( mid_ - beg_ == 1 ) {
                    // left split is one element with minimum value, check if other is already sorted
                    auto rightful_ = rightful( );
                    for (auto it = rightful_.beg( ); it != rightful_.end( ) - 1; ++it ) {
                        if ( compare( it + 1, it ) ) {
                            swap( rightful_.end( ) - 1, it );
                            return;
                        }
                    }
                    // right split is already sorted make it one element
                    end_ = mid_ + 1;
                }
            }
        }
        // accessors
        auto leftmost( ) const { return RangeType{ beg_, mid_ }; }
        auto rightful( ) const { return RangeType{ mid_, end_ }; }
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
