#include "Game.hpp"

Game::Game() : window(sf::VideoMode(800, 600), "Test") { 
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    background = sf::RectangleShape(sf::Vector2f(800, 600));
    background.setFillColor(sf::Color::White);
    sf::Vector2i spriteSize(50, 37);

    auto& idleAnimation = animator.CreateAnimation("idle", "Sheet.png", sf::seconds(0.5), true);
    idleAnimation.AddFrames(sf::Vector2i(0, 0), spriteSize, 4);
    auto& runAnimation = animator.CreateAnimation("run", "Sheet.png", sf::seconds(0.5), true);
    runAnimation.AddFrames(sf::Vector2i(50, 37), spriteSize, 6);
    sprite.setScale(
        1200 / sprite.getLocalBounds().width,
        1500 / sprite.getLocalBounds().height
    );

    // auto rect = sprite.getTextureRect();
    // rect.left += rect.width;
    // rect.width = - rect.width;
    // sprite.setTextureRect(rect);
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        isMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        isMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        isMovingRight = isPressed;
}

void Game::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        switch (event.type) {
        case sf::Event::KeyPressed:
            if(animator.GetCurrentAnimationName() != "run")
                animator.SwitchAnimation("run");
            handlePlayerInput(event.key.code, true);
            break;
        
        case sf::Event::KeyReleased:
            animator.SwitchAnimation("idle");
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}

void Game::update(sf::Time deltTime) {
    animator.update(deltTime);

    sf::Vector2f movement(0.f, 0.f);

    if (isMovingUp)
        movement.y -= PlayerSpeed;

    if (isMovingDown)
        movement.y += PlayerSpeed;

    if (isMovingLeft)
        movement.x -= PlayerSpeed;

    if (isMovingRight)
        movement.x += PlayerSpeed;

    sprite.move(movement * deltTime.asSeconds());
}

void Game::render() {
    window.clear();
    window.draw(background);
    window.draw(sprite);
    window.display();
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > sf::seconds(1.f / 60.f)) {
            timeSinceLastUpdate -= sf::seconds(1.f / 60.f); // Time Per Frame
            processEvents();
            update(sf::seconds(1.f / 60.f));
        }
        render();
    }
}