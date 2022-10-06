#include "map.h"

#define MAP0_P(f, p, x, peek, ...) f(p, x) MAP_NEXT(peek, MAP1_P)(f, p, peek, __VA_ARGS__)
#define MAP1_P(f, p, x, peek, ...) f(p, x) MAP_NEXT(peek, MAP0_P)(f, p, peek, __VA_ARGS__)

#define MAP_LIST0_P(f, p, x, peek, ...) f(p, x) MAP_LIST_NEXT(peek, MAP_LIST1_P)(f, p, peek, __VA_ARGS__)
#define MAP_LIST1_P(f, p, x, peek, ...) f(p, x) MAP_LIST_NEXT(peek, MAP_LIST0_P)(f, p, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters with the
 * argument `p` applied before each parameter
 *
 * Example:
 *  MAP_P(FOO, a, 1, 2, 3) -> FOO(a, 1) FOO(a, 2) FOO(a, 3)
 *
 */
#define MAP_P(f, p, ...) EVAL(MAP1_P(f, p, __VA_ARGS__, ()()(), ()()(), ()()(), 0))

/**
 * Applies the function macro `f` to each of the remaining parameters and
 * inserts commas between the results.
 */
#define MAP_LIST_P(f, p, ...) EVAL(MAP_LIST1_P(f, p, __VA_ARGS__, ()()(), ()()(), ()()(), 0))