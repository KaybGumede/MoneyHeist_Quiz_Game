#include "BankHeistAnimation.hpp"
#include <iostream>
#include <vector>
#include <cmath>

void runBankHeist(sf::RenderWindow& window) {
    window.setFramerateLimit(60);

    // Get window dimensions for centering
    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f - 390; // Half of bankFloor width (780/2)
    float centerY = windowSize.y / 2.0f - 150 - 100; // Shift up by 100 pixels

    // Load font for title
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML FONT\\arial.ttf")) {
        std::cerr << "Failed to load font for animation title" << std::endl;
        return;
    }

    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("Bank Heist Plan");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
    title.setPosition(windowSize.x / 2.0f, centerY - 100); // Above the animation

    // **Bank Floor (Front View)**
    sf::RectangleShape bankFloor(sf::Vector2f(780, 300));
    bankFloor.setPosition(centerX + 10, centerY + 250);
    bankFloor.setFillColor(sf::Color(255, 253, 208)); // Cream
    bankFloor.setOutlineThickness(5);
    bankFloor.setOutlineColor(sf::Color::Black);

    // **Entrance**
    sf::RectangleShape entrance(sf::Vector2f(100, 50));
    entrance.setFillColor(sf::Color(139, 69, 19)); // Brown
    entrance.setPosition(centerX + 350, centerY + 480);

    // **Waiting Room**
    sf::RectangleShape waitingRoom(sf::Vector2f(400, 200));
    waitingRoom.setFillColor(sf::Color(100, 100, 255)); // Light Blue
    waitingRoom.setPosition(centerX + 100, centerY + 300);

    // **Sofas in Waiting Room**
    std::vector<sf::RectangleShape> sofas;
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape sofa(sf::Vector2f(150, 50));
        sofa.setFillColor(sf::Color(169, 169, 169)); // Gray
        if (i < 2) sofa.setPosition(centerX + 120 + (i * 210), centerY + 340);
        else sofa.setPosition(centerX + 120 + ((i - 2) * 210), centerY + 420);
        sofas.push_back(sofa);
    }

    // **Offices**
    std::vector<sf::RectangleShape> offices;
    for (int i = 0; i < 2; i++) {
        sf::RectangleShape office(sf::Vector2f(150, 150));
        office.setFillColor(sf::Color(0, 0, 255));
        office.setOutlineThickness(5);
        office.setOutlineColor(sf::Color::Black);
        office.setPosition(centerX + 600, centerY + 150 + (i * 150));
        offices.push_back(office);
    }

    // **Small Office**
    sf::RectangleShape smallOffice(sf::Vector2f(100, 100));
    smallOffice.setFillColor(sf::Color(0, 0, 255));
    smallOffice.setOutlineThickness(5);
    smallOffice.setOutlineColor(sf::Color::Black);
    smallOffice.setPosition(centerX + 650, centerY + 460);

    // **Bank Vault**
    sf::RectangleShape vault(sf::Vector2f(150, 100));
    vault.setFillColor(sf::Color(0, 128, 0));
    vault.setOutlineThickness(5);
    vault.setOutlineColor(sf::Color::Black);
    vault.setPosition(centerX + 600, centerY + 20);

    // **Moving Man**
    sf::CircleShape man(10);
    man.setFillColor(sf::Color::Red);
    sf::Vector2f manPos(centerX + 400, centerY + 480);

    // **Stolen Money (Green Object - Initially Hidden)**
    sf::RectangleShape stolenMoney(sf::Vector2f(15, 15));
    stolenMoney.setFillColor(sf::Color::Green);
    sf::Vector2f moneyPos;
    bool hasMoney = false;

    // **Waypoints (Full Bank Heist Route, Centered)**
    std::vector<sf::Vector2f> waypoints = {
        {centerX + 400, centerY + 380}, // Move to waiting room
        {centerX + 650, centerY + 250}, // Move to offices
        {centerX + 675, centerY + 70},  // Move to vault (stealing money)
        {centerX + 400, centerY + 480}  // Exit bank
    };

    size_t currentWaypoint = 0;
    bool moving = true;
    float speed = 50.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            // Allow skipping animation with a key press (e.g., Space)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                return; // Skip animation
            }
        }

        // **Man Movement**
        if (moving && currentWaypoint < waypoints.size()) {
            sf::Time elapsed = clock.restart();
            sf::Vector2f direction = waypoints[currentWaypoint] - manPos;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (length > 1.0f) {
                direction /= length;
                manPos += direction * speed * elapsed.asSeconds();
                if (hasMoney) {
                    moneyPos += direction * speed * elapsed.asSeconds(); // Move money with the man
                }
            }
            else {
                if (currentWaypoint == 2) { // Vault reached, take money
                    hasMoney = true;
                    moneyPos = manPos; // Money appears on man
                }
                currentWaypoint++;
                clock.restart();
            }
        }
        else if (currentWaypoint >= waypoints.size()) {
            // Animation complete, return to story sequence
            return;
        }

        man.setPosition(manPos);
        if (hasMoney) stolenMoney.setPosition(moneyPos);

        // **Clear and Draw**
        window.clear();
        window.draw(title); // Draw the title
        window.draw(bankFloor);
        window.draw(entrance);
        window.draw(waitingRoom);
        for (auto& sofa : sofas) window.draw(sofa);
        for (auto& office : offices) window.draw(office);
        window.draw(smallOffice);
        window.draw(vault);
        window.draw(man);
        if (hasMoney) window.draw(stolenMoney); // Draw money only after vault
        window.display();
    }
}