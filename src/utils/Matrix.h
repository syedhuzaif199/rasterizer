#pragma once
#include "Vector.h"
#include <string>
#include <ostream>
namespace utils {
    class Matrix4 {
    public:
        Matrix4();
        Matrix4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33);
        Matrix4(float s);
        Matrix4(const Vector4& col1, const Vector4& col2, const Vector4& col3, const Vector4& col4);
        Matrix4(const Matrix4& other);

        Matrix4& operator+=(const Matrix4& other);
        Matrix4& operator-=(const Matrix4& other);
        Matrix4& operator*=(const Matrix4& other);
        Matrix4& operator*=(float scalar);
        bool operator==(const Matrix4& other) const;
        bool operator!=(const Matrix4& other) const;
        Matrix4 operator+(const Matrix4& other) const;
        Matrix4 operator-(const Matrix4& other) const;
        Matrix4 operator*(const Matrix4& other) const;
        Matrix4 operator*(float scalar) const;
        Vector4 operator*(const Vector4& vec) const;
        Vector4 getColumn(int index) const;
        Vector4 getRow(int index) const;
        Matrix4 transpose() const;
        Matrix4 quickInverse() const;
        static Matrix4 identity();

        Matrix4 rotationX(float angle);
        Matrix4 rotationY(float angle);
        Matrix4 rotationZ(float angle);
        Matrix4 translation(float x, float y, float z);
        Matrix4 translation(const Vector3& vec);

        std::string toString() const;
        friend std::ostream& operator<<(std::ostream& os, const Matrix4& mat);

    private:
        float m[16];
    };
}