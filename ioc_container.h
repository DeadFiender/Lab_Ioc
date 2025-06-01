#ifndef IOC_CONTAINER_H
#define IOC_CONTAINER_H

#include <functional>
#include <memory>
#include <map>
#include <QVector>
#include "ChartFactory.h"
#include "ReaderFactory.h"

class IOCContainer {
    static int s_nextTypeId;
    template<typename T>
    static int GetTypeID() {
        static int typeId = s_nextTypeId++;
        return typeId;
    }

public:
    class FactoryRoot {
    public:
        virtual ~FactoryRoot() {}
    };

    std::map<int, std::shared_ptr<FactoryRoot>> m_factories;

    template<typename T>
    class CFactory : public FactoryRoot {
        std::function<std::shared_ptr<T>()> m_functor;
    public:
        CFactory(std::function<std::shared_ptr<T>()> functor) : m_functor(functor) {}
        std::shared_ptr<T> GetObject() { return m_functor(); }
    };

    template<typename T>
    std::shared_ptr<T> GetObject() {
        auto typeId = GetTypeID<T>();
        auto factoryBase = m_factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->GetObject();
    }

    template<typename TInterface>
    void RegisterFunctor(std::function<std::shared_ptr<TInterface>()> functor) {
        m_factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(functor);
    }

    template<typename TInterface, typename TConcrete>
    void RegisterInstance() {
        RegisterFunctor<TInterface>([] { return std::make_shared<TConcrete>(); });
    }

    template<typename... ReaderTs>
    void RegisterReaders() {
        (RegisterInstance<ReaderTs, ReaderTs>(), ...);
        RegisterFunctor<ReaderFactory>([=] {
            return std::make_shared<ReaderFactory>(
                QVector<std::shared_ptr<IDataReader>>{ GetObject<ReaderTs>()... });
        });
    }

    template<typename... RenderTs>
    void RegisterCharts() {
        (RegisterInstance<RenderTs, RenderTs>(), ...);
        RegisterFunctor<ChartFactory>([=] {
            return std::make_shared<ChartFactory>(
                QVector<std::shared_ptr<IChartRender>>{ GetObject<RenderTs>()... });
        });
    }
};

#endif // IOC_CONTAINER_H
