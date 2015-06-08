#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include "lz77.hpp"

#ifndef __LZ77_EQ_HPP__
#define __LZ77_EQ_HPP__

using namespace std;

tuple<unsigned, unsigned, unsigned> longest_prefix_eq(vector<Chord> input, vector<Chord> dictionary);
vector<tuple<unsigned, unsigned, unsigned, Chord> > compress77_eq(vector<Chord> input, unsigned l_buf, unsigned l_prev);
vector<vector<Chord> > print_dictionary_eq(vector<tuple<unsigned, unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev);
map<string, unsigned> allSequences_eq(vector<Chord> input, unsigned threshold);
bool equiv(Chord c1, Chord c2);
bool equivv(vector<Chord> v1, vector<Chord> v2);

unsigned operator-(Chord c1, Chord c2);
/*ostream& operator<<(ostream &flux, Chord c);
ostream& operator<<(ostream &flux, vector<Chord> v);
ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t);
ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v);
ostream& operator<<(ostream &flux, map<string, unsigned> m);*/

#endif



