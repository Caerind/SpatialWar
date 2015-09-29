#ifndef PLANETATTRACTIONSYSTEM_HPP
#define PLANETATTRACTIONSYSTEM_HPP

#include "../../Lib/EntitySystem/System.hpp"

#include <SFML/System/Time.hpp>

class PlanetAttractionSystem : public ses::System
{
    public:
        PlanetAttractionSystem(std::shared_ptr<ses::EntityManager> entityManager);

        static std::string getId();

        void update(sf::Time dt);
};

#endif // PLANETATTRACTIONSYSTEM_HPP
