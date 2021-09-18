#pragma once

#include <vector>

#define GOOGLE_STRIP_LOG 2

namespace blink {

struct NullStream {};

constexpr NullStream nullStream;

template<class T>
const NullStream& operator<<(const NullStream& nullStream, const T&) {
    return nullStream;
}

template<class T>
const NullStream& operator<<(const NullStream& nullStream, T[]) {
    return nullStream;
}

template<class T>
const NullStream& operator<<(const NullStream& nullStream, const T*) {
    return nullStream;
}

}  // namespace blink

#define LOG(level) blink::nullStream
