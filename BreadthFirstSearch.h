//
// Created by noy on ١٤‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_BREADTHFIRSTSEARCH_H
#define PROJECT2_BREADTHFIRSTSEARCH_H

#include <set>
#include <iterator>
#include "cmake-build-debug/AbstractSearcher.h"
template<typename T,typename C>
class BreadthFirstSearch : public AbstractSearcher<T,C> {
    std::vector<State<T,C>*> search(ISearchable<T, C> *iSearchable)
    {
        this->openList.push(iSearchable->getInitialState());
        std::vector<State<T, C>*> closeSet;
        while (!this->openLis.empty())
        {
            State<T, C> *n = this->openList.pop();
            closeSet.insert(n);
            if (iSearchable->isGoalState(n))
            {
                return this->backtrace(closeSet, iSearchable->getInitialState());
            }
            // save the initial cost
            std::vector<State<T,C>> *saveCost;
            std::vector<State<T,C>> *successors = iSearchable>getAllPossibleStates(n);
            for(State<T,C> s: successors) {
                // if s isn't in close lust and s is not in openList.
                if (!this->openList.find(s) && findInVector(closeSet, s) == NULL){
                    saveCost->insert(s);
                    s.setCameFrom(n);
                    s.setCost(s.getC() + n->getC());
                    this->openList.insert(s);
                }
                //otherwise , if this new path is better then previous
                State<T,C>* copyS = findInVector(saveCost, s);
                if (s.getC() > copyS->getC() + n->getC()) {
                    // remove s from openList, update and push again
                    this->openList.remove(s);
                    s.setCost(copyS->getC() + n->getC());
                    this->openList.insert(s);
                }
            }
        }
    }
    State<T,C>* findInVector(State<T,C> state, std::vector<State<T,C>*> close)
    {
        typename std::vector<State<T,C>*>::iterator it;
        it = std::find (close.begin(), close.end(), state);
        if (it != close.end())
        {
            return *it;
        }
        else
            return NULL;
    }

};



#endif //PROJECT2_BREADTHFIRSTSEARCH_H
