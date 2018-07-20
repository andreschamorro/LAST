/*
 * =====================================================================================
 *
 *       Filename:  tree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/12/2018 10:40:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "tree.hpp"

using namespace std;

namespace dtrie {

    node* node::addSequence(string& s, size_t i) {

        if (i == s.size()){
					count++;
					return this;
				}

        node* mc = NULL; // matching child
        for (vector<node*>::iterator c = children.begin();
             c != children.end(); ++c) {
            if ((*c)->label == s[i]) {
                mc = *c; break;
            }
        }
        if (!mc) {
            mc = new node(s[i]);
            children.push_back(mc);
        }
        return mc->addSequence(s, i+1);
    }

    long int node::size(void) {
        long int s = 1; // count self
        for (vector<node*>::iterator c = children.begin();
             c != children.end(); ++c) {
            s += (*c)->size();
        }
        return s;
    }

    bool node::isLeaf(void) {
        return children.size() == 0;
    }

    long int node::numLeaves(void) {
        long int s = 0;
        if (isLeaf()) {
            ++s; // counts self if leaf
        } else {
            for (vector<node*>::iterator c = children.begin();
                 c != children.end(); ++c) {
                s += (*c)->numLeaves();
            }
        }
        return s;
    }
		void node::display(char str[], int level, int numk){
			  // If node is leaf node, it indiicates end
				// of string, so a null charcter is added
				// and string is displayed
        if (isLeaf()) {
					str[level] = label + '\0';
					cout << str << " " << count << " "  << (long double) count / (long double) numk << " ";
          vector<uint64_t>* v = (vector<uint64_t>*) data;
          vector<uint64_t>::iterator p = v->begin();
          cout << *p;
					p++;
          for ( ;  p != v->end(); p++) {
              cout << "," << *p;
          }
					cout << endl;
					return;
        } else {
            for (vector<node*>::iterator c = children.begin();
                 c != children.end(); ++c) {
							str[level] = label;
                (*c)->display(str, level + 1, numk);
            }
        }
		}
}
