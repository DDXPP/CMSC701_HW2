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

using namespace std;
using namespace sdsl;

class rank_support_new {
    public: 
    bit_vector* b;

    int bit_vector_size;
    int chunk_length;
    int chunk_count;

    int each_sub_chunk_length;
    int each_sub_chunk_count;

    vector<int> chunk_rank;
    vector<int> sub_chunk_rank;

    rank_support_new(bit_vector* b) {
        bit_vector_size = b->size();
        
        chunk_length = pow(log2(bit_vector_size), 2);
        chunk_count = bit_vector_size/chunk_length;

        each_sub_chunk_length = log2(bit_vector_size)/2;
        each_sub_chunk_count = 2 * log2(bit_vector_size);

        int temp_chunk_cumulative_rank = 0;
        int temp_sub_chunk_relative_rank = 0;

        for (int i = 0; i < bit_vector_size; i++) {
            if (i % chunk_length == 0) {
                chunk_rank.push_back(temp_chunk_cumulative_rank);
                temp_sub_chunk_relative_rank = 0;
            }

            if (i % each_sub_chunk_length == 0) {
                sub_chunk_rank.push_back(temp_sub_chunk_relative_rank);
            }

            if ((*b)[i] == 1) {
                temp_chunk_cumulative_rank++;
                temp_sub_chunk_relative_rank++;
            }
        }
        this->b = b;
    }

    // Returns the number of 1s in the underlying bit-vector up to position i (exclusive).
    uint64_t rank1(uint64_t i) {
        int chunk_cumulative_rank = chunk_rank[floor(i/chunk_length)];
        // cout << "chunk_cumulative_rank " << chunk_cumulative_rank<< endl;

        int sub_chunk_relative_cumulative_rank = sub_chunk_rank[floor(i/chunk_length) * each_sub_chunk_count + floor((i % chunk_length)/each_sub_chunk_length)];
        // cout << "sub_chunk_relative_cumulative_rank " << sub_chunk_relative_cumulative_rank<< endl;

        int within_sub_chunk_start_index = (floor(i/chunk_length) * each_sub_chunk_count + floor((i % chunk_length)/each_sub_chunk_length)) * each_sub_chunk_length; 
        // cout << "within_sub_chunk_start_index " << within_sub_chunk_start_index<< endl;
        
        int within_sub_chunk_length = i - within_sub_chunk_start_index;
        // cout << "within_sub_chunk_length " << within_sub_chunk_length << endl;

        int rank_within_sub_chunk = __popcount(b->get_int(within_sub_chunk_start_index, within_sub_chunk_length));
        // cout << "get_int_within " << b->get_int(within_sub_chunk_start_index, within_sub_chunk_length) << endl;

        return chunk_cumulative_rank + sub_chunk_relative_cumulative_rank + rank_within_sub_chunk;
    }



    // Returns the size of the rank data structure (in bits) that is required to support constant-time rank on the current bitvector.
    uint64_t overhead() {
        // each int takes 4 bytes or 32 bits in C++
        return 32 * (chunk_rank.size() + sub_chunk_rank.size() + 5);
    }



    // Saves the rank data structure for this bit vector to the file fname (your bit vector should also have a save() function).
    void save(string& fname) {
        ofstream output_file;
        output_file.open(fname, ios::out | ios::binary);

        b->serialize(output_file);

        int chunk_rank_size = chunk_rank.size();
        output_file.write(reinterpret_cast<const char *>(&chunk_rank_size), sizeof(chunk_rank_size));
        output_file.write(reinterpret_cast<const char *>(&chunk_rank[0]), chunk_rank_size * sizeof(int));

        int sub_chunk_rank_size = sub_chunk_rank.size();
        output_file.write(reinterpret_cast<const char *>(&sub_chunk_rank_size), sizeof(sub_chunk_rank_size));
        output_file.write(reinterpret_cast<const char *>(&sub_chunk_rank[0]), sub_chunk_rank_size * sizeof(int));

        // output_file.write(reinterpret_cast<const char *>(&chunk_length), sizeof(chunk_length));
        // output_file.write(reinterpret_cast<const char *>(&chunk_count), sizeof(chunk_count));
        // output_file.write(reinterpret_cast<const char *>(&each_sub_chunk_length), sizeof(each_sub_chunk_length));
        // output_file.write(reinterpret_cast<const char *>(&each_sub_chunk_count), sizeof(each_sub_chunk_count));

        output_file.close();
    }


    // Loads the rank data structure for this bit vector from the file fname (your bit vector should also have a load() function).
    void load(string& fname) {
        ifstream input_file;
        input_file.open(fname, ios::in);

        b->load(input_file);

        int chunk_rank_size;
        input_file.read((char *)(&chunk_rank_size), sizeof(chunk_rank_size));
        chunk_rank.clear();
        chunk_rank.resize(chunk_rank_size);
        input_file.read((char *)(&chunk_rank[0]), chunk_rank_size * sizeof(int));


        int sub_chunk_rank_size;
        input_file.read((char *)(&sub_chunk_rank_size), sizeof(sub_chunk_rank_size));
        sub_chunk_rank.clear();
        sub_chunk_rank.resize(sub_chunk_rank_size);
        input_file.read((char *)(&sub_chunk_rank[0]), sub_chunk_rank_size * sizeof(int));

        // input_file.read((char *)(&chunk_length), sizeof(chunk_length));
        // input_file.read((char *)(&chunk_count), sizeof(chunk_count));
        // input_file.read((char *)(&each_sub_chunk_length), sizeof(each_sub_chunk_length));
        // input_file.read((char *)(&each_sub_chunk_count), sizeof(each_sub_chunk_count));
        
        bit_vector_size = b->size();
        
        chunk_length = pow(log2(bit_vector_size), 2);
        chunk_count = bit_vector_size/chunk_length;

        each_sub_chunk_length = log2(bit_vector_size)/2;
        each_sub_chunk_count = 2 * log2(bit_vector_size);

        input_file.close();
    }
};



