#include "Player.hpp"

void	Player::IncantationBgn(Incantation &incantation)
{
	is_encantating = true;
	encantation_prechecked = false;
	incantationFailed = false;
	Command_Data IncantationStartCmd;
	IncantationStartCmd.cmd = Command::IncantationStart;
	IncantationStartCmd.cmd_name = "incantation_start";

	command_queue.insert(command_queue.begin() + 1, IncantationStartCmd);
	incantationStartTime = incantation.start;
	//send_buffer = "elevation en cours\n";
}

void	Player::IncantationStart()
{
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
