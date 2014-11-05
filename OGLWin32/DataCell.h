#pragma once

#include <type_traits>
#include <utility>
#include <typeinfo>
#include <string>
#include <cassert>


template<class T>
using StorageType = typename std::decay<typename std::remove_reference<T>::type>::type;

struct DataCell
{
    bool null() const { return !ptr; }

    template<typename T> DataCell(T&& value) : ptr(new Derived<StorageType<T>>(std::forward<T>(value))){}

    template<class Type> bool is() const
    {
        typedef StorageType<Type> T;

        auto derived = dynamic_cast<Derived<T>*> (ptr);

        return derived;
    }

    template<class Type>
    StorageType<Type>& as()
    {
        typedef StorageType<Type> T;

        auto derived = dynamic_cast<Derived<T>*> (ptr);

        if (!derived)
        {
            throw std::bad_cast();
        }

        return derived->value;
    }

    template<class Type>
    operator Type()
    {
        return as<StorageType<Type>>();
    }

    DataCell()
        : ptr(nullptr)
    {

    }

    DataCell(DataCell& that)
        : ptr(that.clone())
    {

    }

    DataCell(DataCell&& that)
        : ptr(that.ptr)
    {
        that.ptr = nullptr;
    }

    DataCell(const DataCell& that)
        : ptr(that.clone())
    {

    }

    DataCell(const DataCell&& that)
        : ptr(that.clone())
    {

    }

    DataCell& operator=(const DataCell& a)
    {
        if (ptr == a.ptr)
            return *this;

        auto old_ptr = ptr;

        ptr = a.clone();

        if (old_ptr)
            delete old_ptr;

        return *this;
    }

    DataCell& operator=(DataCell&& a)
    {
        if (ptr == a.ptr)
        {
            return *this;
        }
        std::swap(ptr, a.ptr);
        return *this;
    }

    ~DataCell()
    {
        if (ptr)
        {
            delete ptr;
        }
    }

private:
    struct Base
    {
        virtual ~Base() {}

        virtual Base* clone() const = 0;
    };

    template<typename T>
    struct Derived : Base
    {
        template<typename U> Derived(U&& value) : value(std::forward<U>(value)) { }

        T value;

        Base* clone() const { return new Derived<T>(value); }
    };

    Base* clone() const
    {
        if (ptr)
            return ptr->clone();
        else
            return nullptr;
    }

    Base* ptr;
};