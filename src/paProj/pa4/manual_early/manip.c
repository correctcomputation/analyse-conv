#include "manip.h"
#include "hbt.h"
#include "pa4.h"
#include "build.h"

#pragma CHECKED_SCOPE on

//inserts a key into the BST and balances it
_Ptr<Tnode> insertKey(_Ptr<Tnode> root, int toInsert)
{

	if(root == NULL)
	{
		_Ptr<Tnode> newNode = malloc<Tnode>(sizeof(*newNode));
		newNode -> key = toInsert;
		newNode -> left = NULL;
		newNode -> right = NULL;
		newNode -> balance = 0;
		return newNode;
	}
	if(toInsert <= root -> key)
	{
		root -> left = insertKey(root->left, toInsert);
	}
	else if(toInsert > root -> key)
	{
		root -> right = insertKey(root->right, toInsert);
	}
	else
		return root;
	
	getBalanceNS(root);
	
	if(root -> balance < -1 || root -> balance > 1)
	{
		if(root -> balance < -1)
		{
			if(root -> right != NULL)
				if((root -> right) -> balance > 0)
					root -> right = clkRot(root -> right);
			root = cntClkRot(root);
		}

		else if(root -> balance > 1)
		{
			if(root -> left != NULL)
				if((root -> left) -> balance < 0)
					root -> left = cntClkRot(root -> left);
			root = clkRot(root);
		}
	}


	return root;
}


//deletes key from the BST and balances it
_Ptr<Tnode> deleteKey(_Ptr<Tnode> root, int keyDelete)
{
	if(root == NULL)
		return root;
	
	
	if(keyDelete > root -> key)
		root -> right = deleteKey(root -> right, keyDelete);
	
	else if(keyDelete < root -> key)
		root -> left = deleteKey(root -> left, keyDelete);
	
	else
	{
		if(root -> left == NULL && root -> right == NULL)
		{
			free<Tnode>(root);
			return NULL;
		}
		if(root -> right == NULL)
		{	
			_Ptr<Tnode> tmp = root -> left;
			free<Tnode>(root);
			return tmp;
		}
		if(root -> left == NULL)
		{
			_Ptr<Tnode> tmp = root -> right;
			free<Tnode>(root);
			return tmp;
		}
		if(root -> left != NULL && root -> right != NULL)
		{
			_Ptr<Tnode> pred = getPred(root -> left);
			int tmp = pred -> key;
			pred -> key = root -> key;
			root -> key = tmp;
			root -> left = deleteKey(root -> left, keyDelete);
		}
	}



	if(root == NULL)
		return root;
	
	getBalanceNS(root);
	
	if(root -> balance < -1 || root -> balance > 1)
	{
		if(root -> balance < -1)
		{
			if(root -> right != NULL)
				if((root -> right) -> balance > 0)
					root -> right = clkRot(root -> right);
			root = cntClkRot(root);
			return root;
		}

		if(root -> balance > 1)
		{
			if(root -> left != NULL)
				if((root -> left) -> balance < 0)
					root -> left = cntClkRot(root -> left);
			root = clkRot(root);
			return root;
		}
	}
	return root;
}

//gets inorder predecessor
_Ptr<Tnode> getPred(_Ptr<Tnode> root)
{	
    while(root -> right != NULL)
    {	
        root = root -> right;
    }
	return root;
}

//balances tree at given root node
_Ptr<Tnode> balance(_Ptr<Tnode> root, _Ptr<Tnode> previous)
{
    if(root -> balance > 1)
    {

        root = clkRot(root);
    }
    else if(root -> balance < -1)
    {

        root = cntClkRot(root);

    }
    return root;
}

//performs a clockwise rotation at given root node
_Ptr<Tnode> clkRot(_Ptr<Tnode> root)
{

	_Ptr<Tnode> p = root -> left;
	_Ptr<Tnode> q = p -> right;

	p -> right = root;
	root -> left = q;

	getBalanceNS(p);
	getBalanceNS(root);

	return p;
}

//performs a counter clockwise rotation at given root node
_Ptr<Tnode> cntClkRot(_Ptr<Tnode> root)
{

	_Ptr<Tnode> p = root -> right;
	_Ptr<Tnode> q = p -> left;

	p -> left = root;
	root -> right = q;

	getBalanceNS(root);
	getBalanceNS(p);

	return p;
}


//prints the output of the passed tree
void printTreeOutput (_Ptr<Tnode> root, _Ptr<FILE> writeFile)
{
    if(root == NULL)
        return;


    char code = 0;

    fwrite(&(root -> key), sizeof(int), 1, writeFile);
    if(root -> left != NULL || root -> right != NULL)
    {
        code = root -> left != NULL ? code | 2 : code | 0;
        code = root -> right != NULL ? code | 1 : code | 0;
    }
    fwrite(&(code), sizeof(char), 1, writeFile);

    printTreeOutput(root -> left, writeFile);
    printTreeOutput(root -> right, writeFile);
    return;
}


void printTree (_Ptr<Tnode> root)
{
    if(root == NULL)
        return;
		
		_Unchecked {
    	fprintf(stderr, "root key: %d\n", root -> key);
    	fprintf(stderr, "balance: %d\n", root -> balance);
    }

		printTree(root -> left);
    printTree(root -> right);
    return;
}

