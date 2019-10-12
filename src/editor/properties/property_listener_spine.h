#ifndef PROPERTYLISTENERSKELETONANIMATION_H
#define PROPERTYLISTENERSKELETONANIMATION_H

#include "editor/properties/property_listener.h"
#include <string>

namespace Editor
{
    class PropertyListenerSpine : public PropertyListener
    {
    public:
        PropertyListenerSpine();
        virtual void onPropertyChange(PropertyParam &param) override;
    };
}

#endif // PROPERTYLISTENERSKELETONANIMATION_H
