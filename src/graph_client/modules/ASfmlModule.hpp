//
// EPITECH PROJECT, 2018
// SfmlTests
// File description:
// ISfmlModule.hpp
//

#ifndef SFMLTESTS_ASFMLMODULE_HPP
#define SFMLTESTS_ASFMLMODULE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace zappy::client::module {
	class ASfmlModule {
		public:
		explicit ASfmlModule(sf::RenderWindow * window) :
			_window(window) {};
		private:
			sf::RenderWindow *_window;
	};
}

#endif //SFMLTESTS_ASFMLMODULE_HPP
