#include <SFML/Graphics.hpp>

int main(){

    sf::Clock clock;
    sf::Time deltaTime;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::VertexArray lines = sf::VertexArray(sf::Lines, 4);
    lines[0].position = sf::Vector2f(0, 0);
    lines[1].position = sf::Vector2f(800, 600);
    lines[2].position = sf::Vector2f(800, 0);
    lines[3].position = sf::Vector2f(0, 600);

    lines[0].color = sf::Color::Blue;
    lines[1].color = sf::Color::Green;
    lines[2].color = sf::Color::Red;
    lines[3].color = sf::Color::Yellow;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    window.close();
                }
            }

        }

        deltaTime = clock.restart();

        window.clear(sf::Color::Black);
        window.draw(lines);
        window.display();
    }

    return 0;
}