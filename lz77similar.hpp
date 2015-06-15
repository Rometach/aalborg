#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>
#include "lz77.hpp"

#ifndef __LZ77_SIM_HPP__
#define __LZ77_SIM_HPP__

using namespace std;


/* INTERESTING FUNCTIONS*/
/* Computes the longest similar-equivalent prefix of 'input' in 'dictionary+input', beginning in 'dictionary'
   outputs the positions of its first and last 'Chord's in 'dictionary+input', and the value of the translation */
pair<unsigned, unsigned> longest_prefix_sim(vector<Chord> input, vector<Chord> dictionary, unsigned metric=0, double threshold=0);

/* Computes and outputs the LZ77 compression of 'input' using similarity equivalence
   with buffer and preview sizes 'l_buf' and 'l_pref' */
vector<tuple<unsigned, unsigned, Chord> > compress77_sim(vector<Chord> input, unsigned l_buf, unsigned l_prev, unsigned metric=0, double threshold=0);

/* Computes and outputs the decompression of the LZ77-compressed sequence 'dico', done using parameters 'l_buf' and 'l_pref'
   prints the (similarity-equivalent) sequences used in the compressed dictionary */
vector<vector<Chord> > print_dictionary_sim(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev);

/* Computes exhaustively every subsequence of 'input' and the number of times similarity-equivalent sequences occur;
   outputs all sequences that occur >= than 'occ_thres' times, along with their number of occurences */
vector<pair<vector<Chord>, unsigned> > allSequences_sim(vector<Chord> input, unsigned occ_thres, unsigned metric=0, double threshold=0);


/* USEFUL AUXILIARY PROCEDURES */
/* Computes the intersection of 's1' and 's2' */
set<unsigned> inter(set<unsigned> s1, set<unsigned> s2);
/* true iff 'c1' and 'c2' are similar
   'metric' = 1: with F1-distance 
            = 2: PCS-Prime equivalence (http://composertools.com/Theory/PCSets/PCSets3.htm) */
bool similar(Chord c1, Chord c2, unsigned metric=0, double threshold=0);
/* auxiliary similarity measures */
bool similarF1_aux(set<unsigned> s1, set<unsigned> s2, double threshold);
set<unsigned> PCS_prime(set<unsigned> s);


/* OPERATOR OVERLOADINGS */
/* Computes the distance between fondamental notes of 'Chords' 'c1' and 'c2', if they are equivalent */
unsigned operator-(Chord c1, Chord c2);

/*ostream& operator<<(ostream &flux, Chord c);
ostream& operator<<(ostream &flux, vector<Chord> v);
ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t);
ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v);
ostream& operator<<(ostream &flux, map<string, unsigned> m);*/

#endif



