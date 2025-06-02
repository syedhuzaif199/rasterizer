#pragma once
#include <string>
#include <ostream>
#include <initializer_list>
namespace utils
{
    class Vector3;
    class Vector2
    {
    public:
        float x, y;

        Vector2();
        Vector2(float x, float y);
        Vector2(float s);
        Vector2(const Vector2 &other);
        Vector2(std::initializer_list<float> values);

        Vector2 &operator+=(const Vector2 &other);
        Vector2 &operator-=(const Vector2 &other);
        Vector2 &operator*=(float scalar);
        Vector2 &operator/=(float scalar);
        Vector2 operator-() const;
        bool operator==(const Vector2 &other) const;
        bool operator!=(const Vector2 &other) const;
        Vector2 operator+(const Vector2 &other) const;
        Vector2 operator-(const Vector2 &other) const;
        Vector2 operator*(float scalar) const;
        Vector2 operator/(float scalar) const;

        float &operator[](int index);
        const float &operator[](int index) const;

        float length() const;
        float dot(const Vector2 &other) const;
        void normalize();
        Vector2 normalized() const;
        Vector3 cross(const Vector2 &other) const;

        static float dot(const Vector2 &a, const Vector2 &b);

        static Vector3 cross(const Vector2 &a, const Vector2 &b);

        // string representation for debugging
        std::string toString() const;
        friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec);
    };
    class Vector3
    {
    public:
        float x, y, z;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(float s);
        Vector3(const Vector3 &other);
        Vector3(std::initializer_list<float> values);

        Vector3 &operator+=(const Vector3 &other);
        Vector3 &operator-=(const Vector3 &other);
        Vector3 &operator*=(float scalar);
        Vector3 &operator/=(float scalar);
        Vector3 operator-() const;
        bool operator==(const Vector3 &other) const;
        bool operator!=(const Vector3 &other) const;
        Vector3 operator+(const Vector3 &other) const;
        Vector3 operator-(const Vector3 &other) const;
        Vector3 operator*(float scalar) const;
        Vector3 operator/(float scalar) const;

        float &operator[](int index);
        const float &operator[](int index) const;

        float length() const;
        float dot(const Vector3 &other) const;
        void normalize();
        Vector3 normalized() const;
        Vector3 cross(const Vector3 &other) const;

        static float dot(const Vector3 &a, const Vector3 &b);

        static Vector3 cross(const Vector3 &a, const Vector3 &b);

        // string representation for debugging
        std::string toString() const;
        friend std::ostream &operator<<(std::ostream &os, const Vector3 &vec);
    };

    Vector3 operator*(float scalar, const Vector3 &vector);

    class Vector4
    {
    public:
        float x, y, z, w;

        Vector4();
        Vector4(float x, float y, float z, float w);
        Vector4(const Vector3 &vec, float w = 1.0f);
        Vector4(float s);
        Vector4(const Vector4 &other);
        Vector4(std::initializer_list<float> values);

        Vector4 &operator+=(const Vector4 &other);
        Vector4 &operator-=(const Vector4 &other);
        Vector4 &operator*=(float scalar);
        Vector4 &operator/=(float scalar);
        Vector4 operator-();
        bool operator==(const Vector4 &other) const;
        bool operator!=(const Vector4 &other) const;
        Vector4 operator+(const Vector4 &other) const;
        Vector4 operator-(const Vector4 &other) const;
        Vector4 operator*(float scalar) const;
        Vector4 operator/(float scalar) const;

        float &operator[](int index);
        const float &operator[](int index) const;

        float length() const;
        float dot(const Vector4 &other) const;
        void normalize();
        Vector4 normalized() const;
        Vector4 cross(const Vector4 &other) const;

        static float dot(const Vector4 &a, const Vector4 &b);
        static Vector4 cross(const Vector4 &a, const Vector4 &b);

        // string representation for debugging
        std::string toString() const;
        friend std::ostream &operator<<(std::ostream &os, const Vector4 &vec);
    };
}