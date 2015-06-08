#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>
#include <map>

#include "lz77equiv.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

using namespace std;

//string harm_table[313] = {" ", "#11  ", "6b5  ", "m11M7b5  ", "mM7#11  ", "6omit3  ", "dimadd11  ", "slash7  ", "Lydian  ", "M7#9b5  ", "7b9#9b5  ", "m7b5#11  ", "13b9#11  ", "M7#9b9  ", "7b5b9  ", "mb9add11  ", "+-9  ", "dim7add11  ", "7b5#9  ", "M7#11(omit3)  ", "69omit5  ", "7b9omit3  ", "+  ", "omit5  ", "m(omit3)  ", "9add13  ", "omit3  ", "pedal  ", "wt  ", "m9#11  ", "2  ", "7  ", "6  ", "5  ", "mM7add11  ", "m7b13  ", "#9  ", "9  ", "madd11  ", "(add9)  ", "13(add11)  ", "halfdim7sus4  ", "7b9b5  ", "dim7add9  ", "mb6  ", "mb5  ", "M  ", "m9M7#11  ", "m9sus4  ", "13  ", "6#9  ", "11  ", "M7(omit5)  ", "(9,#11)  ", "7b13  ", "m(M13)  ", "(b9b13)  ", "m(M9)  ", "M13#11  ", "(#5)add9  ", "add9b5  ", "4(addb9)  ", "7#9  ", "m  ", "m(omit5)  ", "7#4  ", "69M7  ", "7#5  ", "4(add9)  ", "m7b5b13  ", "9#5  ", "7b9#5  ", "addb13  ", "7b9#9  ", "7susadd3  ", "7#9#5  ", "addb9  ", "7#9(omit5)  ", "13#9b5  ", "m6(omit5)  ", "m9M7  ", "M7(4)  ", "#9#11  ", "7#5#11  ", "(b5)sus4  ", "7susadd13  ", "7b5  ", "7b6  ", "M7#9#11  ", "b9sus  ", "m13#11  ", "M7(add6)  ", "7b9  ", "69  ", "6sus4  ", "dim7  ", "#5add#9  ", "7(#11)  ", "7b9sus  ", "m7b9  ", "7#5#9  ", "M7addb13  ", "M9sus  ", "M7(add#11)  ", "halfdim7  ", "Phrygian(add3)  ", "sus4add13  ", "M7#11  ", "msus4  ", "m9b13  ", "Dorian  ", "5add9  ", "4sus  ", "halfdim7add11  ", "M9b5add13  ", "13b9sus  ", "b9  ", "m7addb13  ", "sus  ", "(#11)  ", "alt  ", "m7(6)  ", "sus4b9  ", "9#11  ", "dim7M7add9  ", "M9#11  ", "add#11  ", "m11M7  ", "m9M7b5  ", "+7#9  ", "m69(11)  ", "M9add13  ", "13sus  ", "mM7(add9)  ", "halfdim7add13  ", "m9add#5  ", "7alt  ", "add9sus  ", "m7#5add4  ", "7b9#11  ", "m69(#11)  ", "M9#5  ", "M13  ", "M7b6  ", "M7  ", "M7b5  ", "m69addM7  ", "m7#5  ", "M7(add9)  ", "aug#4  ", "7#9add4  ", "M9  ", "M7#9  ", "(#5)  ", "m7add9  ", "m(b9)  ", "madd9  ", "7susomit5  ", "dim(9)  ", "dim7b13  ", "13omit3  ", "m6(add11)  ", "M769  ", "69#11  ", "m69  ", "7#9b5  ", "7b9b13  ", "7b9b11  ", "mM7#5  ", "add9addb13  ", "+7  ", "m7add4  ", "(add#9)  ", "b9#5sus  ", "m(add9)  ", "7b9b5#5  ", "m11b5  ", "m11b6  ", "m11b9  ", "M7b9  ", "dim11  ", "13(b9#11)  ", "m11omit5  ", "6#9#11  ", "69(omit3)  ", "9omit5  ", "M7(6)  ", "9omit3  ", "m7b6  ", "m7b5  ", "7b9#5sus  ", "m9b5  ", "m7#11  ", "m7(add11)  ", "mb6(add9)  ", "#9b13  ", "m9add13  ", "m(addb9)  ", "m9add11  ", "9b5b13  ", "13#9#11  ", "Phrygian  ", "halfdim7b9  ", "m#5  ", "madd9add11  ", "M9b5  ", "m6M7  ", "M9#11(6)  ", "9+  ", "sus4add9  ", "7(13)  ", "m9#5  ", "M7#5#11  ", "6#11  ", "13b9b5  ", "+7b9  ", "#11add9  ", "(add2)  ", "(b5)  ", "7add11  ", "sus4omit5  ", "sus24  ", "13b9add#5  ", "sus4  ", "(no3rd)  ", "sus2  ", "m(m7M7)  ", "7b9#5#11  ", "M7(omit3)  ", "m+  ", "m(add4)  ", "7b13sus  ", "M7add11  ", "m7(omit5)  ", "Aeolian  ", "m#11  ", "13#9#5  ", "dim7M7  ", "M7add13  ", "m13  ", "7#5b5  ", "m11  ", "7sus  ", "m9  ", "M7(69)  ", "m9b6  ", "m6  ", "m7  ", "7omit3  ", "m2  ", "add11  ", "7omit5  ", "7#9#11  ", "7#9b13  ", "m7sus4  ", "m6add11  ", "dimM7  ", "m7(add11omit5)  ", "b9#11  ", "+(b9)  ", "11b9#5  ", "mM7  ", "m7add13  ", "add9  ", "add9omit3  ", "7#4#5  ", "13#9  ", "m6(M7)  ", "7b9b13sus  ", "9b13  ", "m7add11  ", "m7b5#5  ", "mM9  ", "13#11  ", "+(add9)  ", "M7sus  ", "dim  ", "+add9  ", "m7(b5b2)  ", "9b5omit3  ", "dim7M7b13  ", "sus4(9,13)  ", "dim(b13)  ", "mM7b5  ", "m7add11add13  ", "7#11  ", "9sus  ", "13b9  ", "11b9  ", "7#5b9  ", "9b5  ", "9#11omit3  ", "13b5  ", "13(b9b5)  ", "m7M7  ", "M9omit3  ", "M7#5b5  ", "sus(addb9)  ", "5#11  ", "7b13#11  ", "m6(add9)  ", "m11#5  ", "7#9sus4  ", "M7#4  ", "9#5#11  ", "M7#5  ", "(b9)  ", "mM7b13  ", "Lydian(#6)  ", "m7addM7  ", "mb5b13  ", "aug  ", "halfdim7add9  "};


/* Not optimal implementation */
tuple<unsigned, unsigned, unsigned> longest_prefix_eq(vector<Chord> input, vector<Chord> dictionary) {
    int lp_begin=1, lp_end=0, dif=-1;
    unsigned initial_dictionary_size = dictionary.size();

    FOR(i,input.size())
        dictionary.push_back(input[i]);

    FOR(i,initial_dictionary_size) {
        int diftemp = -1;
        if (equiv(dictionary[i],input[0])) {
            diftemp = dictionary[i]-input[0];
        }
        FOR(j,input.size()) {
            if (!equiv(dictionary[i+j],input[j])) {
                break;
            } else if (diftemp != (int)(dictionary[i+j]-input[j])) {
                break;
            } else {
                if ((int)j>(lp_end-lp_begin)) {
                    lp_begin = i;
                    lp_end = i+j;
                    dif = diftemp;
                }
            }
        }
    }

    return make_tuple(lp_begin, lp_end, dif);
}


//vector<tuple<unsigned, unsigned, unsigned, Chord> > compress77_eq(vector<Chord> input, unsigned l_buf, unsigned l_prev) {
//    vector<tuple<unsigned, unsigned, unsigned Chord> > output;
/*    queue<Chord> buffer;
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
        pair<unsigned, unsigned> pref = longest_prefix(qtov(preview), qtov(buffer));
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
*/
//    return output;
//}

//vector<vector<Chord> > print_dictionary_eq(vector<tuple<unsigned, unsigned, unsigned Chord> > dico, unsigned l_buf, unsigned l_prev) {
//    vector<Chord> reconstruction;
//    vector<vector<Chord> > res;
/*    unsigned res_index=-1;

    cout << endl << "Dictionary (for buffer size = " << l_buf << " and preview size = " << l_prev << ") :" << endl;
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

cout << reconstruction << endl << endl;
FOR(i,res.size()) {
cout << res[i] << endl; }
*/
//    return res;
//}


//map<string, unsigned> allSequences_eq(vector<Chord> input, unsigned threshold) {
//    map<string, unsigned> res;

/*    for (unsigned i=1; i<input.size()+1; i++) {          // length
        for (unsigned j=0; j<input.size()-i+1; j++) {    // beginning
            string seq = "";
            for (unsigned k=j; k<i+j; k++) {
                seq += to_string(Ctou(input[k]));
                seq += ";";
            }
            res[seq] = 0;
        }
    }

    for (unsigned i=1; i<input.size()+1; i++) {
        for (unsigned j=0; j<input.size()-i+1; j++) {
            string seq = "";
            for (unsigned k=j; k<i+j; k++) {
                seq += to_string(Ctou(input[k]));
                seq += ";";
            }
            res[seq]++;
        }
    }

    std::map<std::string, unsigned>::iterator it, itEnd = res.end();
    for(it = res.begin(); it!=itEnd; ++it) {
        if((it->second)<threshold) {
            res.erase(it->first);
        }
    }
*/
//    return res;
//}

bool equiv(Chord c1, Chord c2) {
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

bool equivv(vector<Chord> v1, vector<Chord> v2) {
    if(v1.size()!=v2.size()) {
        return false;
    } else if ((v1.size()==0) || (v2.size()==0)) {
        return false;
    } else {
        Chord c1=v1[0], c2=v2[0];
        if (!equiv(c1,c2)) {
            return false;
        } else {
            unsigned dif=c1-c2;
            for (unsigned i=1; i<v1.size(); i++) {
                c1=v1[i], c2=v2[i];
                if (!equiv(c1,c2)) {
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

/*bool operator==(Chord c1, Chord c2) {
    if ((c1.nc == true) && (c2.nc == true)) {
        return true;
    } else {
        if ((c1.n == c2.n) && (c1.a == c2.a) && (c1.h == c2.h)) {
            return true;
        }
    }
    return false;
}

bool operator!=(Chord c1, Chord c2) {
    return !(c1==c2);
}

ostream& operator<<(ostream &flux, Chord c) {
    if(c.nc) {
        flux << "NC";
    } else {
        switch(c.n) {
            case A:
                flux << "A";
                break;
            case B:
                flux << "B";
                break;
            case C:
                flux << "C";
                break;
            case D:
                flux << "D";
                break;
            case E:
                flux << "E";
                break;
            case F:
                flux << "F";
                break;
            case G:
                flux << "G";
                break;
        }
        switch(c.a) {
            case DUR:
                flux << "#";
                break;
            case MOLL:
                flux << "b";
                break;
            case NONE:
                break;
        }
        if(c.h!=0)
        flux << " " << harm_table[c.h];
    }
    return flux;
}

ostream& operator<<(ostream &flux, vector<Chord> v) {
    FOR(i,v.size()) {
        flux << v[i] << endl;
    }
    return flux;
}

ostream& operator<<(ostream &flux, tuple<unsigned, unsigned, Chord> t) {
    flux << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")" << endl;
    return flux;
}

ostream& operator<<(ostream &flux, vector<tuple<unsigned, unsigned, Chord> > v) {
    FOR(i,v.size()) {
        flux << v[i] << endl;
    }
    return flux;
}

ostream& operator<<(ostream &flux, map<string, unsigned> m) {
    std::map<std::string, unsigned>::iterator it, itEnd = m.end();
    for(it = m.begin(); it!=itEnd; ++it) {
        string s = it->first;
        string ch = "";
        FOR(i,s.length()) {
            if (s[i]!=';') {
                ch += s[i];
            } else {
                flux << utoC((unsigned)(stoul(ch))) << ";";
                ch = "";
            }
        }
        flux << " : " << it->second << endl;
    }
    return flux;
}*/

unsigned NAtou(NOTE n, ACCIDENTAL a) {
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
    if(!equiv(c1,c2)) {
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

