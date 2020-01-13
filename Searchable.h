//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_SEARCHABLE_H
#define PROJECT2_SEARCHABLE_H
#if 0
class Searchable {
    //get initial state

    virtual State<T> *getInitialState() = 0;

    virtual bool isGoalState(State <T> state) = 0;

    //get all possible next states from current state received************
    virtual State<T>[] getAllPossibleStates(State<T> state) = 0;

    virtual ~Searchable() {}
};
#endif //PROJECT2_SEARCHABLE_H
#endif