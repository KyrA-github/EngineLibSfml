// Engine.hpp
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>

struct Poligon3 {
    sf::VertexArray sfVerAry;
    sf::Vector2f localOffset;
    sf::Vector3f localCamera;
    sf::Vector3f pos;
};

class Engine {
public:
    // Конструктор: инициализирует окно с заданным размером
    Engine(unsigned int uiWidth, unsigned int uiHeight);

    // Метод отрисовки, вызываемый из main
    void render();

    // Деструктор: выводит размер окна при завершении работы
    ~Engine();

private:
    sf::Vector3f sfVec3fCamera;
    // Указатель на окно SFML
    sf::RenderWindow* pWindow;

    float m_fDistanceToProjection;

    // Размер окна
    unsigned int uiWidth;
    unsigned int uiHeight;

    // Массив треугольных полигонов
    std::vector<sf::VertexArray> vTriangles;
    std::vector<Poligon3> vsTriangles;

    // Метод для добавления треугольника в список
    void addTriangle(const sf::Vector3f& point1, const sf::Vector3f& point2, const sf::Vector3f& point3);
    static sf::Vector3f posVec2_XY_In_PosVec3_XYZ(sf::Vector2f ValueXY);
    [[nodiscard]] sf::Vector2f posVec3_XYZ_In_posVec2_XY(sf::Vector3f ValueXYZ) const;
};

#endif // ENGINE_HPP
