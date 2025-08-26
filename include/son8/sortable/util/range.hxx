#ifndef SON8_SORTABLE_UTIL_RANGE_HXX
#define SON8_SORTABLE_UTIL_RANGE_HXX

#include <cassert>

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
    }; // class Range

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_RANGE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
