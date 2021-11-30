#ifndef _VECTOR_H
#define _VECTOR_H


class Vec2D {
private:
    int x;
    int y;
public:
    Vec2D(int x, int y);
    ~Vec2D() = default;
    Vec2D(const Vec2D&) = default;
    Vec2D& operator=(const Vec2D&) = default;
    bool operator==(Vec2D v);
    bool operator>(Vec2D v);
    bool operator>=(Vec2D v);
    bool operator<(Vec2D v);
    bool operator<=(Vec2D v);
    void updateX(int new_x);
    void updateY(int new_y);
};


#endif //_VECTOR_H
