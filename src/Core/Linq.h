#pragma once

#include <vector>
#include <functional>

template <class T> bool any(const std::vector<T>& list, std::function<bool(const T&)> predicate) {
    for (const T& item : list) {
        if (predicate(item)) return true;
    }
    return false;
}
