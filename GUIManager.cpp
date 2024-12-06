#include "GUIManager.h"
#include <iostream>

GUIManager::GUIManager() 
    : window(sf::VideoMode(800, 600), "Data Structure Visualizer"), 
      bTree(3), // Initialize BTree with a minimum degree of 3
      currentState(MENU) 
{
    if (!font.loadFromFile("Roboto.ttf")) {
        std::cerr << "Error loading font\n";
        exit(1);
    }
}

void GUIManager::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (currentState == MENU) {
                handleMenuInput(event);
            } else {
                handleADTInput(event);
            }
        }

        window.clear();
        if (currentState == MENU) {
            drawMenu();
        } else {
            drawADT(currentState);
        }
        window.display();
    }
}

void GUIManager::drawMenu() {
    sf::Text title("Select Data Structure", font, 30);
    title.setFillColor(sf::Color::White);
    title.setPosition(250, 50);
    window.draw(title);

    std::vector<std::string> options = {
        "1. Heap", "2. Binary Search Tree (BST)", 
        "3. Stack/Queue", "4. AVL Tree", 
        "5. Red-Black Tree", "6. B-Tree"
    };

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text optionText(options[i], font, 20);
        optionText.setFillColor(sf::Color::White);
        optionText.setPosition(300, 150 + i * 40);
        window.draw(optionText);
    }
}

void GUIManager::handleMenuInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Num1:
            currentState = HEAP;
            break;
        case sf::Keyboard::Num2:
            currentState = BST;
            break;
        case sf::Keyboard::Num3:
            currentState = STACK_QUEUE;
            break;
        case sf::Keyboard::Num4:
            currentState = AVL_TREE;
            break;
        case sf::Keyboard::Num5:
            currentState = RED_BLACK_TREE;
            break;
        case sf::Keyboard::Num6:
            currentState = B_TREE;
            break;
        default:
            break;
        }
    }
}

void GUIManager::drawADT(State adtState) {
    switch (adtState) {
    case HEAP:
        heap.visualize(window, font);
        break;
    case BST:
        bst.visualize(window, font);
        break;
    case STACK_QUEUE:
        stackQueue.visualize(window, font);
        break;
    case AVL_TREE:
        avl.visualize(window, font);
        break;
    case RED_BLACK_TREE:
        rbTree.visualize(window, font);
        break;
    case B_TREE:
        bTree.visualize(window, font);
        break;
    default:
        break;
    }
}

void GUIManager::handleADTInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Escape: // Return to menu
            currentState = MENU;
            break;
        case sf::Keyboard::I: // Insert key
            std::cout << "Enter a value to insert: ";
            int value;
            std::cin >> value;

            if (currentState == HEAP) heap.insert(value);
            if (currentState == BST) bst.insert(value);
            if (currentState == AVL_TREE) avl.insert(value);
            if (currentState == RED_BLACK_TREE) rbTree.insert(value);
            if (currentState == B_TREE) bTree.insert(value);
            if (currentState == STACK_QUEUE) stackQueue.push(value);
            break;
        case sf::Keyboard::D: // Delete key
    std::cout << "Enter a value to delete: ";
    std::cin >> value;
    if (currentState == HEAP) heap.deleteRoot();
    if (currentState == BST) bst.deleteNode(value);
    if (currentState == AVL_TREE) avl.deleteNode(value);
    if (currentState == STACK_QUEUE) stackQueue.pop();
    break;

        default:
            break;
        }
    }
}
