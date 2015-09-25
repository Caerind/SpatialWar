#ifndef COMPONENTFILTER_HPP
#define COMPONENTFILTER_HPP

#include <memory>
#include <string>
#include <vector>

#include <SFML/System/Utf.hpp>

namespace ses
{

class EntityManager;

class ComponentFilter
{
    public:
        ComponentFilter();
        ~ComponentFilter();

        void requires(std::string const& componentId);
        void excludes(std::string const& componentId);
        void requiresOne(std::vector<std::string> componentIds);

        bool passFilter(sf::Int32 const& entityId, std::shared_ptr<EntityManager> em);

    protected:
        std::vector<std::string> mRequiredComponents;
        std::vector<std::string> mExcludedComponents;
        std::vector<std::vector<std::string>> mRequiredOneComponents;
};

} // namespace ses

#endif // COMPONENTFILTER_HPP
