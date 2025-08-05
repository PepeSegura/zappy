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

double Utils::get_distance(int ay, int ax, int by, int bx)
{
	int dy = abs(ay - by);
	int dx = abs(ax - bx);

	double distance = sqrt((dy * dy) + (dx * dx));
	std::cout << "Distance: " << distance << std::endl;
	return (distance);
}

std::vector<std::string> Utils::split_by_spaces(const std::string& s) {
	std::vector<std::string> result;
	auto it = s.begin();
	
	while (it != s.end()) {
		it = std::find_if_not(it, s.end(), [](char c) { return c == ' '; });
		
		auto end = std::find_if(it, s.end(), [](char c) { return c == ' '; });
		
		if (it != end) {
			result.emplace_back(it, end);
			it = end;
		}
	}
	
	return result;
}
