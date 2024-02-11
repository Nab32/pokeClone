#include "Action.h"

Action::Action()
{
    
}

Action::Action(const std::string& name, const std::string& type)
    : m_name(name), m_type(type)
{
    
}

const std::string& Action::getName() const
{
    return m_name;
}

const std::string& Action::getType() const
{
    return m_type;
}