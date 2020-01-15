//
// Created by noy on ١٢‏/١‏/٢٠٢٠.
//

#ifndef PROJECT2_STATE_H
#define PROJECT2_STATE_H

template< typename T, typename C>
class State {
private:
    T m_state;
    C m_cost;
    State<T, C> *m_cameFrom;
public:
    State(T state) {
       m_state = state;
       m_cameFrom =nullptr;
       //m_cost =
    }
    // check if this State and "other" State are equals.
    bool operator==(State<T,C> other) {
        return (this->m_state == other.m_state);
    }
    bool operator<(State<T,C> other) {
        return this->cost == other.cost;
    }
    T getT() {
        return m_state;
    }
    C getC() {
        return m_cost;
    }
    void setCameFrom(State<T,C> *cameFrom)
    {
        m_cameFrom(cameFrom);
    }
    void setCost(C cost){
        m_cost(cost);
    }
    State<T,C> *getCameFrom(State<T,C> *state)
    {
        return m_cameFrom;
    }

};


#endif //PROJECT2_STATE_H
