#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>
#include "similarities.hpp"

#ifndef __LZ77_ANALYSIS_HPP__
#define __LZ77_ANALYSIS_HPP__

using namespace std;/* INTERESTING FUNCTIONS*/
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

#endif
