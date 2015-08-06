#include "analysis.hpp"
#include "similarities.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

#define METRIC 0
#define THRESHOLD 0.9
#define LBUF 1469
#define LPREV 1469
#define OCC_THRES 0
#define LG_THRES 0

using namespace std;

int main(int argc, char** argv)
{
    vector<vector<Chord> > chordsequences = chords_from_file("chordSequences.txt");
    nc_reduce(chordsequences);

    vector<Chord> input;
    FOR(i,chordsequences.size()) {
        FOR(j,chordsequences[i].size()) {
            input.push_back(chordsequences[i][j]);
        }
    }

//    vector<Chord> input = chordsequences[0];

    main_plot_compression(input);
    return 0;

//    main_compression(chordsequences);
    cout << "Overall compression" << endl;
    vector<double> thresholds = {0,0.85,0,0,2,0.8,0.8,15,0.5,0};

    FOR(i,10) {
        cout << "Measure " << i << " (threshold " << thresholds[i] << ")" << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, LBUF, LPREV, i, thresholds[i]);
        cout << "Compression factor: " << (((double)input.size())/((double)compressed_data.size()*3)) << endl << endl;
        continue;

        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, OCC_THRES, LG_THRES, i, thresholds[i]);
        cout << "Compression factor: " << compression_factor(input, total_compression) << endl;
        cout << "Loss factor: " << loss_factor(input, total_compression) << endl << endl;
    }

//    main_LZ77(chordsequences, LBUF, LPREV, OCC_THRES, LG_THRES, METRIC, THRESHOLD);
    vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, LBUF, LPREV, METRIC, THRESHOLD);
    cout << "Overall LZ77 compression" << endl;
    cout << "Compression factor: " << (((double)input.size())/((double)compressed_data.size()*3)) << endl;

//    main_segmentation(chordsequences)

    return 0;
}

