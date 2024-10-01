#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct Polygon3 {
    sf::VertexArray sfVerAry;
    sf::Vector2f localOffset;
    sf::Vector3f posVec3[3]; // Не изменяем, но мы поменяем использование
};

struct Obj {
    std::string name;
    std::vector<Polygon3> polygons;
    sf::Vector3f position;
     // Метод для рисования объекта с учётом позиции камеры
    void draw(sf::RenderWindow* pWindow, const sf::Vector3f& cameraPosition, const float m_fDistanceToProjection) {
        for (auto& polygon : polygons) {
            for (int i = 0; i < 3; ++i) {
                // Вычисляем относительную позицию вершины
                sf::Vector3f relativePos = polygon.posVec3[i] - cameraPosition;
                // Проецируем 3D-координаты в 2D
                polygon.sfVerAry[i].position = sf::Vector2f((relativePos.x * m_fDistanceToProjection) / relativePos.z + pWindow->getSize().x / 2,
                        (relativePos.y * m_fDistanceToProjection) / relativePos.z + pWindow->getSize().y / 2);
            }
            // Рисуем треугольник
            pWindow->draw(polygon.sfVerAry);
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
    float m_fDistanceToProjection;
    float y = 1.0f; // Начальная координата Y для объектов (переменная переименована)
    float z = 1.0f; // Начальная координата Z для объектов (переменная добавлена)

    unsigned int uiWidth;
    unsigned int uiHeight;

    std::vector<Polygon3> vsTriangles;
    std::vector<Obj> vsObjects;

    void addTriangle(const sf::Vector3f& point1, const sf::Vector3f& point2, const sf::Vector3f& point3);
    [[nodiscard]] sf::Vector2f projectTo2D(const sf::Vector3f& point) const;
    void addObj(const sf::Vector3f &baseCenter, float baseSize, float height);

};

#endif // ENGINE_HPP
