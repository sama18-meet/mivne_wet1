#include "Vec2D.h"
#include <iostream>
using namespace std;

Vec2D::Vec2D(int x, int y) : x(x), y(y) {}

bool Vec2D::operator==(const Vec2D& v) const {
    return this->x == v.x && this->y == v.y;
}

bool Vec2D::operator>(const Vec2D& v) const {
    return this->x > v.x || (this->x == v.x && this->y < v.y);
}

bool Vec2D::operator>=(const Vec2D& v) const {
    return *this == v || *this > v;
}

bool Vec2D::operator<(const Vec2D& v) const {
    return !(*this>=v);
}

bool Vec2D::operator<=(const Vec2D& v) const {
    return !(*this>v);
}

void Vec2D::updateX(int new_x) {
    this->x = new_x;
}
void Vec2D::updateY(int new_y) {
    this->y = new_y;
}
