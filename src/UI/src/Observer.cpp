#include "Observer.hpp"
#include <iostream>

void Subject::attach(Observer &o)
{
    _observers.push_back(&o);
}

void Subject::notify() const
{
    for (int o = 0; o < _observers.size(); o++)
    {
        _observers[o]->update();
    }
}

void Observer::update() {}