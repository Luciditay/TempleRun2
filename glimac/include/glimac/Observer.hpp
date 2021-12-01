#pragma once
#include <vector>

class Observer{
    public:
    virtual void update();
};

class Subject{
    public:
    void attach(Observer &o);
    const void notify() const;

    public:
    std::vector<Observer*> _observers;
};