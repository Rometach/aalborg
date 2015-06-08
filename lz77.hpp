#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>

#ifndef __LZ77_HPP__
#define __LZ77_HPP__

using namespace std;

enum NOTE { A, B, C, D, E, F, G };

enum ACCIDENTAL {NONE, MOLL, DUR};

typedef unsigned HARM;

typedef struct{
    bool nc;
    NOTE n;
    ACCIDENTAL a;
    HARM h;
} Chord;


/* INTERESTING FUNCTIONS*/
/* Computes the longest prefix of 'input' in 'dictionary+input', beginning in 'dictionary'
   outputs the positions of its first and last 'Chord's in 'dictionary+input' */
pair<unsigned, unsigned> longest_prefix(vector<Chord> input, vector<Chord> dictionary);

/* Computes and outputs the LZ77 compression of 'input' using buffer and preview sizes 'l_buf' and 'l_pref' */
vector<tuple<unsigned, unsigned, Chord> > compress77(vector<Chord> input, unsigned l_buf, unsigned l_prev);

/* Computes and outputs the decompression of the LZ77-compressed sequence 'dico', done using parameters 'l_buf' and 'l_pref'
   prints the sequences used in the compressed dictionary */
vector<vector<Chord> > print_dictionary(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev);

/* Computes exhaustively every subsequence of 'input' and the number of times it occurs;
   outputs all sequences that occur >= than 'threshold' times, along with their number of occurences */
map<string, unsigned> allSequences(vector<Chord> input, unsigned threshold);


/* USEFUL AUXILIARY PROCEDURES */
/* Computes a 'Chord' from the string description in input file */
Chord stoC(string s);
/* Converts a queue of Chords into a vector */
vector<Chord> qtov(queue<Chord> s);
/* Attribute an unsigned integer to every 'NOTE', 'ACCIDENTAL' and 'Chord' */
unsigned Ntou(NOTE n);
unsigned Atou(ACCIDENTAL a);
unsigned Ctou(Chord c);
/* Inverse of Ntou, Atou and Ctou */
NOTE utoN(unsigned u);
ACCIDENTAL utoA(unsigned u);
Chord utoC(unsigned u);


/* OPERATOR OVERLOADINGS */
bool operator==(Chord c1, Chord c2);
bool operator!=(Chord c1, Chord c2);
ostream& operator<<(ostream &flux, Chord c);
ostream& operator<<(ostream &flux, vector<Chord> v);
ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t);
ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v);
ostream& operator<<(ostream &flux, map<string, unsigned> m);





#endif


