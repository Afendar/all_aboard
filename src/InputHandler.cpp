#include "InputHandler.h"
#include "Action.h"

InputHandler::InputHandler()
{
	init();
}

InputHandler::~InputHandler()
{

}

void InputHandler::init()
{
	up = new Action(this);
	down = new Action(this);
	left = new Action(this);
	right = new Action(this);
	attack = new Action(this);
	backpack = new Action(this);
	achievements = new Action(this);
	crafting = new Action(this);
	select = new Action(this);
	exit = new Action(this);
	pause = new Action(this);
}

void InputHandler::releaseAll()
{
	for (unsigned int i = 0; i < keys.size(); ++i)
	{
		keys.at(i)->down = false;
	}
}

void InputHandler::tick()
{
	for (unsigned int i = 0; i < keys.size(); ++i)
	{
		keys.at(i)->tick();
	}
}

void InputHandler::handleKeys(sf::Event* evt)
{
	up->toggle(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
	down->toggle(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
	left->toggle(sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
	right->toggle(sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

	attack->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	backpack->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::B);
	select->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
	up->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	down->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	left->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	right->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	pause->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
	exit->clicked = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

void InputHandler::add(Action* key)
{
	keys.push_back(key);
}