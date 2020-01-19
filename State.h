//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H

#include <iostream>

template<typename T, typename C>
class State {
public:
    State() : m_state(T()), m_cost(C()), m_cameFrom(nullptr) {}
    ~State() {
        //if (m_cameFrom != nullptr)
        //    delete m_cameFrom;
    }
    State(T state, C cost) : m_state(state), m_cost(cost) {
       m_cameFrom = nullptr;
    }
    // check if this State and "other" State are equals.
    bool operator==(State<T,C> other) {
        return (this->m_state == other.m_state);
    }
    // check if this State and "other" State are equals.
    bool operator==(State<T,C> other) const {
        return (this->m_state == other.m_state);
    }
    // check if this State and "other" State are equals.
    bool operator!=(State<T,C> other) {
        return !(this->m_state == other.m_state);
    }
    bool operator<(State<T,C> other) {
        return this->m_cost < other.getC();
    }
    bool operator<(const State<T,C> other) const {
        return this->m_cost < other.getC();
    }
    T getT() {
        return m_state;
    }
    C getC() const {
        return m_cost;
    }
    void setCameFrom(State<T,C> cameFrom) {
        m_cameFrom = new State<T,C>(cameFrom);
    }
    void setCost(C cost){
        m_cost = cost;
    }
    State<T,C> getCameFrom()
    {
        return *m_cameFrom;
    }
private:
    T m_state;
    C m_cost;
    State<T, C> *m_cameFrom;
};


#endif //PROJECT2_STATE_H
