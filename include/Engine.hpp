#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>

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
    void draw(sf::RenderWindow* pWindow, const sf::Vector3f& sfVec3fCamera, float fDistanceToProjection) {
        for (auto& polygon : polygons) {
            // Рисуем основной треугольник
            for (int i = 0; i < 3; ++i) {
                sf::Vector3f relativePos = polygon.posVec3[i] - sfVec3fCamera;
                polygon.sfVerAry[i].position = sf::Vector2f((relativePos.x * fDistanceToProjection) / relativePos.z + pWindow->getSize().x / 2,
                        (relativePos.y * fDistanceToProjection) / relativePos.z + pWindow->getSize().y / 2);
            }
            pWindow->draw(polygon.sfVerAry);

            // Теперь создаём обводку
            sf::VertexArray outline(sf::LineStrip, 4);  // 4 точки: 3 вершины + 1 повторение для замыкания

            for (int i = 0; i < 3; ++i) {
                outline[i].position = polygon.sfVerAry[i].position;
                outline[i].color = sf::Color::White;  // Цвет обводки, например, белый
            }
            outline[3].position = polygon.sfVerAry[0].position; // Замыкаем линию

            // Рисуем обводку
            pWindow->draw(outline);
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
    sf::Vector3f rotateX(const sf::Vector3f& point, float angle);
    sf::Vector3f rotateY(const sf::Vector3f& point, float angle);
    sf::Vector3f rotateZ(const sf::Vector3f& point, float angle);
    void rotatePyramid(Obj& pyramid, float angleX, float angleY, float angleZ);
    float getPolygonDepth(const Polygon3& polygon);
};

#endif // ENGINE_HPP
