//
// Created by noy on ١٤‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_MYPRIORITYQUEUE_H
#define PROJECT2_MYPRIORITYQUEUE_H

#include "State.h"
#include <queue>
#include <algorithm>
#include <iostream>
template <typename T, typename C>
struct Compare {
    bool operator()(State<T,C> first, State<T,C> second) {
        return first < second;
    }
};

//std::priority_queue is basically a thin layer on top of the heap algorithms.
template <typename T, typename C>
class MyPriorityQueue : public std::priority_queue<State<T,C>> {//, std::vector<State<T,C>>, Compare<T,C>
public:
    MyPriorityQueue() {}
    void remove(State<T,C> stateToDel) {
        // find it
        auto it = std::find(this->c.begin(), this->c.end(), stateToDel);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }
    }
    State<T, C> find(State<T,C> state, bool *fFound){
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first == state) {
                *fFound = true;
                return *first;
            }
            ++first;
        }
        return state;
    }
};

#endif //PROJECT2_MYPRIORITYQUEUE_H
