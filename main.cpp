//#include "Example.h"
#include "Compucter.h"
#include "IOC_Contaner.h"

IOCContainer gContainer;

// инициализируем ненулевым числом
int IOCContainer::s_nextTypeId = 115094801;

int main(int argc, const char *argv[])
{
    IOCContainer injector;

    // === Регистрируем начальные параметры ===
    injector.RegisterInstance<double>(std::make_shared<double>(3.5)); // GHz
    injector.RegisterInstance<ProcessorType>(std::make_shared<ProcessorType>(x64));
    injector.RegisterInstance<std::string>(std::make_shared<std::string>("i7-12700K"));

    // === Intel Processor ===
    injector.RegisterFunctor<IProcessor, double, ProcessorType, std::string>(
        std::function<std::shared_ptr<IProcessor>(std::shared_ptr<double>,
                                                  std::shared_ptr<ProcessorType>,
                                                  std::shared_ptr<std::string>)>(
            [](std::shared_ptr<double> speed,
               std::shared_ptr<ProcessorType> type,
               std::shared_ptr<std::string> model) -> std::shared_ptr<IProcessor> {
                return std::make_shared<IntelProcessor>(*speed, *type, *model);
            }));

    injector.RegisterFactory<Computer, Computer, IProcessor>();
    auto pc = injector.GetObject<Computer>();

    std::cout << "Intel processor: ";
    pc->configure();

    // === AMD Processor: Ryzen 5 5600G, 3.5GHz, x64 ===
    injector.RegisterInstance<std::string>(std::make_shared<std::string>("Ryzen 5 5600G"));

    injector.RegisterFunctor<IProcessor, double, ProcessorType, std::string>(
        std::function<std::shared_ptr<IProcessor>(std::shared_ptr<double>,
                                                  std::shared_ptr<ProcessorType>,
                                                  std::shared_ptr<std::string>)>(
            [](std::shared_ptr<double> speed,
               std::shared_ptr<ProcessorType> type,
               std::shared_ptr<std::string> model) -> std::shared_ptr<IProcessor> {
                return std::make_shared<AMDProcessor>(*speed, *type, *model);
            }));

    pc->setProcessor(injector);
    std::cout << "AMD processor: ";
    pc->configure();

    // === AMD Processor: Ryzen 5 5600G, 2.8GHz, x86 ===
    injector.RegisterInstance<double>(std::make_shared<double>(2.8));
    injector.RegisterInstance<ProcessorType>(std::make_shared<ProcessorType>(x86));
    pc->setProcessor(injector);
    std::cout << "AMD processor: ";
    pc->configure();

    return 0;
}
