//
// EPITECH PROJECT, 2018
// SfmlTests
// File description:
// DislayManager.hpp
//

#ifndef SFMLTESTS_DISLAYMANAGER_HPP
#define SFMLTESTS_DISLAYMANAGER_HPP

#include "SFML/Graphics.hpp"
#include "../modules/ISfmlModule.hpp"

namespace zappy::client {
	class GameManager {
	public:
		void clean();
		bool start();
		void stop();
		void display();
		int handleEvents(module::ISfmlModule &module);
		bool isOpen();
		sf::RenderWindow *getWindow() const;
	private:
		sf::RenderWindow *_window;
	};
}

#endif //SFMLTESTS_DISLAYMANAGER_HPP
