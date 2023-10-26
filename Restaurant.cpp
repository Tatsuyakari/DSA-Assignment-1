#include "main.h"

class imp_res : public Restaurant
{
private:
	customer *head;
	customer *X; // node X is the current node(customer)
	int size = 0;
	bool checkName(string name)
	{
		customer *temp = X;
		for (int i = 0; i < size; i++)
		{
			if (temp->name == name)
				return true;
			temp = temp->next;
		}
		return false;
	}

public:
	imp_res(){};
	// destructor
	~imp_res()
	{
		customer *temp = head;
		for (int i = 0; i < size; i++)
		{
			customer *next = temp->next;
			delete temp;
			temp = next;
		}
	}
	void RED(string name, int energy)
	{
		if (energy == 0 || size == MAXSIZE || checkName(name))
			return;
		cout << name << " " << energy << endl;
		customer *cus = new customer(name, energy, nullptr, nullptr);
		if (head == nullptr)
		{
			head = cus;
			head->next = head;
			head->prev = head;
			X = head;
		}
		else if (size < MAXSIZE / 2) // Case size < MAXSIZE / 2
		{
			if (cus->energy >= X->energy)
			{
				// add cus after X
				cus->next = X->next;
				cus->prev = X;
				X->next->prev = cus;
				X->next = cus;
				X = cus;
			}
			else
			{
				// add cus before X
				cus->next = X;
				cus->prev = X->prev;
				X->prev->next = cus;
				X->prev = cus;
				// update X
				X = cus;
			}
		}
		else // Case size >= MAXSIZE / 2
		{
			// calculate max RES (=abs(cus->energy - all->energy))
			int max_res = 0;
			customer *temp = X;
			for (int i = 0; i < size; i++)
			{
				int res = abs(cus->energy - temp->energy);
				if (res > max_res)
					max_res = res;
				temp = temp->next;
			}
			// find the node with max RES
			temp = X;
			for (int i = 0; i < size; i++)
			{
				int res = abs(cus->energy - temp->energy);
				if (res == max_res)
					break;
				temp = temp->next;
			}
			// Same as Case size < MAXSIZE / 2
			if (cus->energy >= X->energy)
			{
				// add cus after X
				cus->next = X->next;
				cus->prev = X;
				X->next->prev = cus;
				X->next = cus;
				X = cus;
			}
			else
			{
				// add cus before X
				cus->next = X;
				cus->prev = X->prev;
				X->prev->next = cus;
				X->prev = cus;
				// update X
				X = cus;
			}
		}
		size++;
		cout << MAXSIZE << endl;
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
	}
	void PURPLE()
	{
		cout << "purple" << endl;
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
	}
	void LIGHT(int num)
	{
		cout << size << endl;
		if (num == 0)
			return;
		if (num > 0)
		{
			for (int i = 0; i < size; i++)
			{
				X->print();
				X = X->next;
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				X->print();
				X = X->prev;
			}
		}
	}
};