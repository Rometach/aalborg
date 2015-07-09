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

    if(l_buf > input.size())
        l_buf = input.size();
    if(l_prev > input.size())
        l_prev = input.size();

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

vector<vector<Chord> > dictionary_sim(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev) {
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
    return res;
}

static bool sort_aux_patterns(vector<Chord> v1, vector<Chord> v2) {
    if(v1.size()==v2.size()) {
        FOR(i,v1.size()) {
            if(v1[i].nc == true) {
                if(v2[i].nc == false) {
                    return true;
                }
            } else if(v2[i].nc == true) {
                return false;
            } else {
                if (Ntou(v1[i].n)<Ntou(v2[i].n)) {
                    return true;
                } else if (Atou(v1[i].a)<Atou(v2[i].a)) {
                    return true;
                } else if (v1[i].h<v2[i].h) {
                    return true;
                }
            }
        }
        return false;
    } else {
        return (v1.size()>v2.size());
    }
}

void print_dictionary_sim(vector<vector<Chord> > patterns, unsigned occ_thres, unsigned lg_thres, ostream &flux) {
    std::sort(patterns.begin(), patterns.end(), sort_aux_patterns);
    vector<tuple<vector<Chord>,unsigned> > patterns_occ;

    FOR(i,patterns.size()) {
        unsigned count=0;
        for(unsigned j=i; j<patterns.size(); j++) {
            if(patterns[j]==patterns[i]) {
                count++;
            } else {
                i=j-1;
                patterns_occ.push_back(make_tuple(patterns[i],count));
                break;
            }
        }
    }

    FOR(i,patterns_occ.size()) {
        if(get<0>(patterns_occ[i]).size() < lg_thres) {
            break;
        }
        if(get<1>(patterns_occ[i]) >= occ_thres) {
            FOR(j,get<0>(patterns_occ[i]).size()) {
                flux << get<0>(patterns_occ[i])[j];
            }
            flux << " : " << get<1>(patterns_occ[i]) << endl;
        }
    }
    flux << endl;
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

vector<tuple<vector<Chord>, vector<unsigned> > > get_patterns_sim(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
    vector<vector<Chord> > patterns;
cout << "aaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
    // Compute all closed patterns
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
                    patterns.push_back(sequence_to_add);
                    in_sequence = false;
                }
            }
        }
        if(in_sequence) {
            vector<Chord> sequence_to_add (input.begin()+begin, input.begin()+begin+length);
            patterns.push_back(sequence_to_add);
        }
    }

    // Add single notes
    for (Chord c : input) {
        vector<Chord> v (1,c);
        patterns.push_back(v);
    }
cout << "bbbbbbbbbbbbbbbbbbb" << endl;
    // Reduce
    FOR(i,patterns.size()-1) {
        for(unsigned j=i+1; j<patterns.size(); j++) {
            if(similar(patterns[i], patterns[j], metric, threshold)) {
                patterns.erase(patterns.begin()+j);
                j--;
            }
        }
    }
cout << "ccccccccccccccc" << endl;
    // Compute the positions
    vector<tuple<vector<Chord>, vector<unsigned> > > res;
    FOR(i,patterns.size()) {
        vector<unsigned> positions;
        FOR(j,input.size()-patterns[i].size()+1) {
            vector<Chord> sequence_to_compare(input.begin()+j, input.begin()+j+patterns[i].size()); // -1 ?
            if(similar(sequence_to_compare, patterns[i], metric, threshold)) {
                positions.push_back(j);
            }
        }
        res.push_back(make_tuple(patterns[i],positions));
    }
cout << "ddddddddddddddddddddddddd" << endl;
    return res;
}

static unsigned weight(tuple<vector<Chord>, vector<unsigned> > t) {
    return (get<0>(t).size()+get<1>(t).size());
}

static vector<tuple<vector<Chord>, vector<unsigned> > > compress_patterns_sim_aux_1(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
cout << "Bonjour !" << endl;
    vector<tuple<vector<Chord>, vector<unsigned> > > res;
    vector<tuple<vector<Chord>, vector<unsigned> > > patterns = get_patterns_sim(input, occ_thres, lg_thres, metric, threshold);
    vector<unsigned> cost (patterns.size(),0);
    FOR(i,cost.size()) {
        cost[i] = weight(patterns[i]);
    }
cout << "::::" << endl;
    unsigned size = 0;
    FOR(i, patterns.size()) {
        if((get<0>(patterns[i]).size()+get<1>(patterns[i])[get<1>(patterns[i]).size()-1]) > size) {
            size = get<0>(patterns[i]).size()+get<1>(patterns[i])[get<1>(patterns[i]).size()-1];
        }
    }
    vector<bool> coverture (size, false);
    unsigned total_covered = 0;
cout << "Au revoir !" << endl;
    while(1) {
        if(total_covered == coverture.size()) {
            break;
        }

        vector<unsigned> gain (patterns.size(),0);
        FOR(i,gain.size()) {
            vector<bool> coverture_aux = coverture;
            FOR(j,get<1>(patterns[i]).size()) {
                FOR(k,get<0>(patterns[i]).size()) {
                    coverture_aux[get<1>(patterns[i])[j]+k] = true;
                }
            }
            FOR(j, coverture_aux.size()) {
                gain[i] += coverture_aux[j] ? 1 : 0;
            }
            gain[i] -= total_covered;
        }

        int max_benefit=0;
        unsigned arg_max_benefit=0;
        FOR(i,patterns.size()) {
            if(((int)gain[i])-((int)cost[i]) > max_benefit) {
                max_benefit = ((int)gain[i])-((int)cost[i]);
                arg_max_benefit = i;
            }
        }
        FOR(i,get<1>(patterns[arg_max_benefit]).size()) {
            FOR(j,get<0>(patterns[arg_max_benefit]).size()) {
                if(coverture[get<1>(patterns[arg_max_benefit])[i]+j] == false) {
                    total_covered++;
                    coverture[get<1>(patterns[arg_max_benefit])[i]+j] = true;
                }
            }
        }
        res.push_back(patterns[arg_max_benefit]);

        FOR(i,patterns.size()) {
            if(i!=arg_max_benefit) {
                FOR(j,get<1>(patterns[i]).size()) {
                    bool useless = true;
                    FOR(k,get<0>(patterns[i]).size()) {
                        useless = useless && coverture[get<1>(patterns[i])[j]+k];
                    }
                    if(useless) {
                        get<1>(patterns[i]).erase(get<1>(patterns[i]).begin()+j);
                        j--;
                    }
                }
                cost[i] = weight(patterns[i]);
                if(get<1>(patterns[i]).size()==0) {
                    patterns.erase(patterns.begin()+i);
                    cost.erase(cost.begin()+i);
                    if(i < arg_max_benefit) {
                        arg_max_benefit--;
                    }
                    i--;
                }
            }
        }

        patterns.erase(patterns.begin()+arg_max_benefit);
        cost.erase(cost.begin()+arg_max_benefit);
    }

    return res;
}

static bool compare_aux_pat(tuple<vector<Chord>, vector<unsigned> > t1, tuple<vector<Chord>, vector<unsigned> > t2) {
    return weight(t1) > weight(t2);
}

static vector<tuple<vector<Chord>, vector<unsigned> > > compress_patterns_sim_aux_2(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
    vector<tuple<vector<Chord>, vector<unsigned> > > patterns = get_patterns_sim(input, occ_thres, lg_thres, metric, threshold);
    vector<unsigned> coverture (input.size(), 0);
    FOR(i, patterns.size()) {
        FOR(j, get<1>(patterns[i]).size()) {
            FOR(k, get<0>(patterns[i]).size()) {
                coverture[get<1>(patterns[i])[j]+k]++;
            }
        }
    }

    while(1) {
        std::sort(patterns.begin(), patterns.end(), compare_aux_pat);
        bool finished = true;
        FOR(i,patterns.size()) {
            FOR(j,get<1>(patterns[i]).size()) {
                bool useless = true;
                FOR(k,get<0>(patterns[i]).size()) {
                    if(coverture[get<1>(patterns[i])[j]+k] == 1) {
                        useless = false;
                    }
                }
                if(useless) {
                    FOR(k,get<0>(patterns[i]).size()) {
                        coverture[get<1>(patterns[i])[j]+k]--;
                    }
                    get<1>(patterns[i]).erase(get<1>(patterns[i]).begin()+j);
                    j--;
                    finished = false;
                }
            }
            if (get<1>(patterns[i]).size() == 0) {
                patterns.erase(patterns.begin()+i);
                i--;
            }
        }
        if (finished) {
            return patterns;
        }
    }
}

vector<tuple<vector<Chord>, vector<unsigned> > > compress_patterns_sim(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
cout << "1111111111" << endl;
    vector<tuple<vector<Chord>, vector<unsigned> > > v1 = compress_patterns_sim_aux_1(input, occ_thres, lg_thres, metric, threshold);
cout << "2222222222" << endl;
    vector<tuple<vector<Chord>, vector<unsigned> > > v2 = compress_patterns_sim_aux_2(input, occ_thres, lg_thres, metric, threshold);
cout << "3333333333" << endl;
    return (compression_factor(input, v1) > compression_factor(input, v2)) ? v1 : v2;
}

double compression_factor(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression) {
    unsigned res_aux=0;
    FOR(i,compression.size()) {
        res_aux += weight(compression[i]);
    }

    return ((double)input.size())/((double)res_aux);
}

static bool compare_aux_pat_occ(tuple<vector<Chord>, vector<unsigned> > t1, tuple<vector<Chord>, vector<unsigned> > t2) {
    return (get<0>(t1).size() > get<1>(t2).size());
}

static bool compare_aux_pat_occ_inv(tuple<vector<Chord>, vector<unsigned> > t1, tuple<vector<Chord>, vector<unsigned> > t2) {
    return (get<0>(t1).size() >= get<1>(t2).size());
}

double loss_factor_aux(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression) {
    Chord c; c.nc = true;
    vector<Chord> reconstruction (input.size(), c);
    std::sort(compression.begin(), compression.end(), compare_aux_pat_occ);
    FOR(i,compression.size()) {
        FOR(j,get<1>(compression[i]).size()) {
            FOR(k,get<0>(compression[i]).size()) {
                reconstruction[get<1>(compression[i])[j]+k] = get<0>(compression[i])[k];
            }
        }
    }

    unsigned exact=0;
    FOR(i,input.size()) {
        if(reconstruction[i] == input[i]) {
            exact++;
        }
    }

    return (((double)exact)/((double)input.size()));
}

double loss_factor(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression) {
    std::sort(compression.begin(), compression.end(), compare_aux_pat_occ_inv);
    vector<tuple<vector<Chord>, vector<unsigned> > > compression_aux = compression;
    FOR(i,compression.size()) {
        FOR(j,get<1>(compression[i]).size()) {
            FOR(k,get<0>(compression[i]).size()) {
                get<0>(compression_aux[i])[k] = input[get<1>(compression[i])[j]+k];
            }
            if(loss_factor_aux(input, compression_aux) < loss_factor_aux(input, compression)) {
                compression = compression_aux;
            } else {
                compression_aux = compression;
            }
        }
    }

    return loss_factor_aux(input, compression);
}

//static unsigned median(vector<unsigned> v) {
//    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
//    return v[v.size()/2];
//}

void main_compression(vector<vector<Chord> > chordsequences) {
    vector<double> thresholds = {0,0.85,0,0,2,0.4,0.5,0,0.5,0};
    vector<double> mean (chordsequences.size(), 0);
    FOR(i,10) {
        cout << "MEASURE " << i << endl;
        if(i==7) {
            continue;
        }
        FOR(j, chordsequences.size()) {
//if(j==16) {
    cout << endl << endl << endl << chordsequences[j] << endl;
//}
            vector<tuple<vector<Chord>, vector<unsigned> > > compression = compress_patterns_sim(chordsequences[j], 0, 0, i, thresholds[i]);
            cout << "Piece " << j << ": " << compression_factor(chordsequences[j], compression) << endl;
            FOR(k, compression.size()) {
                cout << '\t';
                FOR(l, get<0>(compression[k]).size()) {
                    cout << get<0>(compression[k])[l] << " ";
                }
                cout << " : ";
                FOR(l, get<1>(compression[k]).size()) {
                    cout << get<1>(compression[k])[l] << " ";
                }
                cout << endl;
            }
            mean[i] += compression_factor(chordsequences[j], compression);
        }
        cout << endl;
    }
    cout << endl;
    FOR(i,10) {
        cout << "Mean " << i << ": " << (mean[i]/chordsequences.size()) << endl;
    }
}

static double mean(vector<unsigned> v) {
    double res=0;
    FOR(i,v.size()) {
        res += v[i];
    }
    return (res/((double)v.size()));
}

void segmentation(vector<Chord> input, ostream& flux) {
    vector<unsigned> scores (input.size(), 0);

    set<pair<unsigned,double> > measures;
    measures.insert(make_pair(1,0.8));      // F1
    measures.insert(make_pair(8,0.5));      // Isaacson
    measures.insert(make_pair(4,3));        // Morris

    for(auto p : measures) {
        vector<unsigned> score_aux(input.size(),0);
        FOR(i,input.size()) {
            FOR(j,input.size()) {
                score_aux[i] += similar(input[i], input[j], p.first, p.second) ? 1 : 0;
            }
        }
        double mean_aux = mean(score_aux);
        FOR(i,score_aux.size()) {
            scores[i] += (score_aux[i] < mean_aux) ? 1 : 0;
        }
    }

    measures.clear();
    measures.insert(make_pair(6,0.5));      // Lewin
    measures.insert(make_pair(5,0.4));      // Rahn

    for(auto p : measures) {
        vector<unsigned> score_aux(input.size(),0);
        FOR(i,input.size()) {
            FOR(j,input.size()) {
                score_aux[i] += similar(input[i], input[j], p.first, p.second) ? 1 : 0;
            }
        }
        double mean_aux = mean(score_aux);
        FOR(i,score_aux.size()) {
            scores[i] += (score_aux[i] > mean_aux) ? 1 : 0;
        }
    }

    FOR(i,scores.size()) {
        if(scores[i] >= 3) {
            flux << "[" << input[i] << "] ";
        } else {
            flux << input[i] << " ";
        }
    }
}


