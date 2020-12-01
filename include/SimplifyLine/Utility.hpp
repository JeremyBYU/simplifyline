#ifndef SIMPLIFYLINE_UTILITY
#define SIMPLIFYLINE_UTILITY

#include <utility>
#include <type_traits>
namespace SimplifyLine {

namespace Utility {


// template <unsigned int i, unsigned int end>
// struct static_for {
//   template <typename Lambda>
//   void operator()(const Lambda& function) const {
//     if (i < end) {
//       function(std::integral_constant<int, i>{});
//       static_for<i + 1, end>(function);
//     }
//   }
// };


// template <unsigned N> struct faux_unroll {
//     template <typename F> static void call(F const& f) {
//         f(std::integral_constant<int, N-1>{});
//         faux_unroll<N-1>::call(f);
//     }
// };

// template <> struct faux_unroll<0u> {
//     template <typename F> static void call(F const&) {}
// };

template <unsigned N, unsigned M=N> struct faux_unroll {
    template <typename F> static void call(F const& f) {
        f(std::integral_constant<int, M>{} - std::integral_constant<int, N>{});
        faux_unroll<N-1, M>::call(f);
    }
};

template <> struct faux_unroll<0u,3u> {
    template <typename F> static void call(F const& ) {}
};

template <> struct faux_unroll<0u,2u> {
    template <typename F> static void call(F const& ) {}
};

} // namespace Utility
} // namespace SimplifyLine

#endif