//
// Created by osboxes on 1/21/20.
//

#ifndef PROJECT2_DEPTHFIRSTSEARCH_H
#define PROJECT2_DEPTHFIRSTSEARCH_H

#include <unordered_set>
#include <iterator>
#include "AbstractSearcher.h"
#include "Matrix.h"

template<typename T, typename C>
class DepthFirstSearch : public AbstractSearcher<T,C> {
public:
    std::vector<State<T,C>> search(ISearchable<T, C> *searchable) {

        std::unordered_map<T, C, CellHash> original_scores_map;
        // Initialize the closeSet, so we don't duplicate
        std::unordered_set<T, CellHash> closeSet;

        // Start the queue with the initial state
        auto init_state = searchable->getInitialState();
        original_scores_map[init_state.getT()] = init_state.getC();
        init_state.setCost(C());
        this->queue.push(init_state);

        C prev_max_score = 100;// go downwards from there

        // Go until the queue is empty
        while (!this->queue.empty()) {
            // Get the current item, and make sure we don't go back
            State<T, C> n = this->queue.top();
            this->queue.pop();
            if (closeSet.find(n.getT()) != closeSet.end())
                continue;
            this->evaluatedNodes++;
            closeSet.insert(n.getT());
            // Are we at the goal? if so, return
            if (searchable->isGoalState(n)) {
                auto ret = this->backtrace(n, searchable->getInitialState());
                // hold up
                // put the scores back in
                unsigned i;
                for (i = 0; i < ret.size(); i++)
                    ret[i].setCost(original_scores_map[ret[i].getT()]);
                return ret;
            }

            // Go through all the neighbors!
            for (State<T,C> s : searchable->getAllPossibleStates(n)) {
                // Have we seen this guy already?
                if (closeSet.find(s.getT()) != closeSet.end())
                    continue;

                // Set our new score (everything is copied, so no need to worry about upsetting
                // other handles to this object)
                C new_c = original_scores_map[n.getT()] + s.getC();
                s.setCost(--prev_max_score);
                s.setCameFrom(n);
                // Do we have this already in our queue?
                bool fFound = false;
                State<T,C> prevInQueue = this->queue.find(s, &fFound);
                if (fFound) continue;
                // Add in our score, either we didnt' have it, or we don't have a better score
                this->queue.push(s);
                original_scores_map[s.getT()] = new_c;
                // next neighbor state
            }
            // next item in the open queue
        }
        // end of search
        return std::vector<State<T,C>>();
    }
};

#endif //PROJECT2_DEPTHFIRSTSEARCH_H
