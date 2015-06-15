#include "lz77equiv.hpp"
#include "lz77similar.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

#define METRIC 0
#define THRESHOLD 0.9

using namespace std;



ostream& operator<<(ostream &flux, vector<pair<vector<Chord>, unsigned> > v) {
    FOR(i,v.size()) {
        FOR(j,v[i].first.size()) {
            flux << v[i].first[j] << " ";
        }
        flux << ": " << v[i].second << endl;
    }
    return flux;
}



int main(int argc, char** argv)
{
    vector<vector<Chord> > chordsequences = chords_from_file("chordSequences.txt");

    cout << chordsequences[0];
    vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(chordsequences[0], 10, 10, METRIC, THRESHOLD);

    cout << compressed_data << endl;
    vector<vector<Chord> > x = print_dictionary_sim(compressed_data, 10, 10);

    vector<pair<vector<Chord>, unsigned> > complete_dictionary = allSequences_sim(chordsequences[0], 0, METRIC, THRESHOLD);
    cout << complete_dictionary;

    return 0;
}
