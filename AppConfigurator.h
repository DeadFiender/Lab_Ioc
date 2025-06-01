#ifndef APPCONFIGURATOR_H
#define APPCONFIGURATOR_H

#include "ioc_container.h"
#include "ReaderFactory.h"
#include "ChartFactory.h"

class AppConfigurator {
public:
    AppConfigurator() = default;

    template<typename... Readers>
    void registerReaders() {
        container.RegisterReaders<Readers...>();
    }

    template<typename... Charts>
    void registerCharts() {
        container.RegisterCharts<Charts...>();
    }

    IOCContainer& getContainer() {
        return container;
    }

private:
    IOCContainer container;
};


#endif // APPCONFIGURATOR_H
