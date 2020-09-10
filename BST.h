#include <iostream>
using namespace std;

template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode * left;
	TreeNode * right;
};

template <class ItemType>
class TreeType
{
public:
	TreeType();  //Constructor
	~TreeType(); //Destructor
	TreeType(const TreeType& origTree); //Copy COnstructor
	void operator = (const TreeType & origTree); // Assignment operator

	void makeEmpty();
	bool isEmpty() const;
	bool isFull() const;

	int getLength() const;

	ItemType getItem(ItemType item, bool & found);

	void addItem(ItemType item);

	void deleteItem(ItemType item);

	void printTree();

	void swapTree();

private:
	TreeNode<ItemType> * root;

	void destroy(TreeNode<ItemType> *& tree);
	void copyTree(TreeNode<ItemType> *& copy, const TreeNode<ItemType> * origTree);
	void deleteNode(TreeNode<ItemType> *& tree);
	void printNode(TreeNode<ItemType> *& tree) ;
	void Delete(TreeNode<ItemType> *& tree, ItemType item);
	int countNodes(TreeNode<ItemType> *& tree);
	void getPredecessor(TreeNode<ItemType> *& tree, ItemType& item);
	void retrieve(TreeNode<ItemType> *& tree, ItemType& item, bool & found);
	void insert(TreeNode<ItemType> *& tree, ItemType& item);
	void SwapT(TreeNode<ItemType>*& root);
	void Swap(TreeNode<ItemType>*& item1, TreeNode<ItemType>*& item2);

}; 

template <class ItemType>
void TreeType<ItemType>::swapTree()
{
	SwapT(root);
}

template<class ItemType>
void TreeType<ItemType>::SwapT(TreeNode<ItemType>*& tree)
// Post: Contents of item1 and item2 have been swapped. 
{
	if ((tree != NULL))
	{
		Swap(tree->left, tree->right);
		//cout << "Here\n";
		SwapT(tree->left);
		SwapT(tree->right);
	}
}
template<class ItemType>
void TreeType<ItemType>::Swap(TreeNode<ItemType>*& item1, TreeNode<ItemType>*& item2)
{
	TreeNode<ItemType>* tempItem;
	tempItem = item1;
	item1 = item2;
	item2 = tempItem;
}
template <class ItemType>
TreeType<ItemType>::TreeType()
{
	root = NULL;
}

template <class ItemType>
TreeType<ItemType>::~TreeType()
{
	destroy(root);
}

template <class ItemType>
void TreeType<ItemType>::destroy(TreeNode<ItemType> *& tree)
{
	if (tree != NULL)
	{
		destroy(tree->left);
		destroy(tree->right);
		delete tree;
	}
}

template <class ItemType>
TreeType<ItemType>::TreeType(const TreeType& origTree)
{
	copyTree(root, origTree);
}

template<class ItemType>
void TreeType<ItemType>::operator=(const TreeType & origTree)
{
	if (&origTree == this)
		return;
	destroy(root);
	copyTree(root, origTree.root);
}

template<class ItemType>
void TreeType<ItemType>::makeEmpty()
{
	destroy(root);
	root = NULL;
}

template<class ItemType>
inline bool TreeType<ItemType>::isEmpty() const
{

	return root == NULL;
}

template<class ItemType>
bool TreeType<ItemType>::isFull() const
{
	TreeNode<ItemType> * location;
	try
	{
		location = new TreeNode<ItemType>;
		delete location;
		return false;
	}
	catch (std::bad_alloc)
	{
		return true;
	}
}

template<class ItemType>
inline int TreeType<ItemType>::getLength() const
{
	return countNodes( root );
}

template<class ItemType>
ItemType TreeType<ItemType>::getItem(ItemType item, bool & found)
{
	retrieve(root, item, found);
	return item;
}

template<class ItemType>
void TreeType<ItemType>::addItem(ItemType item)
{
	insert(root, item);
}

template<class ItemType>
void TreeType<ItemType>::deleteItem(ItemType item)
{
	Delete(root, item);
}

template<class ItemType>
void TreeType<ItemType>::printTree()
{
	printNode(root);
	cout << endl;
}

template <class ItemType>
void TreeType<ItemType>::copyTree(TreeNode<ItemType> *& copy, const TreeNode<ItemType> * origTree)
{
	if (origTree == NULL)
		copy = NULL;
	else
	{
		copy = new TreeNode<ItemType>;
		copy->info = origTree->info;

		copyTree(copy->left, origTree->left);
		copyTree(copy->right, origTree->right);
	}
}

template<class ItemType>
void TreeType<ItemType>::deleteNode(TreeNode<ItemType>*& tree)
{
	ItemType data;
	TreeNode<ItemType> * tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		getPredecessor(tree->left, data);
		tree->info = data;
		Delete(tree->left, data);//Delete predecessor node
	}
}

template<class ItemType>
void TreeType<ItemType>::printNode(TreeNode<ItemType>*& tree) 
{
	if (tree == root)
		cout << "roots info " << tree->info << endl;
	if (tree != NULL)
	{
		printNode(tree->left);
		cout << tree->info << " ";
		printNode(tree->right);
	}
}

template<class ItemType>
void TreeType<ItemType>::Delete(TreeNode<ItemType>*& tree, ItemType item)
{
	if (item < tree->info)
		Delete(tree->left, item);
	else if (item > tree->info)
		Delete(tree->right, item);
	else
		deleteNode(tree);
}

template<class ItemType>
int TreeType<ItemType>::countNodes(TreeNode<ItemType>*& tree)
{
	if (tree == NULL)
		return 0;
	else
		return (countNodes(tree->left) + countNodes(tree->right)) + 1;
}

template<class ItemType>
void TreeType<ItemType>::getPredecessor(TreeNode<ItemType>*& tree, ItemType& item)
{
	while (tree->right != NULL)
		tree = tree->right;
	item = tree->info;
}

template<class ItemType>
void TreeType<ItemType>::retrieve(TreeNode<ItemType>*& tree, ItemType & item, bool & found)
{
	if (tree == NULL)
		found = false;
	else if (item < tree->info)
		retrieve(tree->left, item, found);
	else if (item > tree->info)
		retrieve(tree->right, item, found);
	else
	{
		item = tree->info;
		found = true;
	}
}

template<class ItemType>
void TreeType<ItemType>::insert(TreeNode<ItemType>*& tree, ItemType & item)
{
	if (tree == NULL)
	{
		tree = new TreeNode<ItemType>;
		tree->right = NULL;
		tree->left = NULL;
		tree->info = item;
	}
	else if (item < tree->info)
		insert(tree->left, item);
	else
		insert(tree->right, item);

}

