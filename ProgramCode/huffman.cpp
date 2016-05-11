#include "huffman.h"

Huffman::Huffman(string encodeThis)
//Constructor which also does the encoding
{
	originalStr = encodeThis;	//Store original string

	//GET FREQUENCIES=====================================================
	vector<pair<string,int> > lettFreqs;	//Vector of letter frequencies

	//Loop until encodeThis is empty
	while (encodeThis != "")
	{
		string current = encodeThis.substr(0,1);
		int freq = 0;
		//Iterate through encodeThis
		for (int x = 0; x < (int)encodeThis.size(); x++)
		{
			//If a matching letter is found, delete it and count it
			if (current == encodeThis.substr(x,1))
			{
				freq++;
				encodeThis.erase(encodeThis.begin() + x);
				x--;
			}
		}
		//Create a pair between current and freq, and push into lettFreqs
		pair<string,int> freqPair = make_pair(current,freq);
		lettFreqs.push_back(freqPair);
	}
	//BUILD TREE==========================================================
	//Convert lettFreqs into non star starNodes
	for (int x = 0; x < (int)lettFreqs.size(); x++)
	{
		starNode newStar(lettFreqs.at(x).first,lettFreqs[x].second,false);
		treeGen.push_back(newStar);
	}
	//Sort the vector based on frequency with smallest on top
	sort(treeGen.begin(),treeGen.end(),based_on_freq());

	//Loop until there's only one left in treeGen to generate tree
	while (treeGen.size() != 1)
	{
		//Grab first two
		starNode first = treeGen.at(0);
		starNode second = treeGen.at(1);

		//Pop the first two
		treeGen.erase(treeGen.begin());
		treeGen.erase(treeGen.begin());

		//Generate an internal node (a true star node in this case)
		int combineFreqs = first.freq + second.freq;
		starNode internal("",combineFreqs,true);

		//If first should be left child of internal
		if (first.freq < second.freq)
		{
			internal.children.push_back(first);
			internal.children.push_back(second);
		}
		//Otherwise second should be the left child
		else
		{
			internal.children.push_back(second);
			internal.children.push_back(first);
		}
		//Push internal into treeGen and resort
		treeGen.push_back(internal);
		sort(treeGen.begin(),treeGen.end(),based_on_freq());
	}
	//GENERATE HUFFMAN CODE===============================================
	//The tree has been made, now traverse and generate HuffCode
	deque<starNode> needsVisiting;	//Queue for bfs traversal
	vector<starNode> vectCursor;	//Holds current children
	starNode cursor = treeGen.at(0);//Holds current node
	cursor.code = "";	//Root of tree has no HuffCode
	results.push_back(cursor);

	//If cursor has children
	if (cursor.star)
	{
		//Queue to visit later
		needsVisiting.push_back(cursor);
	}
	//Loop until needsVisiting is empty
	while (!needsVisiting.empty())
	{
		//Cursor points to parent
		cursor = needsVisiting.front();
		needsVisiting.pop_front();

		//vectCursor represents cursor's children
		vectCursor = cursor.children;

		//Loop through vectCursor
		for (int x = 0; x < (int)vectCursor.size(); x++)
		{
			//If left child, assign 0 HuffCode
			if (x == 0)
			{
				vectCursor[x].code = cursor.code + "0";
			}
			//If right child, assign 1 HuffCode
			else if (x == 1)
			{
				vectCursor[x].code = cursor.code + "1";
			}
			//Queue into needsVisiting if necessary
			if (vectCursor[x].star)
			{
				needsVisiting.push_back(vectCursor[x]);
			}
			//Push into results
			results.push_back(vectCursor[x]);

		}
	}
	//GENERATE PRINTABLE TREE=============================================
	vector<starNode> sortedResults = results;	//Copy of results vect
	string curCode;								//Holds current HuffCode
	BinaryTree *ptr;							//Tree pointer
	BinaryTree *node = new BinaryTree;			//Tree node

	//Sort the copied result vector by code
	sort(sortedResults.begin(),sortedResults.end(),based_on_code());

	//Create root
	if (sortedResults.at(0).star)
	{
		node->data = "()";
	}
	else
	{
		node->data = sortedResults.at(0).data;
	}
	node->left = NULL;
	node->right = NULL;
	root = node;

	//Loop through all results (skipping root)
	for (int x = 1; x < (int)sortedResults.size(); x++)
	{
		//Create new node
		node = new BinaryTree;
		node->left = NULL;
		node->right = NULL;
		if (sortedResults[x].star)
		{
			node->data = "()";
		}
		else
		{
			node->data = sortedResults[x].data;
		}
		//Set current code
		curCode = sortedResults[x].code;

		//Reset ptr to root
		ptr = root;

		//Loop through code
		while (curCode != "")
		{
			//If the current letter is a 0
			if (curCode[0] == '0')
			{
				//If there's a left child, go there
				if (ptr->left != NULL)
				{
					ptr = ptr->left;
				}
				//Otherwise insert
				else
				{
					ptr->left = node;
				}
			}
			//Otherwise current letter is a 1
			else
			{
				//If there's a right child go there
				if (ptr->right != NULL)
				{
					ptr = ptr->right;
				}
				//Otherwise insert
				else
				{
					ptr->right = node;
				}
			}
			//Delete the first character
			curCode.erase(curCode.begin());
		}
	}
}

Huffman::~Huffman()
//Destructor
{deleteTree(root);}

void Huffman::printHuffCodes() const
//Prints out all Huffman Code for all letters
{
	//Display results
	for (int x = 0; x < (int)results.size(); x++)
	{
		//Only print non-internal nodes
		if (!results.at(x).star)
		{
			cout << "(" <<  results[x].data << ") = "
				 << results[x].code << endl;
		}
	}
}

void Huffman::generateEncoding(string fileName)
//Outputs encoding to specified text file
{
	string encodeThis = originalStr;
	string returnThis = "";
	ofstream fout;
	fout.open(fileName.c_str());

	//Loop until encodeThis is empty
	while (encodeThis != "")
	{
		//Current is first letter of original
		string current = encodeThis.substr(0,1);

		//Pop the front off the original
		encodeThis.erase(encodeThis.begin());

		//Search results for current
		for (int x = 0; x < (int)results.size(); x++)
		{
			if (current == results[x].data)
			{
				fout << results[x].code;
				x = results.size();
			}
		}
	}
	fout.close();
}

void Huffman::decodeFile(string iFile,string oFile)
//Decodes a Huffman encoded file and exports it to another text file
{
	ifstream fin(iFile.c_str());
	ofstream fout;
	BinaryTree *cursor = root;
	char c;

	//Open output file
	fout.open(oFile.c_str());

	//Read one char at a time from input file
	while (fin.get(c))
	{
		//If c = 0 go left
		if (c == '0')
		{
			cursor = cursor->left;
		}
		//Otherwise go right
		if (c == '1')
		{
			cursor = cursor->right;
		}
		//If cursor has no children
		if (cursor->right == NULL && cursor->left == NULL)
		{
			//Write to output and reset cursor
			fout << cursor->data;
			cursor = root;
		}
	}
	//Close files
	fin.close();
	fout.close();
}

void Huffman::printFreqs() const
//Print frequencies of every character
{
	//Loop through results
	for (int x = 0; x < (int)results.size(); x++)
	{
		//Only print external nodes
		if (!results[x].star)
		{
			cout << "[" << results[x].data << "] x " << results[x].freq
				 << endl;
		}
	}
}

void Huffman::deleteTree(BinaryTree *node)
//Deletes printable tree recursively
{
	if (node == NULL)
	{
		return;
	}
	//Recur
	deleteTree(node->left);
	deleteTree(node->right);

	//Delete
	delete node;
}

void Huffman::recurTree(BinaryTree *cursor, int spaces)
//Recursive BST tree printing method
{
	//If cursor isn't null
	if (cursor != NULL)
	{
		//Recur
		recurTree(cursor->right, spaces + 3);

		//Loop through spaces
		for (int i = 0; i < spaces; i++)
		{
			cout << ' ';
		}
		//Output like this if it's an internal node
		if (cursor->data == "()")
		{
			cout << cursor->data << endl;
		}
		//Otherwise put brackets around the character
		else
		{
			cout << "[" << cursor->data << "]\n";
		}
		//Recur
		recurTree( cursor->left, spaces + 3 );
	}
}
