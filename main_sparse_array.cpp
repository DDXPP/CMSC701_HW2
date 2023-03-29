// #include "src/rank_support_new.cpp"
#include "src/sparse_array.cpp"


int main() {
    sparse_array s_2_10;
    sparse_array s_2_14;
    sparse_array s_2_18;
    sparse_array s_2_22;

    s_2_10.create(pow(2, 10));
    s_2_14.create(pow(2, 14));
    s_2_18.create(pow(2, 18));
    s_2_22.create(pow(2, 22));

    vector<sparse_array> sparse_arrays = {s_2_10, s_2_14, s_2_18, s_2_22};
    
    for (int i = 0; i < sparse_arrays.size(); i++) {
        // Set every test sparse array's sparsity to 5% 
        // 1/0.05 = 20
        for (int j = 0; j < sparse_arrays[i].size(); j += 20) {
            sparse_arrays[i].append("test", j);
        }
        sparse_arrays[i].finalize();   
    }

    // get_at_rank()
    cout << "get_at_rank() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays.size(); i++) {
        string elem;
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays[i].get_at_rank(1, elem);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "get_at_rank(), sparsity: 5%, size: " << sparse_arrays[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    // get_at_index()
    cout << "get_at_index() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays.size(); i++) {
        string elem;
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays[i].get_at_index(sparse_arrays[i].size()/2, elem);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "get_at_index(), sparsity: 5%, size: " << sparse_arrays[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    // get_index_of()
    cout << "get_index_of() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays.size(); i++) {
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays[i].get_index_of(1);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "get_index_of(), sparsity: 5%, size: " << sparse_arrays[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    // num_elem_at()
    cout << "num_elem_at() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays.size(); i++) {
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays[i].num_elem_at(sparse_arrays[i].size()/2);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "num_elem_at(), sparsity: 5%, size: " << sparse_arrays[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }




















    
    cout << "testing different sparsity --------------------------------" << endl;
    sparse_array s_2_18_1;
    sparse_array s_2_18_5;
    sparse_array s_2_18_10;

    s_2_18_1.create(pow(2, 18));
    s_2_18_5.create(pow(2, 18));
    s_2_18_10.create(pow(2, 18));

    for (int j = 0; j < s_2_18_1.size(); j += 100) {
        s_2_18_1.append("test", j);
    }

    for (int j = 0; j < s_2_18_5.size(); j += 20) {
        s_2_18_5.append("test", j);
    }

    for (int j = 0; j < s_2_18_10.size(); j += 10) {
        s_2_18_10.append("test", j);
    }

    s_2_18_1.finalize();
    s_2_18_5.finalize();
    s_2_18_10.finalize();

    vector<sparse_array> sparse_arrays2 = {s_2_18_1, s_2_18_5, s_2_18_10};
    

    // get_at_rank()
    cout << "get_at_rank() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays2.size(); i++) {
        string elem;
        string sparsity = i == 0 ? "1%" : (i == 1 ? "5%" : "10%");
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays2[i].get_at_rank(1, elem);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "get_at_rank(), sparsity: " << sparsity << ", size: " << sparse_arrays2[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    // get_at_index()
    cout << "get_at_index() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays2.size(); i++) {
        string elem;
        string sparsity = i == 0 ? "1%" : (i == 1 ? "5%" : "10%");
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays2[i].get_at_index(sparse_arrays2[i].size()/2, elem);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "get_at_index(), sparsity: " << sparsity << ", size: " << sparse_arrays2[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    // get_index_of()
    cout << "get_index_of() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays2.size(); i++) {
        string sparsity = i == 0 ? "1%" : (i == 1 ? "5%" : "10%");
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays2[i].get_index_of(1);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "get_index_of(), sparsity: " << sparsity << ", size: " << sparse_arrays2[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    // num_elem_at()
    cout << "num_elem_at() --------------------------------" << endl;
    for (int i = 0; i < sparse_arrays2.size(); i++) {
        string sparsity = i == 0 ? "1%" : (i == 1 ? "5%" : "10%");
        auto clock_start = chrono::high_resolution_clock::now();

        sparse_arrays2[i].num_elem_at(sparse_arrays2[i].size()/2);
        
        auto clock_end = chrono::high_resolution_clock::now();
        chrono::duration<double> clock_duration = clock_end - clock_start;
        chrono::nanoseconds clock_duration_nanoseconds = chrono::duration_cast<chrono::nanoseconds>(clock_duration);
        cout << "num_elem_at(), sparsity: " << sparsity << ", size: " << sparse_arrays2[i].size() << ", time: " << clock_duration_nanoseconds.count() << " ns\n";
    }

    return 0;
}
