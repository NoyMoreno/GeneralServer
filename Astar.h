//
// Created by noy on ١٩‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include <set>
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
        std::set<State<T, C>> closeSet;
        State<T, C> initNode = searchable->getInitialState();
        initNode.setCost(initNode.getC() + heuristic_cost_estimate(initNode, searchable));
        // The set of tentative nodes to be evaluated, initially containing the start node
        this->queue.push(initNode);
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




    }
};

template<typename T, typename C>
double Astar<T, C>::heuristic_cost_estimate(State<Cell, double> state, ISearchable<T, C> *searchable) {
    State<Cell, double > goalState = searchable->getGoalState();
    // Return using the distance formula
    return ((double)sqrt (pow(state.getT().getI() - goalState.getT().getI(),2) +
                      pow(state.getT().getJ() - goalState.getT().getJ(),2)));
}




//};
//function A*(start,goal)
//
//closedset := the empty set // The set of nodes already evaluated.
//
//        openset := {start} node
//
//came_from := the empty map // The map of navigated nodes.
//
//
//        g_score[start] := 0 // Cost from start along best known path.
//
//// Estimated total cost from start to goal through y.
//
//f_score[start] := g_score[start] + heuristic_cost_estimate(start, goal)
//
//
//
//while openset is not empty
//
//        current := the node in openset having the lowest f_score[] value
//
//if current = goal
//
//return reconstruct_path(came_from, goal)
//
//
//
//remove current from openset
//
//add current to closedset
//
//for each neighbor in neighbor_nodes(current)
//
//tentative_g_score := g_score[current] + dist_between(current,neighbor)
//
//if neighbor in closedset or tentative_g_score >= g_score[neighbor]
//
//continue
//
//if neighbor not in openset or tentative_g_score < g_score[neighbor]
//
//        came_from[neighbor] := current
//
//        g_score[neighbor] := tentative_g_score
//
//        f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
//
//if neighbor not in openset
//
//add neighbor to openset
//
//
//return failure
//
//
//        function reconstruct_path(came_from, current_node)
//
//if current_node in came_from
//
//        p := reconstruct_path(came_from, came_from[current_node])
//
//return (p + current_node)
//
//else
//
//return current_node


#endif //PROJECT2_ASTAR_H
