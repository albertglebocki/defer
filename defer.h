#ifndef DEFER_H
#define DEFER_H

#ifndef _MAX_DEFERRED_BLOCKS
    #define _MAX_DEFERRED_BLOCKS (128)
#endif

#if defined(__GNUC__) || defined(__TINYC__)
    #define _defer_label(prefix, count) prefix ## count

    #define _defer_scope(_inner_scope) do {                                            \
        unsigned char _defer_count = 0;                                         \
        void *_defer_stack[_MAX_DEFERRED_BLOCKS] = {0};                         \
        _inner_scope                                                            \
        _defer_clean:                                                           \
            if (_defer_count > 0) {                                          \
                goto *_defer_stack[--_defer_count];                             \
            }                                                                   \
    } while(0)

    #define _defer_block(_scope, _count) do {                                    \
        _defer_stack[_defer_count++] = &&_defer_label(_defer_begin_, _count);    \
        if (0) {                                                                \
            _defer_label(_defer_begin_, _count):                                 \
                _scope;                                                         \
                goto _defer_clean;                                              \
        }                                                                       \
    } while(0)

    #define defer(scope) _defer_block(scope, __COUNTER__)
    #define scope(scope) _defer_scope(scope)
#else
    #warning "Defer library is supported only in GNUC and TINYC."
#endif /* __GNUC__ || __TINYC__ */

#endif /* DEFER_H */
