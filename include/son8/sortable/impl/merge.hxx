#ifndef SON8_SORTABLE_IMPL_MERGE_HXX
#define SON8_SORTABLE_IMPL_MERGE_HXX

#include <son8/sortable/util/compare.hxx>
#include <son8/sortable/util/range.hxx>
#include <son8/sortable/util/swap.hxx>

#include <array>
#include <cstddef>
#include <vector>

namespace son8::sortable {

    template< typename Type >
    void merge( Range< Type > range )
    {
        using RangeType = Range< Type >;
        constexpr std::size_t StackBuffSize = 256u / sizeof( Type );
        RangeType buffer = range;

        std::vector< Type > buffvec_;
        std::array< Type, StackBuffSize > buffarr_;
        if ( range.size( ) > StackBuffSize ) {
            buffvec_.resize( range.size( ) );
            buffer = RangeType{ buffvec_.data( ), buffvec_.data( ) + buffvec_.size( ) };
        } else {
            buffer = RangeType{ buffarr_.data( ), buffarr_.data( ) + range.size( ) };
        }
        auto min_size = []( std::size_t a, std::size_t b ) { return a < b ? a : b; };

        std::size_t step = 1u;
        std::size_t offset = 0u;
        bool switch_buffer = false;
        RangeType buffers[2] = { range, buffer };
        while ( step < range.size( ) ) {
            auto srs = buffers[switch_buffer];
            auto dst = buffers[!switch_buffer];

            while ( offset < range.size( ) ) {
                auto full_size = range.size();
                auto itSrsLft = srs.beg() + offset;
                auto itSrsLnd = srs.beg() + min_size(offset + step, full_size);
                auto itSrsRht = itSrsLnd;
                auto itSrsRnd = srs.beg() + min_size(offset + step * 2, full_size);
                auto itDstLt = dst.beg() + offset;

                while ( itSrsLft != itSrsLnd && itSrsRht != itSrsRnd ) {
                    if ( compare( itSrsRht, itSrsLft ) )  assign( *itDstLt++, *itSrsRht++ );
                    else                                  assign( *itDstLt++, *itSrsLft++ );
                }
                while ( itSrsRht != itSrsRnd ) assign( *itDstLt++, *itSrsRht++ );
                while ( itSrsLft != itSrsLnd ) assign( *itDstLt++, *itSrsLft++ );

                offset += step * 2;
            } // while offset
            offset = 0;
            step *= 2;
            switch_buffer = !switch_buffer;
        } // while step
        if ( switch_buffer ) {
            auto itS = buffer.beg( );
            auto itD = range.beg( );
            while ( itS != buffer.end( ) ) assign( *itD++, *itS++ );
        }
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_IMPL_MERGE_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
