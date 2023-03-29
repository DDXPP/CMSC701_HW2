#include <iostream>
#include <memory>
#include <fstream>
#include <chrono>
#include <array>
#include <cmath>
#include <bit>
#include <bitset>
#include <cstdint>

#include <sdsl/bit_vectors.hpp>

#include "rank_support_new.cpp"

using namespace std;
using namespace sdsl;

class select_support_new {
    public:
    rank_support_new *r;

    select_support_new(rank_support_new *r) {
        this->r = r;
    }

    // Returns the position, in the underlying bit-vector, of the FIRST index, j for which rank1(j) = 1.
    uint64_t select1(uint64_t i) {
        int left_bound = 0, right_bound = r->bit_vector_size - 1;

        // If rank(n/2) > i, 
        //      then the ith 1-bit is in B[1..n/2] 
        //      Otherwise in B[n/2+1..n]
        while (left_bound < right_bound) {
            int mid_index = floor((float)(left_bound + right_bound) / 2);
            uint64_t rank_mid_index = r->rank1(mid_index);
 
            if (rank_mid_index > i) {
                right_bound = mid_index;
            }
            else if (rank_mid_index < i) {
                left_bound = mid_index;
            }
            else { // rank_mid_index == i
                if ((*(r->b))[mid_index] == 1) {
                    return mid_index;
                }
                else {
                    if (mid_index + 1 == right_bound) {
                        if ((*(r->b))[right_bound] == 1) {
                            return right_bound;
                        }
                        else {
                            return 0;
                        }
                    }
                    left_bound = mid_index;
                }
            }
            
        }
        return 0;
    }

    // Returns the size of the select data structure (in bits) that is required to support log-time select on the current bitvector (how does this relate to the size of the rank data structure built above).
    uint64_t overhead() {
        return r->overhead();
    }

    // Saves the select data structure for this bit vector to the file fname (your bit vector should also have a save() function).
    void save(string& fname) {
        return r->save(fname);
    }


    // Loads the select data structure for this bit vector from the file fname (your bit vector should also have a load() function)
    void load(string& fname) {
        return r->load(fname);
    }

};