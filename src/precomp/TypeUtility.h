#ifndef TYPE_UTILITY
#define TYPE_UTILITY

#include <string>

template <typename T> char const* getTypeName()
{
    static std::string cached;
    if (!cached.empty()) {
        return cached.c_str();
    }
    static char const* fallback = "<UNKNOWN>";

    char const* sig = __FUNCSIG__;
    char const* start = std::strchr(sig, '<');
    char const* end = std::strrchr(sig, '>');

    if (start && end && end > start) {
        cached = std::string(start + 1, end);
    } else {
        cached = fallback;
    }
    return cached.c_str();
}

template <typename FuncPtrType, FuncPtrType funcPtr> char const* getFuncPtrName()
{
    static std::string cached;
    if (!cached.empty()) {
        return cached.c_str();
    }
    static char const* fallback = "<UNKNOWN>";

    char const* sig = __FUNCSIG__;
    char const* typePart = getTypeName<FuncPtrType>();
    if (!typePart) {
        cached = fallback;
        return cached.c_str();
    }

    char const* typeInThisSig = std::strstr(sig, typePart);
    if (!typeInThisSig) {
        cached = fallback;
        return cached.c_str();
    }

    char const* start = typeInThisSig + std::strlen(typePart);
    char const* end = std::strrchr(sig, '>');
    if (start && end && end > start) {
        cached = std::string(start + 1, end); // 1 for comma
    } else {
        cached = fallback;
    }

    return cached.c_str();
}

#endif // TYPE_UTILITY
