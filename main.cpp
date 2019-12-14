#include <Binomial_Heap.h>
#include <Leftist_Heap.h>
#include <Skew_Heap.h>

#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <deque>

const unsigned int MAX_HEAPS = 100;
const unsigned int MAX_OPERATIONS = 1e5;
const unsigned int MAX_KEY = 1000;

int gen_number(int from, int to){
    return from + std::rand() % (to - from);
}

template <typename Heap_Type>
void my_random_test(Heap_Type* Heaps) {
    std::vector<int>Heap_Elements_Quantity(MAX_HEAPS, 0);
    std::vector<std::vector<int>>Ideal_Heaps(MAX_HEAPS);
    int operation_key;
    int heap_id;
    for(int i = 0; i < MAX_OPERATIONS; ++i){
        operation_key = gen_number(0, 4);
        heap_id = gen_number(0, MAX_HEAPS);
        if(operation_key == 0){
            int key = gen_number(0, MAX_KEY);
//            std::cout <<"A["<< heap_id << "].insert("  << key << ");\n";
            Heaps[heap_id].insert(key);
            Ideal_Heaps[heap_id].push_back(key);
            std::push_heap(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[heap_id].end(), std::greater<int>());
            ++Heap_Elements_Quantity[heap_id];
        }else if(operation_key == 1){
            int another_head_id = gen_number(0, MAX_HEAPS);
            if(heap_id != another_head_id){
//                std::cout<<"A[" << heap_id << "].meld(A["<< another_head_id << "]);\n";
                Heaps[heap_id].meld(Heaps[another_head_id]);
                Ideal_Heaps[heap_id].insert(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[another_head_id].begin(), Ideal_Heaps[another_head_id].end());
                std::make_heap(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[heap_id].end(), std::greater<int>());
                Heap_Elements_Quantity[heap_id] += Heap_Elements_Quantity[another_head_id];

                Ideal_Heaps[another_head_id].clear();
                Heap_Elements_Quantity[another_head_id] = 0;
            }
        }else if(operation_key == 2){
            if(Heap_Elements_Quantity[heap_id] >= 1){
//                std::cout << "A[" << heap_id << "].get_min();" << "\n";
                ASSERT_EQ(Heaps[heap_id].get_min(), Ideal_Heaps[heap_id].front());
            }
        }else if(operation_key == 3){
            if(Heap_Elements_Quantity[heap_id] >= 1){
//                std::cout << "A[" << heap_id << "].extract_min();" << "\n";
                Heaps[heap_id].extract_min();
                std::pop_heap(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[heap_id].end(), std::greater<int>());
                Ideal_Heaps[heap_id].pop_back();
                --Heap_Elements_Quantity[heap_id];
            }
        }
    }
}

TEST(Bin_Heap, Insertion){
    Binomial_Heap A;
    A.insert(5);
    A.insert(1);
    A.insert(3);
    ASSERT_EQ(A.get_min(), 1);
}

TEST(Bin_Heap, Execution){
    Binomial_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(3);
    A.insert(1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 3);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

TEST(Bin_Heap, Equals){
    Binomial_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
    ASSERT_EQ(A.get_min(), 1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

TEST(Bin_Heap, Merge){
    Binomial_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
    Binomial_Heap B;
    B.insert(5);
    B.insert(7);
    B.insert(5);
    B.insert(4);
    B.insert(7);
    B.insert(4);
    B.insert(1);
    B.insert(5);
    ASSERT_EQ(A.get_min(), 1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
    A.meld(B);
    ASSERT_EQ(A.get_min(), 1);
    Binomial_Heap C;
    A.meld(C);
}

TEST(Bin_Heap, Random_Tests){
    std::srand(unsigned(std::time(0)));
    Binomial_Heap* A = new Binomial_Heap[MAX_HEAPS];
    my_random_test(A);
    delete [] A;
}

TEST(Bin_Heap, test1){
    Binomial_Heap A;
    A.insert(9);
    A.extract_min();
    A.insert(3);
    A.extract_min();
    A.insert(4);
    A.insert(1);
    A.get_min();
    A.extract_min();
    A.insert(0);
    A.insert(5);
    A.extract_min();
    A.insert(9);
    ASSERT_EQ(4,A.get_min());
}

TEST(Leftist_Heap, Insertion){
    Leftist_Heap A;
    A.insert(5);
    A.insert(1);
    A.insert(3);
    ASSERT_EQ(A.get_min(), 1);
}

TEST(Leftist_Heap, Execution){
    Leftist_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(3);
    A.insert(1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 3);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

TEST(Leftist_Heap, Equals){
    Leftist_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
    ASSERT_EQ(A.get_min(), 1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

TEST(Leftist_Heap, Merge){
    Leftist_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
    Leftist_Heap B;
    B.insert(5);
    B.insert(7);
    B.insert(5);
    B.insert(4);
    B.insert(7);
    B.insert(4);
    B.insert(1);
    B.insert(5);
    ASSERT_EQ(A.get_min(), 1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
    A.meld(B);
    ASSERT_EQ(A.get_min(), 1);
    Leftist_Heap C;
    A.meld(C);
}

TEST(Leftist_Heap, Random_Tests){
    std::srand(unsigned(std::time(0)));
    Leftist_Heap* A = new Leftist_Heap[MAX_HEAPS];
    my_random_test(A);
    delete [] A;
}

TEST(Skew_Heap, Insertion){
    Skew_Heap A;
    A.insert(5);
    A.insert(1);
    A.insert(3);
    ASSERT_EQ(A.get_min(), 1);
}

TEST(Skew_Heap, Execution){
    Skew_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(3);
    A.insert(1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 3);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

TEST(Skew_Heap, Equals){
    Skew_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
    ASSERT_EQ(A.get_min(), 1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

TEST(Skew_Heap, Merge){
    Skew_Heap A;
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
    Skew_Heap B;
    B.insert(5);
    B.insert(7);
    B.insert(5);
    B.insert(4);
    B.insert(7);
    B.insert(4);
    B.insert(1);
    B.insert(5);
    ASSERT_EQ(A.get_min(), 1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 4);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
    A.meld(B);
    ASSERT_EQ(A.get_min(), 1);
    Skew_Heap C;
    A.meld(C);
}

TEST(Skew_Heap, Random_Tests){
    std::srand(unsigned(std::time(0)));
    Skew_Heap* A = new Skew_Heap[MAX_HEAPS];
    my_random_test(A);
    delete [] A;
}