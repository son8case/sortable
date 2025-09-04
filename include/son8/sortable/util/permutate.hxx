#ifndef SON8_SORTABLE_UTIL_PERMUTATE_HXX
#define SON8_SORTABLE_UTIL_PERMUTATE_HXX

#include <algorithm>
#include <array>
#include <initializer_list>

namespace son8::sortable {

    template< typename Type, unsigned Size >
    class Permutate final {
        static inline constexpr std::initializer_list< unsigned > factors_{ 2u, 3u, 4u, 5u, 8u };
        static constexpr bool check_factor( unsigned n ) {
            return ( Size % n == 0 && Size / n != 1 );
        }
        static constexpr unsigned permutate_outer_size( ) {
            unsigned ret = Size;
            for ( auto n : factors_ ) {
                if ( check_factor( n ) ) ++ret;
            }
            return ret;
        }
        static constexpr unsigned const Inner_Size = Size;
        static constexpr unsigned const Outer_Size = permutate_outer_size( );
        using ValueType = Type;
        using ArrayType = std::array< ValueType, Inner_Size >;
        using DataType = std::array< ArrayType, Outer_Size >;
        DataType data_;
        ArrayType *curr_;
    public:
        Permutate( ) : curr_( &data_[0] ) {
            // unsigned step = 1u;
            unsigned k = Inner_Size;
            unsigned outer = 0u;
            for ( ; outer < Inner_Size; ++outer ) {
                ValueType value{ };
                data_[outer].fill( ++value );

                for ( unsigned inner = k; inner < Inner_Size; ++inner ) {
                    data_[outer][inner] = ++value;
                }
                --k;
            }
            for ( auto n : factors_ ) {
                if ( check_factor( n ) ) {
                    ValueType value{ };
                    data_[outer].fill( ++value );
                    auto step = Inner_Size / n;
                    auto offset = step;
                    while ( offset < Inner_Size ) {
                        ++value;
                        for ( auto inner = offset; inner < offset + step && inner < Inner_Size; ++inner ) {
                            data_[outer][inner] = value;
                        }
                        offset += step;
                    }
                    ++outer;
                }
            }
        }

        void reset( ) { curr_ = &data_[0]; }

        auto curr( ) const -> ArrayType { return *curr_; }

        bool next( ) {
            if ( std::next_permutation( curr_->begin( ), curr_->end( ) ) ) return true;
            return ++curr_ > &data_[Outer_Size - 1] ? reset( ), false : true;
        }

        template< typename OutT >
        void print( OutT &out ) const {
            for ( auto const &row : data_ ) {
                out << "[ ";
                for ( auto const &elem : row ) {
                    out << elem << " ";
                }
                out << "]\n";
            }
        }
    };
}

#endif//SON8_SORTABLE_UTIL_PERMUTATE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
