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

#include "lz77similar.hpp"

#define FOR(i,n) for(unsigned i=0;i<unsigned(n);i++)

using namespace std;

//string harm_table[313] = {" ", "#11  ", "6b5  ", "m11M7b5  ", "mM7#11  ", "6omit3  ", "dimadd11  ", "slash7  ", "Lydian  ", "M7#9b5  ", "7b9#9b5  ", "m7b5#11  ", "13b9#11  ", "M7#9b9  ", "7b5b9  ", "mb9add11  ", "+-9  ", "dim7add11  ", "7b5#9  ", "M7#11(omit3)  ", "69omit5  ", "7b9omit3  ", "+  ", "omit5  ", "m(omit3)  ", "9add13  ", "omit3  ", "pedal  ", "wt  ", "m9#11  ", "2  ", "7  ", "6  ", "5  ", "mM7add11  ", "m7b13  ", "#9  ", "9  ", "madd11  ", "(add9)  ", "13(add11)  ", "halfdim7sus4  ", "7b9b5  ", "dim7add9  ", "mb6  ", "mb5  ", "M  ", "m9M7#11  ", "m9sus4  ", "13  ", "6#9  ", "11  ", "M7(omit5)  ", "(9,#11)  ", "7b13  ", "m(M13)  ", "(b9b13)  ", "m(M9)  ", "M13#11  ", "(#5)add9  ", "add9b5  ", "4(addb9)  ", "7#9  ", "m  ", "m(omit5)  ", "7#4  ", "69M7  ", "7#5  ", "4(add9)  ", "m7b5b13  ", "9#5  ", "7b9#5  ", "addb13  ", "7b9#9  ", "7susadd3  ", "7#9#5  ", "addb9  ", "7#9(omit5)  ", "13#9b5  ", "m6(omit5)  ", "m9M7  ", "M7(4)  ", "#9#11  ", "7#5#11  ", "(b5)sus4  ", "7susadd13  ", "7b5  ", "7b6  ", "M7#9#11  ", "b9sus  ", "m13#11  ", "M7(add6)  ", "7b9  ", "69  ", "6sus4  ", "dim7  ", "#5add#9  ", "7(#11)  ", "7b9sus  ", "m7b9  ", "7#5#9  ", "M7addb13  ", "M9sus  ", "M7(add#11)  ", "halfdim7  ", "Phrygian(add3)  ", "sus4add13  ", "M7#11  ", "msus4  ", "m9b13  ", "Dorian  ", "5add9  ", "4sus  ", "halfdim7add11  ", "M9b5add13  ", "13b9sus  ", "b9  ", "m7addb13  ", "sus  ", "(#11)  ", "alt  ", "m7(6)  ", "sus4b9  ", "9#11  ", "dim7M7add9  ", "M9#11  ", "add#11  ", "m11M7  ", "m9M7b5  ", "+7#9  ", "m69(11)  ", "M9add13  ", "13sus  ", "mM7(add9)  ", "halfdim7add13  ", "m9add#5  ", "7alt  ", "add9sus  ", "m7#5add4  ", "7b9#11  ", "m69(#11)  ", "M9#5  ", "M13  ", "M7b6  ", "M7  ", "M7b5  ", "m69addM7  ", "m7#5  ", "M7(add9)  ", "aug#4  ", "7#9add4  ", "M9  ", "M7#9  ", "(#5)  ", "m7add9  ", "m(b9)  ", "madd9  ", "7susomit5  ", "dim(9)  ", "dim7b13  ", "13omit3  ", "m6(add11)  ", "M769  ", "69#11  ", "m69  ", "7#9b5  ", "7b9b13  ", "7b9b11  ", "mM7#5  ", "add9addb13  ", "+7  ", "m7add4  ", "(add#9)  ", "b9#5sus  ", "m(add9)  ", "7b9b5#5  ", "m11b5  ", "m11b6  ", "m11b9  ", "M7b9  ", "dim11  ", "13(b9#11)  ", "m11omit5  ", "6#9#11  ", "69(omit3)  ", "9omit5  ", "M7(6)  ", "9omit3  ", "m7b6  ", "m7b5  ", "7b9#5sus  ", "m9b5  ", "m7#11  ", "m7(add11)  ", "mb6(add9)  ", "#9b13  ", "m9add13  ", "m(addb9)  ", "m9add11  ", "9b5b13  ", "13#9#11  ", "Phrygian  ", "halfdim7b9  ", "m#5  ", "madd9add11  ", "M9b5  ", "m6M7  ", "M9#11(6)  ", "9+  ", "sus4add9  ", "7(13)  ", "m9#5  ", "M7#5#11  ", "6#11  ", "13b9b5  ", "+7b9  ", "#11add9  ", "(add2)  ", "(b5)  ", "7add11  ", "sus4omit5  ", "sus24  ", "13b9add#5  ", "sus4  ", "(no3rd)  ", "sus2  ", "m(m7M7)  ", "7b9#5#11  ", "M7(omit3)  ", "m+  ", "m(add4)  ", "7b13sus  ", "M7add11  ", "m7(omit5)  ", "Aeolian  ", "m#11  ", "13#9#5  ", "dim7M7  ", "M7add13  ", "m13  ", "7#5b5  ", "m11  ", "7sus  ", "m9  ", "M7(69)  ", "m9b6  ", "m6  ", "m7  ", "7omit3  ", "m2  ", "add11  ", "7omit5  ", "7#9#11  ", "7#9b13  ", "m7sus4  ", "m6add11  ", "dimM7  ", "m7(add11omit5)  ", "b9#11  ", "+(b9)  ", "11b9#5  ", "mM7  ", "m7add13  ", "add9  ", "add9omit3  ", "7#4#5  ", "13#9  ", "m6(M7)  ", "7b9b13sus  ", "9b13  ", "m7add11  ", "m7b5#5  ", "mM9  ", "13#11  ", "+(add9)  ", "M7sus  ", "dim  ", "+add9  ", "m7(b5b2)  ", "9b5omit3  ", "dim7M7b13  ", "sus4(9,13)  ", "dim(b13)  ", "mM7b5  ", "m7add11add13  ", "7#11  ", "9sus  ", "13b9  ", "11b9  ", "7#5b9  ", "9b5  ", "9#11omit3  ", "13b5  ", "13(b9b5)  ", "m7M7  ", "M9omit3  ", "M7#5b5  ", "sus(addb9)  ", "5#11  ", "7b13#11  ", "m6(add9)  ", "m11#5  ", "7#9sus4  ", "M7#4  ", "9#5#11  ", "M7#5  ", "(b9)  ", "mM7b13  ", "Lydian(#6)  ", "m7addM7  ", "mb5b13  ", "aug  ", "halfdim7add9  "};

//string PCS_table[313] = {"00,04,07", "00,04,07,10,02,06", "00,04,06,09", "00,03,06,11,05", "00,03,07,11,02,06", "00,07,09", "00,03,06,05", "10,00,04,07", "00,04,07,11,02,06", "00,04,06,11,03", "00,04,06,10,01,03", "00,03,06,10", "00,04,07,10,01,06,08", "00,04,07,10,01,03", "00,04,06,10,01", "00,03,07,01,05", "00,04,07,10", "00,03,06,09,05", "00,04,06,10,03", "00,07,11,06", "00,04,09,02", "00,07,10,01", "00,04,08", "00,04", "00,07", "00,04,07,10,02,09", "00,07", "00", "00,02,04,06,08,10", "00,03,07,10,02,06", "00,02,04,07", "00,04,07,10", "00,04,07,09", "00,07", "00,03,07,11,05", "00,03,07,10,08", "00,04,07,03", "00,04,07,10,02", "00,03,07,05", "00,04,07,02", "00,04,07,10,02,05,09", "00,05,06,10", "00,04,06,10,01", "00,03,06,09,02", "00,03,07,08", "00,03,06", "00,04,07", "00,03,07,11,02,06", "00,05,07,10,02", "00,04,07,10,02,06,09", "00,04,07,09,03", "00,04,07,10,02,05", "00,04,11", "00,04,07,10,02,06", "00,04,07,10,02,06,08", "00,03,07,10,02,09", "00,04,07,10,01,08", "00,03,07,02", "00,04,07,10,02,06,09", "00,04,08,02", "00,04,06,02", "00,05,07,01", "00,04,07,10,03", "00,03,07", "00,03", "00,04,06,07,10", "00,04,07,10", "00,04,08,10", "00,05,07,02", "00,03,06,10,02,08", "00,04,08,10,02", "00,04,08,10,01", "00,04,07,08", "00,04,07,10,01,03", "00,04,05,10", "00,04,08,10,03", "00,04,07,01", "00,04,10,03", "00,04,06,10,03,06,09", "00,03,09", "00,03,07,11,02", "00,04,05,07,11", "00,04,07,03,06", "00,05,08,10,02,06", "00,05,06", "00,05,07,10,09", "00,04,06,10", "00,04,07,08,10", "00,04,07,11,03,06", "00,05,07,01", "00,03,07,10,02,06,09", "00,04,07,09,11", "00,04,07,10,01", "00,04,07,09,02", "00,05,07,09", "00,03,06,09", "00,04,08,03", "00,04,07,10,06", "00,05,07,10,01", "00,03,07,10,01", "00,04,08,10,03", "00,04,07,11,08", "00,05,07,11,02", "00,04,07,11,06", "00,03,06,10", "00,04,05,07,10,01", "00,05,07,09", "00,04,07,11,02,06", "00,03,05,07", "00,03,07,10,02,08", "00,03,07,10,02,05", "00,04,07,02", "00,05,07", "00,03,06,10,05", "00,04,06,11,02,09", "00,04,07,10,01,09", "00,04,07,01", "00,03,07,10,08", "00,05,07", "00,04,07,06", "00,04,08,10,03", "00,03,09,10", "00,05,07,01", "00,04,07,10,02,06", "00,03,06,11,02", "00,04,07,11,02,06", "00,04,07,06", "00,03,07,11,02,05", "00,03,06,11,02", "00,04,08,10,03", "00,03,07,09,02,05", "00,04,07,11,02,09", "00,05,07,10,02,09", "00,03,07,11,02", "00,03,06,10,09", "00,03,07,08,10,02", "00,04,08,10,03", "00,05,07,02", "00,03,08,10,05", "00,05,07,10,01,06", "00,03,07,09,02,06", "00,04,08,11,02", "00,04,07,11,02,06,09", "00,04,07,08,11", "00,04,07,11", "00,04,06,11", "00,03,07,09,11,02", "00,03,08,10", "00,04,07,11,02", "00,04,06,08", "00,04,07,10,03,05", "00,04,07,11,02", "00,04,07,11,03", "00,04,08", "00,03,07,10,02", "00,03,07,01", "00,03,07,02", "00,05,10", "00,03,06,09,02", "00,03,06,09", "00,07,10,02,06,09", "00,03,07,09,05", "00,04,07,09,11,02", "00,04,07,09,02,06", "00,03,07,09,02", "00,04,06,10,03", "00,04,07,10,01,06,08", "00,04,07,10,01,05", "00,03,08,11", "00,04,07,02,08", "00,04,08,10", "00,03,05,07,10", "00,03,04,07", "00,05,08,10,01", "00,03,07,02", "00,04,06,08,10,01", "00,03,06,10,02,05", "00,03,07,08,10,02,05", "00,03,07,10,01,05", "00,04,07,11,01", "00,03,06,09,02,05", "00,04,07,10,01,06", "00,03,10,02,05", "00,04,07,09,03,06", "00,07,09,02", "00,04,10,02", "00,04,07,09,11", "00,07,11,02", "00,03,07,08,10", "00,03,06,10", "00,05,08,10,01", "00,03,06,10,02", "00,03,07,10,06", "00,03,07,10,05", "00,03,07,08,02", "00,04,07,03,08", "00,03,07,10,02,09", "00,03,07,01", "00,04,07,10", "00,04,06,02,08", "00,04,07,10,03,06,09", "00,05,07,10,01", "00,03,06,10,01", "00,03,08", "00,03,07,02,05", "00,04,06,02", "00,03,07,09,11", "00,04,07,09,11,02,06", "00,04,07,10", "00,05,07,02", "00,04,07,10,09", "00,03,08,10,02", "00,04,08,10,02,06", "00,04,07,09,06", "00,04,06,10,01,06,08", "00,04,08,10,01", "00,04,07,02,06", "00,02,04,07", "00,04,06", "00,04,07,10,05", "00,05", "00,02,05", "00,04,07,10,01,08,09", "00,05,07", "00,07", "00,02,07", "00,03,07,11", "00,04,08,10,01,06", "00,07,11", "00,04,07,10", "00,03,05,07", "00,05,07,10,02,08", "00,04,07,11,05", "00,03,10", "00,03,07,10,02,05", "00,03,07,10,02,06", "00,04,08,10,03,06,09", "00,03,06,11", "00,04,07,11,02,09", "00,03,07,10,02,05,09", "00,04,06,08,10", "00,03,07,10,02,05", "00,05,07,10", "00,03,07,10,02", "00,04,09,11,02", "00,03,07,08,02", "00,03,07,09", "00,03,07,10", "00,07,10", "00,02,03,07", "00,04,07,05", "00,04,10", "00,04,07,10,03,06", "00,04,07,10,01,05", "00,05,07,10", "00,03,07,09,05", "00,03,06,11", "00,03,10,05", "00,04,07,01,06", "00,04,08,01", "00,04,08,10,01,05", "00,03,07,11", "00,03,07,10,08", "00,04,07,02", "00,07,02", "00,04,06,08,10", "00,04,07,10,03,09", "00,03,07,09,11", "00,05,07,10,01,08", "00,04,07,10,02,08", "00,04,07,10", "00,03,06,08,10", "00,03,07,02", "00,04,07,10,02,06,09", "00,04,08,02", "00,05,07,11", "00,03,06", "00,04,08,02", "00,01,03,06,10", "00,06,10,02", "00,03,06,11,08", "00,05,07,02,09", "00,03,06,08", "00,03,06,11", "00,03,07,10,05,09", "00,04,07,10,02,06", "00,05,07,10,02", "00,04,07,10,01,06,09", "00,04,07,10,01,05", "00,04,08,10,01", "00,04,06,10,02", "00,07,10,02,06", "00,04,06,10,02,09", "00,04,06,10,01,06,09", "00,03,07,10,11", "00,04,07,10", "00,04,06,08,11", "00,05,07,01", "00,07,06", "00,04,07,10,02,06,08", "00,03,07,09,02", "00,03,08,10,02,05", "00,05,07,10,03", "00,04,06,07,11", "00,04,08,10,02,06", "00,04,08,11", "00,04,07,01", "00,03,07,10,02,08", "00,04,07,10,02,06", "00,03,07,10,11", "00,03,06,10,02,08", "00,04,08", "00,03,06,10,02"};

set<unsigned> PCS_table[313] = {{0,4,7}, {0,4,7,10,2,6}, {0,4,6,9}, {0,3,6,11,5}, {0,3,7,11,2,6}, {0,7,9}, {0,3,6,5}, {10,0,4,7}, {0,4,7,11,2,6}, {0,4,6,11,3}, {0,4,6,10,1,3}, {0,3,6,10}, {0,4,7,10,1,6,8}, {0,4,7,10,1,3}, {0,4,6,10,1}, {0,3,7,1,5}, {0,4,7,10}, {0,3,6,9,5}, {0,4,6,10,3}, {0,7,11,6}, {0,4,9,2}, {0,7,10,1}, {0,4,8}, {0,4}, {0,7}, {0,4,7,10,2,9}, {0,7}, {0}, {0,2,4,6,8,10}, {0,3,7,10,2,6}, {0,2,4,7}, {0,4,7,10}, {0,4,7,9}, {0,7}, {0,3,7,11,5}, {0,3,7,10,8}, {0,4,7,3}, {0,4,7,10,2}, {0,3,7,5}, {0,4,7,2}, {0,4,7,10,2,5,9}, {0,5,6,10}, {0,4,6,10,1}, {0,3,6,9,2}, {0,3,7,8}, {0,3,6}, {0,4,7}, {0,3,7,11,2,6}, {0,5,7,10,2}, {0,4,7,10,2,6,9}, {0,4,7,9,3}, {0,4,7,10,2,5}, {0,4,11}, {0,4,7,10,2,6}, {0,4,7,10,2,6,8}, {0,3,7,10,2,9}, {0,4,7,10,1,8}, {0,3,7,2}, {0,4,7,10,2,6,9}, {0,4,8,2}, {0,4,6,2}, {0,5,7,1}, {0,4,7,10,3}, {0,3,7}, {0,3}, {0,4,6,7,10}, {0,4,7,10}, {0,4,8,10}, {0,5,7,2}, {0,3,6,10,2,8}, {0,4,8,10,2}, {0,4,8,10,1}, {0,4,7,8}, {0,4,7,10,1,3}, {0,4,5,10}, {0,4,8,10,3}, {0,4,7,1}, {0,4,10,3}, {0,4,6,10,3,6,9}, {0,3,9}, {0,3,7,11,2}, {0,4,5,7,11}, {0,4,7,3,6}, {0,5,8,10,2,6}, {0,5,6}, {0,5,7,10,9}, {0,4,6,10}, {0,4,7,8,10}, {0,4,7,11,3,6}, {0,5,7,1}, {0,3,7,10,2,6,9}, {0,4,7,9,11}, {0,4,7,10,1}, {0,4,7,9,2}, {0,5,7,9}, {0,3,6,9}, {0,4,8,3}, {0,4,7,10,6}, {0,5,7,10,1}, {0,3,7,10,1}, {0,4,8,10,3}, {0,4,7,11,8}, {0,5,7,11,2}, {0,4,7,11,6}, {0,3,6,10}, {0,4,5,7,10,1}, {0,5,7,9}, {0,4,7,11,2,6}, {0,3,5,7}, {0,3,7,10,2,8}, {0,3,7,10,2,5}, {0,4,7,2}, {0,5,7}, {0,3,6,10,5}, {0,4,6,11,2,9}, {0,4,7,10,1,9}, {0,4,7,1}, {0,3,7,10,8}, {0,5,7}, {0,4,7,6}, {0,4,8,10,3}, {0,3,9,10}, {0,5,7,1}, {0,4,7,10,2,6}, {0,3,6,11,2}, {0,4,7,11,2,6}, {0,4,7,6}, {0,3,7,11,2,5}, {0,3,6,11,2}, {0,4,8,10,3}, {0,3,7,9,2,5}, {0,4,7,11,2,9}, {0,5,7,10,2,9}, {0,3,7,11,2}, {0,3,6,10,9}, {0,3,7,8,10,2}, {0,4,8,10,3}, {0,5,7,2}, {0,3,8,10,5}, {0,5,7,10,1,6}, {0,3,7,9,2,6}, {0,4,8,11,2}, {0,4,7,11,2,6,9}, {0,4,7,8,11}, {0,4,7,11}, {0,4,6,11}, {0,3,7,9,11,2}, {0,3,8,10}, {0,4,7,11,2}, {0,4,6,8}, {0,4,7,10,3,5}, {0,4,7,11,2}, {0,4,7,11,3}, {0,4,8}, {0,3,7,10,2}, {0,3,7,1}, {0,3,7,2}, {0,5,10}, {0,3,6,9,2}, {0,3,6,9}, {0,7,10,2,6,9}, {0,3,7,9,5}, {0,4,7,9,11,2}, {0,4,7,9,2,6}, {0,3,7,9,2}, {0,4,6,10,3}, {0,4,7,10,1,6,8}, {0,4,7,10,1,5}, {0,3,8,11}, {0,4,7,2,8}, {0,4,8,10}, {0,3,5,7,10}, {0,3,4,7}, {0,5,8,10,1}, {0,3,7,2}, {0,4,6,8,10,1}, {0,3,6,10,2,5}, {0,3,7,8,10,2,5}, {0,3,7,10,1,5}, {0,4,7,11,1}, {0,3,6,9,2,5}, {0,4,7,10,1,6}, {0,3,10,2,5}, {0,4,7,9,3,6}, {0,7,9,2}, {0,4,10,2}, {0,4,7,9,11}, {0,7,11,2}, {0,3,7,8,10}, {0,3,6,10}, {0,5,8,10,1}, {0,3,6,10,2}, {0,3,7,10,6}, {0,3,7,10,5}, {0,3,7,8,2}, {0,4,7,3,8}, {0,3,7,10,2,9}, {0,3,7,1}, {0,4,7,10}, {0,4,6,2,8}, {0,4,7,10,3,6,9}, {0,5,7,10,1}, {0,3,6,10,1}, {0,3,8}, {0,3,7,2,5}, {0,4,6,2}, {0,3,7,9,11}, {0,4,7,9,11,2,6}, {0,4,7,10}, {0,5,7,2}, {0,4,7,10,9}, {0,3,8,10,2}, {0,4,8,10,2,6}, {0,4,7,9,6}, {0,4,6,10,1,6,8}, {0,4,8,10,1}, {0,4,7,2,6}, {0,2,4,7}, {0,4,6}, {0,4,7,10,5}, {0,5}, {0,2,5}, {0,4,7,10,1,8,9}, {0,5,7}, {0,7}, {0,2,7}, {0,3,7,11}, {0,4,8,10,1,6}, {0,7,11}, {0,4,7,10}, {0,3,5,7}, {0,5,7,10,2,8}, {0,4,7,11,5}, {0,3,10}, {0,3,7,10,2,5}, {0,3,7,10,2,6}, {0,4,8,10,3,6,9}, {0,3,6,11}, {0,4,7,11,2,9}, {0,3,7,10,2,5,9}, {0,4,6,8,10}, {0,3,7,10,2,5}, {0,5,7,10}, {0,3,7,10,2}, {0,4,9,11,2}, {0,3,7,8,2}, {0,3,7,9}, {0,3,7,10}, {0,7,10}, {0,2,3,7}, {0,4,7,5}, {0,4,10}, {0,4,7,10,3,6}, {0,4,7,10,1,5}, {0,5,7,10}, {0,3,7,9,5}, {0,3,6,11}, {0,3,10,5}, {0,4,7,1,6}, {0,4,8,1}, {0,4,8,10,1,5}, {0,3,7,11}, {0,3,7,10,8}, {0,4,7,2}, {0,7,2}, {0,4,6,8,10}, {0,4,7,10,3,9}, {0,3,7,9,11}, {0,5,7,10,1,8}, {0,4,7,10,2,8}, {0,4,7,10}, {0,3,6,8,10}, {0,3,7,2}, {0,4,7,10,2,6,9}, {0,4,8,2}, {0,5,7,11}, {0,3,6}, {0,4,8,2}, {0,1,3,6,10}, {0,6,10,2}, {0,3,6,11,8}, {0,5,7,2,9}, {0,3,6,8}, {0,3,6,11}, {0,3,7,10,5,9}, {0,4,7,10,2,6}, {0,5,7,10,2}, {0,4,7,10,1,6,9}, {0,4,7,10,1,5}, {0,4,8,10,1}, {0,4,6,10,2}, {0,7,10,2,6}, {0,4,6,10,2,9}, {0,4,6,10,1,6,9}, {0,3,7,10,11}, {0,4,7,10}, {0,4,6,8,11}, {0,5,7,1}, {0,7,6}, {0,4,7,10,2,6,8}, {0,3,7,9,2}, {0,3,8,10,2,5}, {0,5,7,10,3}, {0,4,6,7,11}, {0,4,8,10,2,6}, {0,4,8,11}, {0,4,7,1}, {0,3,7,10,2,8}, {0,4,7,10,2,6}, {0,3,7,10,11}, {0,3,6,10,2,8}, {0,4,8}, {0,3,6,10,0}};

set<unsigned> PCS(Chord c) {
    if(!c.nc) {
        return PCS_table[c.h];
    } else {
        return {0};
    }
}

set<unsigned> inter(set<unsigned> s1, set<unsigned> s2) {
    set<unsigned> res;
    for(auto x : s1) {
        if(s2.find(x)!=s2.end()) {
            res.insert(x);
        }
    }
    return res;
}

bool similarF1_aux(set<unsigned> s1, set<unsigned> s2, double threshold) {
    double F1 = (2*(double)inter(s1,s2).size())/((double)(s1.size()+s2.size()));
    if (F1 > threshold) {
        return true;
    } else {
        return false;
    }
}

set<unsigned> reduce_PCS_table(vector<vector<unsigned> > rotation_table) {
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

vector<vector<unsigned> > rot_table(set<unsigned> s) {
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

bool similar(Chord c1, Chord c2, unsigned metric, double threshold) {
    if(metric==0) {
        return (c1==c2);
    } else if(metric==1) {
        return similarF1_aux(PCS(c1), PCS(c2), threshold);
    } else if(metric==2) {
        return(PCS_prime(PCS(c1))==PCS_prime(PCS(c2)));
    }
    exit(-1);
}

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

vector<vector<Chord> > print_dictionary_sim(vector<tuple<unsigned, unsigned, Chord> > dico, unsigned l_buf, unsigned l_prev) {
    vector<Chord> reconstruction;
    vector<vector<Chord> > res;
    unsigned res_index=-1;

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

//cout << reconstruction << endl << endl;
FOR(i,res.size()) {
cout << res[i] << endl; }

    return res;
}

vector<pair<vector<Chord>, unsigned> > allSequences_sim(vector<Chord> input, unsigned occ_thres, unsigned metric, double threshold) {
    map<unsigned, unsigned> res_aux; // beginning, length

    for (unsigned i=1; i<input.size(); i++) {
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
                    unsigned key = begin*input.size() + length;
                    if(res_aux.find(key)==res_aux.end()) {
                        res_aux[key]=2;
                    } else {
                        res_aux[key]++;
                    }
                    in_sequence=false;
                }
            }
        }
        if(in_sequence) {
            unsigned key = begin*input.size() + length;
            if(res_aux.find(key)==res_aux.end()) {
                res_aux[key]=2;
            } else {
                res_aux[key]++;
            }
        }
    }

    vector<pair<vector<Chord>, unsigned> > res;
    for (auto &it : res_aux) {
        if (it.second >= occ_thres) {
            vector<Chord> v;
            unsigned begin = it.first/input.size();
            unsigned length = it.first % input.size();
            for(unsigned i=begin; i<begin+length; i++) {
                v.push_back(input[i]);
            }
            res.push_back(make_pair(v,it.second));
        }
    }

    return res;
}



int main_test(int argc, char** argv) {
    set<unsigned> PCS[313];
    ifstream data("LSDBChords.txt");
    string line;

    FOR(i,313) {
        getline(data,line);
        unsigned j=0;
        while(1) {
            string s = "";
            s += line[j];
            s += line[j+1];
            PCS[i].insert((unsigned)stoi(s));
            if (line[j+2]==';') {
                break;
            } else {
                j+=3;
            }
        }
    }

    ofstream F1half("F1half.txt");
    ofstream F1ninth("F1ninth.txt");
    unsigned counthalf=0, countninth=0;
    FOR(i,12) {
cout << i << endl;
        FOR(j,313) {
            FOR(k,12) {
                FOR(l,313) {
                    set<unsigned> s1, s2;
                    for(auto x : PCS[j]) {
                        s1.insert(x+i);
                    }
                    for(auto x : PCS[l]) {
                        s2.insert(x+k);
                    }
                    if(similarF1_aux(s1,s2,0.5)) {
                        F1half << 1;
                        if((i!=k)||(j!=l)) {
                            counthalf++;
                        }
                    } else {
                        F1half << 0;
                    }
                    if(similarF1_aux(s1,s2,0.9)) {
                        F1ninth << 1;
                        if((i!=k)||(j!=l)) {
                            countninth++;
                        }
                    } else {
                        F1ninth << 0;
                    }
                }
            }
        }
    }
    cout << "Count 1/2 : " << counthalf << endl;
    cout << "Count 9/10 : " << countninth << endl;
    F1half.close();
    F1ninth.close();

    return 0;
}




