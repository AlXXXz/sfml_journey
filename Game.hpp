#pragma once

#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include "Animator.hpp"

/**
 * @name Game - класс, представляющий игровой движок
 * @brief Здесь обрабатывается вся игровая логика
*/
class Game {
    AssetManager manager;
    sf::RenderWindow window;
    sf::RectangleShape background;
    sf::Sprite sprite;
    Animator animator = Animator(sprite);

    float PlayerSpeed = 200.f;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight; 

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    // Обработка событий
    void processEvents();
    // Обновление игровой логики
    void update(sf::Time deltaTime);
    // Отрисовка на экране
    void render();

public:
    // Конструктор класса
    Game();
    // Запуск игрового цикла
    void run();
};