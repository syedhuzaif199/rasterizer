#include "Vector.h"
#include <cmath>
#include <string>
#include <ostream>

namespace utils {
    Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    Vector3::Vector3(float s) : x(s), y(s), z(s) {}
    Vector3::Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}
    Vector3::Vector3(std::initializer_list<float> values) {
        if (values.size() == 3) {
            auto it = values.begin();
            x = *it++;
            y = *it++;
            z = *it;
        } else {
            x = y = z = 0.0f; // Default to zero vector if not exactly 3 values
        }
    }

    Vector3& Vector3::operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;   
    }

    Vector3& Vector3::operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;   
    }

    Vector3& Vector3::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;   
    }

    Vector3& Vector3::operator/=(float scalar) {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }
        return *this;   
    }

    Vector3 Vector3::operator-() const {
        return Vector3(-x, -y, -z);   
    }

    bool Vector3::operator==(const Vector3& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    bool Vector3::operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    Vector3 Vector3::operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    Vector3 Vector3::operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    Vector3 Vector3::operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }
    Vector3 Vector3::operator/(float scalar) const {
        if (scalar != 0.0f) {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }
        return Vector3(); // Return a zero vector if division by zero
    }

    float& Vector3::operator[](int index) {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("Index out of range for Vector3");
        }
    }

    const float& Vector3::operator[](int index) const {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            throw std::out_of_range("Index out of range for Vector3");
        }
    }

    float Vector3::length() const {
        return sqrt(x * x + y * y + z * z);
    }

    float Vector3::dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    void Vector3::normalize() {
        float len = length();
        if (len > 0.0f) {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    Vector3 Vector3::normalized() const {
        float len = length();
        if (len > 0.0f) {
            return Vector3(x / len, y / len, z / len);
        }
        return Vector3(); // Return a zero vector if length is zero
    }

    Vector3 Vector3::cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    Vector3 operator*(float scalar, const Vector3& vec) {
        return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    float Vector3::dot(const Vector3& a, const Vector3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
        return Vector3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    std::string Vector3::toString() const {
        return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
    std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
        os << vec.toString();
        return os;
    }


    Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4::Vector4(const Vector3& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {}
    Vector4::Vector4(float s) : x(s), y(s), z(s), w(s) {}
    Vector4::Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}
    Vector4& Vector4::operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;   
    }
    Vector4& Vector4::operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;   
    }
    Vector4& Vector4::operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;   
    }
    Vector4& Vector4::operator/=(float scalar) {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
        }
        return *this;   
    }

    Vector4 Vector4::operator-() {
        return Vector4(-x, -y, -z, -w);
    }
    bool Vector4::operator==(const Vector4& other) const {
        return (x == other.x && y == other.y && z == other.z && w == other.w);
    }
    bool Vector4::operator!=(const Vector4& other) const {
        return !(*this == other);
    }
    Vector4 Vector4::operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    Vector4 Vector4::operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    Vector4 Vector4::operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }
    Vector4 Vector4::operator/(float scalar) const {
        if (scalar != 0.0f) {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        return Vector4(); // Return a zero vector if division by zero
    }

    float& Vector4::operator[](int index) {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw std::out_of_range("Index out of range for Vector3");
            break;
        }
    }

    const float& Vector4::operator[](int index) const {
        switch (index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            throw std::out_of_range("Index out of range for Vector3");
            break;
        }
    }

    float Vector4::length() const {
        return sqrt(x * x + y * y + z * z + w * w);
    }
    float Vector4::dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    Vector4 Vector4::cross(const Vector4& other) const {
        return Vector4(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
            0.0f // w component is not defined for cross product
        );
    }
    float Vector4::dot(const Vector4& a, const Vector4& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    void Vector4::normalize() {
        float len = length();
        if (len > 0.0f) {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    }

    Vector4 Vector4::normalized() const {
        float len = length();
        if(len > 0.0f) {
            return Vector4(x/len, y/len, z/len, w/len);
        }
        return Vector4();
    }
    Vector4 Vector4::cross(const Vector4& a, const Vector4& b) {
        return Vector4(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
            0.0f // w component is not defined for cross product
        );
    }
    std::string Vector4::toString() const {
        return "Vector4(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
    }
    std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
        os << vec.toString();
        return os;
    }
}