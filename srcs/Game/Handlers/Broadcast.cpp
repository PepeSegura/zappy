#include "Game.hpp"

double	Game::dist_copy_pos(Player *origin, Player *dest, int y, int x)
{
	int ay = origin->get_y();
	int ax = origin->get_x();
	int by = dest->get_y();
	int bx = dest->get_x();
	std::cout << "Getting distance from: (" << ay <<", "<< ax << ") to -> (" << by << ", " << bx <<")"<< std::endl;

	return (Utils::get_distance(ay, ax, (by + (y * this->map_height)), (bx + (x * this->map_width))));
}

std::pair<int, int>	Game::dda(Player *origin, Player *dest, int y_mod, int x_mod)
{
	int ay = origin->get_y();
	int ax = origin->get_x();
	int by = dest->get_y() + (y_mod * this->map_height);
	int bx = dest->get_x() + (x_mod * this->map_width);

	int dy = by - ay;
	int dx = bx - ax;

	int step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	double inc_x = dx / (double)step;
	double inc_y = dy / (double)step;

	double x = ax;
	double y = ay;

	for (int i = 0; i < step - 1; i++)
	{
		std::cout << "(" << y << ", " << x << ")" << std::endl;
		y += inc_y;
		x += inc_x;
	}
	std::cout << "BEFORE CONVERSION: (" << y << ", " << x << ")" << std::endl;
	y -= (y_mod * this->map_height);
	x -= (x_mod * this->map_width);
	std::cout << "AFTER CONVERSION: (" << y << ", " << x << ")" << std::endl;
	return (std::pair<int, int>(y, x));
}

uint8_t Game::get_sound_direction(Player *origin, Player *dest)
{
	double closest_dist = std::numeric_limits<double>::max();
	int closest_y = INT32_MAX;
	int closest_x = INT32_MAX;

	for (int dy = -1; dy <= 1; dy++)
	{
		for (int dx = -1; dx <= 1; dx++)
		{
			double distance = dist_copy_pos(origin, dest, dy, dx);
			if (distance < closest_dist)
			{
				closest_dist = distance;
				closest_y = dy;
				closest_x = dx;
			}
		}
	}
	std::cout << "Nearest enemie is in map: (" << closest_y << ", " << closest_x << ")" << std::endl;
	std::pair<int,int> coords = dda(origin, dest, closest_y, closest_x);

	int cnt = 1;
	int dy, dx, py, px, i;

	switch (dest->get_dir()) {
		case 'N':
			dy = 0;
			dx = -1;
			py = dest->get_y() - 1;
			px = dest->get_x();
			break;
		case 'S':
			dy = 0;
			dx = 1;
			py = dest->get_y() + 1;
			px = dest->get_x();
			break;
		case 'W':
			dy = 1;
			dx = 0;
			py = dest->get_y();
			px = dest->get_x() - 1;
			break;
		case 'E':
			dy = -1;
			dx = 0;
			py = dest->get_y();
			px = dest->get_x() + 1;
			break;
		default:
			break;
	}

	std::cout << "Checking player at (" << std::to_string(dest->get_y()) << ", " << std::to_string(dest->get_x()) << ") looking at " << dest->get_dir() + 'A' << std::endl;

	for (i = 1; i < 9; ++i) {
		if (py < 0) py = map_height - 1;
		if (px < 0) px = map_width - 1;
		if (py == map_height) py = 0;
		if (px == map_width) px = 0;
		std::cout << "Checking coord (" << std::to_string(px) << ", " << std::to_string(py) << "), looking for (" << std::to_string(coords.second) << ", " << std::to_string(coords.first) << ")\n";
		if (py == coords.first && px == coords.second) {
			std::cout << "Found!!!\n";
			break ;
		}
		py += dy;
		px += dx;
		++cnt;
		if (cnt == 2) {
			if (dy == -1 && dx == 0) {
				dy = 0;
				dx = -1;
			} else if (dy == 1 && dx == 0) {
				dy = 0;
				dx = 1;
			} else if (dy == 0 && dx == -1) {
				dy = 1;
				dx = 0;
			} else if (dy == 0 && dx == 1) {
				dy = -1;
				dx = 0;
			}
			cnt = 0;
		}
	}

	return (i);
}

void Game::_Broadcast(Player *p)
{
	std::string msg = p->get_current_command().args;
	std::cout << "EXECUTING BROADCAST\n";
	for (auto [fd, player] : this->playersfd_map)
	{
		if (player->get_handshake() == true && player != p)
		{
			player->set_send_buffer("message " + std::to_string(get_sound_direction(p, player)) + "," + msg + "\n");
		}
	}
	(void)p;
}
