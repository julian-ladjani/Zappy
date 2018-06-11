#include <iostream>
#include "manager/GameManager.hpp"
#include "manager/ModuleLauncher.hpp"

int main()
{
        zappy::client::GameManager  manager;
        zappy::client::module::ModuleLauncher launcher(manager);

        launcher.launchModule("GameModule");
        manager.start();
        manager.display();
        return 0;
}