#pragma once

# include <ostream>
# include <iostream>

class Inventory
{
	private:
		/* food */
		int nourriture;

		/* minerals */
		int linemate;
		int deraumere;
		int sibur;
		int mendiane;
		int phiras;
		int thystame;

	public:
		Inventory();
		~Inventory();
		Inventory(const Inventory& other) = default; // shallow copy
		Inventory&  operator=(const Inventory &other) = default;
		Inventory&  operator+(const Inventory &other);

		int get_item(std::string);
		int get_nourriture() const;
		int get_linemate() const;
		int get_deraumere() const;
		int get_sibur() const;
		int get_mendiane() const;
		int get_phiras() const;
		int get_thystame() const;

		void add_item(std::string, int);
		void add_nourriture(int);
		void add_linemate(int);
		void add_deraumere(int);
		void add_sibur(int);
		void add_mendiane(int);
		void add_phiras(int);
		void add_thystame(int);
};
	
std::ostream& operator<<(std::ostream &out, Inventory const &other);
