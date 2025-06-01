#ifndef APPCONFIGURATOR_H
#define APPCONFIGURATOR_H

#include "ioc_container.h"

class AppConfigurator {
public:
    AppConfigurator() = default;// Конструктор по умолчанию.

    template<typename... Readers>
    void registerReaders() {// Метод регистрирует (Readers) в контейнере зависимостей.
        container.RegisterReaders<Readers...>();
    }

    template<typename... Charts>
    void registerCharts() {// Метод регистрирует (Charts) в контейнере зависимостей
        container.RegisterCharts<Charts...>();
    }

    IOCContainer& getContainer() {
        return container;// Возвращает ссылку на контейнер зависимостей
    }

private:
    IOCContainer container;
};


#endif // APPCONFIGURATOR_H
