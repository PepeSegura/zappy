#include "Player.hpp"

void	Player::IncantationBgn()
{
	is_encantating = true;
	encantation_prechecked = false;
	Command_Data IncantationEndCmd;
	IncantationEndCmd.cmd = Command::IncantationEnd;
	IncantationEndCmd.cmd_name = "incantation_end";

	command_queue.insert(command_queue.begin() + 1, IncantationEndCmd);
	send_buffer = "elevation en cours\n";
}

void	Player::IncantationEnd()
{
	this->level++;
	send_buffer = "niveau actuel : "+ std::to_string(level) +"\n";
	is_encantating = false;
}
