#pragma once

#include <iomanip>
#include <cstdlib>
#include <stack>


class Tree {
	struct Node {
		int key;
		Node *left, *right;
		Node(int k, Node* l = nullptr, Node *r = nullptr) {
			key = k; left = l; right = r;
		}
	};
	Node* root;
public:

	Tree() { root = nullptr; }
	Tree(int k) { root = new Node(k); }
	Tree(const Tree& t) { root = copy(t.root); }
	Tree(Tree&& t) { root = t.root; t.root = nullptr; }
	~Tree() { deleteTree(); }

	void deleteTree();
	bool nodeFound(int key) const;
	void addNode(int key); 
	void deleteNode(int key);
	void makeTree(int arr[], int n);
	void printInorder() const;
	void printLevelorder() const;
	void maxNumOfValues();

private:
	static Node* copy(Tree::Node *root) {
		return root ? new Node(root->key, copy(root->left), copy(root->right)) : 0;
	}
	/*static void showstack(stack <Tree::Node*> s)
	{
		while (!s.empty())
		{
			cout << '\t' << s.top()->key;
			s.pop();
		}
		cout << '\n';
	}*/
};