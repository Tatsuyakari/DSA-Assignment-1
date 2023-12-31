#include "main.h"
// Modified version of Insertion Sort for varying increments

class imp_res : public Restaurant
{
private:
	// node X is the current node(customer)
	customer *X = nullptr;
	// queue of customers who are waiting for a seat
	customer *queue_head = nullptr;
	// sequence of customers in the restaurant
	customer *sequence_head = nullptr;
	int size, queue_size, sequence_size = 0;
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
	bool checkNameInSequence(string name)
	{
		customer *temp = sequence_head;
		for (int i = 0; i < sequence_size; i++)
		{
			if (temp->name == name)
				return true;
			temp = temp->next;
		}
		return false;
	}
	void enQueue(customer *cus)
	{
		if (queue_head == nullptr)
		{
			queue_head = cus;
			queue_head->next = queue_head;
			queue_head->prev = queue_head;
		}
		else
		{
			cus->next = queue_head;
			cus->prev = queue_head->prev;
			queue_head->prev->next = cus;
			queue_head->prev = cus;
		}
		queue_size++;
		// // cout << "queue_size: " << queue_size << endl;
		for (int i = 0; i < queue_size; i++)
		{
			// queue_head->print();
			queue_head = queue_head->next;
		}
	}
	void deQueue()
	{
		if (queue_head == nullptr)
			return;
		if (queue_size == 1)
		{
			customer *temp = queue_head;
			queue_head = nullptr;
			queue_size = 0;
			delete temp;
		}
		else
		{
			customer *temp = queue_head;
			queue_head->prev->next = queue_head->next;
			queue_head->next->prev = queue_head->prev;
			queue_head = queue_head->next;
			delete temp;
		}
		queue_size--;
	}

	void enSequence(string name, int energy)
	{
		customer *cus = new customer(name, energy, nullptr, nullptr);
		if (sequence_head == nullptr)
		{
			sequence_head = cus;
			sequence_head->next = sequence_head;
			sequence_head->prev = sequence_head;
		}
		else
		{
			cus->next = sequence_head;
			cus->prev = sequence_head->prev;
			sequence_head->prev->next = cus;
			sequence_head->prev = cus;
		}
		sequence_size++;
		// // cout << "sequence_size: " << sequence_size << endl;
		for (int i = 0; i < sequence_size; i++)
		{
			// sequence_head->print();
			sequence_head = sequence_head->next;
		}
	}
	void deSequence()
	{
		if (sequence_head == nullptr)
			return;
		if (sequence_size == 1)
		{
			customer *temp = sequence_head;
			sequence_head = nullptr;
			sequence_size = 0;
			delete temp;
		}
		else
		{
			customer *temp = sequence_head;
			sequence_head->prev->next = sequence_head->next;
			sequence_head->next->prev = sequence_head->prev;
			sequence_head = sequence_head->next;
			delete temp;
		}
		sequence_size--;
	}
	void remove(string name, int energy)
	{
		if (size == 1)
		{
			customer *temp = X;
			X = nullptr;
			size = 0;
			delete temp;
			return;
		}
		if (energy > 0)
		{
			// // cout << "Clear Right" << endl;
			for (int i = 0; i < size; i++)
			{
				if (X->name == name)
				{
					customer *temp = X;
					X = X->next;
					X->prev = temp->prev;
					X->prev->next = X;
					delete temp;
					size--;
					break;
				}
				X = X->next;
			}
		}
		else
		{
			// // cout << "Clear Left" << endl;
			for (int i = 0; i < size; i++)
			{
				if (X->name == name)
				{
					customer *temp = X;
					X = X->prev;
					X->next = temp->next;
					X->next->prev = X;
					delete temp;
					size--;
					break;
				}
				X = X->next;
			}
		}
	}
	void removeinSequence(string name, int energy)
	{
		if (sequence_size == 1)
		{
			customer *temp = sequence_head;
			sequence_head = nullptr;
			sequence_size = 0;
			delete temp;
			return;
		}
		if (energy > 0)
		{
			// // cout << "Clear Right" << endl;
			for (int i = 0; i < sequence_size; i++)
			{
				if (sequence_head->name == name)
				{
					customer *temp = sequence_head;
					sequence_head = sequence_head->next;
					sequence_head->prev = temp->prev;
					sequence_head->prev->next = sequence_head;
					delete temp;
					sequence_size--;
					break;
				}
				sequence_head = sequence_head->next;
			}
		}
		else
		{
			// // cout << "Clear Left" << endl;
			for (int i = 0; i < sequence_size; i++)
			{
				if (sequence_head->name == name)
				{
					customer *temp = sequence_head;
					sequence_head = sequence_head->prev;
					sequence_head->next = temp->next;
					sequence_head->next->prev = sequence_head;
					delete temp;
					sequence_size--;
					break;
				}
				sequence_head = sequence_head->next;
			}
		}
	}
	void removeinQueue(string name, int energy)
	{
		if (queue_size == 1)
		{
			customer *temp = queue_head;
			queue_head = nullptr;
			queue_size = 0;
			delete temp;
			return;
		}
		if (energy > 0)
		{
			// // cout << "Clear Right" << endl;
			for (int i = 0; i < queue_size; i++)
			{
				if (queue_head->name == name)
				{
					customer *temp = queue_head;
					queue_head = queue_head->next;
					queue_head->prev = temp->prev;
					queue_head->prev->next = queue_head;
					delete temp;
					queue_size--;
					break;
				}
				queue_head = queue_head->next;
			}
		}
		else
		{
			// // cout << "Clear Left" << endl;
			for (int i = 0; i < queue_size; i++)
			{
				if (queue_head->name == name)
				{
					customer *temp = queue_head;
					queue_head = queue_head->prev;
					queue_head->next = temp->next;
					queue_head->next->prev = queue_head;
					delete temp;
					queue_size--;
					break;
				}
				queue_head = queue_head->next;
			}
		}
	}

public:
	imp_res(){};
	// destructor
	~imp_res()
	{
		customer *temp = X;
		for (int i = 0; i < size; i++)
		{
			customer *next = temp->next;
			delete temp;
			temp = next;
		}
		temp = queue_head;
		for (int i = 0; i < queue_size; i++)
		{
			customer *next = temp->next;
			delete temp;
			temp = next;
		}
		temp = sequence_head;
		for (int i = 0; i < sequence_size; i++)
		{
			customer *next = temp->next;
			delete temp;
			temp = next;
		}
	}

	void RED(string name, int energy)
	{
		// // cout << "-----------------" << endl;
		// // cout << "RED" << name << " " << energy << endl;
		if (energy == 0 || (size == MAXSIZE && queue_size == MAXSIZE) || checkName(name))
			return;
		// // cout << name << " " << energy << endl;
		customer *cus = new customer(name, energy, nullptr, nullptr);
		// if name is not in the restaurant but in sequence,don't add it
		if (!checkNameInSequence(name))
		{
			enSequence(name, energy);
		}
		if (size == MAXSIZE && queue_size < MAXSIZE)
		{
			enQueue(cus);
			return;
		}

		if (X == nullptr)
		{
			X = cus;
			X->next = X;
			X->prev = X;
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
		// // cout << MAXSIZE << endl;
		// // cout << "-----------------" << endl;
	}
	void BLUE(int num)
	{
		if (num == 0 || size == 0)
			return;
		for (int i = 0; i < num; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (X->name == sequence_head->name)
				{
					// // cout << "remove: " << X->name << " " << X->energy << endl;
					remove(X->name, X->energy);
					deSequence();
					break;
				}
				X = X->next;
			}
		}

		while (queue_size > 0 && size < MAXSIZE)
		{
			RED(queue_head->name, queue_head->energy);
			deQueue();
		}
	}
	void PURPLE()
	{
		// // cout << "purple" << endl;
	}
	void REVERSAL()
	{
		// // cout << "reversal" << endl;
	}
	void UNLIMITED_VOID()
	{
		// // cout << "unlimited_void" << endl;
	}
	void DOMAIN_EXPANSION()
	{
		// cout << "domain_expansion" << endl;
		int sum = 0;
		customer *temp = sequence_head;
		for (int i = 0; i < sequence_size; i++)
		{
			sum += temp->energy;
			temp = temp->next;
		}
		// cout << "sum: " << sum << endl;

		if (sum > 0)
		{
			temp = sequence_head;
			for (int i = 0; i < sequence_size; i++)
			{
				if (temp->energy < 0)
				{
					cout << temp->name << "-" << temp->energy << endl;
					removeinSequence(temp->name, temp->energy);
					i--;
				}
				temp = temp->next;
			}
			temp = X;
			for (int i = 0; i < size; i++)
			{
				if (temp->energy < 0)
				{
					remove(temp->name, temp->energy);
				}
				temp = temp->next;
			}
			temp = queue_head;
			for (int i = 0; i < queue_size; i++)
			{
				if (temp->energy < 0)
				{
					removeinQueue(temp->name, temp->energy);
				}
				temp = temp->next;
			}
		}
		else if (sum < 0)
		{
			temp = sequence_head;
			for (int i = 0; i < sequence_size; i++)
			{
				if (temp->energy > 0)
				{
					cout << temp->name << "-" << temp->energy << endl;
					removeinSequence(temp->name, temp->energy);
					i--;
				}
				temp = temp->next;
			}
			temp = X;
			for (int i = 0; i < size; i++)
			{
				if (temp->energy > 0)
				{
					remove(temp->name, temp->energy);
				}
				temp = temp->next;
			}
			temp = queue_head;
			for (int i = 0; i < queue_size; i++)
			{
				if (temp->energy > 0)
				{
					removeinQueue(temp->name, temp->energy);
				}
				temp = temp->next;
			}
		}
		else if (sum == 0)
		{
			// Print Queue
			for (int i = 0; i < queue_size; i++)
			{
				queue_head->print();
				queue_head = queue_head->next;
			}
		}
	}
	void LIGHT(int num)
	{
		// cout << "-----------------" << endl;
		// cout << size << endl;
		if (num == 0)
		{
			for (int i = 0; i < queue_size; i++)
			{
				queue_head->print();
				queue_head = queue_head->next;
			}
		}
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
		// cout << "-----------------" << endl;
	}
};