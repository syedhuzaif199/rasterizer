#include "Mesh.h"
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
namespace geometry {
    Mesh::Mesh() = default;
    Mesh::Mesh(const std::vector<utils::Vector3>& vertices, const std::vector<Triangle>& faces) : vertices(vertices), faces(faces) {}
    Mesh::Mesh(const Mesh& other) : vertices(other.vertices) {}
    Mesh::Mesh(const std::string& filename) {
        loadFromFile(filename);
    }
    Mesh::~Mesh() = default;

    Mesh Mesh::box(float width, float height, float depth) {
        std::vector<utils::Vector3> vertices = {
            utils::Vector3(-width / 2, -height / 2, -depth / 2),
            utils::Vector3(width / 2, -height / 2, -depth / 2),
            utils::Vector3(width / 2, height / 2, -depth / 2),
            utils::Vector3(-width / 2, height / 2, -depth / 2),
            utils::Vector3(-width / 2, -height / 2, depth / 2),
            utils::Vector3(width / 2, -height / 2, depth / 2),
            utils::Vector3(width / 2, height / 2, depth / 2),
            utils::Vector3(-width / 2, height / 2, depth / 2)
        };
        std::vector<Triangle> faces = {
            Triangle(4, 5, 6),
            Triangle(4, 6, 7),
            Triangle(5, 1, 2),
            Triangle(5, 2, 6),
            Triangle(7, 6, 2),
            Triangle(7, 2, 3),
            Triangle(1, 0, 2),
            Triangle(0, 3, 2),
            Triangle(0, 4, 7),
            Triangle(0, 7, 3),
            Triangle(4, 1, 5),
            Triangle(4, 0, 1)
        };

        return Mesh(vertices, faces);
    }

    Mesh Mesh::sphere(float radius, int segments, int rings) {
        if (rings < 2) {
            rings = 2;
        }
        if(segments < 3) {
            segments = 3;
        }
        int vertCount = segments * (rings - 1) + 2;
        std::vector<utils::Vector3> vertices(vertCount);
        const float phiInc = M_PI / rings;
        const float thetaInc = 2 * M_PI / segments;
        vertices[0] = utils::Vector3(0, radius, 0);
        int vertIdx = 1;
        for(int i = 1; i < rings; i++) {
            float phi = i * phiInc;
            for(int j = 0; j < segments; j++) {
                float theta = j * thetaInc;
                float y = radius * cosf(phi);
                float x = radius * sinf(phi) * cosf(theta);
                float z = radius * sinf(phi) * sinf(theta);
                vertices[vertIdx] = utils::Vector3(x, y, z);
                vertIdx++;
            }
        }
        vertices[vertCount-1] = utils::Vector3(0, -radius, 0);

        int faceCount = (rings-2) * segments * 2 + 2 * segments;
        std::vector<Triangle> faces(faceCount);
        int faceIdx = 0;
        for(int i = 0; i < rings - 2; i++) {
            int ring1 = i;
            int ring2 = i + 1;
            for(int j = 0; j < segments; j++) {
                int seg1 = j;
                int seg2 = (j + 1) % segments;
                int vert1 = ring1 * segments + seg1 + 1; // top right
                int vert2 = ring1 * segments + seg2 + 1; // top left
                int vert3 = ring2 * segments + seg1 + 1; // bottom right
                int vert4 = ring2 * segments + seg2 + 1; // bottom left
                faces[faceIdx++] = Triangle(vert1, vert2, vert4);
                faces[faceIdx++] = Triangle(vert4, vert3, vert1);
            }
        }

        // North Pole
        for(int i = 0; i < segments; i++) {
            int vert1 = 0; 
            int vert2 = i + 1;
            int vert3 = (i + 1) % segments + 1; // wrap around
            faces[faceIdx++] = Triangle(vert1, vert3, vert2);
        }

        // South Pole
        for(int i = 0; i < segments; i++) {
            int vert1 = vertCount-1;
            int vert2 = (rings - 2) * segments + i + 1;
            int vert3 = (rings - 2) * segments + (i + 1) % segments + 1; // wrap around
            faces[faceIdx++] = Triangle(vert1, vert2, vert3);
        }

        return Mesh(vertices, faces);

    }

    bool Mesh::loadFromFile(const std::string& filepath) {
        if (filepath.substr(filepath.find_last_of(".") + 1) == "obj") {
            std::cout << "Loading mesh from " << filepath << std::endl;

            // open the file


            return true;
        } 

        // other cases

        std::cerr << "Unsupported file format: " << filepath << std::endl;
        return false;
    }

    bool Mesh::saveToOBJFile(const std::string& filepath) {
        // open the file
        std::ofstream file(filepath);
        if(!file.is_open()) {
            std::cerr << "Failed to open file for writing: " << filepath << std::endl;
            return false;
        }

        // write vertices and faces to the file
        for (const auto& vertex : vertices) {
            file << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
        }
        for (const auto& face : faces) {
            file << "f " << (face.i0 + 1) << " " << (face.i1 + 1) << " " << (face.i2 + 1) << "\n";
        }
        // close the file
        file.close();
        return true;
    }
}