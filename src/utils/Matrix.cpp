#include "Matrix.h"
#include <cmath>
#include <string>

namespace utils
{
    Matrix4::Matrix4()
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] = (i % 5 == 0) ? 1.0f : 0.0f; // Identity matrix
        }
    }

    Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                     float m10, float m11, float m12, float m13,
                     float m20, float m21, float m22, float m23,
                     float m30, float m31, float m32, float m33)
    {
        m[0] = m00;
        m[1] = m01;
        m[2] = m02;
        m[3] = m03;
        m[4] = m10;
        m[5] = m11;
        m[6] = m12;
        m[7] = m13;
        m[8] = m20;
        m[9] = m21;
        m[10] = m22;
        m[11] = m23;
        m[12] = m30;
        m[13] = m31;
        m[14] = m32;
        m[15] = m33;
    }

    Matrix4::Matrix4(float s)
    {
        for (int i = 0; i < 16; ++i)
        {
            if (i % 5 == 0)
            {
                m[i] = s;
            }
            else
            {
                m[i] = 0.0f;
            }
        }
    }

    Matrix4::Matrix4(const Vector4 &col1, const Vector4 &col2, const Vector4 &col3, const Vector4 &col4)
    {
        for (int i = 0; i < 4; ++i)
        {
            m[i * 4 + 0] = col1[i];
            m[i * 4 + 1] = col2[i];
            m[i * 4 + 2] = col3[i];
            m[i * 4 + 3] = col4[i];
        }
    }

    Matrix4::Matrix4(const Matrix4 &other)
    {
        for (int i = 0; i < 16; ++i)
        {
            this->m[i] = other.m[i];
        }
    }

    Matrix4 &Matrix4::operator+=(const Matrix4 &other)
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] += other.m[i];
        }
        return *this;
    }
    Matrix4 &Matrix4::operator-=(const Matrix4 &other)
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] -= other.m[i];
        }
        return *this;
    }
    Matrix4 &Matrix4::operator*=(const Matrix4 &other)
    {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.m[i * 4 + j] = m[i * 4 + 0] * other.m[0 * 4 + j] +
                                      m[i * 4 + 1] * other.m[1 * 4 + j] +
                                      m[i * 4 + 2] * other.m[2 * 4 + j] +
                                      m[i * 4 + 3] * other.m[3 * 4 + j];
            }
        }
        *this = result;
        return *this;
    }
    Matrix4 &Matrix4::operator*=(float scalar)
    {
        for (int i = 0; i < 16; ++i)
        {
            m[i] *= scalar;
        }
        return *this;
    }
    bool Matrix4::operator==(const Matrix4 &other) const
    {
        for (int i = 0; i < 16; ++i)
        {
            if (m[i] != other.m[i])
                return false;
        }
        return true;
    }
    bool Matrix4::operator!=(const Matrix4 &other) const
    {
        return !(*this == other);
    }
    Matrix4 Matrix4::operator+(const Matrix4 &other) const
    {
        Matrix4 result;
        for (int i = 0; i < 16; ++i)
        {
            result.m[i] = m[i] + other.m[i];
        }
        return result;
    }
    Matrix4 Matrix4::operator-(const Matrix4 &other) const
    {
        Matrix4 result;
        for (int i = 0; i < 16; ++i)
        {
            result.m[i] = m[i] - other.m[i];
        }
        return result;
    }
    Matrix4 Matrix4::operator*(const Matrix4 &other) const
    {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.m[i * 4 + j] = m[i * 4 + 0] * other.m[0 * 4 + j] +
                                      m[i * 4 + 1] * other.m[1 * 4 + j] +
                                      m[i * 4 + 2] * other.m[2 * 4 + j] +
                                      m[i * 4 + 3] * other.m[3 * 4 + j];
            }
        }
        return result;
    }
    Matrix4 Matrix4::operator*(float scalar) const
    {
        Matrix4 result;
        for (int i = 0; i < 16; ++i)
        {
            result.m[i] = m[i] * scalar;
        }
        return result;
    }
    Vector4 Matrix4::operator*(const Vector4 &vec) const
    {
        Vector4 result;
        result.x = m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.w;
        result.y = m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.w;
        result.z = m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] * vec.w;
        result.w = m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w;
        return result;
    }
    Vector4 Matrix4::getColumn(int index) const
    {
        return Vector4(m[index], m[index + 4], m[index + 8], m[index + 12]);
    }
    Vector4 Matrix4::getRow(int index) const
    {
        return Vector4(m[index * 4], m[index * 4 + 1], m[index * 4 + 2], m[index * 4 + 3]);
    }
    Matrix4 Matrix4::transpose() const
    {
        Matrix4 result;
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                result.m[i * 4 + j] = m[j * 4 + i];
            }
        }
        return result;
    }

    Matrix4 Matrix4::quickInverse() const
    {
        Matrix4 result;
        result.m[0] = m[0];
        result.m[1] = m[4];
        result.m[2] = m[8];
        result.m[3] = 0.0f;
        result.m[4] = m[1];
        result.m[5] = m[5];
        result.m[6] = m[9];
        result.m[7] = 0.0f;
        result.m[8] = m[2];
        result.m[9] = m[6];
        result.m[10] = m[10];
        result.m[11] = 0.0f;
        result.m[12] = -(m[12] * m[0] + m[13] * m[1] + m[14] * m[2]);
        result.m[13] = -(m[12] * m[4] + m[13] * m[5] + m[14] * m[6]);
        result.m[14] = -(m[12] * m[8] + m[13] * m[9] + m[14] * m[10]);
        result.m[15] = 1.0f;
        return result;
    }

    Matrix4 Matrix4::identity()
    {
        return Matrix4(1.0f);
    }

    Matrix4 Matrix4::rotationX(float angle)
    {
        float c = cos(angle);
        float s = sin(angle);
        return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, c, -s, 0.0f,
                       0.0f, s, c, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::rotationY(float angle)
    {
        float c = cos(angle);
        float s = sin(angle);
        return Matrix4(c, 0.0f, s, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       -s, 0.0f, c, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::rotationZ(float angle)
    {
        float c = cos(angle);
        float s = sin(angle);
        return Matrix4(c, -s, 0.0f, 0.0f,
                       s, c, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::translation(float x, float y, float z)
    {
        return Matrix4(1.0f, 0.0f, 0.0f, x,
                       0.0f, 1.0f, 0.0f, y,
                       0.0f, 0.0f, 1.0f, z,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::translation(const Vector3 &vec)
    {
        return translation(vec.x, vec.y, vec.z);
    }

    Matrix4 Matrix4::projection(float fovDegrees, int screenWidth, int screenHeight, float zNear, float zFar)
    {
        float aspectRatio = static_cast<float>(screenWidth) / screenHeight;
        float tanFovInv = 1.0f / tan(fovDegrees * M_PI / 360.0f);
        Matrix4 matrix = Matrix4(0.0f);
        matrix.m[0] = tanFovInv / aspectRatio;
        matrix.m[5] = tanFovInv;
        matrix.m[10] = (zFar + zNear) / (zFar - zNear);
        matrix.m[11] = -2 * zNear * zFar / (zFar - zNear);
        matrix.m[14] = -1.0f;
        return matrix;
    }

    std::string Matrix4::toString() const
    {
        std::string result = "Matrix4(\n";
        for (int i = 0; i < 4; ++i)
        {
            result += "  [";
            for (int j = 0; j < 4; ++j)
            {
                result += std::to_string(m[i * 4 + j]);
                if (j < 3)
                    result += ", ";
            }
            result += "]\n";
        }
        result += ")";
        return result;
    }

    std::ostream &operator<<(std::ostream &os, const Matrix4 &mat)
    {
        os << mat.toString();
        return os;
    }

}