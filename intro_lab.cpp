#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Menu {
private:
    std::vector<sf::Text> menuItems;
    sf::Font font;
    int selectedItemIndex;

public:
    Menu(float width, float height) : selectedItemIndex(0) {
        //Load the font
        if (!font.loadFromFile("Roboto.ttf")) {
            std::cerr << "Error loading font\n";
        }

        // Menu options
        std::vector<std::string> options = {"Heap", "BST", "Stack", "Queue", "Priority Queue", "Import from File"};

        // Create menu items with proper text, position, and size
        for (size_t i = 0; i < options.size(); ++i) {
            sf::Text item;
            item.setFont(font);
            item.setString(options[i]);
            item.setCharacterSize(30);  // Set a larger character size for readability
            item.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);  // Highlight first item in red
            item.setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 100 + i * 50)); // Adjust the position of each item
            menuItems.push_back(item);
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& item : menuItems) {
            window.draw(item);  // Draw each menu item to the window
        }
    }

    void moveUp() {
        if (selectedItemIndex > 0) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White);  // Deselect current item
            selectedItemIndex--;  // Move up
            menuItems[selectedItemIndex].setFillColor(sf::Color::Red);  // Highlight new selected item
        }
    }

    void moveDown() {
        if (selectedItemIndex < menuItems.size() - 1) {
            menuItems[selectedItemIndex].setFillColor(sf::Color::White);  // Deselect current item
            selectedItemIndex++;  // Move down
            menuItems[selectedItemIndex].setFillColor(sf::Color::Red);  // Highlight new selected item
        }
    }

    int getSelectedItemIndex() const {
        return selectedItemIndex;
    }

    std::string getSelectedOption() const {
        switch (selectedItemIndex) {
            case 0: return "Heap";
            case 1: return "BST";
            case 2: return "Stack";
            case 3: return "Queue";
            case 4: return "Priority Queue";
            case 5: return "Import from File";
            default: return "Unknown";
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu");

    Menu menu(800, 600);  // Create a Menu object with window dimensions

    // Create a circle
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(375, 275);  // Position the circle in the center of the window

    // Create a text to show the selected ADT on the circle
    sf::Text circleText;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font for circle text\n";
    }
    circleText.setFont(font);
    circleText.setCharacterSize(20);
    circleText.setFillColor(sf::Color::Black);
    circleText.setPosition(375, 275);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();  // Move up through the menu
                } else if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();  // Move down through the menu
                } else if (event.key.code == sf::Keyboard::Return) {  // Enter key to select menu item
                    int selectedItem = menu.getSelectedItemIndex();
                    std::cout << "You selected: " << selectedItem << std::endl;
                    // You can implement specific logic for each ADT selection if needed
                }
            }
        }

        // Update the text on the circle based on the selected menu item
        circleText.setString(menu.getSelectedOption());  // Update text with the selected ADT

        window.clear();  // Clear the window

        window.draw(circle);  // Draw the circle
        window.draw(circleText);  // Draw the text on the circle
        menu.draw(window);  // Draw the menu

        window.display();  // Display the content
    }

    return 0;
}
