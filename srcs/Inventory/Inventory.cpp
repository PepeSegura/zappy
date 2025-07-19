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

int	Inventory::get_item(std::string item)
{
	if (item == "nourriture")	return (this->get_nourriture());
	if (item == "linemate")		return (this->get_linemate());
	if (item == "deraumere")	return (this->get_deraumere());
	if (item == "sibur")		return (this->get_sibur());
	if (item == "mendiane")		return (this->get_mendiane());
	if (item == "phiras")		return (this->get_phiras());
	if (item == "thystame")		return (this->get_thystame());
	return (-1);
}

void Inventory::add_item(std::string item, int new_ammout)
{
	if (item == "nourriture")	this->add_nourriture(new_ammout);
	if (item == "linemate")		this->add_linemate(new_ammout);
	if (item == "deraumere")	this->add_deraumere(new_ammout);
	if (item == "sibur")		this->add_sibur(new_ammout);
	if (item == "mendiane")		this->add_mendiane(new_ammout);
	if (item == "phiras")		this->add_phiras(new_ammout);
	if (item == "thystame")		this->add_thystame(new_ammout);
}

void Inventory::add_nourriture(int new_ammount)
{
	if ((this->nourriture + new_ammount) >= 0) {
		this->nourriture += new_ammount;
	} else {
		this->nourriture = 0;
	}
}

void Inventory::add_linemate(int new_ammount)
{
	if ((this->linemate + new_ammount) >= 0) {
		this->linemate += new_ammount;
	} else {
		this->linemate = 0;
	}
}

void Inventory::add_deraumere(int new_ammount)
{
	if ((this->deraumere + new_ammount) >= 0) {
		this->deraumere += new_ammount;
	} else {
		this->deraumere = 0;
	}
}

void Inventory::add_sibur(int new_ammount)
{
	if ((this->sibur + new_ammount) >= 0) {
		this->sibur += new_ammount;
	} else {
		this->sibur = 0;
	}
}

void Inventory::add_mendiane(int new_ammount)
{
	if ((this->mendiane + new_ammount) >= 0) {
		this->mendiane += new_ammount;
	} else {
		this->mendiane = 0;
	}
}

void Inventory::add_phiras(int new_ammount)
{
	if ((this->phiras + new_ammount) >= 0) {
		this->phiras += new_ammount;
	} else {
		this->phiras = 0;
	}
}

void Inventory::add_thystame(int new_ammount)
{
	if ((this->thystame + new_ammount) >= 0) {
		this->thystame += new_ammount;
	} else {
		this->thystame = 0;
	}
}


std::ostream& operator<<(std::ostream &out, Inventory const &other)
{
    out << "Nourriture: " << other.get_nourriture() << std::endl
		<< "Linemate:   " << other.get_linemate()   << std::endl
		<< "deraumere:  " << other.get_deraumere()  << std::endl
		<< "Sibur:      " << other.get_sibur()      << std::endl
		<< "Mendiane:   " << other.get_mendiane()   << std::endl
		<< "Phiras:     " << other.get_phiras()     << std::endl
		<< "Thystame:   " << other.get_thystame()   << std::endl
		<< "--------------------------------------" << std::endl
		;
    return (out);
}
