#ifndef EXAMPLE_H
#define EXAMPLE_H

//#include <IOC_Contaner.h>
#include <functional>
#include <iostream>
#include <memory>
#include <map>
#include <string>

using namespace std;

class IAmAThing
{
public:
    virtual ~IAmAThing() {}
    virtual void TestThis() = 0;
};

class IAmTheOtherThing
{
public:
    virtual ~IAmTheOtherThing() {}
    virtual void TheOtherTest() = 0;
};

class TheThing : public IAmAThing
{
public:
    TheThing() {}
    void TestThis() {
        std::cout << "A Thing" << std::endl;
    }
};

class TheOtherThing : public IAmTheOtherThing
{
    std::shared_ptr<IAmAThing> m_thing;
    string m_superInfo;

public:
    TheOtherThing(std::shared_ptr<IAmAThing> thing)
        : m_thing(thing) {
        m_superInfo = "From TheOtherThing";
    }
    TheOtherThing(std::shared_ptr<IAmAThing> thing, string sInfo)
        : m_thing(thing)
        , m_superInfo(sInfo) {
        m_superInfo = sInfo;
    }
    void TheOtherTest() {
        std::cout << m_superInfo << std::endl;
        m_thing->TestThis();
    }
};

class IHello
{
public:
    virtual void hello() const = 0;
    virtual ~IHello() = default;
};

class Hello : public IHello
{
public:
    virtual void hello() const {
        std::cout << "hello world!" << std::endl;
    }
};

class Privet : public IHello
{
public:
    virtual void hello() const {
        std::cout << "Privet world!" << std::endl;
    }
};
#endif // EXAMPLE_H
