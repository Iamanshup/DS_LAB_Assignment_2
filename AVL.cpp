#include <bits/stdc++.h>
#include "AVL.h"

using namespace std;

int main()
{
	AVL_Tree *tree = new AVL_Tree();

	int c = 0;

	while (c != -1)
	{
		int num;
		string filename;
		cout << "MENU:\n";
		cout << "1. Insert(x)\n2. Search(x)\n3. Delete(x)\n4. Print Tree\n5. Exit\n";
		cout << "Enter your choice: ";
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "Enter a number: ";
			cin >> num;
			try
			{
				tree->AVL_Insert(num);
				cout << "Key inserted successfully!\n";
			}
			catch (const char *e)
			{
				cout << e << endl;
			}
			break;

		case 2:
			cout << "Enter a number: ";
			cin >> num;
			if (tree->AVL_Search(num))
				cout << "Number is present in AVL Tree.\n";
			else
				cout << "Number is not present in AVL Tree.\n";
			break;

		case 3:
			cout << "Enter a number: ";
			cin >> num;
			try
			{
				tree->AVL_Delete(num);
				cout << "Key deleted successfully!\n";
			}
			catch (const char *e)
			{
				cout << e << endl;
			}
			break;

		case 4:
			try
			{
				cout << "Enter filename(without extension): ";
				cin >> filename;
				tree->AVL_Print(filename.c_str());
			}
			catch (...)
			{
				cout << "Some error occurred!\n";
			}

			break;

		case 5:
			c = -1;
			break;

		default:
			cout << "Invalid Choice!\n Try again.\n";
			break;
		}
		cout << "\n\n";
	}
	delete (tree);
}