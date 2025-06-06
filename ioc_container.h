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
        // Шаблонная функция для получения уникального ID типа.
        // Каждый тип получает свой уникальный ID при первом вызове.
    }

public:
    class FactoryRoot {
    public:
        virtual ~FactoryRoot() {}
    };

    std::map<int, std::shared_ptr<FactoryRoot>> m_factories;
// Карта, хранящая фабрики. Ключ — уникальный ID типа, значение — фабрика.
    template<typename T>
    class CFactory : public FactoryRoot {
        std::function<std::shared_ptr<T>()> m_functor;
        // Функциональный объект для создания экземпляров типа T.
    public:
        CFactory(std::function<std::shared_ptr<T>()> functor) : m_functor(functor) {}
        // Конструктор принимает функцию для создания объектов.
        std::shared_ptr<T> GetObject() { return m_functor(); }
        // Метод для получения нового объекта типа T.
    };

    template<typename T>
    std::shared_ptr<T> GetObject() {
        auto typeId = GetTypeID<T>();
        auto factoryBase = m_factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->GetObject();
        // Метод для получения объекта типа T через его фабрику.
    }

    template<typename TInterface>
    void RegisterFunctor(std::function<std::shared_ptr<TInterface>()> functor) {
        m_factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(functor);
        // Регистрация фабрики для интерфейса TInterface.
    }

    template<typename TInterface, typename TConcrete>
    void RegisterInstance() {
        RegisterFunctor<TInterface>([] { return std::make_shared<TConcrete>(); });
        // Регистрация конкретного типа TConcrete как реализации интерфейса TInterface.
    }

    template<typename... ReaderTs>
    void RegisterReaders() {
        (RegisterInstance<ReaderTs, ReaderTs>(), ...);
        // Регистрация всех читателей (типов ReaderTs).

        RegisterFunctor<ReaderFactory>([=] {
            return std::make_shared<ReaderFactory>(
                QVector<std::shared_ptr<IDataReader>>{ GetObject<ReaderTs>()... });
            // Создание фабрики `ReaderFactory` с зарегистрированными Reader.
        });
    }

    template<typename... RenderTs>
    void RegisterCharts() {
        (RegisterInstance<RenderTs, RenderTs>(), ...);
        // Регистрация всех рендеров (типов RenderTs).
        RegisterFunctor<ChartFactory>([=] {
            return std::make_shared<ChartFactory>(
                QVector<std::shared_ptr<IChartRender>>{ GetObject<RenderTs>()... });
            // Создание фабрики `ChartFactory` с зарегистрированными рендерами.
        });
    }
};

#endif // IOC_CONTAINER_H
