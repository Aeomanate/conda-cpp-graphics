#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <rapidjson/document.h>
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>

// Structure to hold configuration
struct Config {
    int width;
    int height;
    std::string text;
    sf::Color color;
};

// Function to read settings from a JSON file
Config readSettings(const std::string& filename) {
    boost::filesystem::path path(filename);
    if (!boost::filesystem::exists(path)) {
        std::cerr << "Settings file not found!" << std::endl;
        exit(1);
    }

    std::ifstream file(path.string());
    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    rapidjson::Document doc;
    doc.Parse(jsonString.c_str());

    Config config;
    config.width = doc["resolution"]["width"].GetInt();
    config.height = doc["resolution"]["height"].GetInt();
    config.text = doc["text"].GetString();

    int r = doc["color"]["r"].GetInt();
    int g = doc["color"]["g"].GetInt();
    int b = doc["color"]["b"].GetInt();
    config.color = sf::Color(r, g, b);

    return config;
}

// Test the reading of settings
TEST(SettingsTest, ReadSettings) {
    Config config = readSettings("settings.json");

    EXPECT_EQ(config.width, 800);
    EXPECT_EQ(config.height, 600);
    EXPECT_EQ(config.text, "Hello, World!");
    EXPECT_EQ(config.color, sf::Color::Red);  // Expect red as per settings
}

// Main function to draw the text on screen
int main() {
    Config config = readSettings("settings.json");

    // Create the window
    sf::RenderWindow window(sf::VideoMode(config.width, config.height), "SFML Graphics");

    // Create the text
    sf::Font font;
    if (!font.loadFromFile("Lato-Black.ttf")) {  // Make sure you have this font file or adjust the path
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }
    sf::Text text(config.text, font, 30);
    text.setFillColor(config.color);

    // Run the game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(config.color == sf::Color::Black ? sf::Color::White : sf::Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}

