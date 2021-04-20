#include <iostream>
#include <climits>
#include <string>
using namespace std;
template<class T>
class avl{
	public:
    struct node { 
		T key; 
		struct node* left; 
		struct node* right; 
		int height; 
		int count; 
    }; 
struct node* root;
struct node* lbvar;
struct node* ubvar;
T kthelement;
// struct node* kthnode;

avl()
{
	root=NULL;
}
//==================utility functions=========================

 node* createNewNode(T key) 
{ 
	//struct node* newnode = (struct node*)malloc(sizeof(struct node)); 
	node* newnode = new node;
	newnode->key = key; 
	newnode->left = NULL; 
	newnode->right = NULL; 
	newnode->height = 1;
	newnode->count = 1; 
	return (newnode); 
} 
int getHeight(node* a) 
{ 
	if (a == NULL) 
		return 0; 
	return a->height; 
} 
void setHeight(node* a)
{
    if(a == NULL)
     return;
    else
    {
        a->height = max(getHeight(a->left),getHeight(a->right)) + 1;
    } 
}
int getBalanceFactor(node* a) 
{ 
	if (a == NULL) 
		return 0; 
	return getHeight(a->left) - getHeight(a->right); 
}
node* minValueNode(node* a) 
{   //cout<<"here"<<endl;
// Given a non-empty binary search tree, return the node with minimum key value found in that tree
	struct node* mvn = a; 
	while (mvn->left != NULL) 
		mvn = mvn->left; 
	return mvn; 
}
node* maxValueNode(node* a) 
{   //cout<<"here"<<endl;
	struct node* mvn = a; 
	while (mvn->right != NULL) 
		mvn = mvn->right; 
	return mvn; 
}
node* rightRotation( node* y) 
{ 
	node* x = y->left; 
	node* T2 = x->right; 
	x->right = y; 
	y->left = T2; 
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1; 
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 
	return x; 
} 

node* leftRotation( node* x) 
{ 
	node* y = x->right; 
	node* T2 = y->left; 
	y->left = x; 
	x->right = T2; 
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1; 
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1; 
	return y; 
} 
//=================functions====================================
//1. search
//2. count
//3. insert
//4. delete
node* search_node(node *a,T element)
{
    if(a->key == element)
    {
        return a;
    }
    else if(element < a->key && a->left != NULL)
    {
        return search_node( a->left, element);
    }
    else if(a->key < element && a->right != NULL)
    {
        return search_node( a->right, element);
    }
    else{
        return NULL;
    }
}
bool search(T val)
{
    node* s = search_node(root, val);
    if(s == NULL)
      return false;
    else
    {
        return true;
    }  
}
node* count_node(node *a, T element)
{
    if(a->key == element)
    {
        return a;
    }
    else if(element < a->key && a->left != NULL)
    {
        return count_node(a->left, element);
    }
    else if(a->key < element && a->right != NULL)
    {
        return count_node( a->right, element);
    }
    else
    {
        ;
    }
    return 0;
}
int count(T val)
{
    node* c = count_node(root,val);
    if(c == NULL)
     return 0;
    return c->count;
}
node* insert_node(node* a, T keyelement) 
{ 
	if (a == NULL) 
		return (createNewNode(keyelement)); 
	if (keyelement == a->key)
	{ 
		(a->count)++; 
		return a; 
	} 
	if (keyelement < a->key) 
		a->left = insert_node(a->left, keyelement); 
	else
		a->right = insert_node(a->right, keyelement); 

	a->height = max(getHeight(a->left), getHeight(a->right)) + 1; 

	int bf = getBalanceFactor(a); 

	if (bf > 1 && keyelement < a->left->key) 
		return rightRotation(a); 

	if (bf < -1 && keyelement > a->right->key) 
		return leftRotation(a); 
	if (bf > 1 && keyelement > a->left->key)
	{ 
		a->left = leftRotation(a->left); 
		return rightRotation(a); 
	} 
	if (bf < -1 && keyelement < a->right->key)
	{ 
		a->right = rightRotation(a->right); 
		return leftRotation(a); 
	} 
	return a; 
} 
void insert(T element)
{
	root = insert_node(root, element);
} 

node* deleteNode(node* root, T key) 
{ 
	if (root == NULL) 
		return root; 

	if (key < root->key) 
		root->left = deleteNode(root->left, key); 

	else if (key > root->key) 
		root->right = deleteNode(root->right, key); 

	else { 
		if (root->count > 1) { 
			(root->count)--; 
			return root; 
		} 
		if ((root->left == NULL) || (root->right == NULL)) { 
			struct node* temp = root->left ? root->left : root->right; 
			if (temp == NULL) { 
				temp = root; 
				root = NULL; 
			} 
			else // One child case 
				*root = *temp;  

			free(temp); 
		} 
		else
		{ 
			struct node* temp = minValueNode(root->right); 
			root->key = temp->key; 
			root->count = temp->count; 
			temp->count = 1; 
			root->right = deleteNode(root->right, temp->key); 
		} 
	} 
	if (root == NULL) 
		return root; 
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1; 
	int bf = getBalanceFactor(root); 
	if (bf > 1 && getBalanceFactor(root->left) >= 0) 
		return rightRotation(root); 
	if (bf > 1 && getBalanceFactor(root->left) < 0)
	{ 
		root->left = leftRotation(root->left); 
		return rightRotation(root); 
	} 
	if (bf < -1 && getBalanceFactor(root->right) <= 0) 
		return leftRotation(root); 
	if (bf < -1 && getBalanceFactor(root->right) > 0)
	{ 
		root->right = rightRotation(root->right); 
		return leftRotation(root); 
	} 

	return root; 
} 
void del(T element)
{
   node* del;
   root=deleteNode(root,element);
}
//==============================================================
//                   upper bound
//==============================================================

node* upper_bound(node *a, T element)
{   //conventionally ub returns the address of element
    //for element larger that max tree element returns max element  
	// lower bound(x) -> first element not less than 'x'
    // upper bound(x) -> first element greater than ‘x’
// 	input is 3,4,6,6 
// lower_bound(5) = 6
// upper_bound(5) = 6
// lower_bound(4) = 4
// upper_bound(4) = 6 
    if(a == NULL)
    {
        return ubvar;
    }
    if(element < a->key)
    {
        ubvar = a;
        //cout<<"ubvar: "<<ubvar->key<<endl;
        return upper_bound(a->left, element);
    }
    else
    {   
		// if(a->key == element)
		// return ubvar;
        return upper_bound(a->right, element);
    }
    return ubvar; 
}

T upperbound(T val)
{
    node* l = upper_bound(root, val);
    return l->key;
}
//=========================================================================
//            lowerbound
//=========================================================================

node* lower_bound(node *a, T element)
{   //conventionally lb returns the address of element
    //for element larger that max tree element returns max element
    // lower bound(x) -> first element not less than 'x'(returns equal)
    // upper bound(x) -> first element greater than ‘x’(never returns equal)
// 	input is 3,4,6,6 
// lower_bound(5) = 6
// upper_bound(5) = 6
// lower_bound(4) = 4
// upper_bound(4) = 6
    if(a == NULL)
    {
        return lbvar;
    }
	
	if(a->key == element)
    {
        return a;
    }
    else
    {
        if(element < a->key )
        {
            lbvar = a;
            return lower_bound( a->left, element);
        }
        else if(a->key < element )
        {
			//tempnode = a->right;
            return lower_bound( a->right, element);
            
        }
        else{
            return lbvar;
        }
        
    }
    
}
T lowerbound(T val)
{
    node* l = lower_bound(root, val);
    return l->key;
}
//=================closest=============================
//=====================================================
void closestutility(node *ptr, int k, int &min_diff, int &min_diff_key) 
{ 
	if (ptr == NULL) 
		return ; 
	if (ptr->key == k) 
	{ 
		min_diff_key = k; 
		return; 
	} 
	if (min_diff > abs(ptr->key - k)) 
	{ 
		min_diff = abs(ptr->key - k); 
		min_diff_key = ptr->key; 
	} 
	if (k < ptr->key) 
		closestutility(ptr->left, k, min_diff, min_diff_key); 
	else
		closestutility(ptr->right, k, min_diff, min_diff_key); 
}

T closestelement(node* a,T element)
{   
   int min_diff = INT_MAX;
   int min_diff_key = -1; 
	closestutility(root, element, min_diff, min_diff_key); 
	return T(min_diff_key); 
}
T closest(T element)
{
	return closestelement(root, element);
}
//=========================================================
//                    kth largest
//=========================================================
void kthlargest(node* n, int k, int &c)
{
    if(c >= k || n == NULL)
	return;
	kthlargest(n->right, k, c);
	c = c + n->count;
	if(c == k)
	{
	  kthelement=n->key;
	  return;
	}
	kthlargest(n->left,k,c);
}

T kth(int k)
{
	int c=0;
    kthlargest(root,k,c);
    return kthelement;
}
//=========================================================
// count number of nodes in a range
//=========================================================

int getcount(node *n, T l, T r) 
{ 
    if (!n) 
	return 0; 
    
	if (n->key == r && n->key == l) 
    return 1; 
    
	if (n->key <= r && n->key >= l) 
    return 1 + getcount(n->left, l, r) + getcount(n->right, l, r); 

    else if (n->key < l) 
    return getcount(n->right, l, r);

    else 
	return getcount(n->left, l, r); 
}

int nodecount(T a, T b)
{
	return getcount(root, a,b);
}
//====================for display===========================
void preorder_avl( node* root) 
{ 
	if (root != NULL)
	{ 
		cout<<root->key<<" "<<root->count;
		cout<<endl;
		preorder_avl(root->left); 
		preorder_avl(root->right); 
	} 
} 
void preorder()
{
	preorder_avl(root);
}
void inorder_avl(node* root) 
{ 
	if (root != NULL)
	{ 
		inorder_avl(root->left); 
		cout<<root->key<<" "<<root->count;
		cout<<endl;
		inorder_avl(root->right); 
	} 
} 

void inorder()
{
	inorder_avl(root);

}
};

//========================main class================================
int main() 
{ 
	avl<int> a;
	 char ch ='A';
	for(int i=1;i<=10;i++)
	{
		a.insert(ch);
		ch++;

	} 
	cout<<a.nodecount('A','C')<<endl;
/* 	a.insert(30);
	 a.insert(10);
	 a.insert(25);
	 a.insert(20);
	 a.insert(40);
	 a.insert(50);
	 a.insert(25);
	 a.insert(35);
	 a.insert(50);
	 a.insert(25);
    cout<<"inorder: "<<endl;
    a.inorder();
    
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
	cout<<"upr bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upr bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upr bound of 31 is = "<<a.upperbound(31)<<endl;

	cout<<"closest of 7 is = "<<a.closest(7)<<endl;
	cout<<"closest of 22 is = "<<a.closest(22)<<endl;
	cout<<"closest of 60 is = "<<a.closest(60)<<endl;

	a.del(25);
    a.del(10);
	a.del(40);

	 cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
	cout<<"upr bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upr bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upr bound of 31 is = "<<a.upperbound(31)<<endl;
	cout<<"closest of 7 is = "<<a.closest(7)<<endl;
	cout<<"closest of 22 is = "<<a.closest(22)<<endl;
	cout<<"closest of 60 is = "<<a.closest(60)<<endl;
    cout<<".........................."<<endl; */

	 cout<<"inorder: "<<endl;
    a.inorder();
    // char c='A';
	/*for(int i=1;i<=10;i++){
        cout<<"upper bound of b is = "<<a.upperbound(c)<<endl;
        c++;
	}
    cout<<"upper bound of f is = "<<a.upperbound('F')<<endl; 
    // cout<<"upper bound of 31 is = "<<tree.upperbound(31)<<endl;*/
    for(int i=1;i<=10;i++)
	cout<<"largest element "<<a.kth(i)<<endl;
    cout<<".........................."<<endl;
    //a.inorder(); 
    // tree.preorder();
   // cout<<"closest value to 22 is = "<<tree.closest_element(22)<<endl;
  //cout<<"closest value to 50 is = "<<tree.closest_element(50)<<endl;
    //cout<<"closest value to 7 is = "<<tree.closest_element(7)<<endl;
    //                                                                                                                                                                                           cout<<"closest value to 55 is = "<<tree.closest_element(45)<<endl;
    /* cout<<".........................."<<endl;
	cout<<a.closest('G')<<endl; */
    
  
	return 0; 
} 
/*
avl<datatype> a;
a.insert(val); -------------done
a.del(val);  ---------------done
a.search(val);--------------done (returns 0 or 1)
a.count(element);-----------done
a.lowerbound(val);----------done
a.upperbound(val);----------done
a.closest(val);-------------done
a.kthlargest(k);------------done
a.countinrange(a,b);--------done
a.comparator(obj1, obj2);
*/