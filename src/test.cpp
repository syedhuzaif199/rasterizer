#include <iostream>
#include "Vector.h"
#include "Mesh.h"

int main() {
    geometry::Mesh sphere = geometry::Mesh::sphere(1.0f, 12, 8);
    sphere.saveToOBJFile("sphere.obj");
}