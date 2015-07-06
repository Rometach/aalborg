#include "analysis.hpp"
#include "similarities.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

#define METRIC 0
#define THRESHOLD 0.9
#define LBUF 100 //1469
#define LPREV 100 //1469
#define OCC_THRES 0
#define LG_THRES 0

using namespace std;


int main(int argc, char** argv)
{
    vector<vector<Chord> > chordsequences = chords_from_file("chordSequences.txt");
/*
    vector<Chord> input;
    FOR(i,chordsequences.size()) {
        FOR(j,chordsequences[i].size()) {
            input.push_back(chordsequences[i][j]);
        }
    }
*/
//    vector<Chord> input = chordsequences[0];

//    main_test_similarities(input);

//    return 0;

//    set<unsigned> pieces = {0, 1, 2, 4, 6, 8, 9, 11, 12, 13, 15, 17, 19, 20, 21, 22, 23, 25, 28};
//    for(auto i : pieces) {
        FOR(i,chordsequences.size()) {
            if(i != 3) {
            vector<Chord> input = chordsequences[i];
            while(input[0].nc == true)
                input.erase(input.begin());
            string filename = "draws/"+to_string(i)+"/LZ77.txt";
            ofstream print_file(filename.c_str());

            print_file << "Input chord sequence:" << endl;
            print_file << input << endl;
            vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, LBUF, LPREV, METRIC, THRESHOLD);

            print_file << "LZ77 compression of size " << compressed_data.size();
            print_file << " (compression factor: " << (((double)input.size())/((double)compressed_data.size())) << ") :" << endl;
        //    cout << " (for buffer size = " << LBUF << " and preview size = " << LPREV << ") :" << endl;
            print_file << compressed_data << endl;
            vector<vector<Chord> > patterns = dictionary_sim(compressed_data, LBUF, LPREV);
            print_file << "Patterns:" << endl;
            print_dictionary_sim(patterns, OCC_THRES, LG_THRES, print_file);

            print_file.close();
        }
    }
//    cout << "Repeated sequences:" << endl;
//    vector<pair<vector<Chord>, unsigned> > complete_dictionary = allSequences_sim(input, OCC_THRES, LG_THRES, METRIC, THRESHOLD);
//    cout << complete_dictionary;

    return 0;
}
