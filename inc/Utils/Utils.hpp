#pragma once

# ifndef UTILS_HPP
#  define UTILS_HPP

#  include <algorithm>
#  include <chrono>
#  include <iostream>
#  include <random>

namespace Utils {

	int64_t	get_current_ms();
	int		random_between(int, int);
}

#endif
