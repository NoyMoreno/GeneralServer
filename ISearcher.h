//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//
#ifndef PROJECT2_SEARCHER_H
#define PROJECT2_SEARCHER_H


#include "ISearchable.h"
// T =
template <typename S, typename T, typename C>
class ISearcher {
public:
    // the search method
    virtual S search(ISearchable<T, C> searchable) = 0;
    // get how many nods were evaluated by the algorithm
    // האלגוריתם שהגיע למסלול הזול ביותר לאחק שעיבד כמות הכי מעטה של קןדקודים הוא הטוב ביותר
    virtual int getNumberOfNodesEvaluated() = 0;


};


#endif //PROJECT2_SEARCHER_H