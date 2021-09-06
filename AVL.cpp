#include <bits/stdc++.h>
#include "AVL.h"

using namespace std;

int main()
{
	AVL_Tree *tree = new AVL_Tree();

	// int arr[] = {20, 10, 30, 3, 15, 25, 40, 2, 9, 35};

	// for (int i = 0; i < 10; i++)
	// {
	// 	tree->AVL_Insert(arr[i]);
	// }

	// AVL_Tree *tree2;
	// tree2 = new AVL_Tree(*tree);

	// tree2.AVL_Delete(20);
	// tree->AVL_Delete(20);
	// tree->AVL_Delete(5);
	// tree->AVL_Delete(47);
	// tree->AVL_Delete(3);

	// const char *filename = "con";
	// tree->AVL_Print(filename);

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