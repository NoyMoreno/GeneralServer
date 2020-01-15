//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_ISEARCHABLE_H
#define PROJECT2_ISEARCHABLE_H

#include "State.h"
#include <vector>

template<typename T, typename  C>
class ISearchable {
    //get initial state
    virtual State<T, C> *getInitialState() = 0;
    // the end
    virtual bool isGoalState(State <T, C> *state) = 0;
    //פונקציית המעברים
    virtual std::vector<State<T, C>*> getAllPossibleStates(State<T, C> *state) = 0;
    virtual ~ISearchable();
};
#endif //PROJECT2_ISEARCHABLE_H
