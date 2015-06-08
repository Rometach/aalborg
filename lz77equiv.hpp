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


/* INTERESTING FUNCTIONS*/
/* Computes the longest translational-equivalent prefix of 'input' in 'dictionary+input', beginning in 'dictionary'
   outputs the positions of its first and last 'Chord's in 'dictionary+input', and the value of the translation */
tuple<unsigned, unsigned, unsigned> longest_prefix_eq(vector<Chord> input, vector<Chord> dictionary);

/* Computes and outputs the LZ77 compression of 'input' using translational equivalence
   with buffer and preview sizes 'l_buf' and 'l_pref' */
vector<tuple<unsigned, unsigned, unsigned, Chord> > compress77_eq(vector<Chord> input, unsigned l_buf, unsigned l_prev);

/* Computes and outputs the decompression of the LZ77-compressed sequence 'dico', done using parameters 'l_buf' and 'l_pref'
   prints the (translational-equivalent) sequences used in the compressed dictionary */
vector<vector<Chord> > print_dictionary_eq(vector<tuple<unsigned, unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev);

/* Computes exhaustively every subsequence of 'input' and the number of times translational-equivalent sequences occur;
   outputs all sequences that occur >= than 'threshold' times, along with their number of occurences */
map<string, unsigned> allSequences_eq(vector<Chord> input, unsigned threshold);


/* USEFUL AUXILIARY PROCEDURES */
/* true iff 'c1' and 'c2' (resp. 'v1' and 'v2') are equivalent by translation */
bool equiv(Chord c1, Chord c2);
bool equivv(vector<Chord> v1, vector<Chord> v2);


/* OPERATOR OVERLOADINGS */
/* Computes the distance between fondamental notes of 'Chords' 'c1' and 'c2', if they are equivalent */
unsigned operator-(Chord c1, Chord c2);

/*ostream& operator<<(ostream &flux, Chord c);
ostream& operator<<(ostream &flux, vector<Chord> v);
ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t);
ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v);
ostream& operator<<(ostream &flux, map<string, unsigned> m);*/

#endif



