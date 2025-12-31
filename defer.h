#ifndef DEFER_H
#define DEFER_H

#ifndef _MAX_DEFERRED_BLOCKS
    #define _MAX_DEFERRED_BLOCKS 64
#endif

#if defined(__GNUC__) || defined(__TINYC__)
    #define _defer_label(prefix, count) prefix ## count

    #define scope(...) do {                                                     \
        unsigned char _defer_count = 0;                                         \
        void *_defer_stack[_MAX_DEFERRED_BLOCKS] = {0};                         \
        __VA_ARGS__                                                             \
        _defer_clean:                                                           \
            while (_defer_count > 0) {                                          \
                goto *_defer_stack[--_defer_count];                             \
            }                                                                   \
    } while(0)

    #define _defer_block(code, count) do {                                      \
        _defer_stack[_defer_count++] = &&_defer_label(_defer_begin_, count);    \
        if (0) {                                                                \
            _defer_label(_defer_begin_, count):                                 \
                code;                                                           \
                goto _defer_clean;                                              \
        }                                                                       \
    } while(0)

    #define defer(block) _defer_block(block, __COUNTER__)
#else
    #warning "Defer library is supported only in GNUC and TINYC."
#endif /* __GNUC__ || __TINYC__ */

#endif /* DEFER_H */
