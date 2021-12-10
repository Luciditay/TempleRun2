#pragma once
#include <vector>

/// \class Observer
/// \brief implement observer design pattern
class Observer{
    public:
    /// \brief depend on what the observer need to do
    virtual void update();
};

/// \class Subject
/// \brief implement observer design pattern
class Subject{
    public:
    /// \brief attach an observer to a subject 
    /// \param o : observer that should be attached
    void attach(Observer &o);
    /// \brief call the update() method of every observer
    const void notify() const;

    public:
    std::vector<Observer*> _observers; /*!< all the observers of this subject */
};