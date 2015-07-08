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
bool similar(vector<Chord> v1, vector<Chord> v2, unsigned metric, double threshold);
/* Test function computing the binary similarity matrix for 'data' with every implemented metric
   and several threshold values */
void main_test_similarities(vector<Chord> data);


/* USEFUL AUXILIARY PROCEDURES */
    /* (0) Equality*/

    /* (1) F1-distance with threshold */
    /* Computes the intersection of 's1' and 's2' */
    set<unsigned> inter(set<unsigned> s1, set<unsigned> s2);
    /* Computes the F1-distance between 's1' and 's2' */
    double similarF1(set<unsigned> s1, set<unsigned> s2);

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

    /* (4) Morris (http://www.jstor.org/stable/832996) */
    /* Computes the interval vector corresponding to s */
    vector<unsigned> interval_vector(set<unsigned> s);
    /* Computes Morris' similarity (sum of absolute values of differences between interval vectors of 'c1' and 'c2') */
    unsigned morris(Chord c1, Chord c2);

    /* (5) Rahn (http://www.jstor.org/stable/832998, http://www.jstor.org/stable/843860) */
    /* Computes Rahn's similarity (sum of dyads embedded mutually in 'c1' and 'c2'), as scaled by Isaacson */
    double rahn(Chord c1, Chord c2);

    /* (6) Lewin (http://www.jstor.org/stable/832999) */
    /* Computes Lewins's similarity (scaled sum of the square roots of the products in the interval vectors of 'c1' and 'c2') */
    double lewin(Chord c1, Chord c2);

    /* (7) Teitelbaum (http://www.jstor.org/stable/843150) */
    /* Computes Teitelbaum's similarity index (euclidian distance) between the interval vectors of 'c1' and 'c2' */
    double similarity_index(Chord c1, Chord c2);

    /* (8) Isaacson (http://www.jstor.org/stable/843860) */
    /* Computes Isaacson's similarity (standard deviation of the difference between the interval vectors of 'c1' and 'c2') */
    double IcVSIM(Chord c1, Chord c2);

    /* (9) Equality based only on root notes */
    /* Returns 'true' if and only if the root notes of 'c1' and 'c2' are the same */
    bool fundamental_eq(Chord c1, Chord c2);


/* SUMMARY OF IMPLEMENTED SIMILARITIES */
/* 0 : equality
   1 : F1-distance
   2 : PCS-Prime equivalence (http://composertools.com/Theory/PCSets/PCSets3.htm)
   3 : translationnal equivalence
   4 : Morris (http://www.jstor.org/stable/832996)
   5 : Rahn (http://www.jstor.org/stable/832998)
   6 : Lewin (http://www.jstor.org/stable/832999)
   7 : Teitelbaum (http://www.jstor.org/stable/843150)
   8 : Isaacson (http://www.jstor.org/stable/843860)
   9 : fundamental notes
*/
#endif
