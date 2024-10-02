#include "../include/Engine.hpp"
#include <iostream>

Engine::Engine(const unsigned int uiWidth, const unsigned int uiHeight)
    : uiWidth(uiWidth), uiHeight(uiHeight), fDistanceToProjection(500) {
    pWindow = new sf::RenderWindow(sf::VideoMode(uiWidth, uiHeight), "3D Engine");
    pWindow->setFramerateLimit(60);

    sfVec3fCamera = sf::Vector3f(0, 0, 0);

    std::cout << "Engine initialized with window size: " << uiWidth << "x" << uiHeight << std::endl;
}

Engine::~Engine() {
    if (pWindow) {
        delete pWindow;
        pWindow = nullptr;
    }
}

void Engine::_addObj(const sf::Vector3f& pos, const std::string& nameFile) {

}


void Engine::render() {
    sfVec3fCamera.z = 1000;
    Object3D object;
    object.loadFromFile("untitled.obj");
    object.setPosition(10, 10, 2);

    float angleX = 0, angleY = 1, angleZ = 0;  // Углы вращения по осям
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
        // Вращение объекта

        //angleX += 0.001f;
        //angleY += 0.001f;
        //angleZ += 0.001f;

        object.rotate(angleX, angleY, angleZ);  // Вращаем объект
        pWindow->clear(sf::Color::Black);

        // Отрисовка объекта
        object.draw(*pWindow, sfVec3fCamera.z);  // 100 - масштаб для проекции

        pWindow->display();
    }
}
void Engine::_control() {
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
}

sf::Vector2f Engine::_projectTo2D(const sf::Vector3f& point) const {
    return {
        (point.x * fDistanceToProjection) / point.z,
        (point.y * fDistanceToProjection) / point.z
    };
}
