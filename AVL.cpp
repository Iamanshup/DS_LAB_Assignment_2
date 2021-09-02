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
	void destructorHelper(AVL_Node *avl_node);

public:
	AVL_Tree();
	AVL_Tree(const AVL_Tree &T);
	AVL_Tree &operator=(const AVL_Tree &T);
	void AVL_Insert(int k);
	void AVL_Delete(int k);
	bool AVL_Search(int k);
	void AVL_Print(const char *filename);
	~AVL_Tree();

	void RotateR(AVL_Node *&ptr) //Right Rotation
	{
		AVL_Node *subR = ptr;
		ptr = subR->LChild;
		subR->LChild = ptr->RChild;
		ptr->RChild = subR;
		ptr->bf = subR->bf = 0;
	}
	void RotateL(AVL_Node *&ptr) //Left Rotation
	{
		AVL_Node *subL = ptr;
		ptr = subL->RChild;
		subL->RChild = ptr->LChild;
		ptr->LChild = subL;
		ptr->bf = subL->bf = 0;
	}
	void RotateRL(AVL_Node *&ptr) //Rotate right then left
	{
		AVL_Node *subL = ptr;
		AVL_Node *subR = ptr->RChild;
		ptr = subR->LChild;

		subR->LChild = ptr->RChild;
		ptr->RChild = subR;
		//subR->bf
		if (ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;

		subL->RChild = ptr->LChild;
		ptr->LChild = subL;
		//subL->bf
		if (ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		ptr->bf = 0;
	}
	void RotateLR(AVL_Node *&ptr) //Rotate left then right
	{
		AVL_Node *subL = ptr->LChild;
		AVL_Node *subR = ptr;
		ptr = subL->RChild;

		subL->RChild = ptr->LChild;
		ptr->LChild = subL;
		//subL->bf;
		if (ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		subR->LChild = ptr->RChild;
		ptr->RChild = subR;
		//subR->bf;
		if (ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;

		ptr->bf = 0;
	}
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
		{
			singleRotation(p, r, s, a);
			// p = r;
			// if (a == 1)
			// {
			// 	RotateRL(s);
			// 	if (k < t->key)
			// 		t->LChild = s;
			// 	else
			// 		t->RChild = s;
			// }
			// else
			// {
			// 	RotateLR(s);
			// 	if (k < t->key)
			// 		t->LChild = s;
			// 	else
			// 		t->RChild = s;
			// }
		}
		else if (r->bf == -a)
		{
			doubleRotation(p, r, s, a);
		}
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
	fout << "node [shape=record, height=0.1];\n";
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

	if (node == root->RChild) // add the label and root in the dot file
	{
		fout << "label = \" rooted at " << node->key << " \";\n";
		fout << node->key << " [root = true]\n";
	}

	fout << node->key << " [label=\"<f0>|<f1>" << node->key << "|<f2> " << node->bf << " |<f3> \"];\n";

	if (node->LChild)
	{
		fout << node->key << ":f0 -> " << node->LChild->key << ":f1\n";
		AVL_PrintHelper(node->LChild, fout);
	}

	if (node->RChild)
	{
		fout << node->key << ":f3 -> " << node->RChild->key << ":f1\n";
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

void AVL_Tree::AVL_Delete(int k)
{
	if (!AVL_Search(k))
	{
		throw "Key does not exist in the tree.";
	}

	AVL_Node *pr = nullptr;
	AVL_Node *p = root->RChild, *q;
	stack<AVL_Node *> st;
	while (p)
	{
		if (k == p->key)
			break;

		pr = p;
		st.push(pr);

		if (k < p->key)
			p = p->LChild;
		else
			p = p->RChild;
	}
	if (p == nullptr)
		return;

	if (p->LChild != nullptr && p->RChild != nullptr)
	{
		pr = p;
		st.push(pr);

		q = p->RChild;
		while (q->LChild != nullptr)
		{
			pr = q;
			st.push(pr);
			q = q->LChild;
		}
		p->key = q->key;
		p = q;
	}

	if (p->LChild != nullptr)
		q = p->LChild;
	else
		q = p->RChild;

	//p deleted node, q deleted child node
	if (pr == nullptr)
		root->RChild = q;
	else
	{
		if (p == pr->LChild)
			pr->LChild = q;
		else
			pr->RChild = q;

		//Adjust Balance
		while (!st.empty())
		{
			pr = st.top();
			st.pop();

			if (p->key < pr->key)
				pr->bf++;
			else
				pr->bf--;

			if (pr->bf == 1 || pr->bf == -1)
				break;

			if (pr->bf != 0)
			{
				//Let q point to a higher subtree
				if (pr->bf < 0)
					q = pr->LChild;
				else
					q = pr->RChild;

				if (q->bf == 0)
				{
					if (pr->bf < 0)
					{
						RotateR(pr);
						pr->bf = 1;
						pr->RChild->bf = -1;
					}
					else
					{
						RotateL(pr);
						pr->bf = -1;
						pr->LChild->bf = 1;
					}

					if (!st.empty())
					{
						AVL_Node *ppr = st.top();
						if (ppr->key < pr->key)
							ppr->RChild = pr;
						else
							ppr->LChild = pr;
					}
					else
						root->RChild = pr;

					break;
				}

				if (pr->bf < 0)
				{
					if (q->bf < 0)
					{
						RotateR(pr);
					}
					else
					{
						RotateLR(pr);
					}
				}
				else
				{
					if (q->bf > 0)
					{
						RotateL(pr);
					}
					else
					{
						RotateRL(pr);
					}
				}

				if (!st.empty())
				{
					AVL_Node *ppr = st.top();
					if (ppr->key < pr->key)
						ppr->RChild = pr;
					else
						ppr->LChild = pr;
				}
				else
					root->RChild = pr;
			}

			q = pr;

		} //end while
	}
	delete p;
}

AVL_Tree::~AVL_Tree()
{
	destructorHelper(root->RChild);
	delete (root);
}

void AVL_Tree::destructorHelper(AVL_Node *avl_node)
{
	if (!avl_node)
		return;
	if (avl_node->LChild)
		destructorHelper(avl_node->LChild);
	if (avl_node->RChild)
		destructorHelper(avl_node->RChild);
	delete (avl_node);
}

int main()
{
	AVL_Tree *tree = new AVL_Tree();

	int arr[] = {20, 10, 30, 3, 15, 25, 40, 2, 9, 35};

	for (int i = 0; i < 10; i++)
	{
		tree->AVL_Insert(arr[i]);
	}

	tree->AVL_Delete(20);
	// tree->AVL_Delete(34);
	// tree->AVL_Delete(5);
	// tree->AVL_Delete(47);
	// tree->AVL_Delete(3);

	char filename[] = "AVL.dot";
	tree->AVL_Print(filename);
}