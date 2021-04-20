#include<iostream>
using namespace std;

template<class T, class U>
class map{
    public:
    struct node
    {
        T key;
        U value;
        node* left;
        node* right;
        int height;
    };

struct node* root;
int siz;
map()
{
    root = NULL;
    siz = 0;
}

//==================utility functions=========================

 node* createNewNode(T keyelement, U val) 
{ 
	struct node* a = (struct node*) 
		malloc(sizeof(struct node)); 
	a->key = keyelement; 
    a->value = val;
	a->left = NULL; 
	a->right = NULL; 
	a->height = 1; // new node is initially added at leaf  
    return (a); 
} 
int getHeight(node* a) 
{ 
	if (a == NULL) 
		return 0; 
	return a->height; 
} 

int getBalanceFactor(node* a) 
{ 
	if (a == NULL) 
		return 0; 
	return getHeight(a->left) - getHeight(a->right); 
}
node* minValueNode(node* a) 
{   //cout<<"here"<<endl;
// Given a non-empty binary find tree, return the node with minimum key value found in that tree
	node* mvn = a; 
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

void clear_map(node* a)
{
    if(a != NULL){
        //a = deleteNode(a->left);
        clear_map(a->right);
        clear_map(a->left);
        free(a);
    }
}

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

node* insert_node(node* a, T keyelement, U val) 
{ 
	if (a == NULL) 
	{
        siz++;
        return (createNewNode(keyelement, val));
    }	 
	if (keyelement == a->key)
	{ 
		a->value = val;
		return a; 
	} 
	if (keyelement < a->key) 
		a->left = insert_node(a->left, keyelement, val); 
	else
		a->right = insert_node(a->right, keyelement, val); 

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

node* deleteNode(node* root, T key) 
{ 
	if (root == NULL) 
		return root; 

	if (key < root->key) 
		root->left = deleteNode(root->left, key); 

	else if (key > root->key) 
		root->right = deleteNode(root->right, key); 

	else { 
		
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
			root->value = temp->value;  
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
//=================functions====================================

void clear()
{   
    siz=0;
    clear_map(root);
    root = NULL;
}
int size()
{
    return siz;
}

bool find(T keyelement)
{
    node* s = search_node(root, keyelement);
    if(s == NULL)
      return false;
    else
    {   //cout<<"hello";
        return true;
    }  
}
void insert(T keyelement, U val)
{
	root = insert_node(root, keyelement, val);
} 
 
void erase(T element)
{
   //node* del;
   if(find(element))
   {
       siz--;
       root=deleteNode(root,element);
   }
}

U& operator[](T keyelement)
{   
    // if(search_node)
    node* temp = search_node(root, keyelement);
    if(temp) //if found
    return temp->value;
    else
    {  
        U value=(U)0;
        string s;
        if(typeid(s).hash_code()==typeid(U).hash_code())
        {
            value=U{};
            insert(keyelement,value);
        }
        else insert(keyelement,value);
        node* t = search_node(root, keyelement);
        // cout<<"hello"<<endl;
        return t->value;
    }
}

//====================for display===========================
void preorder_avl(node* root) 
{ 
	if (root != NULL)
	{ 
		cout<<"{"<<root->key<<","<<root->value<<"}";
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
		cout<<"{"<<root->key<<","<<root->value<<"}";
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
    map<int,int> x;
    // x[10];
    x.insert(7,2);
    x.insert(5,10);
    x.insert(1,5);
    x.insert(3,9);
    x.insert(3,1);
    //cout<<"\n";
    cout<<"\nprinting inorder here after insertion: \n";
    x.inorder();
    //cout<<"\n";
    cout<<endl;
    //cout<<x[3]<<endl;
    cout<<"size: ";
    cout<<x.size()<<endl;
    cout<<"erasing elements: \n";
    x.erase(5);
    // x.erase(3);
    // x.erase(7);
    cout<<"\nprinting inorder and size after clearing: \n";
    x.inorder();
    cout<<"\nsize: ";
    cout<<x.size()<<endl;
    cout<<"find an element\n";
    cout<<x.find(1)<<endl;
    cout<<x.find(5)<<endl;
    cout<<x[1]<<endl;
    cout<<x[3]<<endl;
    cout<<x[7]<<endl;
    cout<<x[1]<<endl;
    cout<<x[3]<<endl;
    cout<<x[7]<<endl;
    cout<<"---------------------\n";
    cout<<x[1];
    cout<<"\nbelow"<<endl;
    cout<<"1 "<<x[100]<<endl;
    cout<<"2 "<<x[56356]<<endl;
    cout<<"1 "<<x[100]<<endl;
    cout<<"2 "<<x[56356]<<endl;
    cout<<"1 "<<x[100]<<endl;
    cout<<"2 "<<x[56356]<<endl;
    cout<<"1 "<<x[100]<<endl;
    cout<<"2 "<<x[56356]<<endl;
    x[10] = 999;
    cout<<"new at 10 "<<x[10]<<endl;
    cout<<"\n---------------------\n";
    cout<<"size: ";
    cout<<x.size()<<endl;
    cout<<"----------clearing-----------\n";
    x.clear();
    //cout<<x[100];
    cout<<"\n---------------------\n";
    // cout<<"1 "<<x[100]<<endl;
    // cout<<"2 "<<x[56356]<<endl;
    cout<<"\nprinting final inorder here: \n";
    // x.find(5);
    x.inorder();
    cout<<endl; 
    
    // x.insert("ishu","soni");
    // x.insert("divas","soni");
    // x.insert("manas","soni");
    // x.insert('b',2.561);
    // x.insert('c',2.12332);
    // x.insert('d',2.6783);
    // x.insert('e',2.3454);

	return 0; 
} 

// insert(key, value) done
// erase(key) done
// find(key) done returns 0 ,1
// map_obj[key] done, if value not present inserts 0 and returns 0 if user provides value then insert that value
// size() done
// clear() done 
//throws seg fault if print value after clearing
//this will throw seg fault as map_obj[], erase, insert, delete works only when map exists

