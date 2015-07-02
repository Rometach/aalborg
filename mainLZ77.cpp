#include "analysis.hpp"
#include "similarities.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

#define METRIC 0
#define THRESHOLD 0.9
#define LBUF 1469
#define LPREV 1469
#define OCC_THRES 2
#define LG_THRES 2

using namespace std;


int main(int argc, char** argv)
{
    vector<vector<Chord> > chordsequences = chords_from_file("chordSequences.txt");

    vector<Chord> input;
    FOR(i,chordsequences.size()) {
        FOR(j,chordsequences[i].size()) {
            input.push_back(chordsequences[i][j]);
        }
    }

//    vector<Chord> input = chordsequences[0];

//    main_test_similarities(input);
//    return 0;

    cout << "Input chord sequence:" << endl;
    cout << input << endl;
    vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, LBUF, LPREV, METRIC, THRESHOLD);

    cout << "LZ77 compression of size " << compressed_data.size();
    cout << "(compression factor: " << (((double)input.size())/((double)compressed_data.size())) << ") :" << endl;
//    cout << " (for buffer size = " << LBUF << " and preview size = " << LPREV << ") :" << endl;
    cout << compressed_data << endl;
    vector<vector<Chord> > patterns = dictionary_sim(compressed_data, LBUF, LPREV);
    cout << "Patterns:" << endl;
    print_dictionary_sim(patterns, OCC_THRES, LG_THRES, cout);

//    cout << "Repeated sequences:" << endl;
//    vector<pair<vector<Chord>, unsigned> > complete_dictionary = allSequences_sim(input, OCC_THRES, LG_THRES, METRIC, THRESHOLD);
//    cout << complete_dictionary;

    return 0;
}
