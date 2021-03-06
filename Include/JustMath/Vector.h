#pragma once

#include <iostream>
#include <cassert>
#include <initializer_list>
#include <cmath>
#include <algorithm>

//通用矢量模板
//------------------------------------------
template<size_t N, typename T>
struct Vector {
    T data[N];

    //默认构造函数
    inline Vector() {
        for (size_t i = 0; i < N; i++)
            data[i] = T();
    }

    //构造函数：数组指针
    inline Vector(const T *ptr) {
        for (size_t i = 0; i < N; i++)
            data[i] = ptr[i];
    }

    //拷贝构造函数
    inline Vector(const Vector<N, T> &v) {
        for (size_t i = 0; i < N; i++)
            data[i] = v.data[i];
    }

    //构造函数：初始化列表
    inline Vector(const std::initializer_list<T> &v) {
        auto it = v.begin();
        for (size_t i = 0; i < N; i++)
            data[i] = *it++;
    }

    //索引操作符重载函数
    inline const T &operator[](size_t i) const {
        assert(i < N);
        return data[i];
    }

    inline T &operator[](size_t i) {
        assert(i < N);
        return data[i];
    }
};

//特化二维矢量
//------------------------------------------
template<typename T>
struct Vector<2, T> {
    union {
        struct {
            T x, y;
        };
        struct {
            T u, v;
        };
        struct {
            T s, t;
        };
        struct {
            T left, right;
        };
        T data[2];
    };

    inline Vector() : x(T()), y(T()) {}

    inline Vector(T _value) : x(_value), y(_value) {}

    inline Vector(T _x, T _y) : x(_x), y(_y) {}

    inline Vector(const Vector<2, T> &v) : x(v.x), y(v.y) {}

    inline Vector(const T *ptr) : x(ptr[0]), y(ptr[1]) {}

    inline const T &operator[](size_t i) const {
        assert(i < 2);
        return data[i];
    }

    inline T &operator[](size_t i) {
        assert(i < 2);
        return data[i];
    }
};

//特化三维矢量
//------------------------------------------
template<typename T>
struct Vector<3, T> {
    union {
        struct {
            T x, y, z;
        };
        struct {
            T r, g, b;
        };
        T data[3];
    };

    inline Vector() : x(T()), y(T()), z(T()) {}

    inline Vector(T _value) : x(_value), y(_value), z(_value) {}

    inline Vector(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    inline Vector(const Vector<3, T> &v) : x(v.x), y(v.y), z(v.z) {}

    inline Vector(const T *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}

    inline const T &operator[](size_t i) const {
        assert(i < 3);
        return data[i];
    }

    inline T &operator[](size_t i) {
        assert(i < 3);
        return data[i];
    }

    inline Vector<2, T> Get2D() const{
        return Vector<2, T>(x, y);
    }

    inline Vector<4, T> Get4D() const{
        return Vector<4, T>(x, y, z, 1);
    }
};

//特化四维矢量
//------------------------------------------
template<typename T>
struct Vector<4, T> {
    union {
        struct {
            T x, y, z, w;
        };
        struct {
            T r, g, b, a;
        };
        T data[4];
    };

    inline Vector() : x(T()), y(T()), z(T()), w(T()) {}

    inline Vector(T _value) : x(_value), y(_value), z(_value), w(_value) {}

    inline Vector(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}

    inline Vector(const Vector<4, T> &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

    inline Vector(const T *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3]) {}

    inline const T &operator[](size_t i) const {
        assert(i < 4);
        return data[i];
    }

    inline T &operator[](size_t i) {
        assert(i < 4);
        return data[i];
    }
    inline Vector<2, T> Get2D() const {
        return Vector<2, T>(x, y);
    }

    inline Vector<3, T> Get3D() const {
        return Vector<3, T>(x, y, z);
    }
};

//矢量运算
//------------------------------------------
//+a
template<size_t N, typename T>
inline Vector<N, T> operator+(const Vector<N, T> &a) {
    return a;
}

//-a
template<size_t N, typename T>
inline Vector<N, T> operator-(const Vector<N, T> &a) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = -a[i];
    return temp;

}

//a==b
template<size_t N, typename T>
inline bool operator==(const Vector<N, T> &a, const Vector<N, T> &b) {
    for (size_t i = 0; i < N; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

//a!=b
template<size_t N, typename T>
inline bool operator!=(const Vector<N, T> &a, const Vector<N, T> &b) {
    return !(a == b);
}

//a+b
template<size_t N, typename T>
inline Vector<N, T> operator+(const Vector<N, T> &a, const Vector<N, T> &b) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] + b[i];
    return temp;
}

//a+k
template<size_t N, typename T>
inline Vector<N, T> operator+(const Vector<N, T> &a, T k) {
    Vector<N, T> temp(k);
    for (size_t i = 0; i < N; i++)
        temp[i] += a[i];
    return temp;
}

//k+a
template<size_t N, typename T>
inline Vector<N, T> operator+(T k, const Vector<N, T> &a) {
    Vector<N, T> temp(k);
    for (size_t i = 0; i < N; i++)
        temp[i] += a[i];
    return temp;
}

//a-b
template<size_t N, typename T>
inline Vector<N, T> operator-(const Vector<N, T> &a, const Vector<N, T> &b) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] - b[i];
    return temp;
}

//a-k
template<size_t N, typename T>
inline Vector<N, T> operator-(const Vector<N, T> &a, T k) {
    Vector<N, T> temp(k);
    for (size_t i = 0; i < N; i++)
        a[i] -= temp[i];
    return temp;
}

//k-a
template<size_t N, typename T>
inline Vector<N, T> operator-(T k, const Vector<N, T> &a) {
    Vector<N, T> temp(k);
    for (size_t i = 0; i < N; i++)
        temp[i] -= a[i];
    return temp;
}

//a*b
template<size_t N, typename T>
inline Vector<N, T> operator*(const Vector<N, T> &a, const Vector<N, T> &b) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] * b[i];
    return temp;
}

//a/b
template<size_t N, typename T>
inline Vector<N, T> operator/(const Vector<N, T> &a, const Vector<N, T> &b) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] / b[i];
    return temp;
}

//a*k
template<size_t N, typename T>
inline Vector<N, T> operator*(const Vector<N, T> &a, T k) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] * k;
    return temp;
}

//k*a
template<size_t N, typename T>
inline Vector<N, T> operator*(T k, const Vector<N, T> &a) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] * k;
    return temp;
}

//a/k
template<size_t N, typename T>
inline Vector<N, T> operator/(const Vector<N, T> &a, T k) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = a[i] / k;
    return temp;
}

//k/a
template<size_t N, typename T>
inline Vector<N, T> operator/(T k, const Vector<N, T> &a) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = k / a[i];
    return temp;
}

//a+=b
template<size_t N, typename T>
inline Vector<N, T> operator+=(Vector<N, T> &a, const Vector<N, T> &b) {
    for (size_t i = 0; i < N; i++)
        a[i] += b[i];
    return a;
}

//a-=b
template<size_t N, typename T>
inline Vector<N, T> operator-=(Vector<N, T> &a, const Vector<N, T> &b) {
    for (size_t i = 0; i < N; i++)
        a[i] -= b[i];
    return a;
}

//a*=b
template<size_t N, typename T>
inline Vector<N, T> operator*=(Vector<N, T> &a, const Vector<N, T> &b) {
    for (size_t i = 0; i < N; i++)
        a[i] *= b[i];
    return a;
}

//a/=b
template<size_t N, typename T>
inline Vector<N, T> operator/=(Vector<N, T> &a, const Vector<N, T> &b) {
    for (size_t i = 0; i < N; i++)
        a[i] /= b[i];
    return a;
}

//a*=k
template<size_t N, typename T>
inline Vector<N, T> operator*=(Vector<N, T> &a, T k) {
    for (size_t i = 0; i < N; i++)
        a[i] *= k;
    return a;
}

//a/=k
template<size_t N, typename T>
inline Vector<N, T> operator/=(Vector<N, T> &a, T k) {
    for (size_t i = 0; i < N; i++)
        a[i] /= k;
    return a;
}

//矢量函数
//------------------------------------------
template<size_t N, typename T>
inline T SquareLength(const Vector<N, T> &a) {
    T sum = 0;
    for (size_t i = 0; i < N; i++)
        sum += a[i] * a[i];
    return sum;
}

//矢量长度
template<size_t N, typename T>
inline T Length(const Vector<N, T> &a) {
    return std::sqrt(SquareLength(a));
}

//特化float类型开方
template<size_t N>
inline float Length(const Vector<N, float> &a) {
    return std::sqrtf(SquareLength(a));
}

//矢量取模（长度的别名）
template<size_t N, typename T>
inline T Norm(const Vector<N, T> &a) {
    return std::sqrt(SquareLength(a));
}

//特化float类型开方
template<size_t N>
inline float Norm(const Vector<N, float> &a) {
    return std::sqrtf(SquareLength(a));
}

//矢量归一化
template<size_t N, typename T>
inline Vector<N, T> Normalize(const Vector<N, T> &a) {
    return a / Length(a);
}

//矢量点乘
template<size_t N, typename T>
inline T Dot(const Vector<N, T> &a, const Vector<N, T> &b) {
    T sum = 0;
    for (size_t i = 0; i < N; i++)
        sum += a[i] * b[i];
    return sum;
}

//二维矢量叉乘得标量
template<typename T>
inline T Cross(const Vector<2, T> &a, const Vector<2, T> &b) {
    return a.x * b.y - a.y - b.y;
}

//三维矢量叉乘得垂直于两矢量得新矢量
template<typename T>
inline Vector<3, T> Cross(const Vector<3, T> &a, const Vector<3, T> &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

//四维矢量叉乘仅当做三维矢量进行计算，w保留
template<typename T>
inline Vector<4, T> Cross(const Vector<4, T> &a, const Vector<4, T> &b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, a.w};
}

//转换到世界坐标系
template<typename T>
inline Vector<3, T> ToWorld(const Vector<3, T> &a, const Vector<3, T> &n) {
    //施密特标准正交化
    auto N = Normalize(n);
    auto temp = std::fabs(n.x) > .1 ? Vector<3, T>(0., 1., 0.) : Vector<3, T>(1., 0., 0.);
    auto U = Normalize(temp - Dot(temp, N) * N);
    auto V = Cross(N, U);
    return a.x * U + a.y * V + a.z * N;
}

//选取两矢量中最大的值组成新的矢量
template<size_t N, typename T>
inline Vector<N, T> MaxVector(const Vector<N, T> &a, const Vector<N, T> &b) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = (a[i] > b[i]) ? a[i] : b[i];

    return temp;
}

//选取两矢量中最小的值组成新的矢量
template<size_t N, typename T>
inline Vector<N, T> MinVector(const Vector<N, T> &a, const Vector<N, T> &b) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = (a[i] < b[i]) ? a[i] : b[i];

    return temp;
}

//线性插值
template<size_t N, typename T>
inline Vector<N, T> MixVector(const Vector<N, T> &a, const Vector<N, T> &b, float t) {
    Vector<N, T> temp;
    for (size_t i = 0; i < N; i++)
        temp[i] = (1.0f - t) * a[i] + t * b[i];

    return temp;
}

//获取矢量中最大的值
template<size_t N, typename T>
inline T MaxValue(const Vector<N, T> &a) {
    T temp;
    for (size_t i = 0; i < N - 1; i++)
        temp = a[i] > a[i + 1] ? a[i] : a[i + 1];
    return temp;
}

//获取矢量中最小的值
template<size_t N, typename T>
inline T MinValue(const Vector<N, T> &a) {
    T temp;
    for (size_t i = 0; i < N - 1; i++)
        temp = a[i] < a[i + 1] ? a[i] : a[i + 1];
    return temp;
}

//获取矢量中最小的值
template<size_t N, typename T>
inline void SwapVector(Vector<N, T> &a, Vector<N, T> &b) {
    for (size_t i = 0; i < N; i++) {
        T temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

//获取矢量中最小的值
template<typename T>
inline void SwapValue(Vector<2, T> &a) {
    T temp = a.x;
    a.x = a.y;
    a.y = temp;
}

// 输出到文本流
template<size_t N, typename T>
inline std::ostream &operator<<(std::ostream &stream, const Vector<N, T> &a) {
    stream << "[";
    for (size_t i = 0; i < N; i++) {
        stream << a[i];
        if (i < N - 1) stream << ", ";
    }
    stream << "]";
    return stream;
}

template<size_t N, typename T>
inline Vector<N,T> ClampVector(const Vector<N, T> &a, T left, T right) {
    Vector<N,T> temp;
    for (size_t i = 0; i < N; i++) {
        temp[i] = std::clamp(a[i],left,right);
    }
    return temp;
}

//特化矢量别名
//------------------------------------------
typedef Vector<4, float> Vector4f;
typedef Vector<4, float> Point4f;

typedef Vector<3, float> Vector3f;
typedef Vector<3, float> Point3f;
typedef Vector<3, float> Color3f;
typedef Vector<3, float> Float3f;

typedef Vector<2, float> Vector2f;
typedef Vector<2, float> Point2f;
typedef Vector<2, float> Range2f;
typedef Vector<2, float> Float2f;

typedef Vector<3, int> Vector3i;
typedef Vector<3, int> Color3i;
typedef Vector<2, int> Point2i;
typedef Vector<2, int> Int2;

typedef Vector<3, Vector<3, int>> Face3i;







