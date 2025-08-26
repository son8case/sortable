#ifndef SON8_SORTABLE_UTIL_ASSIGN_HXX
#define SON8_SORTABLE_UTIL_ASSIGN_HXX

#include <utility>

namespace son8::sortable {

    template< typename OutT, typename ValT >
    void assign( OutT &out, ValT &&val ) {
        out = std::forward< ValT >( val );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_ASSIGN_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
