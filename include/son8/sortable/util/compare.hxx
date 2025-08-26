#ifndef SON8_SORTABLE_UTIL_COMPARE_HXX
#define SON8_SORTABLE_UTIL_COMPARE_HXX

namespace son8::sortable {

    template< typename Type >
    struct Less {
        bool operator()( Type const &lhs, Type const &rhs ) const { return lhs < rhs; }
        bool operator()( Type *lhs, Type *rhs ) const { return *lhs < *rhs; }
    };

    template< typename Type, typename Comp = Less< Type > >
    bool compare( Type const &lhs, Type const &rhs, Comp comp = { } ) {
        return comp( lhs, rhs );
    }

    template< typename Type, typename Comp = Less< Type > >
    bool compare( Type *lhs, Type *rhs, Comp comp = { } ) {
        return comp( lhs, rhs );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_COMPARE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
