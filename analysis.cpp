#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>

#include "analysis.hpp"
#include "similarities.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

using namespace std;


pair<unsigned, unsigned> longest_prefix_sim(vector<Chord> input, vector<Chord> dictionary, unsigned metric, double threshold) {
    int lp_begin=1, lp_end=0;
    unsigned initial_dictionary_size = dictionary.size();

    FOR(i,input.size())
        dictionary.push_back(input[i]);
    FOR(i,initial_dictionary_size) {
        FOR(j,input.size()) {
            if (!similar(dictionary[i+j],input[j], metric, threshold)) {
                break;
            } else {
                if ((int)j>(lp_end-lp_begin)) {
                    lp_begin = i;
                    lp_end = i+j;
                }
            }
        }
    }
    return make_pair(lp_begin, lp_end);
}

vector<tuple<unsigned, unsigned, Chord> > compress77_sim(vector<Chord> input, unsigned l_buf, unsigned l_prev, unsigned metric, double threshold) {
    vector<tuple<unsigned, unsigned, Chord> > output;
    queue<Chord> buffer;
    queue<Chord> preview;
    unsigned input_index = l_prev;
    Chord NC_Chord; NC_Chord.nc = true;

    FOR(i,l_buf) {
        buffer.push(NC_Chord);
    }

    FOR(i,l_prev) {
        preview.push(input[i]);
    }

    while(1) {
        pair<unsigned, unsigned> pref = longest_prefix_sim(qtov(preview), qtov(buffer), metric, threshold);
        if(pref.second < pref.first) {
            output.push_back(make_tuple(0, 0, preview.front()));
            buffer.pop();
            buffer.push(preview.front());
            preview.pop();
            if(input_index < input.size()) {
                preview.push(input[input_index]);
                input_index++;
            }
            if(preview.empty()) {
//                output.push_back(make_tuple(0, 0, NC_Chord));
                break;
            }
        } else {
            FOR(i,pref.second-pref.first+1) {
                buffer.pop();
                buffer.push(preview.front());
                preview.pop();
                if(input_index < input.size()) {
                    preview.push(input[input_index]);
                    input_index++;
                }
            }
            if(preview.empty()) {
                output.push_back(make_tuple(l_buf-pref.first, (pref.second-pref.first+1), NC_Chord));
                break;
            } else {
                output.push_back(make_tuple(l_buf-pref.first, (pref.second-pref.first+1), preview.front()));
                buffer.pop();
                buffer.push(preview.front());
                preview.pop();
                if(input_index < input.size()) {
                    preview.push(input[input_index]);
                    input_index++;
                }
                if(preview.empty()) {
                    break;
                }
            }
        }
    }

    return output;
}

vector<vector<Chord> > print_dictionary_sim(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev, ostream &flux) {
    vector<Chord> reconstruction;
    vector<vector<Chord> > res;
    unsigned res_index=-1;
    FOR(i,dico.size()) {
        tuple<unsigned, unsigned, Chord> t = dico[i];
        if((get<0>(t) == 0) || (get<1>(t) == 0)) {
            reconstruction.push_back(get<2>(t));
        } else {
            res.push_back(vector<Chord>());
            res_index++;
            FOR(j,get<1>(t)) {
                Chord c = reconstruction[reconstruction.size()-get<0>(t)];
                reconstruction.push_back(c);
                res[res_index].push_back(c);
            }
            reconstruction.push_back(get<2>(t));
        }
    }
//cout << reconstruction << endl << endl;
    FOR(i,res.size()) {
    flux << res[i]; }
    flux << endl;

    return res;
}

static bool compare_aux_occ(pair<vector<Chord>, unsigned> x, pair<vector<Chord>, unsigned> y) {
    return (x.second > y.second);
}

static void add_chords_to_table(vector<vector<Chord> > &table, vector<Chord> v) {
    bool is_present=false;
    FOR(i,table.size()) {
        if(table[i]==v) {
            is_present=true;
            break;
        }
    }
    if(!is_present) {
        table.push_back(v);
    }
}

static unsigned nb_occ(vector<Chord> input, vector<Chord> pattern) {
    unsigned res=0;
    FOR(i,input.size()-pattern.size()) {
        bool equal = true;
        FOR(j,pattern.size()) {
            if(input[i+j]!=pattern[j]) {
                equal = false;
                break;
            }
        }
        if(equal) {
            res++;
        }
    }
    return res;
}

vector<pair<vector<Chord>, unsigned> > allSequences_sim(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
    vector<pair<vector<Chord>, unsigned> > res;
    vector<vector<Chord> > res_aux;

    for (unsigned i=1; i<input.size(); i++) {   // diagonal
        bool in_sequence=false;
        unsigned begin, length=0;
        for(unsigned j=0; j<input.size()-i; j++) {
            if (similar(input[i+j], input[j], metric, threshold)) {
                if(in_sequence) {
                    length++;
                } else {
                    in_sequence=true;
                    begin=j;
                    length=1;
                }
            } else {
                if(in_sequence) {
                    vector<Chord> sequence_to_add (input.begin()+begin, input.begin()+begin+length);
                    add_chords_to_table(res_aux, sequence_to_add);
                    in_sequence = false;
                }
            }
        }
        if(in_sequence) {
            vector<Chord> sequence_to_add (input.begin()+begin, input.begin()+begin+length);
            add_chords_to_table(res_aux, sequence_to_add);
        }
    }

    FOR(i,res_aux.size()) {
        if(res_aux[i].size()>=lg_thres) {
            res.push_back(make_pair(res_aux[i],nb_occ(input,res_aux[i])));
        }
    }

    std::sort(res.begin(), res.end(), compare_aux_occ);
    FOR(i,res.size()) {
        if (res[i].second < occ_thres) {
            res.erase(res.begin()+i,res.end());
            break;
        }
    }

    return res;
}
