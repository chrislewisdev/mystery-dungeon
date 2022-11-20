#pragma once

#include "Core/Vec2.h"

class Rect2 {
    public:
        Vec2 location, size;
        Rect2() : location(0, 0), size(0, 0) {}
        Rect2(Vec2 location, Vec2 size): location(location), size(size) {}
        int left() { return location.x; }
        int right() { return location.x + size.x; }
        int top() { return location.y; }
        int bottom() { return location.y + size.y; }
        bool intersects(Rect2& other) {
            return (this->left() < other.right() && this->right() > other.left()
                && this->top() > other.bottom() && this->bottom() < other.top());
        }
};
