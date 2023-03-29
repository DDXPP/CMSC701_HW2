#include "src/rank_support_new.cpp"
// #include "src/select_support_new.cpp"

bit_vector generate_random_bit_vector(int n) {
    bit_vector b(n);

    for (int i = 0; i < n; i++) {
        b[i] = rand() % 2;
    }

    return b;

}

int main() {
    vector<bit_vector> bit_vector_array;
    vector<vector<int>> random_indexes_array;

    for (int i = 10; i<24; i+=2) {
        bit_vector b_test = generate_random_bit_vector(pow(2, i));
        bit_vector_array.push_back(b_test);

        vector<int> random_indexes;
        int size = pow(2, i);
        for (int j = 0; j < 20; j++) {
            random_indexes.push_back(rand() % size);
        }
        random_indexes_array.push_back(random_indexes);
    }
    

    for (int i = 0; i < bit_vector_array.size(); i++) {
        bit_vector b_test = bit_vector_array[i];
        rank_support_new r(&b_test);
        vector<int> random_indexes = random_indexes_array[i];

        auto clock_start = chrono::high_resolution_clock::now();

        for (int k = 0; k < random_indexes.size(); k++) {
            r.rank1(random_indexes[k]);
        }
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "Time to compute 20 ranks for size " << b_test.size() << ": " << clock_duration_nanoseconds.count() << " ns\n";
    }

    for (int i = 0; i < bit_vector_array.size(); i++) {
        bit_vector b_test = bit_vector_array[i];
        rank_support_new r(&b_test);
        cout << "overhead for size " << b_test.size() << ": " << r.overhead() << endl;
    }

    // for (int i = 100; i<100000001; i*=10) {
    //     bit_vector b_test = generate_random_bit_vector(i);
    //     rank_support_new r(&b_test);

    //     vector<int> random_indexes;
    //     for (int j = 0; j < 20; j++) {
    //         random_indexes.push_back(rand() % i);
    //     }

    //     auto clock_start = chrono::high_resolution_clock::now();

    //     for (int k = 0; k < 20; k++) {
    //         r.rank1(random_indexes[k]);
    //     }
        
    //     auto clock_end = chrono::high_resolution_clock::now();
    //     chrono::duration<double> clock_duration = clock_end - clock_start;
    //     chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
    //     cout << "Time to compute 20 ranks for size " << i << ": " << clock_duration_nanoseconds.count() << " ns\n";
    // }

    // for (int i = 100; i<100000001; i*=10) {
    //     bit_vector b_test = generate_random_bit_vector(i);
    //     rank_support_new r(&b_test);
    //     cout << "overhead for size " << i << ": " << r.overhead() << endl;
    // }

    // return 0;
}

