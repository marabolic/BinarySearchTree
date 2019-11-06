#include <iostream>
#include <queue> 
#include "BST.h"
using namespace std;


void Tree::addNode(int key) {
	Node* n = new Node(key);
	if (root == nullptr)
		root = n;
	else {
		Node* temp = root, *prev = nullptr;
		while (temp != nullptr) {
			prev = temp;
			if (key <= temp->key) {
				temp = temp->left;
			}
			else
				temp = temp->right;
		}
		temp = prev;
		if (key <= temp->key) {

			temp->left = n;
		}
		else
			if (key > temp->key) {
				temp->right = n;
			}
	}
}
bool Tree::nodeFound(int key) const {
	Node* temp = root;
	while (temp != nullptr) {
		if (key == temp->key)
			return true;
		else
			if (key < temp->key) {
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
	}
	return false;
}
void Tree::makeTree(int arr[], int n) {
	int i = 0;
	root = nullptr;
	while (i < n) {
		addNode(arr[i]);
		i++;
	}
}
void Tree::printInorder() const {
	if (root == nullptr) return;
	Node* temp = root;
	stack <Node*> s;
	while (true) {
		while (temp != nullptr) {
			s.push(temp);
			temp = temp->left;
		}
		//cout << "The stack is : ";
		//showstack(s);
		if (!s.empty()) {
			temp = s.top();
			cout << s.top()->key << " ";
			s.pop(); 
			temp = temp->right;
		}
		else break;
	}
}
void Tree::printLevelorder() const {
	if (root == nullptr) return;
	Node* temp = root;
	queue <Node*>	Q;
	Q.push(temp);
	while (!Q.empty()) {
		int numOfNodes = Q.size();
		while (numOfNodes > 0) {
			temp = Q.front();
			cout << temp->key << " ";
			Q.pop();
			if (temp->left != nullptr)
				Q.push(temp->left);
			if (temp->right != nullptr)
				Q.push(temp->right);
			numOfNodes--;
		}
		cout << "\n";
	}
}
void Tree::deleteNode(int key) {
	if (!nodeFound(key))
		cout << "ne postoji taj kljuc";
	else {
		Node *temp = root, *prev = nullptr;
		while (temp->key != key) {
			prev = temp;
			if (key < temp->key)
				temp = temp->left;
			else temp = temp->right;
		}
		//kraj trazenja

		//if-ovi, tri slucaja!
		Node *next = nullptr;
		if (temp->left == nullptr && temp->right == nullptr) {
			if (prev) {
				if (prev->left == temp) prev->left = nullptr;
				else if (prev->right == temp) prev->right = nullptr;
			}
			delete temp;
			temp = nullptr;
			if (!prev)
				root = next;
		} //prvi slucaj - list
		else {
			
			if (temp->left == nullptr) {
				next = temp->right;
				if (prev) {
					if (prev->left == temp) prev->left = temp->right;
					else if (prev->right == temp) prev->right = temp->left;
				}
				delete temp;
				temp = nullptr;
			}//samo desni sin
			else
				if (temp->right == nullptr) {
					next = temp->left;
					if (prev) {
						if (prev->right == temp) prev->right = temp->left;
						else if (prev->left == temp) prev->left = temp->right;
					}
					delete temp;
					temp = nullptr;
				} //samo levi sin
				else {
					next = temp->right;
					Node *prevOfNext = next;
					while (next->left != nullptr) {
						prevOfNext = next;
						next = next->left;
					}
					prevOfNext->left = next->right;
					next->left = temp->left;
					next->right = temp->right;
					if (prevOfNext == next) {
						next->right = nullptr;
					}
					if (prev) {
						if (prev->left == temp) prev->left = next;
						else if (prev->right == temp) prev->right = next;
					}
					delete temp;
					temp = nullptr;
					//cout << "\nnext koji treba da bude root " << next->key;
				}//oba sina
			//kraj slucajeva
			if (!prev)
				root = next;
			cout << "\nroot = " << root->key;
		}
		
		
	}
	
	
}
void Tree::deleteTree() {
	while (root != nullptr) {
		deleteNode(root->key);
	}
	cout << "\nstablo je obrisano";
}

void Tree::maxNumOfValues() {
	Node* temp = root;
	int max = temp->key, num = 1;
	int prevNum = num;
	stack <Node*> s;
	while (true) {
		while (temp != nullptr) {
			s.push(temp);
			temp = temp->left;
		}
		if (!s.empty()) {
			temp = s.top();
			s.pop();
			num = 1;
			while (!s.empty() && temp->key == s.top()->key  ) {
				s.pop();
				num++;
			}
			if (num >= prevNum) {
				prevNum = num;
				max = temp->key;
			}
			temp = temp->right;
		}
		else break;
	}
	cout << "najvise se ponavlja cvor " << max << " " << prevNum << "puta\n";
}

int main() {
	int n, key, command;
	cout << "1. unesi broj cvorova\n" << "2. unesi cvorove\n" << "3. inorder ispis stabla\n" <<
		"4. level order ispis stabla\n " << "5. maksimalni broj pojavljivanja\n" << "6. brisanje cvora\n" << "7. brisanje stabla\n";
	cout << "\nunesi komandu: ";
	cin >> command;
	Tree t = Tree();
	int *arr;
	while (command >= 1 && command <= 7) {
		switch (command) {
		case 1: cin >> n;  break;
		case 2:
			arr = new int[n];
			for (int i = 0; i < n; i++) {
				cin >> arr[i];
			}
			t.makeTree(arr, n);
			break;
		case 3: t.printInorder(); cout << "\n"; break;
		case 4: t.printLevelorder(); break;
		case 5: t.maxNumOfValues(); break;
		case 6: cin >> key; t.deleteNode(key); break;
		case 7: t.deleteTree();
		}
		cout << "\nunesi komandu: ";
		cin >> command;
	}
	system("PAUSE");
}
