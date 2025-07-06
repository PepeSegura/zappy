#include "Inventory.hpp"

Inventory::Inventory()
{
	this->nourriture = 0;
	this->linemate = 0;
	this->draumere = 0;
	this->sibur = 0;
	this->mendiane = 0;
	this->phiras = 0;
	this->thystame = 0;
}

Inventory::~Inventory()
{

}

Inventory&  Inventory::operator=(Inventory const &other)
{
	this->nourriture = other.nourriture;
	this->linemate = other.linemate;
	this->draumere = other.draumere;
	this->sibur = other.sibur;
	this->mendiane = other.mendiane;
	this->phiras = other.phiras;
	this->thystame = other.thystame;
	return (*this);
}

Inventory&  Inventory::operator+(Inventory const &other)
{
	this->nourriture += other.nourriture;
	this->linemate += other.linemate;
	this->draumere += other.draumere;
	this->sibur += other.sibur;
	this->mendiane += other.mendiane;
	this->phiras += other.phiras;
	this->thystame += other.thystame;
	return (*this);
}

int Inventory::get_nourriture() const
{
	return (this->nourriture);
}

int Inventory::get_linemate() const
{
	return (this->linemate);
}

int Inventory::get_draumere() const
{
	return (this->draumere);
}

int Inventory::get_sibur() const
{
	return (this->sibur);
}

int Inventory::get_mendiane() const
{
	return (this->mendiane);
}

int Inventory::get_phiras() const
{
	return (this->phiras);
}

int Inventory::get_thystame() const
{
	return (this->thystame);
}


std::ostream& operator<<(std::ostream &out, Inventory const &other)
{
    out << "Nourriture: " << other.get_nourriture() << std::endl
		<< "Linemate:   " << other.get_linemate()   << std::endl
		<< "Draumere:   " << other.get_draumere()   << std::endl
		<< "Sibur:      " << other.get_sibur()      << std::endl
		<< "Mendiane:   " << other.get_mendiane()   << std::endl
		<< "Phiras:     " << other.get_phiras()     << std::endl
		<< "Thystame:   " << other.get_thystame()   << std::endl
		;
    return (out);
}
