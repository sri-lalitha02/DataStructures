// Avl Tree Deletion
#include<bits/stdc++.h>
#include<iostream>
using namespace std;
// create a struct node
struct TreeNode
{
	int data;
	int height;
	TreeNode *left;
	TreeNode *right;
	//create a node by using data
	TreeNode(int val)
	{
		data = val;
		height = 0;
		left = nullptr;
		right = nullptr;
	}
};
struct AvlTree
{
	// initialize the root
	TreeNode *root = nullptr;
	// Calculate the height of root node
	int Height(TreeNode *root)
	{
		if(root == nullptr) return 0;
		return root->height;
	}
	
	// Left Rotate
	TreeNode* LeftRotate(TreeNode *parent)
	{
		TreeNode *x = parent->right;
		TreeNode *y = x->left;
		
		// change the parent
		x->left = parent;
		parent->right = y;
		
		// calculate the heights
		parent->height = max(Height(parent->left), Height(parent->right))+1;
		x->height = max(Height(x->left) , Height(x->right))+1;
		return x;
	}
	
	//Right Rotate
	TreeNode* RightRotate(TreeNode *parent)
	{
		TreeNode *x = parent->left;
		TreeNode *y = x->right;
		
		// change the parent
		x->right = parent;
		parent->left = y;
		
		// calculate the Heights
		parent->height = max(Height(parent->left) , Height(parent->right))+1;
		x->height = max(Height(x->left) , Height(x->right)) +1;
		return x;
	}
	//Insertion
	TreeNode* Insert(TreeNode *root , int val)
	{
		// if root is null create a node with value
		if(root == nullptr)
		{
			return new TreeNode(val);
		}
		//given value < root->data then insert at left sub tree
		else if(root->data > val)
		{
			// recursively call the Insert function for inserting the value
			root->left = Insert(root->left , val);
		}
		// given value > root->data then it is inserted at right sub tree
		else
		{
			root->right = Insert(root->right , val);
		}
		//I need to check the balance factor 
  	    //to know the balance factor we have left height and right height
        //balance factor = abs (left height - right height)
        
		int Balance_factor = Height(root->left) - Height(root->right);
		
		// calculate the Height of the Avl tree
		root->height = max(Height(root->left) , Height(root->right)) +1;
		
		// Update balance factor
		// the curr root node is balanced when balance_factor is equal to {-1 , 0 , 1}
		// when the curr root node is imbalanced then rotate the root node and update balance factor
		// 4 - conditions to rotate 
		
		//left-left imbalance-> Right - Right Rotation
		if(Balance_factor > 1 && val < root->left->data )
		{
			root = RightRotate(root);
		}
		
		
		if(Balance_factor > 1 && val > root->left->data )
		{
			root->left = LeftRotate(root->left);
			root = RightRotate(root);
		}
		if(Balance_factor < -1 && val > root->right->data )
		{
			root = LeftRotate(root);
		}
		if(Balance_factor < -1 && val < root->right->data)
		{
			root->right = RightRotate(root->right);
			root = LeftRotate(root);
		}
		return root;	
	}
	void ADD(int val)
	{
		root = Insert(root , val);
	}
	void Print_Inorder(TreeNode *root)
	{
		if(root == nullptr) return;
		Print_Inorder(root->left);
		cout << root->data <<" ";
		Print_Inorder(root->right);
	}
	
	
	void Inorder()
	{
		Print_Inorder(root);
	}
	
		// Delete
	TreeNode* FindMin(TreeNode *root)
	{
		if(root == nullptr) return nullptr;
		if(root->left != nullptr) return FindMin(root->left);
		return root;
	}
	TreeNode* Remove(TreeNode* root , int val)
	{
		if(root == nullptr) return nullptr;
		else if(val < root->data) 
		{
			root->left = Remove(root->left , val);
		}
		else if(val > root->data)
		{
			root->right = Remove(root->right , val);
		}
		else
		{
			// no child
			if(root->left == nullptr && root->right == nullptr)
			{
				free(root);
				return nullptr;
			}
			// one child
			else if(root->left == nullptr || root->right == nullptr)
			{
				TreeNode* temp ;
				if(root->left == nullptr)
				{
					temp = root->right ;
				}
				else
				{
					temp = root->left;
				}
				free(root);
				return temp;
			}
			// two childs
			else
			{
				 TreeNode *temp = FindMin(root->right);
				 root = temp;
				 root->right = Remove(root->right , temp->data);
			}
	}
	int Balance_factor = Height(root->left) - Height(root->right);
	
	root->height = max(Height(root->left) , Height(root->right)) +1;
	
    //1.Balance_factor (root) > 1 && Balance_factor > 0 (root->left have left) ---->
    // (left left subtree so, right right Rotate)

     // 2.Balance_factor (root) > 1 && Balance_factor < 0 (root ->left have right) ----> 
     //   ( left right subtree so, left right rotate) 
	if(Balance_factor > 1)
	{
		int BfL = Height(root->left->left) - Height(root->left->right);
		if(BfL > 0)
		{
			root = RightRotate(root);
		}
		else if(BfL < 0)
		{
			root->left = LeftRotate(root->left);
			root = RightRotate(root);
		}
	}
	
	//    Balance_factor(root) < 1 && Balance_factor < 0 (root->right have right)
//     (right right subtree so, left left rotate)


// Balance_factor < 1  && Balance_factor > 0 (root->right have left)
// (right left subtree so , right left rotate)

	else if(Balance_factor < 1)
	{
		int BfR = Height(root->right->left) - Height(root->right->right);
		if(BfR < 0)
		{
			root = LeftRotate(root);
		}
		else if(BfR > 0)
		{
			root->right = RightRotate(root->right);
			root = LeftRotate(root);
		}
	}
	return root;
}
void Delete(int val)
{
	root = Remove(root , val);
}
	
};
int main()
{
	int n;
	printf("Enter no of nodes in a tree: ");
	cin >> n;
	vector<int>arr(n);
	printf("Enter node values : ");
	for(int i = 0 ; i < n ; i++)
	{
		cin >> arr[i];
	}
	AvlTree Avl;
	for(int i = 0 ; i < n ; i++)
	{
		Avl.ADD(arr[i]);
	}
	Avl.Inorder();
	int val ;
	cin>>val;
    cout<<"\n";
	Avl.Delete(val);
	Avl.Inorder();
}

// Time complexity : 
// O(log2(n)) {ADD} i.e O(nlogn) {for n nodes), O(1) {Rotation} , O(log2(n)) {search} , O(log2(n)) {Delete}
// overall Time complexity --> O(nlog2(n))
// space complexity : 
// O(n) {Node storage} , Recurision Stack (O(log2(n)) 
// Overall space complexity : O(n)
