//
// EPITECH PROJECT, 2018
// cpp_zappy
// File description:
// ModuleLauncher.hpp
//

#ifndef CPP_ZAPPY_MODULELAUNCHER_HPP
#define CPP_ZAPPY_MODULELAUNCHER_HPP

#include <memory>
#include <thread>
#include "GameManager.hpp"
#include "../GameInfo.hpp"
#include "Clock.hpp"
#include "../modules/SfmlModuleMyWorld.hpp"

namespace zappy::client::module {
	class ModuleLauncher {
	public:
		explicit ModuleLauncher(GameManager &_engine);
		void launchModule(const std::string &);
	private:
		bool loopModule(std::shared_ptr<ISfmlModule> &);

		GameManager &_manager;
		std::map<std::string, std::shared_ptr<ISfmlModule>> _modules;
		GameInfo _info;
	};
}

#endif /* CPP_ZAPPY$_MODULELAUNCHER_HPP */