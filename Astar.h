//
// Created by noy on ١٩‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include <unordered_set>
#include <iterator>
#include "AbstractSearcher.h"
#include <math.h>
#include "Matrix.h"

template<typename T,typename C>
double heuristic_cost_estimate(State<T, C> state, ISearchable<T, C> *searchable);

template<typename T,typename C>
class Astar : public AbstractSearcher<T,C> {
public:
    std::vector<State<T,C>> search(ISearchable<T, C> *searchable) {
        // Start the queue with the initial state
        auto init_state = searchable->getInitialState();
        init_state.setCost(heuristic_cost_estimate<T,C>(init_state, searchable));
        this->queue.push(init_state);

        // Initialize the closeSet, so we don't duplicate
        std::unordered_set<T, CellHash> closeSet;

        // keep a map of the gscores
        std::unordered_map<T, double, CellHash> seenGScores;
        seenGScores[init_state.getT()] = 0;

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
                return this->backtrace(n, searchable->getInitialState());
            }

            double cur_score = seenGScores[n.getT()];

            // Go through all the neighbors!
            for (State<T,C> s : searchable->getAllPossibleStates(n)) {
                // Have we seen this guy already?
                if (closeSet.find(s.getT()) != closeSet.end())
                    continue;

                C orig_cost = s.getC();
                // Set our new score (everything is copied, so no need to worry about upsetting
                // other handles to this object)
                s.setCost(cur_score + heuristic_cost_estimate<T,C>(n, searchable));
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
                seenGScores[s.getT()] = cur_score + orig_cost;
                // next neighbor state
            }
            // next item in the open queue
        }
        // end of search
        // return empty
        return std::vector<State<T,C>>();
    }
    ~Astar(){}
};
template<typename T, typename C>
double heuristic_cost_estimate(State<T, C> state, ISearchable<T, C> *searchable) {
    State<Cell, double> goalState = searchable->getGoalState();
    // Return using the distance formula
    return ((double)sqrt (pow(state.getT().getI() - goalState.getT().getI(),2) +
                          pow(state.getT().getJ() - goalState.getT().getJ(),2)));
}

#endif //PROJECT2_ASTAR_H

