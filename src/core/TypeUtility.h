#ifndef TYPE_UTILITY
#define TYPE_UTILITY

#include <string>

template <typename T> const char* getTypeName()
{
    static std::string cached;
    if (!cached.empty()) {
        return cached.c_str();
    }
    static const char* fallback = "<UNKNOWN>";

    const char* sig = __FUNCSIG__;
    const char* start = std::strchr(sig, '<');
    const char* end = std::strrchr(sig, '>');

    if (start && end && end > start) {
        cached = std::string(start + 1, end);
    } else {
        cached = fallback;
    }
    return cached.c_str();
}

template <typename FuncPtrType, FuncPtrType funcPtr> const char* getFuncPtrName()
{
    static std::string cached;
    if (!cached.empty()) {
        return cached.c_str();
    }
    static const char* fallback = "<UNKNOWN>";

    const char* sig = __FUNCSIG__;
    const char* typePart = getTypeName<FuncPtrType>();
    if (!typePart) {
        cached = fallback;
        return cached.c_str();
    }

    const char* typeInThisSig = std::strstr(sig, typePart);
    if (!typeInThisSig) {
        cached = fallback;
        return cached.c_str();
    }

    const char* start = typeInThisSig + std::strlen(typePart);
    const char* end = std::strrchr(sig, '>');
    if (start && end && end > start) {
        cached = std::string(start + 1, end); // 1 for comma
    } else {
        cached = fallback;
    }

    return cached.c_str();
}

#endif // TYPE_UTILITY
