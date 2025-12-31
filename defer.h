#ifndef DEFER_H
#define DEFER_H

#ifndef _MAX_DEFERRED_BLOCKS
    #define _MAX_DEFERRED_BLOCKS (64)
#endif

#if defined(__GNUC__) || defined(__TINYC__)
    #define _defer_label(prefix, count) prefix ## count

    #define deferred                                                        \
        unsigned char _defer_count = 0;                                     \
        void *_defer_return = 0;                                            \
        void *_defer_stack[_MAX_DEFERRED_BLOCKS] = {0};                     \

    #define _Defer(block, count) do {                                       \
        _defer_stack[_defer_count++] = &&_defer_label(_defer_begin_, count); \
        if (0) {                                                            \
            _defer_label(_defer_begin_, count):                              \
                block;                                                      \
                if (_defer_count) {                                         \
                    goto *_defer_stack[--_defer_count];                     \
                } else {                                                    \
                    goto *_defer_return;                                    \
                }                                                           \
        }                                                                   \
    } while (0)

    #define _Return(count)                                                  \
        if (_defer_count > 0) {                                             \
            _defer_return = &&_defer_label(_defer_end_, count);              \
            goto *_defer_stack[--_defer_count];                             \
        } else _defer_label(_defer_end_, count): return                      \

    #define defer(block) _Defer(block, __COUNTER__);
    #define return _Return(__COUNTER__)
#else
    #warning "Defer library is supported only in GNUC and TINYC."
#endif /* __GNUC__ */
#endif /* DEFER_H */
