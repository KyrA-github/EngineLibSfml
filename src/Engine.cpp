// Engine.cpp
#include "../include/Engine.hpp"
#include <iostream>
// Конструктор класса Engine
Engine::Engine(unsigned int uiWidth, unsigned int uiHeight)
    : uiWidth(uiWidth), uiHeight(uiHeight) {
    // Создаем окно с заданным размером
    pWindow = new sf::RenderWindow(sf::VideoMode(uiWidth, uiHeight), "3D Engine");

    // Устанавливаем ограничение на частоту кадров
    pWindow->setFramerateLimit(60);

    sfVec3fCamera = sf::Vector3f(0,0,0);
    std::cout << "Engine initialized with window size: " << uiWidth << "x" << uiHeight << std::endl;

    // Пример добавления треугольника
    addTriangle(sf::Vector3f(100, 100, 10), sf::Vector3f(200, 100, 10), sf::Vector3f(150, 200, 10));
}

// Метод для добавления треугольника в массив
void Engine::addTriangle(const sf::Vector3f& point1, const sf::Vector3f& point2, const sf::Vector3f& point3) {
    // Создаем треугольник с использованием sf::VertexArray
    Poligon3 st;
    sf::VertexArray triangle(sf::Triangles, 3);

    // Устанавливаем координаты вершин
    triangle[0].position = posVec3_XYZ_In_posVec2_XY(point1)-sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y);
    triangle[1].position = posVec3_XYZ_In_posVec2_XY(point1-sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y);
    triangle[2].position = posVec3_XYZ_In_posVec2_XY(point1-sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y);

    // Назначаем цвет каждой вершине
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Blue;

    st.localCamera = sfVec3fCamera;
    st.sfVerAry = triangle;

    // Добавляем треугольник в массив
    vsTriangles.push_back(st);
}



// Метод render, вызываемый из main
void Engine::render() {
    // Основной цикл работы окна
    while (pWindow->isOpen()) {
        // Обрабатываем события окна
        sf::Event event{};
        while (pWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                pWindow->close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            sfVec3fCamera.y +=1 ;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sfVec3fCamera.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            sfVec3fCamera.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            sfVec3fCamera.x -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            //sfVec3fCamera.y +=1 ;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sfVec3fCamera.z += 0.001;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
           // sfVec3fCamera.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sfVec3fCamera.z -= 0.001;
        }

        // Очищаем окно черным цветом
        pWindow->clear(sf::Color::Black);

        // Отрисовка всех треугольников
        for (auto&[sfVerAry, localOffset, localCamera] : vsTriangles) {
            // передвежение
            if (sf::Vector2f(localCamera.x, localCamera.y) != sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y)) {
                sfVerAry[0].position = (sfVerAry[0].position + sf::Vector2f(localCamera.x, localCamera.y)) - sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y);
                sfVerAry[1].position = (sfVerAry[1].position + sf::Vector2f(localCamera.x, localCamera.y)) - sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y);
                sfVerAry[2].position = (sfVerAry[2].position + sf::Vector2f(localCamera.x, localCamera.y)) - sf::Vector2f(sfVec3fCamera.x, sfVec3fCamera.y);

                localCamera = sf::Vector3f(sfVec3fCamera.x, sfVec3fCamera.y, localCamera.z);

            }

            pWindow->draw(sfVerAry);
        }

        // Отображаем содержимое буфера на экране
        pWindow->display();
    }
}

// Деструктор класса Engine
Engine::~Engine() {
    // Выводим размер окна при завершении работы
    std::cout << "Window size was: " << uiWidth << "x" << uiHeight << std::endl;

    // Освобождаем выделенную память
    if (pWindow) {
        delete pWindow;
        pWindow = nullptr;
    }

    std::cout << "Engine destroyed" << std::endl;
}


sf::Vector3f Engine::posVec2_XY_In_PosVec3_XYZ(sf::Vector2f ValueXY) {
    return {0,0,0};
}

sf::Vector2f Engine::posVec3_XYZ_In_posVec2_XY(const sf::Vector3f ValueXYZ) const {
    return {((ValueXYZ.x * m_fDistanceToProjection)/ValueXYZ.z), ((ValueXYZ.y * m_fDistanceToProjection)/ValueXYZ.z)};
}
