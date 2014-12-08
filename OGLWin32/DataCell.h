#pragma once

#include <type_traits>
#include <typeinfo>
#include <utility>
#include <typeinfo>
#include <string>


//Heavily Inspired by the <boost> any class. 
template<class T>
using Storage = typename std::decay<typename std::remove_reference<T>::type>::type;

struct DataCell
{
    bool isNull() const
    {
        return !pointer;
    }

    template<class Type>
    bool equals(const DataCell& cell) const
    {
        if (!(cell.isA<Type>()) || !(this->isA<Type>())){ return false; }

        auto derived = dynamic_cast<Derived<Storage<Type>>*> (pointer);
        auto comp = dynamic_cast<Derived<Storage<Type>>*> (cell.pointer);
        
        return derived->value == comp->value;
    }

    template<typename T>
    DataCell(T&& val) : pointer(new Derived<Storage<T>>(std::forward<T>(val))){}

    template<class Type>
    bool isA() const
    {
        auto derived = dynamic_cast<Derived<Storage<Type>>*> (pointer);
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
    Storage<Type>& asA()
    {
        auto derived = dynamic_cast<Derived<Storage<Type>>*> (pointer);

        if (!derived)
        {
            throw std::bad_cast();
        }

        return derived->value;
    }

    template<class Type>
    operator Type()
    {
        return asA<Storage<Type>>();
    }

    DataCell() :pointer(nullptr){}

    DataCell(const DataCell& copy) : pointer(copy.clone()){}

    DataCell(const DataCell&& move) : pointer(move.clone()){}
    
    DataCell(DataCell& copy) : pointer(copy.clone()){}

    DataCell(DataCell&& move) : pointer(move.clone()){}

    DataCell& operator=(const DataCell& a)
    {
        if (pointer == a.pointer)
        {
            return *this;
        }
        auto old_pointer = pointer;
        pointer = a.clone();
        if (old_pointer){ delete old_pointer; }
        return *this;
    }

    DataCell& operator= (DataCell& a)
    {
        if (pointer == a.pointer)
        {
            return *this;
        }
        auto old_pointer = pointer;
        pointer = a.clone();
        if (old_pointer){ delete old_pointer; }
        return *this;
    }

    ~DataCell()
    {
        if (pointer)
        {
            delete pointer;
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
        if (pointer)
            return pointer->clone();
        else
            return nullptr;
    }

    Base* pointer;
};

