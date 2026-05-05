#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "Component.h"

#include <memory>
#include <string>


class ComponentFactory {
public:

    static std::unique_ptr<Component> create(const std::string& type,
                                              const std::string& label,
                                              double value);
};

#endif
