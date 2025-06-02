#include <iostream>
#include "Vector.h"
#include "Mesh.h"

int main()
{
    geometry::Mesh mesh = geometry::Mesh::plane(2.0f, 1.0f, 4, 2);
    mesh.saveToOBJFile("plane.obj");
}