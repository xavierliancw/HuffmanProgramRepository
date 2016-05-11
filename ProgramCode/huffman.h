#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <deque>
#include <iomanip>
#include <deque>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <queue>
using namespace std;

class Huffman
{
private:
	//A class that's basically a glorified struct that Huffman uses
	class starNode
	{
	public:
		starNode()
		{
			data = "";
			freq = -1;
			star = false;
			code = "";
		};
		starNode(string inData, int inFreq, bool inStar)
		{
			data = inData;
			freq = inFreq;
			star = inStar;
			code = "";
		}
		~starNode(){}
		string data;
		int freq;
		bool star;
		string code;
		vector<starNode> children;
	};
	struct BinaryTree
	{
		string data;
		BinaryTree *left;
		BinaryTree *right;
	};
	struct based_on_freq
	//Instructs sort() functions to sort using the freq of a starNodeVect
	{
	    bool operator()(const starNode &left,
	                    const starNode &right)
	    {return left.freq < right.freq;}
	};
	struct based_on_code
	//Instructs sort() functions to sort using the code of a starNodeVect
	{
	    bool operator()(const starNode &left,
	                    const starNode &right)
	    {return left.code < right.code;}
	};
	string originalStr;
	vector<starNode> results;	//Vector of Huffman Codes
	vector<starNode> treeGen;	//Huffman Tree
	BinaryTree *root;			//Printable tree

	void deleteTree(BinaryTree *node);
	void recurTree(BinaryTree *cursor, int spaces);

public:
	Huffman(string encodeThis);	//Generates HuffCode for encodeThis
	~Huffman();					//Destructor

	void printHuffCodes() const;//Prints out all HuffCode for all letters
	void generateEncoding(string fileName);	//Outputs encoding to txt file
	void decodeFile(string iFile,string oFile);//Decodes an encoded file
	void printFreqs() const;//Prints frequencies of every character
	void printTree() {recurTree(root,0);}//Prints out Huffman Tree
};

#endif // HUFFMAN_H
