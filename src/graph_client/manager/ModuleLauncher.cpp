//
// EPITECH PROJECT, 2018
// cpp_zappy
// File description:
// ModuleLauncher.cpp
//

#include "ModuleLauncher.hpp"

zappy::client::module::ModuleLauncher::ModuleLauncher(GameManager &manager) :
	_manager(manager)
{
	_manager.start();
	_modules["GameModule"] =
		std::make_shared<zappy::client::module::SfmlModuleMyWorld>
		        (*_manager.getWindow());
}

void zappy::client::module::ModuleLauncher::launchModule
	(const std::string &name)
{
	auto it = _modules.find(name);
	if (it == _modules.end())
		return;
/*		throw Exception("ModuleLauncher",
			"Module " + name + " doesn't exist");*/
	std::shared_ptr<ISfmlModule> module = it->second;
	module->start();
	if (module->start() != BEGIN)
		return;
/*		throw Exception("ModuleLauncher",
			"Failed to launch module " + name);*/
	bool running = loopModule(module);
	module->close();
	std::string next = module->nextModule();
	if (!next.empty() && running)
		launchModule(next);
}

bool zappy::client::module::ModuleLauncher::loopModule
	(std::shared_ptr<zappy::client::module::ISfmlModule> &module)
{
	Clock clock(0);
	bool running = _manager.isOpen();
	while (running && module->update() == CONTINUE)
	{
		_manager.handleEvents(*module);
		_manager.display();
		clock.reset();
		while (clock.getElapsedTime() < 16)
			std::this_thread::sleep_for(std::chrono::milliseconds(
				16 - clock.getElapsedTime()));
		_manager.clean();
		running = _manager.isOpen();
	}
	return running;
}
