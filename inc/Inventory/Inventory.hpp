#pragma once

# include <ostream>

class Inventory
{
	private:
		int nourriture;
		int linemate;
		int draumere;
		int sibur;
		int mendiane;
		int phiras;
		int thystame;

	public:
		Inventory();
		~Inventory();
		Inventory&  operator=(Inventory const &other);
		Inventory&  operator+(Inventory const &other);

		int get_nourriture() const;
		int get_linemate() const;
		int get_draumere() const;
		int get_sibur() const;
		int get_mendiane() const;
		int get_phiras() const;
		int get_thystame() const;
};
	
std::ostream& operator<<(std::ostream &out, Inventory const &other);
