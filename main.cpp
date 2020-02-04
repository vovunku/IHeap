#include <Binomial_Heap.h>
#include <Leftist_Heap.h>
#include <Skew_Heap.h>
#include <Proto_Oblique.h>

#include <gtest/gtest.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <math.h>
#include <deque>

const unsigned int MAX_HEAPS = 100;
const unsigned int MAX_OPERATIONS = 1e3;
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
            Heaps[heap_id].insert(key);
            Ideal_Heaps[heap_id].push_back(key);
            std::push_heap(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[heap_id].end(), std::greater<int>());
            ++Heap_Elements_Quantity[heap_id];
        }else if(operation_key == 1){
            int another_head_id = gen_number(0, MAX_HEAPS);
            if(heap_id != another_head_id){
                Heaps[heap_id].meld(Heaps[another_head_id]);
                Ideal_Heaps[heap_id].insert(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[another_head_id].begin(), Ideal_Heaps[another_head_id].end());
                std::make_heap(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[heap_id].end(), std::greater<int>());
                Heap_Elements_Quantity[heap_id] += Heap_Elements_Quantity[another_head_id];

                Ideal_Heaps[another_head_id].clear();
                Heap_Elements_Quantity[another_head_id] = 0;
            }
        }else if(operation_key == 2){
            if(Heap_Elements_Quantity[heap_id] >= 1){
                ASSERT_EQ(Heaps[heap_id].get_min(), Ideal_Heaps[heap_id].front());
            }
        }else if(operation_key == 3){
            if(Heap_Elements_Quantity[heap_id] >= 1){
                Heaps[heap_id].extract_min();
                std::pop_heap(Ideal_Heaps[heap_id].begin(), Ideal_Heaps[heap_id].end(), std::greater<int>());
                Ideal_Heaps[heap_id].pop_back();
                --Heap_Elements_Quantity[heap_id];
            }
        }
    }
}

template<typename Heap_Type>
void test1(Heap_Type& A){
    A.insert(5);
    A.insert(1);
    A.insert(3);
    ASSERT_EQ(A.get_min(), 1);
}

template<typename Heap_Type>
void test2(Heap_Type& A){
    A.insert(5);
    A.insert(7);
    A.insert(3);
    A.insert(1);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 3);
    A.extract_min();
    ASSERT_EQ(A.get_min(), 5);
}

template<typename Heap_Type>
void test3(Heap_Type& A){
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

template<typename Heap_Type>
void test4(Heap_Type& A, Heap_Type& B, Heap_Type& C){
    A.insert(5);
    A.insert(7);
    A.insert(5);
    A.insert(4);
    A.insert(7);
    A.insert(4);
    A.insert(1);
    A.insert(5);
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
    A.meld(C);
}

template<typename Heap_Type>
void capacity_test(Heap_Type& A){
    std::vector<int>Ideal_Heap;
    int key;
    for(int i = 0; i < MAX_OPERATIONS + 1; ++i){
        key = gen_number(0, MAX_KEY);
        Ideal_Heap.push_back(key);
        std::push_heap(Ideal_Heap.begin(), Ideal_Heap.end(), std::greater<int>());
        A.insert(key);
        ASSERT_EQ(Ideal_Heap.front(), A.get_min());
    }
    for(int i = 0; i < MAX_OPERATIONS; ++i){
        std::pop_heap(Ideal_Heap.begin(), Ideal_Heap.end(), std::greater<int>());
        Ideal_Heap.pop_back();
        A.extract_min();
        ASSERT_EQ(Ideal_Heap.front(), A.get_min());
    }
}

TEST(Bin_Heap, Insertion){
    Binomial_Heap A;
    test1(A);
}

TEST(Bin_Heap, Execution){
    Binomial_Heap A;
    test2(A);
}

TEST(Bin_Heap, Equals){
    Binomial_Heap A;
    test3(A);
}

TEST(Bin_Heap, Merge){
    Binomial_Heap A;
    Binomial_Heap B;
    Binomial_Heap C;
    test4(A, B, C);
}

TEST(Bin_Heap, Random_Tests){
    std::srand(unsigned(std::time(0)));
    Binomial_Heap* A = new Binomial_Heap[MAX_HEAPS];
    my_random_test(A);
    delete [] A;
}

TEST(Bin_Heap, capacity_test){
    Binomial_Heap A;
    std::srand(unsigned(std::time(0)));
    capacity_test(A);
}

TEST(Leftist_Heap, Insertion){
    Leftist_Heap A;
    test1(A);
}

TEST(Leftist_Heap, Execution){
    Leftist_Heap A;
    test2(A);
}

TEST(Leftist_Heap, Equals){
    Leftist_Heap A;
    test3(A);
}

TEST(Leftist_Heap, Merge){
    Leftist_Heap A;
    Leftist_Heap B;
    Leftist_Heap C;
    test4(A, B, C);
}

TEST(Leftist_Heap, Random_Tests){
    std::srand(unsigned(std::time(0)));
    Leftist_Heap* A = new Leftist_Heap[MAX_HEAPS];
    my_random_test(A);
    delete [] A;
}

TEST(Leftist_Heap, capacity_test){
    Leftist_Heap A;
    std::srand(unsigned(std::time(0)));
    capacity_test(A);
}

TEST(Skew_Heap, Insertion){
    Skew_Heap A;
    test1(A);
}

TEST(Skew_Heap, Execution){
    Skew_Heap A;
    test2(A);
}

TEST(Skew_Heap, Equals){
    Skew_Heap A;
    test3(A);
}

TEST(Skew_Heap, Merge){
    Skew_Heap A;
    Skew_Heap B;
    Skew_Heap C;
    test4(A, B, C);
}

TEST(Skew_Heap, Random_Tests){
    std::srand(unsigned(std::time(0)));
    Skew_Heap* A = new Skew_Heap[MAX_HEAPS];
    my_random_test(A);
    delete [] A;
}

TEST(Skew_Heap, capacity_test){
    Skew_Heap A;
    std::srand(unsigned(std::time(0)));
    capacity_test(A);
}
