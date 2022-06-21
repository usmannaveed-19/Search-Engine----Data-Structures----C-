//============================================================================
// Name        : SearchEngine.cpp
// Author      : Muhammad Usman Naveed
// Version     : Final 
// Copyright   : (c) Reserved
// Description : Search Engine using the Data Structures
//============================================================================

#include <iostream>
#include <string>
#include<cmath>
#include <unistd.h> // for sleep()
#include <fstream>
using namespace std;


template <class T>
class Node				// Single Node Class
{
	T data;
	Node<T>* next;

public:
	Node()						
	{
		data = 0;
		next = NULL;
	}

	Node(T temp)
	{
		data = temp;
		next = NULL;
	}

	T getData()
	{
		return data;
	}

	void setNext(Node<T>* p)
	{
		next = p;
	}

	Node<T>* getNext()
	{
		return next;
	}

	void operator=(Node<T>* n)
	{
		this->data = n->data;
		this->next = n->next;
	}

};


template <class T>
class Linked_list		// Linked List Class
{
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	Linked_list()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}

	void setHead(Node<T>* ptr)
	{
		head = ptr;
	}

	Node<T>* getHead()
	{
		return head;
	}

	void setTail(Node<T>* ptr)
	{
		tail = ptr;
	}

	Node<T>* getTail()
	{
		return tail;
	}

	void setSize(int s)
	{
		size = s;
	}

	int getSize()
	{
		return size;
	}

	void insert(Node<T>* ins)
	{
		if (head == NULL)
		{
			head = ins;
			size++;
			tail = ins;
		}

		else
		{
			tail->setNext(ins);
			tail = ins;
			size++;
		}
	}

	void insert(T data)
	{
		Node<T>* ins = new Node<T>(data);
		if (head == NULL)
		{
			head = ins;
			size++;
			tail = ins;
		}

		else
		{
			tail->setNext(ins);
			tail = ins;
			size++;
		}
	}

	void display()
	{
		Node<T>* temp = head;
		while (temp != NULL)
		{
			cout << temp->getData() << " ";
			temp = temp->getNext();
		}
		cout << endl;
	}

};


class Doc_Info 			// DOC Info Class  -- Having DOC-ID and FREQUENCY
{
	string id;
	int frequency;

public:
	Doc_Info()
	{
		id = "";
		frequency = 0;
	}

	Doc_Info(string id, int s)
	{
		this->id = id;
		frequency = s;
	}

	void setId(string id)
	{
		this->id = id;
	}

	string getId()
	{
		return id;
	}

	void setFrequency(int f)
	{
		frequency = f;
	}

	int getFrequency()
	{
		return frequency;
	}

	void operator=(Doc_Info& d)
	{
		this->id = d.id;
		this->frequency = d.frequency;
	}

	friend ostream& operator<<(ostream& ofs, Doc_Info obj)
	{
		ofs <<"\t\t\t"<<"Document Name: "<< obj.getId() << "  Frequency: " << obj.getFrequency() << endl;
		return ofs;
	}

};


template <class T>
class Term_Info			// Term Info Class  -- Having KEY TERM and DOC-INFO LIST of Linked List Type
{
	string key;
	Linked_list<Doc_Info>* doc;

public:
	Term_Info()
	{
		key = "";
		doc = new Linked_list<Doc_Info>;
	}

	void setKey(string k)
	{
		key = k;
	}

	string& getKey()
	{
		return key;
	}

	void setDoc(Doc_Info d)
	{
		 doc->insert(d);
	}

	Linked_list<Doc_Info>*& getDoc()
	{
		return doc;
	}

	friend ostream& operator<<(ostream& ofs, Term_Info t)
	{
		ofs << t.getKey() << endl;
		return ofs;
	}

};


template <class T>
class AVLNode			// AVL NODE Class  -- Having left right pointers data and height
{
	AVLNode<T>* right, * left;
	T data;
	int height;

public:
	AVLNode()
	{
		right, left = NULL;
		data = 0;
		height = 0;
	}

	AVLNode(T data)
	{
		this->data = data;
		right = NULL; left = NULL;
		height = 0;
	}

	void setLeft(AVLNode<T>* l)
	{
		left = l;
	}

	void setRight(AVLNode<T>* r)
	{
		right = r;
	}

	AVLNode<T>*& getLeft()
	{
		return left;
	}

	AVLNode<T>*& getRight()
	{
		return right;
	}

	void setHeight(int h)
	{
		height = h;
	}

	int getHeight()
	{
		return height;
	}

	void setData(T d)
	{
		data = d;
	}

	T getData()
	{
		return data;
	}

};


template <class T>
class AVLTree			// AVL Tree Class  -- Having root pointer
{
private:
	AVLNode<T>* root;

	// Traverse Till returns True if the given root's key term matches with any other node's key term to update the linked list 
	bool traverseTill(AVLNode<T>* root, T data, AVLNode<T>*& ptr)	 
	{
		if (root == NULL)
		{
			return false;
		}

		if (root->getData().getKey() == data.getKey())
		{
			ptr = root;
			return true;
		}

		else if (root->getData().getKey() > data.getKey())
		{
			return traverseTill(root->getLeft(), data, ptr);
		}
		else if (root->getData().getKey() < data.getKey())
		{
			return traverseTill(root->getRight(), data, ptr);
		}
	}

	// just inserts the new node in the tree
	void insertNode(AVLNode<T>*& root, AVLNode<T>* data)
	{
		if (root == NULL)
		{
			root = data;
			return;
		}

		else if (root->getData().getKey() > data->getData().getKey())
		{
			insertNode(root->getLeft(), data);
			root = setBalance(data, root);
		}

		else if (root->getData().getKey() < data->getData().getKey())
		{
			insertNode(root->getRight(), data);
			root = setBalance(data, root);
		}

	}

	// Preorder traversal
	void PreOrder(AVLNode<T>* root)
	{
		if (root == NULL)
		{
			return;
		}

		cout << "\t\t\t\tWord: " << root->getData().getKey() << endl;
		root->getData().getDoc()->display();
		PreOrder(root->getLeft());
		PreOrder(root->getRight());
	}

	// returns the height of the given node
	int Height(AVLNode<T>* r)
	{
		int l_h, r_h;
		if (r == NULL)
			return 0;

		l_h = Height(r->getLeft());
		r_h = Height(r->getRight());

		if (l_h > r_h)
			return l_h + 1;
		else
			return  r_h + 1;
	}

	// returns the balance factor of the given node
	int getBalance(AVLNode<T>* r)
	{
		int lh = Height(r->getLeft());
		int rh = Height(r->getRight());
		return (lh - rh);
	}

	// returns the greater of the two given nodes
	int max(int a, int b)
	{
		if (a > b)
			return a;

		else
			return b;
	}

	// rotates the given node to the right
	AVLNode<T>* rotateRight(AVLNode<T>* y)
	{
		AVLNode<T>* x = y->getLeft();
		AVLNode<T>* T2 = x->getRight();
		x->setRight(y);
		y->setLeft(T2);
		y->setHeight(max(Height(y->getLeft()), Height(y->getRight())) + 1);
		x->setHeight(max(Height(x->getLeft()), Height(x->getRight())) + 1);
		return x;
	}

	// rotates the given node to the left
	AVLNode<T>* rotateLeft(AVLNode<T>* x)
	{
		AVLNode<T>* y = x->getRight();
		AVLNode<T>* T2 = y->getLeft();
		y->setLeft(x);
		x->setRight(T2);

		x->setHeight(max(Height(x->getLeft()), Height(x->getRight())) + 1);
		y->setHeight(max(Height(y->getLeft()), Height(y->getRight())) + 1);
		return y;
	}

	// sets the balance factor of the given two nodes
	AVLNode<T>* setBalance(AVLNode<T>* ptr, AVLNode<T>*& r)
	{
		
		if (getBalance(r) > 1)
		{
			if (ptr->getData().getKey() < r->getLeft()->getData().getKey())
			{
				return rotateRight(r);
			}
			else if (ptr->getData().getKey() > r->getLeft()->getData().getKey())
			{
				r->setLeft(rotateLeft(r->getLeft()));
				return  rotateRight(r);
			}
		}
		if (getBalance(r) < -1)
		{
			if (ptr->getData().getKey() > r->getRight()->getData().getKey())
			{
				return rotateLeft(r);
			}
			else if (ptr->getData().getKey() < r->getRight()->getData().getKey())
			{
				r->setRight(rotateRight(r->getRight()));
				return rotateLeft(r);
			}
		}
		return r;

	}

	// this updates the linked list of the given node along the given new data
	void updateAvlTree(AVLNode<T>*& root, T data)
	{
		root->getData().getDoc()->insert(data.getDoc()->getHead());
	}

	// this searches through all the nodes of the tree and updates the refernce pointer if the word mathers any of the node's key term
	void Search(AVLNode<T>* r, string word, AVLNode<T>*& ptr)
	{
		if (r == NULL)
		{
			return;
			
		}
		if (r->getData().getKey() == word)
		{
			ptr = r;
		}

		else if (r->getData().getKey() > word)
		{
			Search(r->getLeft(), word, ptr);
		}
		else if (r->getData().getKey() < word)
		{
			Search(r->getRight(), word, ptr);
		}
	}

public:
	AVLTree()
	{
		root = NULL;
	}

	// this inserts the given node in the tree and updates if the the nodes is already present
	void insert(T val)
	{

		AVLNode<T>* temp = root;
		AVLNode<T>* temp2;
		if (traverseTill(temp, val, temp2))
		{
			updateAvlTree(temp2, val);
		}
		else
		{
			AVLNode<T>* ptr = new AVLNode<T>(val);
			insertNode(root, ptr);

		}

	}
	
	// this searches for the given word in the tree and returns the node if found
	Linked_list<Doc_Info> Search_List(string word)
	{
		AVLNode<T>* ptr = NULL;

		Search(root, word, ptr);
		if (ptr == NULL)
		{
			Linked_list<Doc_Info> p;
			cout << "\t\t\t\tTerm not found" << endl;
			cout << endl << endl;
			return p;
		}
		else
		{
			cout << "\t\t\t\tTerm found" << endl;
			cout << endl << endl;
			return *(ptr->getData().getDoc());
		}
	}

	// Pre Order
	void displayPreOrder()
	{
		PreOrder(root);
	}

	// returns the root
	AVLNode<T>* getRoot()
	{
		return root;
	}

};


template <class T>
class Search_Engine		// Search Engine Class -- Having All the major functions and INdex of the AVL Tree
{
	AVLTree<T>* index;

public:
	Search_Engine()
	{
		index = new AVLTree<T>;
	}

	void set_index(AVLTree<T>* i)
	{
		index = i;
	}

	AVLTree<T>* getIndex()
	{
		return index;
	}

	// this functions inserts the information into a linked list
	void addition_of_doc(string doc_name, int freq, string term)
	{
		Doc_Info doc;
		doc.setId(doc_name);
		doc.setFrequency(freq);

		Term_Info<Doc_Info> t;
		t.setKey(term);
		t.setDoc(doc);

		index->insert(t);
	}

	// this finds all the unique words in all the documents and makes an array of them
	void unique_words(string* files, int size,string *&unique_words,int &unique_size)
	{
		fstream fs;
		int sp_count = 0;

		string* st = new string[size];
		for (int i = 0; i < size; i++)
		{

			fs.open(files[i] + ".txt", ios::in);

			getline(fs, st[i]);
			st[i] += " ";
			
			for (int j = 0; j < st[i].length(); j++)
			{
				st[i][j] = towlower(st[i][j]);
				if (st[i][j] == ' ')
					sp_count++;
			}

			fs.close();
		}

		string* words;
		int words_size = sp_count + size;
		words = new string[words_size];

		int j = 0;
		for (int k = 0; k < size; k++)
		{
			string word = "";

			for (int i = 0; i < st[k].length() && j < words_size; i++)
			{
				if (st[k][i] != ' ')
				{
					word += st[k][i];
				}

				else
				{
					words[j] = word;
					j++;
					word = "";
				}
			}

			words[j] = "--";
			j++;
		}

		delete[]st;
		int uni_size = 150;
		string* unique = new string[uni_size];

		for (int i = 0; i < uni_size; i++)
		{
			unique[i] = "";

		}

		for (int i = 0; i < words_size; i++)
		{
			bool check = true;
			string s = *(words + i);
			string temp = "";

			for (int k = 0; k < words_size; k++)
			{
				if (s == unique[k] && s != "--")
				{
					check = false;
					break;
				}
			}

			if (check == true)
			{
				for (int j = 0; j < words_size; j++)
				{
					if (s == words[j] && s != "--")
					{
						temp = s;
					}
				}
				unique[i] = temp;
			}
		}

		unique_size = 0;
		for (int i = 0; i < uni_size; i++)
		{
			if (unique[i] != "")
			{
				unique_size++;
			}
		}

		unique_words = new string[unique_size];
		int p = 0;
		for (int i = 0; i < uni_size && p < unique_size; i++)
		{
			if (unique[i] != "")
			{
				unique_words[p] = unique[i];
				p++;
			}
		}
	
		delete[]unique;

	}
	
	// this functions reads the files tokenize words and sends the words to unique words function and then send the words to addtion of doc function
	void Add_Doc_to_Index(string* files, int size)
	{
		string* uniq;
		int unique_size = 0;
		fstream fs;
		unique_words(files, size, uniq, unique_size);

		int f = 0;
		for (int i = 0; i < size; i++)
		{
			string str = "";
			int sp_count = 0;
		
			fs.open(files[i] + ".txt", ios::in);

			getline(fs, str);
			str += " ";
			

			for (int j = 0; j < str.length(); j++)
			{
				str[j] = tolower(str[j]);
				if (str[j] == ' ')
					sp_count++;
			}
			string *words = new string[sp_count];
			string word = "";
			int j = 0;
			for (int i = 0; i < str.length() && j < sp_count; i++)
			{
				if (str[i] != ' ')
					word += str[i];

				else
				{
					words[j] = word;
					j++;
					word = "";
				}
			}

			for (int i = 0; i < unique_size; i++)
			{
				int frequency = 0;
				for (int j = 0; j < sp_count; j++)
				{
					if (words[j] == uniq[i])
					{
						frequency++;
					}
				}
				if (frequency != 0)
				{
					addition_of_doc(files[f], frequency, uniq[i]);
				}
			}
			delete[]words;
			fs.close();
			f++;
		}
		delete[]uniq;
	}

	// this function is used to add the doc to the index
	void Create_Index(string* Docs, int size)
	{
		Add_Doc_to_Index(Docs, size);
	}

	// RULE # 1
	void Rule_No1(int*& num_terms, int size, string*& docs, int*& freq)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (num_terms[i] < num_terms[j])
				{
					swap(num_terms[i], num_terms[j]);
					swap(freq[i], freq[j]);
					swap(docs[i], docs[j]);
				}
			}
		}
	}
	
	// RULE # 2
	void Rule_No2(int*& num_terms, int size, string*& docs, int*& freq)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				if ((num_terms[i] == num_terms[j]) && (freq[i] < freq[j]))
				{
					swap(num_terms[i], num_terms[j]);
					swap(freq[i], freq[j]);
					swap(docs[i], docs[j]);
				}
			}
		}
	}
	
	// RULE # 3
	void Rule_No3(int* &num_terms, int size, string* &docs, int* &freq)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size ; j++)
			{
				if ((freq[i] == freq[j]) && (docs[i]>docs[j]) &&(num_terms[i]== num_terms[j]))
				{
					swap(num_terms[i], num_terms[j]);
					swap(freq[i], freq[j]);
					swap(docs[i], docs[j]);
				}
			}
		}
	}
	
	// Display the Rankings of the documents
	void display_ranked_docs(int* num_terms, int size, string* docs, int* freq)
	{
		cout << "\033[4;33m\t\t\t\t          Ranked List          \033[0m\n" << endl << endl;
		cout << "\t\t\t\tRanked Documents for the Search" << endl << endl;
		bool check = true;
		for (int i = 0; i < size; i++)
		{
			check = false;
			if (freq[i] > 0 && num_terms[i] > 0)
			{
				cout << "\t\t\t\tDocument Name: " << docs[i] << endl;
				cout << "\t\t\t\tCollective Frequency: " << freq[i] << endl;
				cout << "\t\t\t\tNumber of terms: " << num_terms[i] << endl;
				cout << endl << endl;
				check = true;
			}
		}

		if (check == false)
		{
			cout << "\t\t\tSorry No Related Documents Found for your Query" << endl << endl;
		}
	}

	// this function is used to search the query 
	void Search_Documents(string query, int size, string *files)
	{

		int sp_count = 0;
		query += " ";
		for (int j = 0; j < query.length(); j++)
		{
			if (query[j] == ' ')
				sp_count++;
		}

		string* words = new string[sp_count];
		string word = "";
		int j = 0;
		for (int i = 0; i < query.length() && j < sp_count; i++)
		{

			if (query[i] != ' ')
				word += query[i];
			else
			{
				words[j] = word;
				j++;
				word = "";
			}
		}
		
		int* freq = new int[size];
		int *num_terms=new int[size];
		string *doc=new string[size];

		for(int i = 0; i < size; i++)
		{
			freq[i] = num_terms[i] = 0;
			doc[i] = files[i];
		}

		Linked_list<Doc_Info> list;

		for (int i = 0; i < sp_count; i++)
		{
			cout << "\t\t\t\tWord to Search: " << words[i] << endl;
			list = index->Search_List(words[i]);

			while (list.getHead() != NULL)
			{
				for (int i = 0; i < size; i++)
				{
					if (list.getHead()->getData().getId() == doc[i])
					{
						num_terms[i] += 1;
						freq[i] += list.getHead()->getData().getFrequency();
						break;
					}
				}
				list.setHead(list.getHead()->getNext());
			}
		}

		Rule_No1(num_terms, size, doc, freq);
		Rule_No2(num_terms, size, doc, freq);
		Rule_No3(num_terms, size, doc, freq);
		display_ranked_docs(num_terms, size, doc, freq);
	
		delete[]freq;
		delete[] doc;
		delete [] num_terms;
	}

};

// int main()
int main()
{
	string doc[] = {"doc1","doc2","doc3","doc4" };
	Search_Engine<Term_Info<Doc_Info>> s;
	s.Create_Index(doc, 4);

	cout << endl << endl;
	cout << "\033[1;31m\t\t\t<<<<<     S     E     A     R     C     H     ---     E     N     G     I     N     E     >>>>>\033[0m\n";
	cout << endl << endl;

	while (true)
	{
		char opt;

		cout << "\tPress 1 to see the Linked List of Each Unique Term" << endl;
		cout << "|\tPress 2 to Input a Query" << endl;
		cout << "\tPress 3 to Clear Screen" << endl;
		cout << "\tPress 4 to Exit Search Engine" << endl;
		cout << "\tOption: ";
		cin >> opt;
		
		switch (opt)
		{
			case '1':
			{	
				cout << "\033[4;33m\t\t\t\t          LINKED LIST          \033[0m\n" << endl << endl;
				std::cout << "\n\n\tLoading Please Wait  ";
				for (int i=0 ; i<2 ; i++) 
				{
					sleep(1); std::cout << "\b\\" << std::flush;
					sleep(1); std::cout << "\b|" << std::flush;
					sleep(1); std::cout << "\b/" << std::flush;
					sleep(1); std::cout << "\b-" << std::flush;
				}
				s.getIndex()->displayPreOrder();
				break;
			}

			case '2':
			{
				cin.ignore();
				string query;
				cout << "\033[4;33m\t\t\t\t          ENTER YOUR QUERY          \033[0m\n" << endl << endl;
				cout << "Query: ";
				getline(cin, query);
				std::cout << "\n\n\tSearching Please Wait  ";
				for (int i=0 ; i<2 ; i++) 
				{
					sleep(1); std::cout << "\b\\" << std::flush;
					sleep(1); std::cout << "\b|" << std::flush;
					sleep(1); std::cout << "\b/" << std::flush;
					sleep(1); std::cout << "\b-" << std::flush;
				}
				for (int i = 0; i < query.length(); i++)
				{
					query[i] = tolower(query[i]);
				}
				cout << endl;
				s.Search_Documents(query, 4, doc);
				break;
			}

			case '3':
			{
				cout << "\033[4;33m\t\t\t\t          Screen Cleared          \033[0m\n" << endl << endl;
				system("CLS");
			}

		}
		
		if (opt == '4')
		{
			cout << endl << endl;
				cout << "\033[4;33m\t\t\t\t\t\t                         EXIT CALLED                         \033[0m\n" << endl << endl;
			break;
		}

	}
	
}