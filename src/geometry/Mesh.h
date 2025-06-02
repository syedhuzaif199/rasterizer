#pragma once
#include <vector>
#include "Vector.h"
#include <string>
namespace geometry {
    struct Triangle {
        int i0, i1, i2;
        Triangle() : i0(-1), i1(-1), i2(-1) {}
        Triangle(int index0, int index1, int index2) : i0(index0), i1(index1), i2(index2) {}
    };

    class Mesh {
    public:
        Mesh();
        Mesh(const std::vector<utils::Vector3>& vertices, const std::vector<Triangle>& faces);
        Mesh(const Mesh& other);
        Mesh(const std::string& filename);
        ~Mesh();

        const std::vector<utils::Vector3>& getVertices() const;
        const utils::Vector3& getVertex(int index) const;
        const std::vector<Triangle>& getFaces() const;

        // primitive meshes
        static Mesh box(float width = 1.0f, float height = 1.0f, float depth = 1.0f);
        static Mesh sphere(float radius = 1.0f, int segments = 16, int rings = 16);
        static Mesh plane(float width = 1.0f, float length = 1.0f, int widthSegments = 1, int lengthSegments = 1);
        static Mesh cylinder(float radius = 1.0f, float height = 1.0f, int segments = 16);

        bool loadFromFile(const std::string& filename);
        bool saveToOBJFile(const std::string& filename);
        static Mesh loadFromFileStatic(const std::string& filename);

    private:
        std::vector<utils::Vector3> vertices;
        std::vector<Triangle> faces;
    };


}