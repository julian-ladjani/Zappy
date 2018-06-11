//
// EPITECH PROJECT, 2018
// SfmlTests
// File description:
// ISfmlModule.hpp
//

#ifndef SFMLTESTS_ISFMLMODULE_HPP
#define SFMLTESTS_ISFMLMODULE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

namespace zappy::client::module {
	enum ModuleStatus {
		BEGIN,
		CONTINUE,
		END
	};

	class ISfmlModule {
		public:
		virtual ModuleStatus start() = 0;
		virtual ModuleStatus update() = 0;
		virtual void handleEvent(sf::Event &event) = 0;
		virtual ModuleStatus close() = 0;
		virtual std::string nextModule() = 0;
	};
}

#endif //SFMLTESTS_ISFMLMODULE_HPP
