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


pair<unsigned, unsigned> longest_prefix_sim(vector<Chord> preview, vector<Chord> buffer, unsigned metric, double threshold) {
    int lp_begin=1, lp_end=0;
    unsigned initial_dictionary_size = buffer.size();

    FOR(i,preview.size()) {
        buffer.push_back(preview[i]);
	}

    FOR(i,initial_dictionary_size) {
        FOR(j,preview.size()) {
            if (!similar(buffer[i+j], preview[j], metric, threshold)) {
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

    FOR(i,l_prev) {
        preview.push(input[i]);
    }

    while(1) {
        pair<unsigned, unsigned> pref = longest_prefix_sim(qtov(preview), qtov(buffer), metric, threshold);
        if(pref.second < pref.first) {
            output.push_back(make_tuple(0, 0, preview.front()));
			if(buffer.size()==l_buf) {
	            buffer.pop();
			}
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
                output.push_back(make_tuple(buffer.size()-pref.first, (pref.second-pref.first+1), NC_Chord));
                break;
            } else {
                output.push_back(make_tuple(buffer.size()-pref.first, (pref.second-pref.first+1), preview.front()));
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

vector<vector<Chord> > dictionary_sim(vector<tuple<unsigned, unsigned, Chord> > dico) {
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

static void add_pattern_aux(vector<Chord> sequence_to_add, vector<vector<Chord> > &patterns, unsigned metric, double threshold) {
    FOR(i,patterns.size()) {
        if (similar(patterns[i], sequence_to_add, metric, threshold)) {
            return;
        }
    }
    patterns.push_back(sequence_to_add);
}

vector<tuple<vector<Chord>, vector<unsigned> > > get_patterns_sim(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
    vector<vector<Chord> > patterns;

    // Compute all closed patterns
    for (unsigned i=1; i<=input.size(); i++) {   // diagonal
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
                    add_pattern_aux(sequence_to_add, patterns, metric, threshold);
                    in_sequence = false;
                }
            }
        }
        if(in_sequence) {
            vector<Chord> sequence_to_add (input.begin()+begin, input.begin()+begin+length);
            add_pattern_aux(sequence_to_add, patterns, metric, threshold);
        }
    }

    // Add single notes
    for (Chord c : input) {
        vector<Chord> v (1,c);
        add_pattern_aux(v, patterns, metric, threshold);
    }

    // Reduce
/*    FOR(i,patterns.size()-1) {
        for(unsigned j=i+1; j<patterns.size(); j++) {
            if(similar(patterns[i], patterns[j], metric, threshold)) {
                patterns.erase(patterns.begin()+j);
                j--;
            }
        }
    }
*/
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
/*
cout << "EXITING GET_PATTERNS_SIM" << endl;
FOR(i,res.size()) {
cout << "*** ";
    FOR(j,get<0>(res[i]).size()) {
        cout << get<0>(res[i])[j] << " ";
    }
    cout << endl;
    FOR(j,get<1>(res[i]).size()) {
        cout << get<1>(res[i])[j] << " ";
    }
    cout << endl;
}
*/
    return res;
}

static unsigned weight(tuple<vector<Chord>, vector<unsigned> > t) {
    return (get<0>(t).size()+get<1>(t).size());
}

static vector<tuple<vector<Chord>, vector<unsigned> > > compress_patterns_sim_aux_1(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > patterns, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
    vector<tuple<vector<Chord>, vector<unsigned> > > res;

    vector<unsigned> cost (patterns.size(),0);
    FOR(i,cost.size()) {
        cost[i] = weight(patterns[i]);
    }

    vector<bool> coverture (input.size(), false);
    unsigned total_covered = 0;

    while(1) {
        if(total_covered == coverture.size()) {
            break;
        }

        // Compute possible gain for every pattern
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

        // Find pattern with maximum gain
        int max_benefit=0;
        unsigned arg_max_benefit=0;
        FOR(i,patterns.size()) {
            if(((int)gain[i])-((int)cost[i]) > max_benefit) {
                max_benefit = ((int)gain[i])-((int)cost[i]);
                arg_max_benefit = i;
            }
        }
        // Add it and update coverture
        FOR(i,get<1>(patterns[arg_max_benefit]).size()) {
            FOR(j,get<0>(patterns[arg_max_benefit]).size()) {
                if(coverture[get<1>(patterns[arg_max_benefit])[i]+j] == false) {
                    total_covered++;
                    coverture[get<1>(patterns[arg_max_benefit])[i]+j] = true;
                }
            }
        }
        res.push_back(patterns[arg_max_benefit]);

        // Remove redundant occurences of other patterns
        FOR(i,patterns.size()) {
            if(i!=arg_max_benefit) {
                FOR(j,get<1>(patterns[i]).size()) {
                    bool useless = true;
                    FOR(k,get<0>(patterns[i]).size()) {
                        useless = useless && coverture[get<1>(patterns[i])[j]+k];
                    }
                    if(useless) {
                        get<1>(patterns[i])[j] = get<1>(patterns[i]).back();
                        get<1>(patterns[i]).pop_back();
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
    return weight(t1) < weight(t2);
}

static bool compare_aux_pat_occ(tuple<vector<Chord>, vector<unsigned> > t1, tuple<vector<Chord>, vector<unsigned> > t2) {
    return (get<1>(t1).size() > get<1>(t2).size());
}

//static bool compare_aux_pat_occ_inv(tuple<vector<Chord>, vector<unsigned> > t1, tuple<vector<Chord>, vector<unsigned> > t2) {
//    return (get<0>(t1).size() >= get<1>(t2).size());
//}

static vector<tuple<vector<Chord>, vector<unsigned> > > compress_patterns_sim_aux_2(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > patterns, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
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

static double loss_factor_aux(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression) {
    Chord c; c.nc = true;
    vector<Chord> reconstruction (input.size(), c);
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

static vector<tuple<vector<Chord>, vector<unsigned> > > minimize_loss(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
//    vector<tuple<vector<Chord>, vector<unsigned> > > patterns = get_patterns_sim(input, occ_thres, lg_thres, metric, threshold);
    std::sort(compression.begin(), compression.end(), compare_aux_pat_occ);

    Chord c; c.nc = true;
    vector<tuple<Chord, unsigned> > reconstruction (input.size(), tuple<Chord,unsigned> (c, 0));
    FOR(i,compression.size()) {
        FOR(j,get<1>(compression[i]).size()) {
            FOR(k,get<0>(compression[i]).size()) {
                reconstruction[get<1>(compression[i])[j]+k] = make_tuple(get<0>(compression[i])[k],i);
            }
        }
    }

    unsigned exact=0;
    FOR(i,input.size()) {
        if(get<0>(reconstruction[i]) == input[i]) {
            exact++;
        }
    }

    vector<tuple<vector<Chord>, vector<unsigned> > > compression_aux = compression;
    FOR(i,compression.size()) {
        FOR(j,get<1>(compression[i]).size()) {
            int dif=0;
            FOR(k,get<0>(compression[i]).size()) {
                if (get<1>(reconstruction[get<1>(compression[i])[j]+k]) == i) {
                    if(get<0>(reconstruction[get<1>(compression[i])[j]+k]) == input[i]) {
                        dif--;
                    }
                    if(get<0>(reconstruction[get<1>(compression[i])[j]+k]) == get<0>(compression[i])[k]) {
                        dif++;
                    }
                }
            }
            if(dif > 0) {
                FOR(k,get<0>(compression[i]).size()) {
                    get<0>(compression[i])[k] = input[get<1>(compression[i])[j]+k];
                }
            }
        }
    }

    return compression;
}

vector<tuple<vector<Chord>, vector<unsigned> > > compress_patterns_sim(vector<Chord> input, unsigned occ_thres, unsigned lg_thres, unsigned metric, double threshold) {
    vector<tuple<vector<Chord>, vector<unsigned> > > patterns = get_patterns_sim(input, occ_thres, lg_thres, metric, threshold);
    vector<tuple<vector<Chord>, vector<unsigned> > > v1 = compress_patterns_sim_aux_1(input, patterns, occ_thres, lg_thres, metric, threshold);
    vector<tuple<vector<Chord>, vector<unsigned> > > v2 = compress_patterns_sim_aux_2(input, patterns, occ_thres, lg_thres, metric, threshold);
    v1 = minimize_loss(input, v1, occ_thres, lg_thres, metric, threshold);
    v2 = minimize_loss(input, v2, occ_thres, lg_thres, metric, threshold);
    return (compression_factor(input, v1) > compression_factor(input, v2)) ? v1 : v2;
}

double compression_factor(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression) {
    unsigned res_aux=0;
    FOR(i,compression.size()) {
        res_aux += weight(compression[i]);
    }

    return ((double)input.size())/((double)res_aux);
}

double loss_factor(vector<Chord> input, vector<tuple<vector<Chord>, vector<unsigned> > > compression) {
    return loss_factor_aux(input, compression);
}

//static unsigned median(vector<unsigned> v) {
//    std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
//    return v[v.size()/2];
//}

void main_compression(vector<vector<Chord> > chordsequences) {
    vector<double> thresholds = {0,0.85,0,0,2,0.4,0.5,15,0.5,0};
    vector<double> mean (chordsequences.size(), 0);
    FOR(i,10) {
        cout << "MEASURE " << i << endl;
        FOR(j, chordsequences.size()) {
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

void main_LZ77(vector<vector<Chord> > chordsequences, unsigned l_buf, unsigned l_prev, unsigned occ_thres, unsigned lg_thres, unsigned metric, double thres) {
    cout << "Computing the LZ77 compressions" << endl;
    FOR(i,chordsequences.size()) {
        if(i != 3) {
            vector<Chord> input = chordsequences[i];
            while(input[0].nc == true)
                input.erase(input.begin());
            string filename = "draws/"+to_string(i)+"/LZ77.txt";
            ofstream print_file(filename.c_str());

            print_file << "Input chord sequence:" << endl;
            print_file << input << endl;
            vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, l_buf, l_prev, metric, thres);

            print_file << "LZ77 compression of size " << compressed_data.size();
            print_file << " (compression factor: " << (((double)input.size())/((double)compressed_data.size()*3)) << ") :" << endl;
            print_file << compressed_data << endl;
            vector<vector<Chord> > patterns = dictionary_sim(compressed_data);
            print_file << "Patterns:" << endl;
            print_dictionary_sim(patterns, occ_thres, lg_thres, print_file);

            print_file.close();

            cout << "Piece " << i << ": compression factor " << (((double)input.size())/((double)compressed_data.size()*3)) << endl;
        }
    }
}

void main_segmentation(vector<vector<Chord> > chordsequences) {
    for(vector<Chord> v : chordsequences) {
        segmentation(v, cout);
        cout << endl << endl;
    }
}

void main_plot_compression(vector<Chord> input) {
    // F1-distance
    ofstream file_f1("plots/F1.dat");
    file_f1 << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.05) {
        cout << "F1 : " << thres << endl;
        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, 0, 0, 1, thres);
        file_f1 << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
cout << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
    }
    file_f1.close();

    // Morris
    ofstream file_morris("plots/Morris.dat");
    file_morris << "# Threshold\tCompression\tRecovery" << endl;
    for(unsigned thres=1; thres<=20; thres+=1) {
        cout << "Morris : " << thres << endl;
        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, 0, 0, 4, thres);
        file_morris << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
cout << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
    }
    file_morris.close();

    // Rahn
    ofstream file_rahn("plots/Rahn.dat");
    file_rahn << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "Rahn : " << thres << endl;
        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, 0, 0, 5, thres);
        file_rahn << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
cout << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
    }
    file_rahn.close();

    // Lewin
    ofstream file_lewin("plots/Lewin.dat");
    file_lewin << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "Lewin : " << thres << endl;
        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, 0, 0, 6, thres);
        file_lewin << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
cout << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
    }
    file_lewin.close();

    // Teitelbaum
    ofstream file_teitelbaum("plots/Teitelbaum.dat");
    file_teitelbaum << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=10; thres+=0.025) {
        cout << "Teitelbaum : " << thres << endl;
        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, 0, 0, 7, thres);
        file_teitelbaum << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
cout << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
    }
    file_teitelbaum.close();

    // Isaacson
    ofstream file_isaacson("plots/Isaacson.dat");
    file_isaacson << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "Isaacson : " << thres << endl;
        vector<tuple<vector<Chord>, vector<unsigned> > > total_compression = compress_patterns_sim(input, 0, 0, 8, thres);
        file_isaacson << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
cout << thres << '\t' << compression_factor(input, total_compression) << '\t' << loss_factor(input, total_compression) << endl;
    }
    file_isaacson.close();
}


void main_plot_lz77(vector<Chord> input) {
    // F1-distance
    ofstream file_f1("plots/F1.dat");
    file_f1 << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "F1 : " << thres << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, 1469, 1469, 1, thres);
        file_f1 << thres << '\t' << (((double)input.size())/((double)compressed_data.size()*3)) << '\t' << loss_factor_lz77(input, compressed_data) << endl;
    }
    file_f1.close();

    // Morris
    ofstream file_morris("plots/Morris.dat");
    file_morris << "# Threshold\tCompression\tRecovery" << endl;
    for(unsigned thres=1; thres<=20; thres++) {
        cout << "Morris : " << thres << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, 1469, 1469, 4, thres);
        file_morris << thres << '\t' << (((double)input.size())/((double)compressed_data.size()*3)) << '\t' << loss_factor_lz77(input, compressed_data) << endl;
    }
    file_morris.close();

    // Rahn
    ofstream file_rahn("plots/Rahn.dat");
    file_rahn << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "Rahn : " << thres << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, 1469, 1469, 5, thres);
        file_rahn << thres << '\t' << (((double)input.size())/((double)compressed_data.size()*3)) << '\t' << loss_factor_lz77(input, compressed_data) << endl;
    }
    file_rahn.close();

    // Lewin
    ofstream file_lewin("plots/Lewin.dat");
    file_lewin << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "Lewin : " << thres << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, 1469, 1469, 6, thres);
        file_lewin << thres << '\t' << (((double)input.size())/((double)compressed_data.size()*3)) << '\t' << loss_factor_lz77(input, compressed_data) << endl;
    }
    file_lewin.close();

    // Teitelbaum
    ofstream file_teitelbaum("plots/Teitelbaum.dat");
    file_teitelbaum << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.05; thres<=20; thres+=0.5) {
        cout << "Teitelbaum : " << thres << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, 1469, 1469, 7, thres);
        file_teitelbaum << thres << '\t' << (((double)input.size())/((double)compressed_data.size()*3)) << '\t' << loss_factor_lz77(input, compressed_data) << endl;
    }
    file_teitelbaum.close();

    // Isaacson
    ofstream file_isaacson("plots/Isaacson.dat");
    file_isaacson << "# Threshold\tCompression\tRecovery" << endl;
    for(double thres=0.025; thres<=1; thres+=0.025) {
        cout << "Isaacson : " << thres << endl;
        vector<tuple<unsigned, unsigned, Chord> > compressed_data = compress77_sim(input, 1469, 1469, 8, thres);
        file_isaacson << thres << '\t' << (((double)input.size())/((double)compressed_data.size()*3)) << '\t' << loss_factor_lz77(input, compressed_data) << endl;
    }
    file_isaacson.close();
}

double loss_factor_lz77(vector<Chord> input, vector<tuple<unsigned, unsigned, Chord> > compression) {
    vector<Chord> reconstruction;
    FOR(i,compression.size()) {
        tuple<unsigned, unsigned, Chord> t = compression[i];
        if((get<0>(t) == 0) || (get<1>(t) == 0)) {
            reconstruction.push_back(get<2>(t));
        } else {
            FOR(j,get<1>(t)) {
                Chord c = reconstruction[reconstruction.size()-get<0>(t)];
                reconstruction.push_back(c);
            }
            reconstruction.push_back(get<2>(t));
        }
    }
	double exact=0;
	FOR(i,input.size()) {
		if(input[i]==reconstruction[i]) {
			exact++;
		}
	}
	return (exact/((double)input.size()));
}

