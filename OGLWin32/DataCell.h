#pragma once

#include <type_traits>
#include <typeinfo>
#include <utility>
#include <typeinfo>
#include <string>


template<class T>
using StorageType = typename std::decay<typename std::remove_reference<T>::type>::type;

struct DataCell
{

    bool isNull() const
    {
        return !ptr;
    }

    template<class Type>
    bool equals(const DataCell& cell) const
    {
        if (!(cell.isA<Type>())){ return false; }

        auto derived = dynamic_cast<Derived<StorageType<Type>>*> (ptr);
        auto comp = dynamic_cast<Derived<StorageType<Type>>*> (cell.ptr);
        
        return derived->value == comp->value;
    }

    template<typename T>
    DataCell(T&& val) : ptr(new Derived<StorageType<T>>(std::forward<T>(val))){}

    template<class Type>
    bool isA() const
    {
        auto derived = dynamic_cast<Derived<StorageType<Type>>*> (ptr);
        return derived;
    }

    std::string getString()
    {
        if (isA<std::string>())
        {
            return this->asA<std::string>();
        }
        else if (isA<float>())
        {
            return std::to_string(this->asA<float>());
        }
        else if (isA<int>())
        {
            return std::to_string(this->asA<int>());
        }

        else
        {
            return "Incompatible Type";
        }
    }
    template<class Type>
    StorageType<Type>& asA()
    {
        auto derived = dynamic_cast<Derived<StorageType<Type>>*> (ptr);

        if (!derived)
        {
            throw std::bad_cast();
        }

        return derived->value;
    }

    template<class Type>
    operator Type()
    {
        return asA<StorageType<Type>>();
    }

    DataCell() :ptr(nullptr){}

    DataCell(const DataCell& copy) : ptr(copy.clone()){}

    DataCell(const DataCell&& move) : ptr(move.clone()){}
    
    DataCell(DataCell& copy) : ptr(copy.clone()){}

    DataCell(DataCell&& move) : ptr(move.clone()){}

    DataCell& operator=(const DataCell& a)
    {
        if (ptr == a.ptr)
        {
            return *this;
        }
        auto old_ptr = ptr;
        ptr = a.clone();
        if (old_ptr){ delete old_ptr; }
        return *this;
    }

    DataCell& operator= (DataCell& a)
    {
        if (ptr == a.ptr)
        {
            return *this;
        }
        auto old_ptr = ptr;
        ptr = a.clone();
        if (old_ptr){ delete old_ptr; }
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

