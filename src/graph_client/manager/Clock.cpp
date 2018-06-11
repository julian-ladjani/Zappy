//
// EPITECH PROJECT, 2018
// cpp_zappy
// File description:
// Clock.cpp
//

#include "Clock.hpp"

zappy::client::Clock::Clock() :
	_lastReset(std::chrono::steady_clock::now()), _interval(0)
{
}

zappy::client::Clock::Clock(const long interval) :
	_lastReset(std::chrono::steady_clock::now()), _interval(0)
{
	setTimerInterval(interval);
}

void zappy::client::Clock::reset()
{
	_lastReset = std::chrono::steady_clock::now();
}

void zappy::client::Clock::setTimerInterval(const long interval)
{
	_interval = interval;
}

unsigned long long zappy::client::Clock::getElapsedTime() const
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now() - _lastReset).count();
}

bool zappy::client::Clock::isReady() const
{
	return getElapsedTime() >= _interval;
}
