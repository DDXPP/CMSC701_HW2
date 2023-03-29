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

// #include "rank_support_new.cpp"
#include "select_support_new.cpp"


using namespace std;
using namespace sdsl;

class sparse_array {
    public:
    bit_vector *b;
    rank_support_new *rr;
    select_support_new *ss;
    vector<string> elements;

    void create(uint64_t size) {
        b = new bit_vector(size);
        // r = new rank_support_new(b);
        // s = new select_support_new(r);
    }

    void append(string elem, uint64_t pos) {
        if (pos < b->size()) {
            elements.push_back(elem);
            (*b)[pos] = 1;
        }
    }

    void finalize() {
        rr = new rank_support_new(b);
        ss = new select_support_new(rr);
    }

    bool get_at_rank(uint64_t r, std::string& elem) {
        if (r < elements.size()) {
            elem = elements[r];
            return true;
        }
        return false;
    }

    bool get_at_index(uint64_t r, std::string& elem) {
        if (r < b->size() && (*b)[r] == 1) {
            int pos = rr->rank1(r);
            elem = elements[pos];
            return true;
        }
        return false;
    }

    uint64_t get_index_of(uint64_t r) {
        if (r >= elements.size()) {
            return numeric_limits<uint64_t>::max();
        }
        else {
            int index = ss->select1(r);
            return index;
        }
    }

    uint64_t num_elem_at(uint64_t r) {
        return rr->rank1(r) + ((*b)[r] == 1 ? 1 : 0);
    }

    uint64_t size() {
        return b->size();
    }

    uint64_t num_elem() {
        return elements.size();
    }

    void save(string& fname) {
        ofstream output_file;
        output_file.open(fname, ios::out | ios::binary);

        b->serialize(output_file);

        int elements_size = elements.size();
        output_file.write(reinterpret_cast<const char *>(&elements_size), sizeof(elements_size));
        
        for (int i = 0; i < elements_size; i++) {
            output_file << elements[i] << endl;
        }

        output_file.close();
    }

    void load(string& fname) {
        ifstream input_file;
        input_file.open(fname, ios::in);

        b->load(input_file);

        int elements_size;
        input_file.read((char *)(&elements_size), sizeof(elements_size));

        string elem;
        elements.clear();
        elements.resize(elements_size);
        while (getline(input_file, elem)) {
            elements.push_back(elem);
        }

        input_file.close();
        finalize();
    } 
};