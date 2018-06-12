//
// EPITECH PROJECT, 2018
// SfmlTests
// File description:
// DislayManager.cpp
//

#include "GameManager.hpp"

void zappy::client::GameManager::display()
{
        _window->display();
}

void zappy::client::GameManager::clean()
{
	_window->clear();
}

bool zappy::client::GameManager::isOpen()
{
	return _window->isOpen();
}

bool zappy::client::GameManager::start()
{
	_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(),
					"SfmlTests");
        return isOpen();
}

void zappy::client::GameManager::stop()
{
        if (_window->isOpen())
                _window->close();
}

int zappy::client::GameManager::handleEvents(
	zappy::client::module::ISfmlModule &module)
{
	sf::Event event{};
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			stop();
		module.handleEvent(event);
	}
        return 0;
}

sf::RenderWindow *zappy::client::GameManager::getWindow() const
{
	return _window;
}
