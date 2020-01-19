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
        return second < first;
    }
};

//std::priority_queue is basically a thin layer on top of the heap algorithms.
template <typename T, typename C>
class MyPriorityQueue : public std::priority_queue<State<T,C>, std::vector<State<T,C>>, Compare<T,C>> {//, std::vector<State<T,C>>, Compare<T,C>
public:
    MyPriorityQueue() {}
    void remove(State<T,C> stateToDel) {
        // find i
        auto it = this->c.begin();
        while (it != this->c.end()){
            if (*it == stateToDel) {
                this->c.erase(it);
                break;
            }
            else it++;
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
