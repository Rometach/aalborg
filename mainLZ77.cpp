#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

using namespace std;

int main(int argc, char** argv)
{
    ifstream data("chordSequences.txt");
    vector<vector<Chord> > chordsequences;
    unsigned csindex=-1;

    string next_chord;
    while(getline(data,next_chord)) {
        if(next_chord[0] == '@') {
            break;
        } else if (next_chord[0] == '=') {
            chordsequences.push_back(vector<Chord> ());
            csindex++;
        } else {
            chordsequences[csindex].push_back(stoC(next_chord));
        }
    }

    cout << chordsequences[0];
    vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77(chordsequences[0], 10, 10);
    cout << compressed_data << endl;
    vector<vector<Chord> > x = print_dictionary(compressed_data, 10, 10);
    map<string, unsigned> complete_dictionary = allSequences(chordsequences[0], 3);
    cout << complete_dictionary;

    return 0;
}
