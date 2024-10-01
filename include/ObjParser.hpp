#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

struct Vertex {
    float x, y, z;
};

struct Normal {
    float nx, ny, nz;
};

struct TextureCoord {
    float u, v;
};

struct Face {
    std::vector<int> vertices;
    std::vector<int> textures;
    std::vector<int> normals;
};

class ObjParser {
public:
    bool load(const std::string& filename);
    [[nodiscard]] const std::vector<Vertex>& getVertices() const { return vertices; }
    [[nodiscard]] const std::vector<Normal>& getNormals() const { return normals; }
    [[nodiscard]] const std::vector<TextureCoord>& getTextureCoords() const { return textureCoords; }
    [[nodiscard]] const std::vector<Face>& getFaces() const { return faces; }

private:
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;
    std::vector<TextureCoord> textureCoords;
    std::vector<Face> faces;

    void parseLine(const std::string& line);
};

