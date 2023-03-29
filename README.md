# CMSC701_HW2

Name: Elliot Huang 

GitHub repo: https://github.com/DDXPP/CMSC701_HW2

## References

- Lecture slides on "[Bitvector Rank, Select, and Access](https://rob-p.github.io/CMSC701_S23/static_files/presentations/CMSC701_S23_7.pdf)" and "[Succinct Rank & Select](https://rob-p.github.io/CMSC701_S23/static_files/presentations/CMSC701_S23_8.pdf)"

- [Standard C++ library reference](https://en.cppreference.com/w/cpp/numeric/popcount) 

- [SDSL](https://github.com/simongog/sdsl-lite) - Succinct Data Structure Library
- [Stack Overflow]( https://stackoverflow.com/questions/12372531/reading-and-writing-a-stdvector-into-a-file-correctly) for miscellaneous issues



## Getting Started

- This homework uses SDSL's  `bit_vector` for bit vector creation, so please download and install SDSL using the following commands.

  ```sh
  git clone https://github.com/simongog/sdsl-lite.git
  cd sdsl-lite
  ./install.sh
  ```

- The three `*.cpp` files under `./src/` are my implementations for the three programming tasks. 

- The three `main_[***].cpp` files in the project root directory are the test codes for each part of this homework. 

  - The test codes will output the data needed for plots and writeup. 



## Part 1 - Rank

As mentioned above, this implementation uses SDSL's `bit_vector()` for bit vector operation. After installing SDSL, you can build the test code `main_rank.cpp`  with the following command.

```
g++ -std=c++17 -O3 -DNDEBUG -I ~/include -L ~/lib main_rank.cpp -o run_1_rank -lsdsl -ldivsufsort -ldivsufsort64    
```

The above commmand will build the code and create a executable file `run_1_rank` in the project root directory. To run it, use the command below.

```
./run_1_rank
```

The output contains the time required to compute $20$ rank operations in bit vectors of size $2^{10}, 2^{12}, 2^{14}, 2^{16}, 2^{18}, 2^{20}, 2^{22}$, as well as the return values of the `overhead()` function.

 

## Part 2 - Select

Build the test code `main_select.cpp`  with the following command.

```
g++ -std=c++17 -O3 -DNDEBUG -I ~/include -L ~/lib main_select.cpp -o run_2_select -lsdsl -ldivsufsort -ldivsufsort64    
```

The above commmand will build the code and create a executable file `run_2_select` in the project root directory. To run it, use the command below.

```
./run_2_select
```

The output contains the time required to compute $20$ select operations in bit vectors of size $2^{10}, 2^{12}, 2^{14}, 2^{16}, 2^{18}, 2^{20}, 2^{22}$, as well as the return values of the `overhead()` function.



## Part 3 - Sparse Array

Build the test code `main_sparse_array.cpp`  with the following command.

```
g++ -std=c++17 -O3 -DNDEBUG -I ~/include -L ~/lib main_sparse_array.cpp -o run_3_sparse_array -lsdsl -ldivsufsort -ldivsufsort64    
```

The above commmand will build the code and create a executable file `run_3_sparse_array` in the project root directory. To run it, use the command below.

```
./run_3_sparse_array
```

The output contains the time required to run `get_at_rank()`, `get_at_index()`, `get_index_of()`, and `num_elem_at()` functions respectively on sparse arrays of size $2^{10}, 2^{14}, 2^{18}, 2^{22}$ and of sparsity $5$%. The output also contains of the time required to run the same four functions on sparse arrays of size $2^{18}$ with different sparsities (e.g., $1$%, $5$%, and $10$%).




