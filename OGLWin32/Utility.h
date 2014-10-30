#pragma once

#include <iostream>
#include <sstream>

template<typename T>
void _DebugInner(std::stringstream& ss, T const& arg) {
    ss << arg << std::endl;
}

template<typename T, typename... Args>
void _DebugInner(std::stringstream& ss, T const& first, Args&&... rest) {
    ss << first << "\t";
    _DebugInner(ss, std::forward<Args>(rest)...);
}

template<typename... Args>
void Debug(Args&&... args) {
    std::stringstream ss;
    _DebugInner(ss, std::forward<Args>(args)...);
    std::cout << ss.rdbuf();
}
