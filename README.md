# Gриложение для печати графиков по данным временных рядов
## Задача:
Продумать и релизовать архитектуру, которая будет строить графики по данным временных рядов. 
Приложение должно: 
1. Cчитывать данные с разных файлов (.sql, .json и др.)
2. Строить разные типы графиков(линейный, гистограмма, точечный и др.), 
3. Менять стиль графика на черно-белый
4. Сохранять полученный график в .pdf файл.
При этом приложение должно быть легко расширяемым, то есть при добавлении новых типов графиков или новых форматов принимаемых файлов, нам 
не пришлось бы менять уже существующий класс
## Реализация
1. Инверсия зависимостей
   - `IOCContainer` регистрирует и создаёт:
      - **ReaderFactory** (JSON, SQLite и др.)
      - **ChartFactory** (LineChart, ScatterChart и др.)
   - `AppConfigurator` настраивает контейнер в одном месте.
   - `GetObject<ReaderFactory>()` и `GetObject<ChartFactory>()` передаются в `MainWindow`.
2. Адаптер
   - `JsonReader` — адаптирует JSON-файл к интерфейсу `IDataReader` 
   - `SqlReader` — адаптирует SQLite к тому же интерфейсу
   - MainWindow взаимодействует с DataModel, а не с конкретными реализациями
3. Стратегия
   - `IChartRender` - интерфейс стратегии
   - `ChartRender` - хранит конкретные стратегии с помощью указателей
   - `LineChartRender` и др. - конкретные стратегии
4. Изменения в IOC
   - Внедрение функций для регистрации всех Reader и Chart
   ``` c++
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
   ```
## UML-Диаграмма классов
![UML-диаграмма](https://github.com/DeadFiender/Lab_Ioc/blob/LabGraphics/UML_For3rdLab.jpg)

## Расширение
1. Для нового типа данных:
   - Наследование от `IDataReader` и реализация его методов
   - Добавить в
     ``` c++
     config.registerReaders<JsonReader, SqlReader, новый тип данных>();
     ```
2. Для нового типа графика:
   - Наследование от `IChartRender` и реализация его методов
   - Добавить в
          ``` c++
     config.registerCharts<LineChartRender, BarChartRender, PieChartRender, ScatterChartRender, новый тип графика>();
     ```
