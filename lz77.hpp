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


Chord stoC(string s);
pair<unsigned, unsigned> longest_prefix(vector<Chord> , vector<Chord> dictionary);
vector<tuple<unsigned, unsigned, Chord> > compress77(vector<Chord> input, unsigned l_buf, unsigned l_prev);
vector<vector<Chord> > print_dictionary(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev);
map<string, unsigned> allSequences(vector<Chord> input, unsigned threshold);

bool operator==(Chord c1, Chord c2);
bool operator!=(Chord c1, Chord c2);
ostream& operator<<(ostream &flux, Chord c);
ostream& operator<<(ostream &flux, vector<Chord> v);
ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t);
ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v);
ostream& operator<<(ostream &flux, map<string, unsigned> m);


#endif



