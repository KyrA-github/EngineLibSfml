#include "../include/ObjParser.hpp"

bool ObjParser::load(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }

    file.close();
    return true;
}

void ObjParser::parseLine(const std::string& line) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "v") {
        Vertex vertex{};
        iss >> vertex.x >> vertex.y >> vertex.z;
        vertices.push_back(vertex);
    }
    else if (prefix == "vn") {
        Normal normal;
        iss >> normal.nx >> normal.ny >> normal.nz;
        normals.push_back(normal);
    }
    else if (prefix == "vt") {
        TextureCoord texCoord;
        iss >> texCoord.u >> texCoord.v;
        textureCoords.push_back(texCoord);
    }
    else if (prefix == "f") {
        Face face;
        std::string vertexInfo;
        while (iss >> vertexInfo) {
            std::replace(vertexInfo.begin(), vertexInfo.end(), '/', ' '); // Заменяем '/' пробелами
            std::istringstream vss(vertexInfo);
            int vertexIndex, texIndex, normalIndex;
            vss >> vertexIndex;
            if (vss >> texIndex) {
                face.textures.push_back(texIndex - 1); // Индексы начинаются с 1 в .obj
            }
            if (vss >> normalIndex) {
                face.normals.push_back(normalIndex - 1);
            }
            face.vertices.push_back(vertexIndex - 1);
        }
        faces.push_back(face);
    }
}