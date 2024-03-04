
// This is a simple test program to test the loading of sprites from an Acorn Sprite File.
// It uses the AcornSpriteFile class to load the sprites from file and then displays them
// using SFML. This is a simple test program to test the loading of sprites from an Acorn
// Sprite File. It uses the AcornSpriteFile class to load the
// sprites from file and then displays them using SFML.
//
// The program takes a single argument, which is the path to the sprite file to load.
// The sprites are then displayed in a window using SFML.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "../../../ux-src/asf_handler.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_sprite_file>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    std::vector<sf::Texture> textures;

    // Load the sprites from file
    std::cout << "Loading sprites from file: " << filePath << std::endl;
    AcornSpriteFile asf = AcornSpriteFile();
    if (asf.loadFromFile(filePath)) {
        std::cerr << "Failed to load sprites from file." << std::endl;
        return 1;
    }
    std::cout << "Loaded " << asf.getNumSprites() << " sprites." << std::endl;

    // Convert the sprites to SFML textures
    for (size_t i = 0; i < asf.getNumSprites(); i++) {
        std::cout << "Converting sprite " << i << " to texture." << std::endl;
        const std::shared_ptr<AcornSprite> aSprite = asf.getSprite(i);
        sf::Texture texture;
        if (texture.create(aSprite->getWidth(), aSprite->getHeight())) {
            texture.update(aSprite->getImage().data());
            textures.push_back(texture);
        } else {
            std::cerr << "Failed to create texture for sprite " << i << std::endl;
        }

    }

    // Print the first 100 bytes of the first sprite's image data
    if (!textures.empty()) {
        const auto& sprite = asf.getSprite(0); // Getting the first sprite for example
        const auto& imageData = sprite->getImage(); // Assuming this returns a std::vector<uint8_t>
        const size_t imageSize = sprite->getImageSize(); // Or imageData.size()

        std::cout << "Image data (first 100 bytes):" << std::endl;
        for (size_t i = 0; i < imageSize && i < 100; ++i) { // Limiting output to first 100 bytes for brevity
            std::cout << static_cast<int>(imageData[i]) << " ";
        }
        std::cout << std::endl;
    }

    // Create a window and display the sprites
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Display");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Example: Draw the loaded sprites
        //sf::RectangleShape rectangle(sf::Vector2f(1920.f, 1080.f));
        //rectangle.setFillColor(sf::Color::Green);
        //rectangle.setPosition(1, 1);
        //window.draw(rectangle);
        for (auto& texture : textures) {
            sf::Sprite sprite(texture);
            sprite.setPosition(0, 0); // Position the sprite at the top-left corner
            window.draw(sprite);
        }
        window.display();
    }

    return 0;
}
