#ifndef SON8_SORTABLE_UTIL_STAT_HXX
#define SON8_SORTABLE_UTIL_STAT_HXX

#include <utility>

namespace son8::sortable {

    template< typename Type >
    class Stat {
        struct Counter {
            unsigned value{ 0 };
            Counter &operator++( ) {
                if ( is_enabled_ ) ++value;
                return *this;
            }
            Counter &operator+=( unsigned add ) {
                if ( is_enabled_ ) value = value + add;
                return *this;
            }
        };
        inline static bool is_enabled_ = false;
        inline static Counter assigns_count_;
        inline static Counter compare_count_;
        Type value_;
    public:
        // constructors
        Stat( ) = default;
        Stat( Type value ) : value_{ value } { }
        Stat( Stat const &stat ) : value_{ stat.value_ } { ++assigns_count_; }
        Stat( Stat && stat ) noexcept : value_{ std::move( stat.value_ ) } { ++assigns_count_; };
        // operators
        Stat &operator=( Stat const &other ) {
            assert( this != &other );
            ++assigns_count_;
            value_ = other.value_;
            return *this;
        }
        Stat &operator=( Stat&& other ) noexcept {
            assert( this != &other );
            ++assigns_count_;
            value_ = std::move( other.value_ );
            return *this;
        }
        bool operator<( Stat const &other ) const {
            assert( this != &other );
            ++compare_count_;
            return value_ < other.value_;
        }
        bool operator==( Stat const &other ) const {
            assert( this != &other );
            ++compare_count_;
            return value_ == other.value_;
        }
        operator Type( ) const { return value_; }
        // methods
        void swap( Stat &other ) noexcept {
            assert( this != &other );
            using std::swap;
            swap( value_, other.value_ );
            assigns_count_ += 3; // Each swap involves 3 assignments
        }
        // static methods
        static unsigned get_assigns_count() { return assigns_count_.value; }
        static unsigned get_compare_count() { return compare_count_.value; }
        static void reset_counters() {
            assigns_count_.value = 0;
            compare_count_.value = 0;
        }
        static void enable_counters( ) { is_enabled_ = true; }
        static void disable_counters( ) { is_enabled_ = false; }
    }; // class Stat

    template< typename AdlSucks >
    void swap( Stat< AdlSucks > &firstPhase, Stat< AdlSucks > &secondPhase ) {
        firstPhase.swap( secondPhase );
    }

} // namespace son8::sortable

#endif//SON8_SORTABLE_UTIL_STAT_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
