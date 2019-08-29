#include <iostream>

/* NDEBUG */
#ifdef NDEBUG
#define tarzannDebug(x)  std::cout << x << std::endl
#else
#define tarzannDebug(x)
#endif

#ifdef NDEBUG
#define tarzannAssert(condition,message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#define tarzannAssert(condition,message) do { } while (false)
#endif

