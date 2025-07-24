#include "Utils.hpp"

int64_t Utils::get_current_ms()
{
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	return (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
}

int Utils::random_between(int a, int b)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist_ab(a, b);
	return (dist_ab(rng));
}
