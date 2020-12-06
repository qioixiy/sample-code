#pragma once

#include <functional>
#include <unordered_map>
#include "IPluginFactory.h"

class PluginFactory : public IPluginFactory
{
public:
    PluginFactory() = default;
    virtual ~PluginFactory() = default;

    bool registerClass(const PluginID &id, std::function<std::shared_ptr<IPluginBase>()> constructor);
    void unregisterClass(const PluginID &id);

protected:
    virtual std::shared_ptr<IPluginBase> createInstanceWithBase(const PluginID &id);

private:
    PluginFactory(const PluginFactory &) = delete;
    PluginFactory &operator=(const PluginFactory &) = delete;

    std::unordered_map<PluginID, std::function<std::shared_ptr<IPluginBase>()>> constructors;
};

#define PLUGIN_REGISTER(className, pluginName)                                                                \
    static struct PluginRegister##className                                                                   \
    {                                                                                                         \
        PluginRegister##className()                                                                           \
        {                                                                                                     \
            auto factory = dynamic_cast<PluginFactory *>(getPluginFactory());                                 \
            factory->registerClass(                                                                           \
                #pluginName,                                                                                  \
                [] {                                                                                          \
                    /* return std::static_pointer_cast<IPluginBase>(std::shared_ptr<className>::create()); */ \
                    return std::make_shared<className>();                                                     \
                });                                                                                           \
        }                                                                                                     \
        ~PluginRegister##className()                                                                          \
        {                                                                                                     \
            auto factory = dynamic_cast<PluginFactory *>(getPluginFactory());                                 \
            factory->unregisterClass(#pluginName);                                                            \
        }                                                                                                     \
    } PluginRegister##className;
