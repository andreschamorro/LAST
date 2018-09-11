#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <matrix.hpp>
#include <shclu.hpp>

using namespace std;

int main(int argc, char** argv) {

	if (argc != 3) {
		cerr << "usage: " << argv[0] << " k0 [similarity file]" << endl;
		return 1;
	}

	unsigned int k = atoi(argv[1]);
	std::fstream infile(argv[2], fstream::in);

	std::fstream simfile;
	std::string rawname, seqname, outname;
	size_t lastindex, lastsla;
	std::vector<unsigned int> row;
	MatrixRow S;

	while (getline (infile, seqname)){
		lastindex = seqname.find_last_of("."); 
		lastsla = seqname.find_last_of("/"); 
		outname = seqname.substr(lastsla + 1, lastindex) + ".vec";

		simfile.open(seqname, fstream::in);
		if (!simfile) {
			cout << "Unable to open file";
			return false;
		}
		fstream outfile(outname, fstream::out);

		string seq;

		simfile >> S;

		std::cout << "Shrinkage Init" << std::endl;

		row = cpu_shrinkageClustering(S, k, 1000);

		std::cout << "Num Cluster = " << *std::max_element( row.begin(), row.end() ) << std::endl;

		for (unsigned int i = 0; i < row.size(); ++i) {
			outfile << row[i] << std::endl;
		}
		simfile.close();
	}

	return 0;
}
