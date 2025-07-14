#include "Inventory.hpp"

Inventory::Inventory()
{
	this->nourriture = 0;
	this->linemate = 0;
	this->deraumere = 0;
	this->sibur = 0;
	this->mendiane = 0;
	this->phiras = 0;
	this->thystame = 0;
}

Inventory::~Inventory()
{
}

Inventory&  Inventory::operator+(const Inventory &other)
{
	this->nourriture = this->nourriture + other.nourriture;
	this->linemate = this->linemate + other.linemate;
	this->deraumere = this->deraumere + other.deraumere;
	this->sibur = this->sibur + other.sibur;
	this->mendiane = this->mendiane + other.mendiane;
	this->phiras = this->phiras + other.phiras;
	this->thystame = this->thystame + other.thystame;
	return (*this);
}


/*_________GETTERS__________*/

int Inventory::get_nourriture() const
{
	return (this->nourriture);
}

int Inventory::get_linemate() const
{
	return (this->linemate);
}

int Inventory::get_deraumere() const
{
	return (this->deraumere);
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

/*__________SETTERS__________*/

void Inventory::add_nourriture(int new_ammount)
{
	this->nourriture += new_ammount;
}

void Inventory::add_linemate(int new_ammount)
{
	this->linemate += new_ammount;
}

void Inventory::add_deraumere(int new_ammount)
{
	this->deraumere += new_ammount;
}

void Inventory::add_sibur(int new_ammount)
{
	this->sibur += new_ammount;
}

void Inventory::add_mendiane(int new_ammount)
{
	this->mendiane += new_ammount;
}

void Inventory::add_phiras(int new_ammount)
{
	this->phiras += new_ammount;
}

void Inventory::add_thystame(int new_ammount)
{
	this->thystame += new_ammount;
}


std::ostream& operator<<(std::ostream &out, Inventory const &other)
{
    out << "Nourriture: " << other.get_nourriture() << std::endl
		<< "Linemate:   " << other.get_linemate()   << std::endl
		<< "deraumere:  " << other.get_deraumere() << std::endl
		<< "Sibur:      " << other.get_sibur()      << std::endl
		<< "Mendiane:   " << other.get_mendiane()   << std::endl
		<< "Phiras:     " << other.get_phiras()     << std::endl
		<< "Thystame:   " << other.get_thystame()   << std::endl
		<< "--------------------------------------" << std::endl
		;
    return (out);
}
