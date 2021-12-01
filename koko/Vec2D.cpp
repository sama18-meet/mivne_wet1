#include "Vec2D.h"


Vec2D::Vec2D(int x, int y) : x(x), y(y) {}

bool Vec2D::operator==(Vec2D v) {
    return this->x == v.x && this->y == v.y;
}

bool Vec2D::operator>(Vec2D v) {
    return this->x > v.x || (this->x == v.x && this->y > v.y);
}

bool Vec2D::operator>=(Vec2D v) {
    return *this == v || *this > v;
}

bool Vec2D::operator<(Vec2D v) {
    return !(*this>=v);
}

bool Vec2D::operator<=(Vec2D v) {
    return !(*this>v);
}

void Vec2D::updateX(int new_x) {
    this->x = new_x;
}
void Vec2D::updateY(int new_y) {
    this->y = new_y;
}

