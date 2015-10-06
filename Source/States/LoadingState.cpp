#include "LoadingState.hpp"

LoadingState::LoadingState(ah::StateManager& manager)
: ah::State(manager)
, mThread(std::bind(&World::init))
{
    mType = LoadingState::getID();

    mBackground.setSize(sf::Vector2f(800,600));
    mBackground.setFillColor(sf::Color(110,40,240));

    mText.setCharacterSize(40);
    mText.setString("Loading");
    mText.setFont(ah::Application::instance().getFont("future"));
    mText.setColor(sf::Color::White);
    mText.setPosition(400.f - mText.getGlobalBounds().width * 0.5f, 300.f - mText.getGlobalBounds().height * 0.5f - 25.f);

    mTimer.setPosition(400.f-150.f,300.f+50.f+25.f);
    mTimer.setSize(sf::Vector2f(300.f,50.f));
    mTimer.setFillColor(sf::Color(40,195,230));
    mTimer.getShapeTop().setFillColor(sf::Color(40,90,240));
    mTimer.setCallback([&]()
    {
        mThread.wait();
        requestPop();
        requestPush(GameState::getID());
    });
    mTimer.restart(sf::seconds(2.f));

    mThread.launch();
}

std::string LoadingState::getID()
{
    return "LoadingState";
}

bool LoadingState::handleEvent(sf::Event const& event)
{
    mTimer.update(event,sf::Vector2f());
    return true;
}

bool LoadingState::update(sf::Time dt)
{
    mTimer.update(sf::Event(),sf::Vector2f());
    return true;
}

void LoadingState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground);
    target.draw(mText);
    target.draw(mTimer);
}
