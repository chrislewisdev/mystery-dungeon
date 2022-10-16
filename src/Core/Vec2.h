#pragma once

struct Vec2 {
    int x, y;
    Vec2() {}
    Vec2(int x, int y): x(x), y(y) {}
    Vec2 operator+(const Vec2& other) const {
        return Vec2(this->x + other.x, this->y + other.y);
    }
    Vec2 operator-(const Vec2& other) const {
        return Vec2(this->x - other.x, this->y - other.y);
    }
    Vec2 operator*(int multiplier) const {
        return Vec2(this->x * multiplier, this->y * multiplier);
    }
    Vec2 operator/(int divisor) const {
        return Vec2(this->x / divisor, this->y / divisor);
    }
};