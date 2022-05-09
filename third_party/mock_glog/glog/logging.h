#pragma once

#include <vector>

#define GOOGLE_STRIP_LOG 2

namespace fakelog {

struct NullStream {};

constexpr NullStream nullStream;

template<class T>
const NullStream& operator<<(const NullStream& ns, const T&) {
    return ns;
}

template<class T>
const NullStream& operator<<(const NullStream& ns, T[]) {
    return ns;
}

template<class T>
const NullStream& operator<<(const NullStream& ns, const T*) {
    return ns;
}

}  // namespace fakelog

#define LOG(level) fakelog::nullStream
