#pragma once

# ifndef UTILS_HPP
#  define UTILS_HPP

#  include <algorithm>
#  include <chrono>
#  include <iostream>
#  include <random>
#  include <vector>
#  include <string>
#  include <cctype>

namespace Utils {

	int64_t	get_current_ms();
	int		random_between(int, int);
	double	get_distance(int ay, int ax, int by, int bx);
	std::vector<std::string> split_by_spaces(const std::string& s);
	int 	hash_item(std::string item);
}

#endif
