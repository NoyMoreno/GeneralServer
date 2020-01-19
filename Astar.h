//
// Created by noy on ١٩‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include <unordered_set>
#include <unordered_map>
#include "Matrix.h"
#include "AbstractSearcher.h"
#include <math.h>

template<typename T , typename  C>
class Astar : public AbstractSearcher<T,C> {
public:
    double heuristic_cost_estimate(State<Cell, double > state, ISearchable<T, C> *searchable);
    std::vector<State<T, C>> search(ISearchable<T, C> *searchable) {
        // Initialize the closeSet, so we don't duplicate
        std::unordered_set<T, CellHash> closeSet;
        State<T, C> initNode = searchable->getInitialState();
        initNode.setCost(initNode.getC() + heuristic_cost_estimate(initNode, searchable));
        // The set of tentative nodes to be evaluated, initially containing the start node
        this->queue.push(initNode);
        // Go until the queue is empty
        while (!this->queue.empty()) {
            // Get the current item, and make sure we don't go back
            State<T, C> n = this->queue.top();
            this->queue.pop();
            this->evaluatedNodes++;
            closeSet.insert(n.getT());
            // Are we at the goal? if so, return
            if (searchable->isGoalState(n)) {
                return this->backtrace(n, searchable->getInitialState());
            }

            // Go through all the neighbors!
            for (State<T,C> s : searchable->getAllPossibleStates(n)) {
                // Have we seen this already?
                if (closeSet.find(s.getT()) != closeSet.end())
                    continue;
                if(s.getC() == -1) {
                    continue;
                }
                // Set our new score (everything is copied, so no need to worry about upsetting
                // other handles to this object)
                s.setCost(s.getC() + heuristic_cost_estimate(s, searchable));
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

template<typename T, typename C>
double Astar<T, C>::heuristic_cost_estimate(State<Cell, double> state, ISearchable<T, C> *searchable) {
    State<Cell, double > goalState = searchable->getGoalState();
    // Return using the distance formula
    return ((double)sqrt (pow(state.getT().getI() - goalState.getT().getI(),2) +
                      pow(state.getT().getJ() - goalState.getT().getJ(),2)));
}


#endif //PROJECT2_ASTAR_H
