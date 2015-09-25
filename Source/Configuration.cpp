#include "Configuration.hpp"

Configuration Configuration::mInstance;

ah::ActionTarget::ActionMapPtr Configuration::getPlayerInput()
{
    return mInstance.mPlayerInput;
}

sf::TcpSocket& Configuration::getSocket()
{
    return mInstance.mSocket;
}

Configuration::Configuration()
{
    mPlayerInput = std::make_shared<thor::ActionMap<std::string>>();
    (*mPlayerInput)["up"] = thor::Action(sf::Keyboard::Z,thor::Action::Hold);
    (*mPlayerInput)["left"] = thor::Action(sf::Keyboard::Q,thor::Action::Hold);
    (*mPlayerInput)["down"] = thor::Action(sf::Keyboard::S,thor::Action::Hold);
    (*mPlayerInput)["right"] = thor::Action(sf::Keyboard::D,thor::Action::Hold);
    (*mPlayerInput)["speed"] = thor::Action(sf::Keyboard::LShift,thor::Action::Hold);
    (*mPlayerInput)["action1"] = thor::Action(sf::Mouse::Left,thor::Action::PressOnce);
    (*mPlayerInput)["action2"] = thor::Action(sf::Mouse::Right,thor::Action::PressOnce);
    (*mPlayerInput)["action3"] = thor::Action(sf::Mouse::Middle,thor::Action::PressOnce);
    //(*mPlayerInput)["special1"] = thor::Action(sf::Keyboard::Num1,thor::Action::PressOnce);
    //(*mPlayerInput)["special2"] = thor::Action(sf::Keyboard::Num2,thor::Action::PressOnce);
    //(*mPlayerInput)["special3"] = thor::Action(sf::Keyboard::Num3,thor::Action::PressOnce);
    //(*mPlayerInput)["special4"] = thor::Action(sf::Keyboard::Num4,thor::Action::PressOnce);
    //(*mPlayerInput)["special5"] = thor::Action(sf::Keyboard::Num5,thor::Action::PressOnce);
}

Configuration::~Configuration()
{
}
