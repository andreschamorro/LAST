/*
 * =====================================================================================
 *
 *       Filename:  tree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/12/2018 10:33:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andres Chamorro (ach), andresdavidchamorro@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef  DTREE_HPP
#define  DTREE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>

using namespace std;

namespace dtrie {

    class node {

    public:

        char label;
        void* data;
        vector<node*> children;
        bool isLeaf(void);
        long int size(void);
        long int numLeaves(void);
				void display(char str[], int level = 0, int numk = 1);
				size_t count = 0;
        void print(string p = "");

        node(char c) : label(c), data(NULL) { }

        node(void) // root node constructor
            : label('@')
            , data(NULL)
            { }

        node(const node& n) {
            label = n.label;
            children = n.children;
        }

        ~node(void) {
            for (vector<node*>::iterator c = children.begin();
                 c != children.end(); ++c) {
                delete *c;
            }
        }

        // adds sequence to tree.  node* t points to the node corresponding to the last
        // node in the sequence's path through the labeled tree.
        node* addSequence(string& s, size_t i = 0);

        // returns the last node matched by t.  n is set to the number of matched characters in the path.
        node* findSequence(string& s, int& n, size_t i = 0);

    };

}

#endif   /* ----- #ifndef DTREE_HPP  ----- */
