#include "FallingMoneyAnimation.h"
#include <iostream>
#include <vector>
#include <random>

void runFallingMoney(sf::RenderWindow& window, int score, const std::string& heistType) {
    window.setFramerateLimit(60);

    // Random number generator for positions and speeds
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xDist(0.0f, static_cast<float>(window.getSize().x));
    std::uniform_real_distribution<float> speedDist(100.0f, 300.0f);

    // Structure to hold money properties
    struct Money {
        sf::RectangleShape shape;
        sf::Texture coin;
        sf::Sprite dollarCoin;
        float speed;
        Money() {
            if (!coin.loadFromFile("dollar.png")) {
                std::cerr << "Failed to load image for falling money animation" << std::endl;
                return;
            }
            coin.setSmooth(true);
            dollarCoin.setTexture(coin); // Don't forget to set the texture to the sprite!
        }

    };


    // Create multiple money objects
    std::vector<Money> monies;
    for (int i = 0; i < 20; ++i) {
        Money money;
        money.dollarCoin.setScale(sf::Vector2f(20.0f, 10.0f));
        //money.dollarCoin.setFillColor(sf::Color::Green);
        money.dollarCoin.setPosition(xDist(gen), -10.0f);
        money.speed = speedDist(gen);
        monies.push_back(money);
    }

    // Load font and set up text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font for falling money animation" << std::endl;
        return;
    }

    // Win text with score and heist type
    sf::Text winText;
    winText.setFont(font);
    winText.setString("It's a Win!\nScore: " + std::to_string(score) + "/6\n" + heistType);
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Red);
    sf::FloatRect textBounds = winText.getLocalBounds();
    winText.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    winText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    // Clock to control animation duration
    sf::Clock clock;
    const float animationDuration = 3.0f; // 3 seconds
    float deltaTime = 1.0f / 60.0f; // Approximate delta time for 60 FPS

    // Main loop
    while (window.isOpen() && clock.getElapsedTime().asSeconds() < animationDuration) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            // Allow skipping animation with a key press (e.g., Space)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                return;
            }
        }

        // Update money positions
        for (auto& money : monies) {
            money.dollarCoin.move(0.0f, money.speed * deltaTime);
            // Reset money to top if it goes off-screen
            if (money.dollarCoin.getPosition().y > window.getSize().y) {
                money.dollarCoin.setPosition(xDist(gen), -10.0f);
                money.speed = speedDist(gen);
            }
        }

        // Clear and draw
        window.clear(sf::Color::Black);
        for (const auto& money : monies) {
            window.draw(money.dollarCoin);
        }
        window.draw(winText); // Draw the text
        window.display();
    }
}
