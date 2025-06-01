#ifndef OBSERVER_H
#define OBSERVER_H


class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onGraphChanged() = 0;
    // Чисто виртуальный метод для уведомления об изменении графика.
};

#endif // OBSERVER_H
