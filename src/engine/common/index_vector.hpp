#pragma once

#include <vector>
#include <cstdint>

namespace civ
{

using ID = uint64_t;

template<typename T>
struct PRef;

/**
 * @brief Slot of an index vector
 * 
 */
struct Slot
{
    ID id;
    ID data_id;
};

/**
 * @brief Generic provider interface
 * 
 */
struct GenericProvider
{
    virtual ~GenericProvider()
    {
    }

    virtual void* get(civ::ID id) = 0;

    [[nodiscard]]
    virtual bool  isValid(civ::ID, uint64_t validity_id) const = 0;
};

/**
 * @brief Slot metadata
 * 
 */
struct SlotMetadata
{
    ID rid;
    ID op_id;
};

/**
 * @brief Vector of objects with a unique ID
 * 
 * @tparam T 
 */
template<typename T>
struct Vector : public GenericProvider
{
    Vector()
        : data_size(0)
        , op_count(0)
    {}

    ~Vector() override
    {
        // Since we already explicitly destroyed objects >= data_size index
        // the compiler will complain when double freeing these objects.
        // The quick fix for now is to fill these places with default initialized objects
        const uint64_t capacity = data.size();
        for (uint64_t i{data_size}; i<capacity; ++i) {
            new(&data[i]) T();
        }
    }

    // Data ADD / REMOVE
    template<typename... Args>
    ID                 emplace_back(Args&&... args);
    // Data access by ID
    T&                 operator[](ID id);
    const T&           operator[](ID id) const;
    // Check if the data behind the pointer is the same
    [[nodiscard]]
    bool               isValid(ID id, ID validity) const override;
    // Iterators
    typename std::vector<T>::iterator       begin();
    typename std::vector<T>::iterator       end();
    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::const_iterator end() const;
    // Number of objects in the provider
    [[nodiscard]]
    uint64_t size() const;

public:
    std::vector<T>            data;
    std::vector<uint64_t>     ids;
    std::vector<SlotMetadata> metadata;
    uint64_t                  data_size;
    uint64_t                  op_count;

    [[nodiscard]]
    bool          isFull() const;
    // Returns the data emplacement of an ID
    [[nodiscard]]
    uint64_t      getDataID(ID id) const;
    Slot          createNewSlot();
    Slot          getFreeSlot();
    Slot          getSlot();
    const T&      getAt(ID id) const;
    [[nodiscard]]
    void*         get(civ::ID id) override;

    template<class U> friend struct PRef;
};

template<typename T>
template<typename ...Args>
inline uint64_t Vector<T>::emplace_back(Args&& ...args)
{
    const Slot slot = getSlot();
    new(&data[slot.data_id]) T(std::forward<Args>(args)...);
    return slot.id;
}

template<typename T>
inline T& Vector<T>::operator[](ID id)
{
    return const_cast<T&>(getAt(id));
}

template<typename T>
inline const T& Vector<T>::operator[](ID id) const
{
    return getAt(id);
}

template<typename T>
inline uint64_t Vector<T>::size() const
{
    return data_size;
}

template<typename T>
inline typename std::vector<T>::iterator Vector<T>::begin()
{
    return data.begin();
}

template<typename T>
inline typename std::vector<T>::iterator Vector<T>::end()
{
    return data.begin() + data_size;
}

template<typename T>
inline typename std::vector<T>::const_iterator Vector<T>::begin() const
{
    return data.begin();
}

template<typename T>
inline typename std::vector<T>::const_iterator Vector<T>::end() const
{
    return data.begin() + data_size;
}

template<typename T>
inline bool Vector<T>::isFull() const
{
    return data_size == data.size();
}

template<typename T>
inline Slot Vector<T>::createNewSlot()
{
    data.emplace_back();
    ids.push_back(data_size);
    metadata.push_back({data_size, op_count++});
    return { data_size, data_size };
}

template<typename T>
inline Slot Vector<T>::getFreeSlot()
{
    const uint64_t reuse_id = metadata[data_size].rid;
    metadata[data_size].op_id = op_count++;
    return { reuse_id, data_size };
}

template<typename T>
inline Slot Vector<T>::getSlot()
{
    const Slot slot = isFull() ? createNewSlot() : getFreeSlot();
    ++data_size;
    return slot;
}

template<typename T>
inline uint64_t Vector<T>::getDataID(ID id) const
{
    return ids[id];
}

template<typename T>
inline const T& Vector<T>::getAt(ID id) const
{
    return data[getDataID(id)];
}

template<typename T>
inline bool Vector<T>::isValid(ID id, ID validity) const
{
    return validity == metadata[getDataID(id)].op_id;
}

template<typename T>
void *Vector<T>::get(civ::ID id)
{
    return static_cast<void*>(&data[ids[id]]);
}

template<typename T>
struct Ref
{
    Ref()
        : id(0)
        , array(nullptr)
        , validity_id(0)
    {}

    T* operator->()
    {
        return &(*array)[id];
    }

    const T* operator->() const
    {
        return &(*array)[id];
    }

    T& operator*()
    {
        return (*array)[id];
    }

    const T& operator*() const
    {
        return (*array)[id];
    }

    explicit
    operator bool() const
    {
        return array && array->isValid(id, validity_id);
    }

public:
    ID         id;
    Vector<T>* array;
    ID         validity_id;
};


template<typename T>
struct PRef
{
    using ProviderCallback = T*(*)(ID, GenericProvider*);

    PRef()
        : id(0)
        , provider_callback(nullptr)
        , provider(nullptr)
        , validity_id(0)
    {}

    T* operator->()
    {
        return provider_callback(id, provider);
    }

    T& operator*()
    {
        return *provider_callback(id, provider);
    }

    const T& operator*() const
    {
        return *provider_callback(id, provider);
    }

    explicit
    operator bool() const
    {
        return provider && provider->isValid(id, validity_id);
    }

private:
    ID                  id;
    ProviderCallback    provider_callback;
    GenericProvider*    provider;
    uint64_t            validity_id;

    template<class U> friend struct PRef;
    template<class U> friend struct Vector;
};

}
