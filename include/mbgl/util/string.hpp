#pragma once

#include <string>
#include <cstdlib>
#include <type_traits>
#include <exception>

// Polyfill needed by Qt when building for Android with GCC
#if defined(__ANDROID__) && defined(__GLIBCXX__)

namespace std {

inline int stoi(const std::string &str)
{
    return atoi(str.c_str());
}

inline float stof(const std::string &str) {
    return static_cast<float>(atof(str.c_str()));
}

} // namespace std

#endif

namespace mbgl {
namespace util {

std::string toString(int64_t);
std::string toString(uint64_t);
std::string toString(int32_t);
std::string toString(uint32_t);
std::string toString(double, bool decimal = false);

inline std::string toString(int16_t t) {
    return toString(static_cast<int32_t>(t));
}

inline std::string toString(uint16_t t) {
    return toString(static_cast<uint32_t>(t));
}

inline std::string toString(int8_t t) {
    return toString(static_cast<int32_t>(t));
}

inline std::string toString(uint8_t t) {
    return toString(static_cast<uint32_t>(t));
}

#if !defined(__LP64__) || defined(__APPLE__)
// On 32-bit platforms or macOS, unsigned long may differ from uint64_t
inline std::string toString(unsigned long t) {
    return toString(static_cast<uint64_t>(t));
}
#endif

#if !defined(__LP64__)
// On 32-bit platforms, unsigned long long may differ from uint64_t
inline std::string toString(unsigned long long t) {
    return toString(static_cast<uint64_t>(t));
}
#endif

#if defined(_MSC_VER) || (!defined(__LP64__) && !defined(__APPLE__))
// On Windows or some 32-bit platforms, long long may differ from int64_t
inline std::string toString(long long t) {
    return toString(static_cast<int64_t>(t));
}
#endif

inline std::string toString(float t, bool decimal = false) {
    return toString(static_cast<double>(t), decimal);
}

inline std::string toString(long double t, bool decimal = false) {
    return toString(static_cast<double>(t), decimal);
}

std::string toString(const std::exception_ptr &);

template <class T>
std::string toString(T) = delete;

std::string toHex(uint32_t);
std::string toHex(uint64_t);

inline float stof(const std::string& str) {
    return std::stof(str);
}

} // namespace util
} // namespace mbgl

// Android's libstdc++ doesn't have std::to_string()
#if defined(__ANDROID__) && defined(__GLIBCXX__)

namespace std {

template <typename T>
inline std::string to_string(T value) {
    return mbgl::util::toString(value);
}

} // namespace std

#endif
