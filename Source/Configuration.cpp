#include "Configuration.hpp"

Configuration Configuration::mInstance;

ah::ActionTarget::ActionMapPtr Configuration::getPlayerInput()
{
    return mInstance.mPlayerInput;
}

sf::IpAddress Configuration::getServerAddress()
{
    return mInstance.mAddress;
}

unsigned short Configuration::getServerPort()
{
    return mInstance.mPort;
}

void Configuration::setUsername(std::string const& username)
{
    mInstance.mUsername = username;
}

void Configuration::setPassword(std::string const& password)
{
    mInstance.mPassword = password;
}

std::string Configuration::getUsername()
{
    return mInstance.mUsername;
}

std::string Configuration::getPassword()
{
    return mInstance.mPassword;
}

Configuration::Configuration()
{
    mPlayerInput = std::make_shared<thor::ActionMap<std::string>>();
    (*mPlayerInput)["up"] = thor::Action(sf::Keyboard::Z,thor::Action::Hold);
    (*mPlayerInput)["left"] = thor::Action(sf::Keyboard::Q,thor::Action::Hold);
    (*mPlayerInput)["down"] = thor::Action(sf::Keyboard::S,thor::Action::Hold);
    (*mPlayerInput)["right"] = thor::Action(sf::Keyboard::D,thor::Action::Hold);
    (*mPlayerInput)["stationary"] = thor::Action(sf::Keyboard::A,thor::Action::PressOnce);
    (*mPlayerInput)["speed"] = thor::Action(sf::Keyboard::LShift,thor::Action::Hold);
    (*mPlayerInput)["action1"] = thor::Action(sf::Mouse::Left,thor::Action::PressOnce);
    (*mPlayerInput)["action2"] = thor::Action(sf::Mouse::Right,thor::Action::PressOnce);
    (*mPlayerInput)["action3"] = thor::Action(sf::Mouse::Middle,thor::Action::PressOnce);

    mAddress = sf::IpAddress::LocalHost;
    mPort = 4567;
    mUsername = "test";
    mPassword = "test";
}

Configuration::~Configuration()
{
}
