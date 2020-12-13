// 学学学
#pragma once

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};

#endif // !_SINGLETON_H_
