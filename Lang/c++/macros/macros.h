#undef SUPER_MACRO

#if defined(FIRST_TIME)

#undef FIRST_TIME

#define SUPER_MACRO(label, type)                \
    enum IDs {                                  \
              label##__ID = 10                  \
    };

#elif defined(SECOND_TIME)
#undef SECOND_TIME
#define SUPER_MACRO(label, type)                \
    class TestClass                             \
    {                                           \
    public:                                     \
    enum {ID = label##__ID};                    \
    TestClass(type value) : _value(value) {}    \
    type _value;                                \
    };

#endif
