//
// Created by noy on ١٤‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_ABSTRACTSEARCHER_H
#define PROJECT2_ABSTRACTSEARCHER_H

#include <algorithm>
#include "ISearcher.h"
#include "MyPriorityQueue.h"

template <typename T, typename C>
// my S- is vector of all the nods in shores path T-is T, S- is S ---> for me del after
class AbstractSearcher : public ISearcher<std::vector<State<T,C>>,T,C> {
public:
    AbstractSearcher() {
        evaluatedNodes = 0;
    }
    ~AbstractSearcher(){}
    int openListSize(){
        return queue.size();
    }
    int getNumberOfNodesEvaluated(){
        return evaluatedNodes;
    }
    virtual std::vector<State<T,C>> search(ISearchable<T, C> *) = 0;
    std::vector<State<T,C>> backtrace(State<T,C> goal, State<T,C> initState) {
        std::vector<State<T,C>> res;
        State<T,C> temp = goal;
        while (temp != initState) {
            res.push_back(temp);
            temp = temp.getCameFrom();
            //res.push_back(temp);
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
protected:
    MyPriorityQueue<T,C> queue;
    int evaluatedNodes;
};


#endif //PROJECT2_ABSTRACTSEARCHER_H
