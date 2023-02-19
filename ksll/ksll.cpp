#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class BinTree;

class que {
	BinTree* value;
	que* next;

public:

	que() {

		value = NULL;
		next = NULL;
	}

	void push(BinTree* el);

	BinTree* pop();

};

class stek {

	BinTree* value;
	stek* next;

public:

	stek() {

		value = NULL;
		next = NULL;
	}
	void push(BinTree* el);
	BinTree* pop();

};

int konv(int c) {
	int sum = 0;
	int i = 0;
	while (c / 10 != 0) {
		sum += (c % 10) * pow(2, i);
		i++;
		c = c / 10;
	}
	sum += (c % 10) * pow(2, i);
	return sum;
}

class BinTree {

	friend class que;
	friend class stek;

	int vek;
	int value;
	int deep;
	int kolvo;
	BinTree* left;
	BinTree* right;

	void obh2(que* obhod, que* all, BinTree* ss) {

		BinTree* a = new BinTree;
		a = obhod->pop();

		if (a != NULL)
		{
			all->push(a);

			if (a->left != NULL)
				obhod->push(a->left);

			if (a->right != NULL)
				obhod->push(a->right);

			obh2(obhod, all, ss);
			return;
		}
	}

public:

	int getPos() {
		return konv(vek);
	}

	int getValue() {
		return value;
	}

	int getLevel() {
		return deep;
	}

	int getAmount() {
		return kolvo;
	}

	BinTree() {
		deep = 0;
		kolvo = 0;
		vek = 0;
		value = NULL;
		left = NULL;
		right = NULL;
	}

	void Push(int a) {

		if (value == NULL && kolvo == 0)
		{
			value = a;
			kolvo++;
			return;
		}

		if (this->value > a) {

			if (this->left != NULL)
				this->left->Push(a);

			if (this->left == NULL)
			{
				left = new BinTree;
				left->value = a;
				left->vek = vek * 10;
				left->deep += deep + 1;
				left->kolvo++;
			}
		}

		if (this->value < a) {

			if (right != NULL)
				right->Push(a);

			if (right == NULL)
			{
				right = new BinTree;
				right->value = a;
				right->vek = vek * 10 + 1;
				right->deep += deep + 1;
				right->kolvo++;
			}
		}

 		if (this->value == a)
			kolvo++;
	}

	~BinTree() {
		left = NULL;
		right = NULL;
	}

	void check() {
		if (left != NULL)
			left->check();

		cout << this->value << " ";

		if (right != NULL)
			right->check();
	}
	
	que* DFS() {

		que* obhod = new que;
		que* all = new que;

		obhod->push(this);

		obh2(obhod, all, this);

		return all;
	}

	int GetMaxDeep() {

		que* all = this->DFS();

		BinTree* ff = new BinTree;
		int maxdeep = 0;

		while ((ff = all->pop()) != NULL) 
		{
			if (ff->deep > maxdeep)
				maxdeep = ff->deep;
		}

		return maxdeep;
	}

	void printTree(int otst = 3) {

		que* all = this->DFS();

		int min = this->GetMaxDeep();

		cout << endl;

		BinTree* f = new BinTree;
		BinTree* ff = new BinTree;

		ff = NULL;
		int a = 0;
		int pos = 0;
		while ((f = all->pop()) != NULL) {

			pos = f->getPos();

			if (ff == NULL)
			{
				cout << setw(otst * (pow(2, (min - f->getLevel()) - 1)) * 2 - 1) << f->getValue();
				ff = f;
				continue;
			}

			if (ff != NULL) {

				if (f->getLevel() != ff->getLevel())
				{
					a = 0;
					cout << endl;
					cout << setw(otst * (pow(2, (min - f->getLevel()) - 1)) * 2 - 1 + (otst * (pow(2, (min - f->getLevel()) - 1)) * 2) * 2 * (pos - a)) << f->getValue();
				}

				if (f->getLevel() == ff->getLevel())
				{
					cout << setw((otst * (pow(2, (min - f->getLevel()) - 1)) * 2) * 2 * (pos - a)) << f->getValue();
				}
			}
			a = pos;
			ff = f;
		}
	}
};

void stek::push(BinTree* el) {

		if (value == NULL) {
			value = el;
			return;
		}

		stek* a = new stek;

		a->value = value;
		a->next = next;

		value = el;
		next = a;

	}

BinTree* stek::pop() {

	if (value == NULL) {
		return NULL;
	}

	if (next == NULL)
	{
		BinTree* af = value;
		value = NULL;
		return af;
	}

	BinTree* s;

	s = value;

	value = next->value;
	next = next->next;

	return s;
}
	
void que::push(BinTree* el) {

	if (value == NULL) {
		value = el;
		return;
	}

	que* a = new que;

	a->value = value;
	a->next = next;

	value = el;
	next = new que;
	next->next = a->next;
	next->value = a->value;
}

BinTree* que::pop() {

	if (value == NULL)
		return NULL;

	if (next == NULL)
	{
		BinTree* ll = value;
		value = NULL;
		return ll;
	}

	if (next->next == NULL)
	{
		BinTree* a = next->value;
		next = NULL;
		return a;
	}

	if (next != NULL)
		return next->pop();

	BinTree* a = value;
	value = NULL;
	return a;
}


int main() {

	BinTree* a = new BinTree;

	int f;

	do
	{
		cin >> f;
		a->Push(f);

	} while (f != 0);

	a->printTree();

	cout << endl;



}



