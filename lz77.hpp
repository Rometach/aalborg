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

struct Chord {
    bool nc;
    NOTE n;
    ACCIDENTAL a;
    HARM h;
};
typedef struct Chord Chord;


/* This file contains basic functions to handle the 'Chord' structure (especially in-out functions)*/


/* USEFUL AUXILIARY PROCEDURES */
/* Reads and stores the 'Chord' sequences described in data_file */
vector<vector<Chord> > chords_from_file(string filename);
/* Computes a 'Chord' from the string description in input file */
Chord stoC(string s);
/* Converts a queue of Chords into a vector */
vector<Chord> qtov(queue<Chord> s);
/* Attribute an unsigned integer to every 'NOTE', 'ACCIDENTAL' and 'Chord' */
unsigned Ntou(NOTE n);
unsigned Atou(ACCIDENTAL a);
unsigned Ctou(Chord c);
/* Inverses of Ntou, Atou and Ctou */
NOTE utoN(unsigned u);
ACCIDENTAL utoA(unsigned u);
Chord utoC(unsigned u);


/* OPERATOR OVERLOADINGS */
bool operator==(Chord c1, Chord c2);
bool operator!=(Chord c1, Chord c2);
bool operator==(vector<Chord> v1, vector<Chord> v2);
ostream& operator<<(ostream &flux, Chord c);
ostream& operator<<(ostream &flux, vector<Chord> v);
ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t);
ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v);
ostream& operator<<(ostream &flux, map<string, unsigned> m);
ostream& operator<<(ostream &flux, vector<pair<vector<Chord>, unsigned> > v);

#endif


