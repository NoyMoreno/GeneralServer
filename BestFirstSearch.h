//
// Created by noy on ١٤‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_BESTFIRSTSEARCH_H
#define PROJECT2_BESTFIRSTSEARCH_H

#include <set>
#include <iterator>
#include "AbstractSearcher.h"

template<typename T,typename C>
class BestFirstSearch : public AbstractSearcher<T,C> {
public:
    std::vector<State<T,C>> search(ISearchable<T, C> *searchable) {
        // Start the queue with the initial state
        this->queue.push(searchable->getInitialState());
        // Initialize the closeSet, so we don't duplicate
        std::set<State<T, C>> closeSet;

        // Go until the queue is empty
        while (!this->queue.empty()) {
            // Get the current item, and make sure we don't go back
            State<T, C> n = this->queue.top();
            this->queue.pop();
            closeSet.insert(n);
            // Are we at the goal? if so, return
            if (searchable->isGoalState(n)) {
                return this->backtrace(n, searchable->getInitialState());
            }

            // Go through all the neighbors!
            for (State<T,C> s : searchable->getAllPossibleStates(n)) {
                // Have we seen this guy already?
                if (closeSet.find(s) != closeSet.end())
                    continue;

                // Set our new score (everything is copied, so no need to worry about upsetting
                // other handles to this object)
                s.setCost(s.getC() + n.getC());
                s.setCameFrom(n);
                // Do we have this already in our queue?
                bool fFound = false;
                State<T,C> prevInQueue = this->queue.find(s, &fFound);
                if (fFound) {
                    // Is it a better score?
                    if (prevInQueue < s) continue;
                    this->queue.remove(prevInQueue);
                }
                // Add in our score, either we didnt' have it, or we don't have a better score
                this->queue.push(s);
                // next neighbor state
            }
            // next item in the open queue
        }
        // end of search
    }
};



#endif //PROJECT2_BESTFIRSTSEARCH_H
