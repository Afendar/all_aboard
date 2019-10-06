#include "Action.h"
#include "InputHandler.h"

Action::Action(InputHandler* inputHandler) :
	absorbs(0),
	presses(0),
	down(false),
	clicked(false)
{
	inputHandler->add(this);
}

Action::~Action()
{

}

void Action::toggle(bool pressed)
{
	if (pressed != down){
		down = pressed;
	}
	if (pressed){
		presses++;
	}
}

void Action::tick()
{
	/*if(absorbs < presses) {
	    absorbs++;
	    clicked = true;
	} else {
	    clicked = false;
	}*/
	if (clicked)
	{
		clicked = false;
	}
}