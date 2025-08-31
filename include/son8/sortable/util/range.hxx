#ifndef SON8_SORTABLE_UTIL_RANGE_HXX
#define SON8_SORTABLE_UTIL_RANGE_HXX

#include <cassert>
#include <cstddef>

namespace son8::sortable {
    // Range class represents a half-open range [beg, end)
    template< typename Type >
    class Range final {
        Type *beg_;
        Type *end_;
    public:
        Range( ) = delete;
        Range( Type *beg, Type *end )
            : beg_{ beg }, end_{ end } {
            assert( beg < end );
        }
        Type *beg( ) const { return beg_; }
        Type *end( ) const { return end_; }
        Type *mid( ) const { return beg_ + ( ( end_ - beg_ ) >> 1 ); }
        auto size( ) const { return static_cast< std::size_t >( end_ - beg_ ); }
    }; // class Range

    template< typename Type >
    bool operator==( Range< Type > const &lhs, Range< Type > const &rhs ) {
        return lhs.beg( ) == rhs.beg( ) && lhs.end( ) == rhs.end( );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_RANGE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
