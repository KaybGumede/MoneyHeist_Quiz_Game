#include "StorySequence.hpp"
#include "BankHeistAnimation.hpp"
#include <iostream>
#include <sstream>
#include <vector>

StorySequence::StorySequence(sf::RenderWindow& win) : window(win) {
    if (!font.loadFromFile("C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML FONT\\arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Define image sets
    imageSets = {
        {
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\man1.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\man2.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\man3.jpg"
        },
        {
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\girl1.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\girl2.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\girl3.jpg"
        },
        {
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\image1.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\image2.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\image3.jpg"
        },
        {
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\pic1.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\pic2.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\pic3.jpg"
        },
        {
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\pic1.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\pic2.jpg",
            "C:\\Users\\ADMIN\\Desktop\\GAME PROJECT\\SFML IMAGES\\pic3.jpg"
        }
    };

    // Define dialogue sets
    dialogueSets = {
        {
            "John had worked at First National Bank for over 15 years, dedicating himself to his job as a loan officer.",
            "He was a diligent employee, always going above and beyond to help his customers.",
            "However, his life took a devastating turn when his wife, Sarah, passed away after a long battle with cancer.",
            "John was heartbroken, and his world crumbled around him.",
            "To make matters worse, the bank's new management, led by the ruthless and cunning CEO, James, began harsh cost-cutting.",
            "John, still grieving, struggled to make ends meet. The bank showed no empathy or understanding.",
            "He felt like he was being pushed to the edge."
        },
        {
            "Tragedy struck again when John's daughter, Emily, was diagnosed with a rare genetic disorder that required an expensive treatment not covered by their insurance.",
            "The bank's management refused to offer any assistance, and John felt like he was being forced to choose between his job and his daughter's life.",
            "In desperation, John turned to James, pleading for help. However, James showed no compassion, instead choosing to belittle John and imply that he was a failure as a father.",
            "The encounter left John feeling shattered and consumed by anger.",
            "As John struggled to come to terms with his situation, he discovered a shocking truth.",
            "To find out more and help John, play the quiz based on the C++ language."
        },
        {
            "John turned to James—the new CEO—for help. But James, cold and calculating, showed no compassion.",
            "Instead, he humiliated John during a staff meeting, implying that his personal failures were his own burden to bear, and that “the bank doesn’t do charity.”",
            "The words echoed in John’s head for weeks. The man who had just lost a wife, who was watching his daughter slip away, was mocked... in front of his peers.",
            "As John struggled to come to terms with his situation, he discovered a shocking truth."
        },
        {
            "While reviewing internal reports—something he was no longer authorized to see—he uncovered a hidden paper trail: secret offshore accounts, forged client signatures, and illegal foreclosures. The bank was profiting off people's misfortune, and James was at the center of it all.",
            "John realized the hypocrisy—he had begged for help to save his daughter’s life, and was turned down by a man embezzling millions.",
            "To make matters worse, James had quietly authorized massive layoffs disguised as “cost optimization,” including some of John’s closest colleagues, many of whom were single parents or caregivers. The bank didn’t just turn cold—it turned cruel.",
            "John, still grieving, now filled with rage, made his decision."
        },
        {
            "He spent months planning. Not for money—but for evidence. He studied security routines, backup protocols, even the hidden server room that James thought no one knew about. He posed as a technician to install spyware, downloaded files at night, and forged access cards with 3D printers.",
            "The robbery wasn’t just about taking—it was about exposing. About justice.",
            "When the day came, John didn’t run to the vault. He walked straight to James’ office, forced him to open the private safe, and pulled out the encrypted drives. He left the cash. All of it.",
            "Then he looked James in the eye and said: “You wouldn’t give me a loan to save my daughter’s life, but you funded your yacht with stolen homes. This isn’t theft—this is payback.”",
            "The files were leaked. The bank crumbled. James was indicted.",
            "Emily survived—thanks to anonymous donations from an \"unknown source.\" John disappeared, but his actions sparked national outrage, triggering an investigation into corrupt banking practices.",
            "And somewhere out there, a man with nothing left to lose made sure no one else would ever feel as powerless as he once did."
        }
    };
}

void StorySequence::run() {
    // Run all dialogue scenes
    for (size_t i = 0; i < imageSets.size() && window.isOpen(); ++i) {
        runScene(imageSets[i], dialogueSets[i], "Scene " + std::to_string(i + 1));
    }
    // Run bank heist animation before Level 1
    if (window.isOpen()) {
        runBankHeistAnimation();
    }
}

void StorySequence::runScene(const std::vector<std::string>& imageFiles, const std::vector<std::string>& dialoguesRaw, const std::string& windowTitle) {
    std::vector<sf::Texture> textures(imageFiles.size());
    std::vector<sf::Sprite> sprites(imageFiles.size());

    for (size_t i = 0; i < imageFiles.size(); ++i) {
        if (!textures[i].loadFromFile(imageFiles[i])) {
            std::cerr << "Error loading image: " << imageFiles[i] << std::endl;
            return;
        }
        sprites[i].setTexture(textures[i]);
        sprites[i].setOrigin(textures[i].getSize().x / 2.f, textures[i].getSize().y / 2.f);
        sprites[i].setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 50.f);
        sprites[i].setScale(0.76f, 0.53f);
    }

    int currentImage = 0;
    sf::Clock clock;

    // Wrap dialogues
    std::vector<std::string> dialogues;
    for (const auto& d : dialoguesRaw) {
        dialogues.push_back(wrapText(d, 18, 700.f));
    }

    int currentDialogue = 0;

    // Dialogue text setup
    sf::Text dialogueText;
    dialogueText.setFont(font);
    dialogueText.setCharacterSize(18);
    dialogueText.setFillColor(sf::Color::White);
    dialogueText.setString(dialogues[currentDialogue]);
    dialogueText.setPosition(40.f, 460.f);

    // Dialogue background
    sf::RectangleShape dialogueBox(sf::Vector2f(720.f, 120.f));
    dialogueBox.setFillColor(sf::Color(50, 50, 50, 220));
    dialogueBox.setPosition(40.f, 450.f);

    // Next button
    sf::RectangleShape nextButton(sf::Vector2f(100.f, 40.f));
    nextButton.setFillColor(sf::Color::Green);
    nextButton.setPosition(650.f, 510.f);

    sf::Text nextText("Next", font, 18);
    nextText.setFillColor(sf::Color::Black);
    nextText.setPosition(675.f, 515.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                nextButton.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                if (currentDialogue < static_cast<int>(dialogues.size()) - 1) {
                    currentDialogue++;
                    dialogueText.setString(dialogues[currentDialogue]);
                }
                else {
                    return; // End of scene
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() >= 0.5f) {
            clock.restart();
            currentImage = (currentImage + 1) % sprites.size();
        }

        window.clear(sf::Color::White);
        window.draw(sprites[currentImage]);
        window.draw(dialogueBox);
        window.draw(dialogueText);
        window.draw(nextButton);
        window.draw(nextText);
        window.display();
    }
}

void StorySequence::runBankHeistAnimation() {
    runBankHeist(window);
}

std::string StorySequence::wrapText(const std::string& input, unsigned int charSize, float maxWidth) {
    std::istringstream iss(input);
    std::string word, line, wrapped;
    sf::Text text("", font, charSize);

    while (iss >> word) {
        std::string testLine = line + word + " ";
        text.setString(testLine);

        if (text.getLocalBounds().width > maxWidth) {
            wrapped += line + "\n";
            line = word + " ";
        }
        else {
            line = testLine;
        }
    }

    wrapped += line;
    return wrapped;
}

void StorySequence::centerText(sf::Text& text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    text.setPosition(x, y);
}