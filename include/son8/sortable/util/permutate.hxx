#ifndef SON8_SORTABLE_UTIL_PERMUTATE_HXX
#define SON8_SORTABLE_UTIL_PERMUTATE_HXX

#include <algorithm>
#include <array>

namespace son8::sortable {

    template< typename Type, unsigned Size >
    class Permutate final {
        using ValueType = Type;
        using ArrayType = std::array< ValueType, Size >;
        using DataType = std::array< ArrayType, Size >;
        DataType data_;
        ArrayType *curr_;
    public:
        Permutate( ) : curr_( &data_[0] ) {
            unsigned step = 1u;
            unsigned k = Size;
            for ( unsigned outer = 0; outer < Size; ++outer ) {
                ValueType value{ };
                data_[outer].fill( ++value );
                if ( step == outer + 1 ) {
                    auto offset = step;
                    while ( offset < Size ) {
                        ++value;
                        for ( auto inner = offset; inner < offset + step && inner < Size; ++inner ) {
                            data_[outer][inner] = value;
                        }
                        offset += step;
                    }
                    step *= 2;
                } else {
                    for ( unsigned inner = k; inner < Size; ++inner ) {
                        data_[outer][inner] = value;
                        ++value;
                    }

                }
                --k;
            }
        }

        void reset( ) { curr_ = &data_[0]; }

        auto curr( ) const -> ArrayType { return *curr_; }

        bool next( ) {
            if ( std::next_permutation( curr_->begin( ), curr_->end( ) ) ) return true;
            return ++curr_ > &data_[Size - 1] ? reset( ), false : true;
        }
    };
}

#endif//SON8_SORTABLE_UTIL_PERMUTATE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
