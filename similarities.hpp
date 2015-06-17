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


/* This file contains functions to calculate similarities between 'Chord's */


/* MAIN FUNCTION */
/* Returns 'true' if and only if c1 and c2 are similar according to metric 'metric'
   its value corresponds to the choice of metric between the following functions
   the possbilities are summed up at the end of the file */
bool similar(Chord c1, Chord c2, unsigned metric=0, double threshold=0);

/* AUXILIARY PROCEDURES*/



/* USEFUL AUXILIARY PROCEDURES */
    /* (0) Equality*/

    /* (1) F1-distance with threshold */
    /* Computes the intersection of 's1' and 's2' */
    set<unsigned> inter(set<unsigned> s1, set<unsigned> s2);
    /* Returns 'true' if and only if the F1-distance between 's1' and 's2' is >= threshold */
    bool similarF1(set<unsigned> s1, set<unsigned> s2, double threshold);

    /* (2) PCS-Prime equivalence (http://composertools.com/Theory/PCSets/PCSets3.htm) */
    /* Computes the PCS of c */
    set<unsigned> PCS(Chord c);
    /* Returns the PCS_prime set corresponding to s */
    set<unsigned> PCS_prime(set<unsigned> s);

    /* (3) Translationnal equivalence */
    /* Returns 'true' iff 'c1' and 'c2' (resp. 'v1' and 'v2') are equivalent by translation */
    bool similar_translation(Chord c1, Chord c2);
    bool similar_translation(vector<Chord> v1, vector<Chord> v2);
    /* Computes the distance between fondamental notes of 'Chords' 'c1' and 'c2', if they are equivalent by translation */
    unsigned operator-(Chord c1, Chord c2);

/* SUMMARY OF IMPLEMENTED SIMILARITIES */
/* 0 : equality
   1 : F1-distance
   2 : PCS-Prime equivalence (http://composertools.com/Theory/PCSets/PCSets3.htm)
   3 : translationnal equivalence
*/
#endif
