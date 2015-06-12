#include "lz77equiv.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

using namespace std;

int main(int argc, char** argv)
{
    vector<vector<Chord> > chordsequences = chords_from_file("chordSequences.txt");

    cout << chordsequences[0];

    vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77(chordsequences[0], 10, 10);
    cout << compressed_data << endl;
    vector<vector<Chord> > x = print_dictionary(compressed_data, 10, 10);

    map<string, unsigned> complete_dictionary = allSequences(chordsequences[0], 3);
    cout << complete_dictionary;

    return 0;
}
