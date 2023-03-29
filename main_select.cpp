// #include "src/rank_support_new.cpp"
#include "src/select_support_new.cpp"

bit_vector generate_random_bit_vector(int n) {
    bit_vector b(n);
    int count = 0;

    while (count < (n/2)) {
        count = 0;
        for (int i = 0; i < n; i++) {
            b[i] = rand() % 2;
            if (b[i] == 1) {
                count++;
            }
            // cout << b[i] <<",";
        }
    }

    return b;
}

int main() {
    vector<bit_vector> bit_vector_array;
    vector<vector<int>> random_indexes_array;

    for (int i = 10; i<24; i+=2) {
        bit_vector b_test = generate_random_bit_vector(pow(2, i));
        // bit_vector b_test = bit_vector(pow(2, i), 1);
        bit_vector_array.push_back(b_test);

        vector<int> random_indexes;
        for (int j = 0; j < 20; j++) {
            random_indexes.push_back(rand() % (i/2-1));
        }
        random_indexes_array.push_back(random_indexes);
    }

    for (int i = 0; i < bit_vector_array.size(); i++) {
        bit_vector b_test = bit_vector_array[i];
        rank_support_new r(&b_test);
        select_support_new s(&r);
        vector<int> random_indexes = random_indexes_array[i];

        auto clock_start = chrono::high_resolution_clock::now();

        for (int k = 0; k < random_indexes.size(); k++) {
            s.select1(random_indexes[k]);
        }
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "Time to compute 20 select operations for size " << b_test.size() << ": " << clock_duration_nanoseconds.count() << " ns\n";
    }

    for (int i = 0; i < bit_vector_array.size(); i++) {
        bit_vector b_test = bit_vector_array[i];
        rank_support_new r(&b_test);
        select_support_new s(&r);
        cout << "overhead for size " << b_test.size() << ": " << s.overhead() << endl;
    }

    return 0;
}
