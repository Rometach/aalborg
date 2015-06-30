#include "analysis.hpp"
#include "similarities.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

#define METRIC 0
#define THRESHOLD 0.9
#define LBUF 10
#define LPREV 10
#define OCC_THRES 5
#define LG_THRES 2

using namespace std;


int main(int argc, char** argv)
{
    vector<vector<Chord> > chordsequences = chords_from_file("chordSequences.txt");

/*    vector<Chord> input;
    FOR(i,chordsequences.size()) {
        FOR(j,chordsequences[i].size()) {
            input.push_back(chordsequences[i][j]);
        }
    }
*/
    vector<Chord> input = chordsequences[0];

//    main_test_similarities(input);
//    return 0;

    cout << "Input chord sequence:" << endl;
    cout << input << endl;
    vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, LBUF, LPREV, METRIC, THRESHOLD);

    cout << "LZ77 compression (for buffer size = " << LBUF << " and preview size = " << LPREV << ") :" << endl;
    cout << compressed_data << endl;
    vector<vector<Chord> > x = print_dictionary_sim(compressed_data, LBUF, LPREV, cout);

    cout << "Repeated sequences:" << endl;
    vector<pair<vector<Chord>, unsigned> > complete_dictionary = allSequences_sim(input, OCC_THRES, LG_THRES, METRIC, THRESHOLD);
    cout << complete_dictionary;

    return 0;
}
