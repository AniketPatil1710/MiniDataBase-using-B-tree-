#include <iostream>
#include <vector> 
#include <algorithm>
#include <fstream>
#include <string>

using namespace std ;

#ifndef NODE_H
#define NODE_H

class Node {
	/*
		Generally size of the this node should be equal to the block size. Which will limit the number of disk access and increase the accesssing time.
		Intermediate nodes only hold the Tree pointers which is of considerably small size(so they can hold more Tree pointers) and only Leaf nodes hold
		the data pointer directly to the disc.
		IMPORTANT := All the data has to be present in the leaf node
	*/

	public:
		bool isLeaf ;
		vector<int> keys ;
		//ptr2next = p_next
		//ptr2Tree = p_Tree
		//dataptr = p_data
		//ptr2TreeOrData = p_TreeORData
		Node* p_next ;

		//making memory efficient Node
		union ptr{
			vector<Node*> p_Tree ; //vector of pointers to children sub-trees for intermediate nodes
			vector<FILE*> p_data ; //Data-pointer to leaf node

			ptr(); // removing error
			~ptr();
		}p_TreeOrData ;

	friend class BPTree ; //to access private members of the Node 

	public:
		Node();
};

class BPTree {

	private:
		int maxChildlimit ;
		int maxLeafNodelimit ;
		Node* root ;

		void insertInternal(int x , Node** cursor , Node** child);
		Node* findParent(Node* cursor , Node* child);
		Node* firstLeftNode(Node* cursor);
	public:
    	BPTree();
    	BPTree(int degreeInternal, int degreeLeaf);
    	Node* getRoot();
    	int getMaxIntChildLimit();
    	int getMaxLeafNodeLimit();
    	void setRoot(Node *);
    	void display(Node* cursor);
    	void seqDisplay(Node* cursor);
    	void search(int key);
    	void insert(int key, FILE* filePtr);
    	void removeKey(int key);
    	void removeInternal(int x, Node* cursor, Node* child);
};

#endif
