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

#include "similarities.hpp"
#include "lz77.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

using namespace std;


set<unsigned> PCS_table[313] = {{0,4,7}, {0,4,7,10,2,6}, {0,4,6,9}, {0,3,6,11,5}, {0,3,7,11,2,6}, {0,7,9}, {0,3,6,5}, {10,0,4,7}, {0,4,7,11,2,6}, {0,4,6,11,3}, {0,4,6,10,1,3}, {0,3,6,10}, {0,4,7,10,1,6,8}, {0,4,7,10,1,3}, {0,4,6,10,1}, {0,3,7,1,5}, {0,4,7,10}, {0,3,6,9,5}, {0,4,6,10,3}, {0,7,11,6}, {0,4,9,2}, {0,7,10,1}, {0,4,8}, {0,4}, {0,7}, {0,4,7,10,2,9}, {0,7}, {0}, {0,2,4,6,8,10}, {0,3,7,10,2,6}, {0,2,4,7}, {0,4,7,10}, {0,4,7,9}, {0,7}, {0,3,7,11,5}, {0,3,7,10,8}, {0,4,7,3}, {0,4,7,10,2}, {0,3,7,5}, {0,4,7,2}, {0,4,7,10,2,5,9}, {0,5,6,10}, {0,4,6,10,1}, {0,3,6,9,2}, {0,3,7,8}, {0,3,6}, {0,4,7}, {0,3,7,11,2,6}, {0,5,7,10,2}, {0,4,7,10,2,6,9}, {0,4,7,9,3}, {0,4,7,10,2,5}, {0,4,11}, {0,4,7,10,2,6}, {0,4,7,10,2,6,8}, {0,3,7,10,2,9}, {0,4,7,10,1,8}, {0,3,7,2}, {0,4,7,10,2,6,9}, {0,4,8,2}, {0,4,6,2}, {0,5,7,1}, {0,4,7,10,3}, {0,3,7}, {0,3}, {0,4,6,7,10}, {0,4,7,10}, {0,4,8,10}, {0,5,7,2}, {0,3,6,10,2,8}, {0,4,8,10,2}, {0,4,8,10,1}, {0,4,7,8}, {0,4,7,10,1,3}, {0,4,5,10}, {0,4,8,10,3}, {0,4,7,1}, {0,4,10,3}, {0,4,6,10,3,6,9}, {0,3,9}, {0,3,7,11,2}, {0,4,5,7,11}, {0,4,7,3,6}, {0,5,8,10,2,6}, {0,5,6}, {0,5,7,10,9}, {0,4,6,10}, {0,4,7,8,10}, {0,4,7,11,3,6}, {0,5,7,1}, {0,3,7,10,2,6,9}, {0,4,7,9,11}, {0,4,7,10,1}, {0,4,7,9,2}, {0,5,7,9}, {0,3,6,9}, {0,4,8,3}, {0,4,7,10,6}, {0,5,7,10,1}, {0,3,7,10,1}, {0,4,8,10,3}, {0,4,7,11,8}, {0,5,7,11,2}, {0,4,7,11,6}, {0,3,6,10}, {0,4,5,7,10,1}, {0,5,7,9}, {0,4,7,11,2,6}, {0,3,5,7}, {0,3,7,10,2,8}, {0,3,7,10,2,5}, {0,4,7,2}, {0,5,7}, {0,3,6,10,5}, {0,4,6,11,2,9}, {0,4,7,10,1,9}, {0,4,7,1}, {0,3,7,10,8}, {0,5,7}, {0,4,7,6}, {0,4,8,10,3}, {0,3,9,10}, {0,5,7,1}, {0,4,7,10,2,6}, {0,3,6,11,2}, {0,4,7,11,2,6}, {0,4,7,6}, {0,3,7,11,2,5}, {0,3,6,11,2}, {0,4,8,10,3}, {0,3,7,9,2,5}, {0,4,7,11,2,9}, {0,5,7,10,2,9}, {0,3,7,11,2}, {0,3,6,10,9}, {0,3,7,8,10,2}, {0,4,8,10,3}, {0,5,7,2}, {0,3,8,10,5}, {0,5,7,10,1,6}, {0,3,7,9,2,6}, {0,4,8,11,2}, {0,4,7,11,2,6,9}, {0,4,7,8,11}, {0,4,7,11}, {0,4,6,11}, {0,3,7,9,11,2}, {0,3,8,10}, {0,4,7,11,2}, {0,4,6,8}, {0,4,7,10,3,5}, {0,4,7,11,2}, {0,4,7,11,3}, {0,4,8}, {0,3,7,10,2}, {0,3,7,1}, {0,3,7,2}, {0,5,10}, {0,3,6,9,2}, {0,3,6,9}, {0,7,10,2,6,9}, {0,3,7,9,5}, {0,4,7,9,11,2}, {0,4,7,9,2,6}, {0,3,7,9,2}, {0,4,6,10,3}, {0,4,7,10,1,6,8}, {0,4,7,10,1,5}, {0,3,8,11}, {0,4,7,2,8}, {0,4,8,10}, {0,3,5,7,10}, {0,3,4,7}, {0,5,8,10,1}, {0,3,7,2}, {0,4,6,8,10,1}, {0,3,6,10,2,5}, {0,3,7,8,10,2,5}, {0,3,7,10,1,5}, {0,4,7,11,1}, {0,3,6,9,2,5}, {0,4,7,10,1,6}, {0,3,10,2,5}, {0,4,7,9,3,6}, {0,7,9,2}, {0,4,10,2}, {0,4,7,9,11}, {0,7,11,2}, {0,3,7,8,10}, {0,3,6,10}, {0,5,8,10,1}, {0,3,6,10,2}, {0,3,7,10,6}, {0,3,7,10,5}, {0,3,7,8,2}, {0,4,7,3,8}, {0,3,7,10,2,9}, {0,3,7,1}, {0,4,7,10}, {0,4,6,2,8}, {0,4,7,10,3,6,9}, {0,5,7,10,1}, {0,3,6,10,1}, {0,3,8}, {0,3,7,2,5}, {0,4,6,2}, {0,3,7,9,11}, {0,4,7,9,11,2,6}, {0,4,7,10}, {0,5,7,2}, {0,4,7,10,9}, {0,3,8,10,2}, {0,4,8,10,2,6}, {0,4,7,9,6}, {0,4,6,10,1,6,8}, {0,4,8,10,1}, {0,4,7,2,6}, {0,2,4,7}, {0,4,6}, {0,4,7,10,5}, {0,5}, {0,2,5}, {0,4,7,10,1,8,9}, {0,5,7}, {0,7}, {0,2,7}, {0,3,7,11}, {0,4,8,10,1,6}, {0,7,11}, {0,4,7,10}, {0,3,5,7}, {0,5,7,10,2,8}, {0,4,7,11,5}, {0,3,10}, {0,3,7,10,2,5}, {0,3,7,10,2,6}, {0,4,8,10,3,6,9}, {0,3,6,11}, {0,4,7,11,2,9}, {0,3,7,10,2,5,9}, {0,4,6,8,10}, {0,3,7,10,2,5}, {0,5,7,10}, {0,3,7,10,2}, {0,4,9,11,2}, {0,3,7,8,2}, {0,3,7,9}, {0,3,7,10}, {0,7,10}, {0,2,3,7}, {0,4,7,5}, {0,4,10}, {0,4,7,10,3,6}, {0,4,7,10,1,5}, {0,5,7,10}, {0,3,7,9,5}, {0,3,6,11}, {0,3,10,5}, {0,4,7,1,6}, {0,4,8,1}, {0,4,8,10,1,5}, {0,3,7,11}, {0,3,7,10,8}, {0,4,7,2}, {0,7,2}, {0,4,6,8,10}, {0,4,7,10,3,9}, {0,3,7,9,11}, {0,5,7,10,1,8}, {0,4,7,10,2,8}, {0,4,7,10}, {0,3,6,8,10}, {0,3,7,2}, {0,4,7,10,2,6,9}, {0,4,8,2}, {0,5,7,11}, {0,3,6}, {0,4,8,2}, {0,1,3,6,10}, {0,6,10,2}, {0,3,6,11,8}, {0,5,7,2,9}, {0,3,6,8}, {0,3,6,11}, {0,3,7,10,5,9}, {0,4,7,10,2,6}, {0,5,7,10,2}, {0,4,7,10,1,6,9}, {0,4,7,10,1,5}, {0,4,8,10,1}, {0,4,6,10,2}, {0,7,10,2,6}, {0,4,6,10,2,9}, {0,4,6,10,1,6,9}, {0,3,7,10,11}, {0,4,7,10}, {0,4,6,8,11}, {0,5,7,1}, {0,7,6}, {0,4,7,10,2,6,8}, {0,3,7,9,2}, {0,3,8,10,2,5}, {0,5,7,10,3}, {0,4,6,7,11}, {0,4,8,10,2,6}, {0,4,8,11}, {0,4,7,1}, {0,3,7,10,2,8}, {0,4,7,10,2,6}, {0,3,7,10,11}, {0,3,6,10,2,8}, {0,4,8}, {0,3,6,10,0}};

/* MAIN FUNCTION */

bool similar(Chord c1, Chord c2, unsigned metric, double threshold) {
    if(metric==0) {
        return (c1==c2);
    } else if(metric==1) {
        return (similarF1(PCS(c1), PCS(c2)) > threshold) ? true : false;
    } else if(metric==2) {
        return(PCS_prime(PCS(c1))==PCS_prime(PCS(c2)));
    } else if(metric==3) {
        return(similar_translation(c1,c2));
    } else if(metric==4) {
        return (morris(c1,c2) < threshold) ? true : false;
    } else if(metric==5) {
        return (rahn(c1,c2) > threshold) ? true : false;
    } else if(metric==6) {
        return (lewin(c1,c2) > threshold) ? true : false;
    } else if(metric==7) {
        return (similarity_index(c1,c2) < threshold) ? true : false;
    } else if(metric==8) {
        return (IcVSIM(c1,c2) < threshold) ? true : false;
    }
    exit(-1);
}

void main_test_similarities(vector<Chord> data) {
//    vector<vector<unsigned> > matrixu (data.size(), vector<unsigned> (data.size(), 0));
//    vector<vector<double> > matrixd (data.size(), vector<double> (data.size(), 0.0));
    vector<vector<bool> > matrixb (data.size(), vector<bool> (data.size(), 0.0));

    /* Equality */
    FOR(i,data.size()) {
        FOR(j,data.size()) {
            matrixb[i][j] = similar(data[i], data[j], 0);
        }
    }
    // output

    /* F1-distance */
    for(double thres=0; thres<=1; thres+=0.05) {
        FOR(i,data.size()) {
            FOR(j,data.size()) {
                matrixb[i][j] = similar(data[i], data[j], 1, thres);
            }
        }
        // output
    }

    /* PCS-Prime */
    FOR(i,data.size()) {
        FOR(j,data.size()) {
            matrixb[i][j] = similar(data[i], data[j], 2);
        }
    }
    // output

    /* Translation */
    FOR(i,data.size()) {
        FOR(j,data.size()) {
            matrixb[i][j] = similar(data[i], data[j], 3);
        }
    }
    // output

    /* Morris */
    for(unsigned thres=33; thres>=0; thres--) {
        FOR(i,data.size()) {
            FOR(j,data.size()) {
                matrixb[i][j] = similar(data[i], data[j], 4, thres);
            }
        }
        // output
    }

    /* Rahn */
    for(double thres=0; thres<=1; thres+=0.05) {
        FOR(i,data.size()) {
            FOR(j,data.size()) {
                matrixb[i][j] = similar(data[i], data[j], 5, thres);
            }
        }
        // output
    }

    /* Lewin */
    for(double thres=0; thres<=1; thres+=0.05) {
        FOR(i,data.size()) {
            FOR(j,data.size()) {
                matrixb[i][j] = similar(data[i], data[j], 6, thres);
            }
        }
        // output
    }

    /* Teitelbaum */
    for(double thres=1; thres>=0; thres-=0.05) {
        FOR(i,data.size()) {
            FOR(j,data.size()) {
                matrixb[i][j] = similar(data[i], data[j], 7, thres);
            }
        }
        // output
    }

    /* Isaacson */
    for(double thres=1; thres>=0; thres-=0.05) {
        FOR(i,data.size()) {
            FOR(j,data.size()) {
                matrixb[i][j] = similar(data[i], data[j], 8, thres);
            }
        }
        // output
    }
}


/* (1) F1-distance */

set<unsigned> inter(set<unsigned> s1, set<unsigned> s2) {
    set<unsigned> res;
    for(auto x : s1) {
        if(s2.find(x)!=s2.end()) {
            res.insert(x);
        }
    }
    return res;
}

double similarF1(set<unsigned> s1, set<unsigned> s2) {
    return (2*(double)inter(s1,s2).size())/((double)(s1.size()+s2.size()));
}


/* (2) PCS-Prime */

set<unsigned> PCS(Chord c) {
    if(!c.nc) {
        return PCS_table[c.h];
    } else {
        return {0};
    }
}

static set<unsigned> reduce_PCS_table(vector<vector<unsigned> > rotation_table) {
    unsigned min_dist = 24;
    unsigned last = rotation_table[0].size();
    while(rotation_table.size()!=1) {
        FOR(i,rotation_table.size()) {
            if(abs((int)rotation_table[i][0] - (int)rotation_table[i][last]) < (int)min_dist) {
                min_dist = abs((int)rotation_table[i][0] - (int)rotation_table[i][last]);
            }
        }
        FOR(i,rotation_table.size()) {
            if(abs((int)rotation_table[i][0] - (int)rotation_table[i][last]) > (int)min_dist) {
                rotation_table.erase(rotation_table.begin()+i);
            }
        }
        last++; last %= rotation_table[0].size(); last += (last==0 ? 1 : 0);
    }
    set<unsigned> res;
    FOR(i,rotation_table[0].size()) {
        rotation_table[0][i] %= 12;
    }
    std::sort(rotation_table[0].begin(),rotation_table[0].end());
    unsigned offset = rotation_table[0][0];
    FOR(i,rotation_table[0].size()) {
        res.insert(rotation_table[0][i]-offset);
    }
    return res;
}

static vector<vector<unsigned> > rot_table(set<unsigned> s) {
    vector<vector<unsigned> > rotation_table (s.size(), vector<unsigned> ());
    for(auto x : s) {
        rotation_table[0].push_back(x);
    }
    std::sort(rotation_table[0].begin(),rotation_table[0].end());
    for(unsigned i=1; i<rotation_table.size(); i++) {
        FOR(j,rotation_table[0].size()) {
            unsigned u = rotation_table[0][(i+j)%rotation_table.size()];
            u += (j >= rotation_table[0].size() ? 12 : 0);
            rotation_table[j].push_back(u);
        }
    }
    return rotation_table;
}

set<unsigned> PCS_prime(set<unsigned> s) {
    vector<vector<unsigned> > rotation_table = rot_table(s);
    set<unsigned> original = reduce_PCS_table(rotation_table);

    set<unsigned> inverted;
    for(auto x : original) {
        inverted.insert(12-x);
    }
    rotation_table.clear();
    rotation_table = rot_table(inverted);
    inverted = reduce_PCS_table(rotation_table);

    vector<vector<unsigned> > final_choice (2, vector<unsigned> ());
    for(auto x : original) {
        final_choice[0].push_back(x);
    }
    for(auto x : inverted) {
        final_choice[1].push_back(x);
    }

    return reduce_PCS_table(final_choice);
}


/* (3) Translation */

bool similar_translation(Chord c1, Chord c2) {
    if (c1.nc==true) {
        return (c2.nc);
    } else {
        if (c1.h != c2.h) {
            return false;
        } else {
            return true;
        }
    }
}

bool similar_translation(vector<Chord> v1, vector<Chord> v2) {
    if(v1.size()!=v2.size()) {
        return false;
    } else if ((v1.size()==0) || (v2.size()==0)) {
        return false;
    } else {
        Chord c1=v1[0], c2=v2[0];
        if (!similar_translation(c1,c2)) {
            return false;
        } else {
            unsigned dif=c1-c2;
            for (unsigned i=1; i<v1.size(); i++) {
                c1=v1[i], c2=v2[i];
                if (!similar_translation(c1,c2)) {
                    return false;
                } else {
                    if((c1-c2 != dif)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

static unsigned NAtou(NOTE n, ACCIDENTAL a) {
    unsigned res=0;
    switch(n) {
        case A:
            res=1;
            break;
        case B:
            res=3;
            break;
        case C:
            res=4;
            break;
        case D:
            res=6;
            break;
        case E:
            res=8;
            break;
        case F:
            res=9;
            break;
        case G:
            res=11;
            break;
    }
    switch(a) {
        case MOLL:
            res--;
            break;
        case DUR:
            res++;
            break;
        case NONE:
            break;
    }
    return res;
}

unsigned operator-(Chord c1, Chord c2) {
    if(!similar_translation(c1,c2)) {
        return (unsigned)(-1);
    } else {
        if (c1.nc) {
            return 0;
        } else {
            unsigned n1 = NAtou(c1.n, c1.a), n2 = NAtou(c2.n, c2.a);
            if (n1>n2) {
                return (n1-n2);
            } else {
                return (n2-n1);
            }
        }
    }
}


/* (4) Morris */
vector<unsigned> interval_vector(set<unsigned> s) {
    vector<unsigned> res (6,0);
    for(auto x : s) {
        x %= 12;
    }
    for(auto x : s) {
        for(auto y : s) {
            unsigned dif = (x>y) ? (x-y) : (y-x);
            if (dif!=0) {
                res[dif]++;
            }
        }
    }
    FOR(i,6) {
        res[i] /= 2;
    }
    return res;
}

unsigned morris(Chord c1, Chord c2) {
    unsigned res=0;
    vector<unsigned> iv1 = interval_vector(PCS(c1)), iv2 = interval_vector(PCS(c2));
    FOR(i,6) {
        res += (iv1[i] > iv2[i]) ? (iv1[i]-iv2[i]) : (iv2[i]-iv1[i]);
    }
    return res;
}


/* (5) Rahn */
double rahn(Chord c1, Chord c2) {
    double res=0;
    double card1=0, card2=0;
    vector<unsigned> iv1 = interval_vector(PCS(c1)), iv2 = interval_vector(PCS(c2));
    FOR(i,6) {
        if((iv1[i] > 0) && (iv2[i]>0)) {
            res += iv1[i]+iv2[i];
        }
        card1 += (iv1[i]);
        card2 += (iv2[i]);
    }
    res /= (0.5)*(((card1)*(card1-1))+((card2)*(card2-1)));
    return res;
}

/* (6) Lewin */
double lewin(Chord c1, Chord c2) {
    double res=0;
    double card1=0, card2=0;
    vector<unsigned> iv1 = interval_vector(PCS(c1)), iv2 = interval_vector(PCS(c2));
    FOR(i,6) {
        res += sqrt(iv1[i]*iv2[i]);
        card1 += (iv1[i]);
        card2 += (iv2[i]);
    }
    res *= 2/sqrt(card1*(card1-1)*card2*(card2-1));
    return res;
}

/* (7) Teitelbaum */
double similarity_index(Chord c1, Chord c2) {
    double res=0;
    vector<unsigned> iv1 = interval_vector(PCS(c1)), iv2 = interval_vector(PCS(c2));
    FOR(i,6) {
        res += ((int)iv1[i]-(int)iv2[i])*((int)iv1[i]-(int)iv2[i]);
    }
    res = sqrt(res);
    return res;
}

/* (8) Isaacson */
double IcVSIM(Chord c1, Chord c2) {
    double res=0, mean=0;
    vector<unsigned> iv1 = interval_vector(PCS(c1)), iv2 = interval_vector(PCS(c2)), ivdif(6,0);
    FOR(i,6) {
        ivdif[i] = (iv1[i] > iv2[i]) ? (iv1[i]-iv2[i]) : (iv2[i]-iv1[i]);
    }
    FOR(i,6) {
        mean += ivdif[i];
    }
    mean /= 6;
    FOR(i,6) {
        res += (ivdif[i]-mean)*(ivdif[i]-mean);
    }
    res = sqrt(res/6);
    return res;
}
