#ifndef LP_COLLISIONSHAPE_HPP
#define LP_COLLISIONSHAPE_HPP

#include <memory>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace lp
{

class CollisionShape : public sf::ConvexShape
{
    public:
        typedef std::shared_ptr<CollisionShape> Ptr;

        CollisionShape();
        CollisionShape(const sf::FloatRect& rect);
		CollisionShape(const sf::ConvexShape& shape);
		CollisionShape(const sf::CircleShape& shape);

		void loadFromRect(const sf::FloatRect& rect);
		void loadFromConvex(const sf::ConvexShape& shape);
		void loadFromCircle(const sf::CircleShape& shape);

        bool intersects(CollisionShape::Ptr shape) const;
        bool intersects(const CollisionShape& shape) const;
        bool contains(const sf::Vector2f& point) const;

    private:
        void initSettings();
};

} // namespace lp

#endif // LP_COLLISIONSHAPE_HPP
