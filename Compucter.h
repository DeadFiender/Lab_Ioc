#ifndef COMPUCTER_H
#define COMPUCTER_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include "IOC_Contaner.h"

enum ProcessorType { x86, x64 };

class IProcessor {
public:
    virtual ~IProcessor() = default;
    virtual std::string GetProcessorInfo() const = 0;
    static const std::string PROCESSOR_TYPE[2];
};

const std::string IProcessor::PROCESSOR_TYPE[2] = {"x86", "x64"};

class IntelProcessor : public IProcessor {
public:
    IntelProcessor(double speed, ProcessorType type, const std::string& version)
        : Speed(speed), Type(type), Version(version) {}

    IntelProcessor(std::shared_ptr<double> speed, std::shared_ptr<ProcessorType> type, std::shared_ptr<std::string> version)
        : Speed(*speed), Type(*type), Version(*version) {}

    std::string GetProcessorInfo() const override {
        return "Intel processor: " + Version + ", " + std::to_string(Speed) + "GHz, " + PROCESSOR_TYPE[Type];
    }
private:
    double Speed;
    ProcessorType Type;
    std::string Version;
};

class AMDProcessor : public IProcessor {
public:
    AMDProcessor(double speed, ProcessorType type, const std::string& version)
        : Speed(speed), Type(type), Version(version) {}

    AMDProcessor(std::shared_ptr<double> speed, std::shared_ptr<ProcessorType> type, std::shared_ptr<std::string> version)
        : Speed(*speed), Type(*type), Version(*version) {}

    std::string GetProcessorInfo() const override {
        return "AMD processor: " + Version + ", " + std::to_string(Speed) + "GHz, " + PROCESSOR_TYPE[Type];
    }
private:
    double Speed;
    ProcessorType Type;
    std::string Version;
};

class Computer {
    std::shared_ptr<IProcessor> processor;
public:
    Computer() = default;

    explicit Computer(std::shared_ptr<IProcessor> p) : processor(p) {}

    void setProcessor(IOCContainer& container) {
        processor = container.GetObject<IProcessor>();
    }

    void configure() const {
        std::cout << processor->GetProcessorInfo() << std::endl;
    }
};

#endif // COMPUCTER_H
