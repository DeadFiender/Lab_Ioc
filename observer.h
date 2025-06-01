#ifndef OBSERVER_H
#define OBSERVER_H


class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onGraphChanged() = 0;
};

#endif // OBSERVER_H
