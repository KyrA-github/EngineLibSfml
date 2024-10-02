#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

struct Vertex {
    float x, y, z;
};

struct Polygon {
    int vertex1, vertex2, vertex3;
};

class Object3D {
public:
    std::vector<Vertex> vertices;
    std::vector<Polygon> polygons;
    float posX, posY, posZ;

    Object3D() : posX(0), posY(0), posZ(0) {}

    void setPosition(float x, float y, float z) {
        posX = x;
        posY = y;
        posZ = z;
    }

    // Проекция 3D вершины на 2D плоскость
    sf::Vector2f projectVertex(const Vertex& vertex, float scale) {
        float projectedX = (vertex.x + posX) / (vertex.z + posZ) * scale;
        float projectedY = (vertex.y + posY) / (vertex.z + posZ) * scale;
        return sf::Vector2f(projectedX, projectedY);
    }

    // Функция для рисования объекта
    void draw(sf::RenderWindow& window, float scale) {
        for (const Polygon& poly : polygons) {
            sf::ConvexShape triangle;
            triangle.setPointCount(3);

            // Проекция каждой вершины полигона
            sf::Vector2f p1 = projectVertex(vertices[poly.vertex1], scale);
            sf::Vector2f p2 = projectVertex(vertices[poly.vertex2], scale);
            sf::Vector2f p3 = projectVertex(vertices[poly.vertex3], scale);

            triangle.setPoint(0, p1);
            triangle.setPoint(1, p2);
            triangle.setPoint(2, p3);

            // Цвет и отрисовка
            triangle.setFillColor(sf::Color::Green);
            window.draw(triangle);
        }
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            char type;
            iss >> type;

            if (type == 'v') {
                // Чтение вершины
                float x, y, z;
                iss >> x >> y >> z;
                addVertex(x, y, z);
            } else if (type == 'p') {
                // Чтение полигона
                int v1, v2, v3;
                iss >> v1 >> v2 >> v3;
                addPolygon(v1 - 1, v2 - 1, v3 - 1);  // Индексы вершин начинаются с 0
            }
        }

        return true;
    }
    void addVertex(float x, float y, float z) {
        vertices.push_back({x, y, z});
    }

    void addPolygon(int v1, int v2, int v3) {
        polygons.push_back({v1, v2, v3});
    }
    // Функция для рисования граней (ребер) объекта
    void drawEdges(sf::RenderWindow& window, float scale) {
        for (const Polygon& poly : polygons) {
            sf::VertexArray lines(sf::LinesStrip, 4);

            // Проекция каждой вершины полигона
            sf::Vector2f p1 = projectVertex(vertices[poly.vertex1], scale);
            sf::Vector2f p2 = projectVertex(vertices[poly.vertex2], scale);
            sf::Vector2f p3 = projectVertex(vertices[poly.vertex3], scale);

            // Соединение вершин линиями
            lines[0].position = p1;
            lines[1].position = p2;
            lines[2].position = p3;
            lines[3].position = p1;  // Замыкаем треугольник

            // Устанавливаем цвет для линий
            for (int i = 0; i < 4; i++) {
                lines[i].color = sf::Color::White;
            }

            window.draw(lines);
        }
    }void rotate(float angleX, float angleY, float angleZ) {
        float radX = angleX * M_PI / 180;
        float radY = angleY * M_PI / 180;
        float radZ = angleZ * M_PI / 180;

        // Матрицы вращения
        float rotX[3][3] = {
            {1, 0, 0},
            {0, cos(radX), -sin(radX)},
            {0, sin(radX), cos(radX)}
        };

        float rotY[3][3] = {
            {cos(radY), 0, sin(radY)},
            {0, 1, 0},
            {-sin(radY), 0, cos(radY)}
        };

        float rotZ[3][3] = {
            {cos(radZ), -sin(radZ), 0},
            {sin(radZ), cos(radZ), 0},
            {0, 0, 1}
        };

        // Применение вращения
        for (Vertex& vertex : vertices) {
            // Вращение вокруг оси X
            float x1 = vertex.x;
            float y1 = vertex.y * rotX[1][1] + vertex.z * rotX[1][2];
            float z1 = vertex.y * rotX[2][1] + vertex.z * rotX[2][2];

            vertex.x = x1;
            vertex.y = y1;
            vertex.z = z1;

            // Вращение вокруг оси Y
            float x2 = vertex.x * rotY[0][0] + vertex.z * rotY[0][2];
            float y2 = vertex.y;
            float z2 = -vertex.x * rotY[2][0] + vertex.z * rotY[2][2];

            vertex.x = x2;
            vertex.y = y2;
            vertex.z = z2;

            // Вращение вокруг оси Z
            float x3 = vertex.x * rotZ[0][0] + vertex.y * rotZ[0][1];
            float y3 = vertex.x * rotZ[1][0] + vertex.y * rotZ[1][1];
            float z3 = vertex.z;

            vertex.x = x3;
            vertex.y = y3;
            vertex.z = z3;
        }
    }
};

class Engine {
public:
    Engine(unsigned int uiWidth, unsigned int uiHeight);
    void render();

    ~Engine();

private:
    sf::Vector3f sfVec3fCamera; // Позиция камеры
    sf::RenderWindow* pWindow;

    unsigned int uiWidth;
    unsigned int uiHeight;
    float fDistanceToProjection;

    [[nodiscard]] sf::Vector2f _projectTo2D(const sf::Vector3f& point) const;
    void _addObj(const sf::Vector3f &pos, const std::string &nameFile);
    void _control();
};

#endif // ENGINE_HPP
