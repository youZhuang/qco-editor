#include "property_listener_spine.h"
#include "../framework.h"
#include "../tools/json_tools.h"
#include "property_group.h"
#include "runtime/object_factory.h"
#include "runtime/object_loader.h"
#include "property_param.h"

#include <2d/CCNode.h>

namespace Editor
{
    PropertyListenerSpine::PropertyListenerSpine()
    {

    }

    void PropertyListenerSpine::onPropertyChange(PropertyParam &param)
    {
        std::string type;
        param.properties["type"] >> type;

        ObjectLoader *loader = ObjectFactory::instance()->findLoader(type);
        if(loader == nullptr)
        {
            return;
        }

        JsonHandle value = loader->getProperty(param.object, "animations");
        if(value.isNull())
        {
            return;
        }
        Framework::instance()->emitObjectPropertyChange(param.object, "animations", *value);
    }

}
