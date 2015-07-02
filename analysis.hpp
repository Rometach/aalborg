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

using namespace std;


/* This file contains standard compression/analysis functions for 'vector<Chord>' data */
/* For 'metric' and 'threshold' parameters, see similarities.hpp */


/* Computes the longest equivalent prefix of 'input' in 'dictionary+input', beginning in 'dictionary'
   outputs the positions of its first and last 'Chord's in 'dictionary+input' */
pair<unsigned, unsigned> longest_prefix_sim(vector<Chord> input, vector<Chord> dictionary, unsigned metric=0, double threshold=0);

/* Computes and outputs the LZ77 compression of 'input' using similarity equivalence
   with buffer and preview sizes 'l_buf' and 'l_pref' */
vector<tuple<unsigned, unsigned, Chord> > compress77_sim(vector<Chord> input, unsigned l_buf, unsigned l_prev, unsigned metric=0, double threshold=0);

/* Computes and outputs the decompression of the LZ77-compressed sequence 'dico', done using parameters 'l_buf' and 'l_pref' */
vector<vector<Chord> > dictionary_sim(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev);

/* Prints the (similarity-equivalent) sequences used in the compressed dictionary in flux
   if they occur >= than 'occ_thres' times and are of length >= 'lg_thres' */
void print_dictionary_sim(vector<vector<Chord> > patterns, unsigned occ_thres, unsigned lg_thres, ostream &flux);

/* Computes exhaustively every repeated (similarity-equivalently, at least twice) subsequence of 'input'
   and the number of times similarity-equivalent sequences occur;
   outputs all sequences that occur >= than 'occ_thres' times and of length >= 'lg_thres',
   along with their number of occurences */
vector<pair<vector<Chord>, unsigned> > allSequences_sim(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric=0, double threshold=0);

#endif
