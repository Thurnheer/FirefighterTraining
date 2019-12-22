#ifndef REGEXFILTER_HPP
#define REGEXFILTER_HPP

#include "pipe.hpp"
#include "QVector"
#include "QRegularExpression"
#include "QDate"

namespace regex {

const QDate STOPDATE(2000, 1, 1);


inline bool isValid(const QVector<QRegularExpression> &regex, const QString &name)
{
    for(auto r : regex) {
        if(r.match(name).hasMatch()) {
            return true;
        }
    }
    return false;
}

template <class T>
void filterForNames(pipe<T> &in, QVector<QRegularExpression> names, pipe<T> &filterout)
{
    T event;
    do {
        in >> event;
        if(isValid(names, event.name()))
        {
            filterout << event;
        }
    } while (event.date() > STOPDATE);
}

template <class T>
void filterForNames(pipe<T*> &in, QVector<QRegularExpression> names, pipe<T*> &filterout)
{
    T* event;
    do {
        in >> event;
        if(isValid(names, event->name()))
        {
            filterout << event;
        }
    } while (event->date() > STOPDATE);
}
}


#endif // REGEXFILTER_HPP
