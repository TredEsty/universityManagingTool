#include "school.h"
#include <SFML/Graphics.hpp>

int main(){
    std::unordered_set<Student> studentList;


    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML GUI Example");

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw your GUI components here

        // Display the window
        window.display();
    }

    return 0;

}



