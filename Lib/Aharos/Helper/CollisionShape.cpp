#include "CollisionShape.hpp"

namespace lp
{

CollisionShape::CollisionShape()
{
    initSettings();
}

CollisionShape::CollisionShape(const sf::FloatRect& rect)
{
    loadFromRect(rect);
    initSettings();
}

CollisionShape::CollisionShape(const sf::ConvexShape& shape)
{
    loadFromConvex(shape);
    initSettings();
}

CollisionShape::CollisionShape(const sf::CircleShape& shape)
{
    loadFromCircle(shape);
    initSettings();
}

void CollisionShape::loadFromRect(const sf::FloatRect& rect)
{
    setPointCount(4);
    setPoint(0,sf::Vector2f(-rect.width * 0.5f, -rect.height * 0.5f));
    setPoint(1,sf::Vector2f(rect.width * 0.5f, -rect.height * 0.5f));
    setPoint(2,sf::Vector2f(rect.width * 0.5f, rect.height * 0.5f));
    setPoint(3,sf::Vector2f(-rect.width * 0.5f, rect.height * 0.5f));
}

void CollisionShape::loadFromConvex(const sf::ConvexShape& shape)
{
    setPosition(shape.getPosition());
    setOrigin(shape.getOrigin());
    setRotation(shape.getRotation());
    setScale(shape.getScale());
    setPointCount(shape.getPointCount());
	for (std::size_t i = 0; i < getPointCount(); i++)
	{
		setPoint(i,shape.getPoint(i));
	}
}

void CollisionShape::loadFromCircle(const sf::CircleShape& shape)
{
    setPosition(shape.getPosition());
    setOrigin(shape.getOrigin());
    setRotation(shape.getRotation());
    setScale(shape.getScale());
    setPointCount(shape.getPointCount());
	for (std::size_t i = 0; i < getPointCount(); i++)
	{
		setPoint(i,shape.getPoint(i));
	}
}

bool CollisionShape::intersects(CollisionShape::Ptr shape) const
{
    if (shape == nullptr)
    {
        return false;
    }
    return intersects(*shape);
}

bool CollisionShape::intersects(const CollisionShape& shape) const
{
    for (std::size_t i = 0; i < getPointCount(); i++)
    {
        if (shape.contains(getTransform().transformPoint(getPoint(i))))
        {
            return true;
        }
    }
    for (std::size_t i = 0; i < shape.getPointCount(); i++)
    {
        if (contains(shape.getTransform().transformPoint(shape.getPoint(i))))
        {
            return true;
        }
    }
    return false;
}

bool CollisionShape::contains(const sf::Vector2f& point) const
{
    sf::Vector2f p = getInverseTransform().transformPoint(point);
    for (std::size_t i = 0; i < getPointCount(); i++)
    {
        const sf::Vector2f& a = getPoint(i);
        sf::Vector2f b;

        if (i == getPointCount() - 1)
        {
            b = getPoint(0) - a;
        }
        else
        {
            b = getPoint(i + 1) - a;
        }

        if (b.x * (p.y - a.y) - b.y * (p.x - a.x) < 0)
        {
            return false;
        }
    }
    return true;
}

void CollisionShape::initSettings()
{
    setFillColor(sf::Color::Transparent);
    setOutlineThickness(1.f);
    setOutlineColor(sf::Color::Red);
}

} // namespace lp
