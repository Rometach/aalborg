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

#ifndef __LZ77_SIMIL_HPP__
#define __LZ77_SIMIL_HPP__

using namespace std;


/* USEFUL AUXILIARY PROCEDURES */
/* true iff 'c1' and 'c2' (resp. 'v1' and 'v2') are equivalent by translation */
bool equiv(Chord c1, Chord c2);
bool equivv(vector<Chord> v1, vector<Chord> v2);


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

#endif
