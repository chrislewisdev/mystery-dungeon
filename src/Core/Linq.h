#pragma once

#include <vector>
#include <functional>

template <class T> bool any(const std::vector<T>& list, std::function<bool(const T&)> predicate) {
    for (const T& item : list) {
        if (predicate(item)) return true;
    }
    return false;
}

template <class T> std::vector<T> filter(const std::vector<T>& list, std::function<bool(const T&)> f) {
    std::vector<T> result;
    copy_if(list.begin(), list.end(), back_inserter(result), f);
    return result;
}

template <class T> std::tuple<std::vector<T>, std::vector<T>> split(const std::vector<T>& list, std::function<bool(const T&)> f) {
    std::vector<T> pass, fail;
    for (const T& item : list) {
        if (f(item))    pass.push_back(item);
        else            fail.push_back(item);
    }
    return make_tuple(pass, fail);
}

template <typename T, typename O> std::vector<O> select(const std::vector<T>& list, std::function<O(const T&)> f) {
    std::vector<O> result;
    result.reserve(list.size());
    
    for (const T& item : list) {
        result.push_back(f(item));
    }

    return result;
}

template <class T> bool contains(const std::vector<T>& list, const T& item) {
    return find(list.begin(), list.end(), item) != list.end();
}
