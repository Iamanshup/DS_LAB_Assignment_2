#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

class AVL_Node
{
private:
	int key;
	int bf; // balance factor bf = height(left subtree) – height(right subtree)
	AVL_Node *LChild, *RChild;
	friend class AVL_Tree;

public:
	AVL_Node(int k)
	{
		key = k;
		bf = 0;
		LChild = RChild = nullptr;
	}

	AVL_Node()
	{
		bf = 0;
		LChild = RChild = nullptr;
	}
};

class AVL_Tree
{
private:
	AVL_Node *root;
	AVL_Node *link(int a, AVL_Node *node);
	void singleRotation(AVL_Node *&p, AVL_Node *&r, AVL_Node *&s, int a);
	void doubleRotation(AVL_Node *&p, AVL_Node *&r, AVL_Node *&s, int a);
	void AVL_PrintHelper(const AVL_Node *node, ofstream &fout);

public:
	AVL_Tree();
	AVL_Tree(const AVL_Tree &T);
	AVL_Tree &operator=(const AVL_Tree &T);
	void AVL_Insert(int k);
	void AVL_Delete(int k);
	bool AVL_Search(int k);
	void AVL_Print(const char *filename);
	~AVL_Tree();
};

AVL_Tree::AVL_Tree()
{
	root = new AVL_Node();
}

AVL_Node *AVL_Tree::link(int a, AVL_Node *node)
{
	if (a == -1)
		return node->LChild;
	return node->RChild;
};

void AVL_Tree::AVL_Insert(int k)
{
	AVL_Node *t = root;
	AVL_Node *s = root->RChild;
	AVL_Node *p = root->RChild;
	AVL_Node *q, *r;

	AVL_Node *avl_node = new AVL_Node(k);

	if (!p)
	{
		root->RChild = avl_node;
		return;
	}

	while (true)
	{
		if (k < p->key)
		{
			q = p->LChild;
			if (!q)
			{
				q = avl_node;
				p->LChild = q;
				break;
			}
		}
		else if (k > p->key)
		{
			q = p->RChild;
			if (!q)
			{
				q = avl_node;
				p->RChild = q;
				break;
			}
		}
		else
		{
			throw "Element already exists.";
		}

		if (q->bf != 0)
		{
			t = p;
			s = q;
		}

		p = q;
	}

	int a = 1;
	if (k < s->key)
		a = -1;

	r = p = link(a, s);

	while (p != q)
	{
		if (k < p->key)
		{
			p->bf = -1;
			p = p->LChild;
		}
		else if (k > p->key)
		{
			p->bf = 1;
			p = p->RChild;
		}
	}

	if (s->bf == 0)
	{
		s->bf = a;
		return;
	}

	if (s->bf == -a)
	{
		s->bf = 0;
		return;
	}

	if (s->bf == a)
	{
		if (r->bf == a)
			singleRotation(p, r, s, a);
		else if (r->bf == -a)
			doubleRotation(p, r, s, a);
	}

	if (s == t->RChild)
		t->RChild = p;
	else
		t->LChild = p;
}

void AVL_Tree::singleRotation(AVL_Node *&p, AVL_Node *&r, AVL_Node *&s, int a)
{
	p = r;
	if (a == 1)
	{
		s->RChild = r->LChild;
		r->LChild = s;
	}
	else
	{
		s->LChild = r->RChild;
		r->RChild = s;
	}
	s->bf = r->bf = 0;
}

void AVL_Tree::doubleRotation(AVL_Node *&p, AVL_Node *&r, AVL_Node *&s, int a)
{
	if (a == -1)
	{
		p = r->RChild;
		r->RChild = p->LChild;
		p->LChild = r;
		s->LChild = p->RChild;
		p->RChild = s;
	}
	else
	{
		p = r->LChild;
		r->LChild = p->RChild;
		p->RChild = r;
		s->RChild = p->LChild;
		p->LChild = s;
	}

	if (p->bf == a)
	{
		s->bf = -a;
		r->bf = 0;
	}
	else if (p->bf == 0)
	{
		s->bf = 0;
		r->bf = 0;
	}
	else if (p->bf == -a)
	{
		s->bf = 0;
		r->bf = a;
	}
	p->bf = 0;
}

// TODO : use filename in system call
void AVL_Tree::AVL_Print(const char *filename)
{
	ofstream fout;

	fout.open("AVL.dot");
	fout << "digraph g {\n";
	AVL_PrintHelper(root->RChild, fout);
	fout << "}";
	fout.close();
	// string command = "dot -Tpng " + filename + " -o AVL.png";
	system("dot -Tpng AVL.dot -o AVL.png");
}

void AVL_Tree::AVL_PrintHelper(const AVL_Node *node, ofstream &fout)
{
	if (!node)
		return;
	cout << node->key << endl;
	if (node == root->RChild) // add the label and root in the dot file
	{
		fout << "label = \" rooted at " << node->key << " \";\n";
		fout << node->key << " [root = true]\n";
	}

	if (node->LChild)
	{
		fout << node->key << " -> " << node->LChild->key << "\n";
		AVL_PrintHelper(node->LChild, fout);
	}

	if (node->RChild)
	{
		fout << node->key << " -> " << node->RChild->key << "\n";
		AVL_PrintHelper(node->RChild, fout);
	}
}

bool AVL_Tree::AVL_Search(int k)
{
	AVL_Node *avl_node = root->RChild;

	while (avl_node)
	{
		if (k == avl_node->key)
			return true;
		if (k < avl_node->key)
			avl_node = avl_node->LChild;
		else
			avl_node = avl_node->RChild;
	}
	return false;
}

int main()
{
	AVL_Tree *tree = new AVL_Tree();

	for (int i = 1; i < 11; i++)
	{
		tree->AVL_Insert(i);
	}

	char filename[] = "AVL.dot";
	tree->AVL_Print(filename);
}