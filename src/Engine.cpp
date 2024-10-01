#include "../include/Engine.hpp"
#include <iostream>

Engine::Engine(const unsigned int uiWidth, const unsigned int uiHeight)
    : m_fDistanceToProjection(500), uiWidth(uiWidth), uiHeight(uiHeight) {
    pWindow = new sf::RenderWindow(sf::VideoMode(uiWidth, uiHeight), "3D Engine");
    pWindow->setFramerateLimit(60);

    sfVec3fCamera = sf::Vector3f(0, 0, 0);

    std::cout << "Engine initialized with window size: " << uiWidth << "x" << uiHeight << std::endl;

    addTriangle(sf::Vector3f(0, 0, 2), sf::Vector3f(1, 0, 2), sf::Vector3f(0.5f, 1, 2));
}

void Engine::addTriangle(const sf::Vector3f& point1, const sf::Vector3f& point2, const sf::Vector3f& point3) {
    Poligon3 polygon;
    sf::VertexArray triangle(sf::Triangles, 3);

    triangle[0].position = projectTo2D(point1);
    triangle[1].position = projectTo2D(point2);
    triangle[2].position = projectTo2D(point3);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Blue;

    polygon.sfVerAry = triangle;
    polygon.posVec3[0] = point1;
    polygon.posVec3[1] = point2;
    polygon.posVec3[2] = point3;

    vsTriangles.push_back(polygon);
}

void Engine::render() {
    while (pWindow->isOpen()) {
        sf::Event event{};
        while (pWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                pWindow->close();
            }
            if (event.type == sf::Event::MouseWheelMoved) {
                if (event.mouseWheel.delta > 0) {
                    sfVec3fCamera.z += 0.1f;  // При прокрутке колесика вперед — объект приближается
                } else if (event.mouseWheel.delta < 0) {
                    sfVec3fCamera.z -= 0.1f;  // При прокрутке назад — объект отдаляется
                }
            }
        }

        // Обработка клавиш для перемещения камеры
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sfVec3fCamera.y += 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sfVec3fCamera.y -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sfVec3fCamera.x -= 0.1f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sfVec3fCamera.x += 0.1f;
        }

        pWindow->clear(sf::Color::Black);

        for (auto& polygon : vsTriangles) {
            for (int i = 0; i < 3; ++i) {
                sf::Vector3f relativePos = polygon.posVec3[i] - sfVec3fCamera;
                polygon.sfVerAry[i].position = projectTo2D(relativePos);
            }
            pWindow->draw(polygon.sfVerAry);
        }

        pWindow->display();
    }
}

Engine::~Engine() {
    if (pWindow) {
        delete pWindow;
        pWindow = nullptr;
    }
}

sf::Vector2f Engine::projectTo2D(const sf::Vector3f& point) const {
    return sf::Vector2f((point.x * m_fDistanceToProjection) / point.z + uiWidth / 2,
                        (point.y * m_fDistanceToProjection) / point.z + uiHeight / 2);
}
