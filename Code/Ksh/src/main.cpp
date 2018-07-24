#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <kmer.hpp>

using namespace std;

char getChar(char base){
	char ret;
	int r = rand() % 3;
	string seq;
  switch (base)
  {
      case 'A':
					seq = "CGT";
					ret = seq[r];
          break;
      case 'C':
					seq = "AGT";
					ret = seq[r];
          break;
      case 'G':
					seq = "ACT";
					ret = seq[r];
          break;
      case 'T':
					seq = "ACG";
					ret = seq[r];
          break;
      default:
          throw std::runtime_error("invalid DNA base");
  }
	return ret;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        cerr << "usage: " << argv[0] << " [sequence file]" << endl;
        return 1;
    }
/* initialize random seed: */
		srand (time(NULL));


		std::string seqname = argv[1];
		size_t lastindex = seqname.find_last_of("."); 
		size_t lastsla = seqname.find_last_of("/"); 
		string rawname = seqname.substr(lastsla + 1, lastindex);

		string outname = rawname + ".csv";

    fstream infile(seqname, fstream::in);
		if (!infile) {
			cout << "Unable to open file";
			return false;
		}
		fstream outfile(outname, fstream::out);
		Kmer prof;
		unsigned int ks;
		string seq;
		int r;
		unsigned int i, count, ssize;

		while (getline (infile, seq)){
			ssize = seq.size();
			count = 3;
			ks = prof.getKs(seq);
			outfile << ks << std::endl;
			for (i = 0; i < count; ++i) {
				r = rand() % ssize;
				outfile << r << "," << seq[r] << ",";
				seq[r] = getChar(seq[r]);
				outfile << seq[r] << ",";
				ks = prof.getKs(seq);
				outfile << ks << std::endl;
			}
		}

    return 0;
}
