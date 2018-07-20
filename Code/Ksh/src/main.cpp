#include <iostream>
#include <fstream>
#include <cstdlib>
#include <kmer.hpp>

using namespace std;

int main(int argc, char** argv) {

    if (argc != 3) {
        cerr << "usage: " << argv[0] << " [k] [sequence]" << endl;
        return 1;
    }

    size_t k = atoi(argv[1]);
		std::cout << k << std::endl;

    fstream infile(argv[2], fstream::in);
    // read each char in file
		Kmer prof;
		string seq((istreambuf_iterator<char>(infile)), (istreambuf_iterator<char>()));
		seq.pop_back();

		std::cout << unsigned(prof.toBin("AAATTCG")) << std::endl;
		std::cout << unsigned(prof.toBin("AAAAATTCG")) << std::endl;

//		unsigned int ns = prof.fromSequence(seq, k);
//		std::cout << "ns " << ns << std::endl;
//		unsigned int ks = prof.getKs(seq);
//		std::cout << "ks " << ks << std::endl;
//		std::vector<BST> tks = prof.BSTForest(seq, ks, 30); 

		// tree->print();

    // // count the nodes in the tree
    // cout << endl;
    // cout << "kmers inserted: " << bufcount << endl;
    // cout << "tree size: " << tree->size() << endl;
    // cout << "tree leaves: " << tree->numLeaves() << endl;
    // cout << endl;
		// string s;
		// char str[20];
		// tree->display(str, 0, bufcount);

    // delete tree;
		//

    return 0;
}
