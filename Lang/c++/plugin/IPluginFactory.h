#pragma once

#include <memory>
#include <string>

#define DLL_PUBLIC __attribute__((visibility("default")))

struct IPluginBase : public std::enable_shared_from_this<IPluginBase>
{
    virtual ~IPluginBase() = default;
};

class IPluginFactory
{
public:
    // GUID format: company.product.module.class
    using PluginID = std::string;

    virtual ~IPluginFactory() = default;

    template <typename T>
    std::shared_ptr<T> createInstance(const PluginID id)
    {
        return std::static_pointer_cast<T>(createInstanceWithBase(id));
    }

protected:
    virtual std::shared_ptr<IPluginBase> createInstanceWithBase(const PluginID &id) = 0;
};

extern "C" IPluginFactory *getPluginFactory();
