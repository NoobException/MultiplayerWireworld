#ifndef AUTOMATON_HPP
#define AUTOMATON_HPP

#include "GridController.hpp"

class Automaton
{
public:
    virtual void update(GridController) = 0;
};


#endif // AUTOMATON_HPP

