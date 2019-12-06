#ifndef D_VERTEX_H_
#define D_VERTEX_H_

#include <iostream>

template<class T>
struct vertex {
    T x, y;
};

template<class T>
std::istream& operator>> (std::istream& is, vertex<T>& v){
    is >> v.x >> v.y;
    return is;
}

template<class T>
std::ostream& operator<< (std::ostream& os, const vertex<T>& v){
    os << "(" << v.x << ", " << v.y << ") ";
    return os;
}

template<class T>
vertex<T> operator+ (const vertex<T> lhs,const vertex<T> rhs){
    vertex<T> res;
    res.x = lhs.x + rhs.x;
    res.y = lhs.y + rhs.y;
    return res;
}

template<class T>
vertex<T> operator/ (const vertex<T> vert, const int num) {
    vertex<T> res;
    res.x = vert.x / num;
    res.y = vert.y / num;
    return res;
}

#endif