//
// EPITECH PROJECT, 2018
// cpp_zappy
// File description:
// Clock.hpp
//

#ifndef CPP_ZAPPY_CLOCK_HPP
#define CPP_ZAPPY_CLOCK_HPP

#include <chrono>
#include <iostream>

namespace zappy::client {
	class Clock {
	public:
		Clock();
		Clock(long interval);
		void reset();
		void setTimerInterval(long interval);
		unsigned long long getElapsedTime() const;
		bool isReady() const;
	private:
		std::chrono::time_point<std::chrono::steady_clock> _lastReset;
		unsigned long long _interval;
	};
}

#endif /* CPP_ZAPPY_CLOCK_HPP */
