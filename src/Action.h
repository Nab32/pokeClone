#pragma once

#include <string>

class Action
{
    public:
        Action();
        Action(const std::string& name, const std::string& type);
        const std::string& getName() const;
        const std::string& getType() const;
    private:
        std::string m_name;
        std::string m_type;
};