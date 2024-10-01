#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct Poligon3 {
    sf::VertexArray sfVerAry;
    sf::Vector2f localOffset;
    sf::Vector3f posVec3[3];
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
    float z = 1.0f; // Начальная координата Z для объектов

    unsigned int uiWidth;
    unsigned int uiHeight;

    std::vector<Poligon3> vsTriangles;

    void addTriangle(const sf::Vector3f& point1, const sf::Vector3f& point2, const sf::Vector3f& point3);
    sf::Vector2f projectTo2D(const sf::Vector3f& point) const;
};

#endif // ENGINE_HPP
