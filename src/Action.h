#pragma once
class InputHandler;

class Action
{
	public:
		Action(InputHandler* inputHandler);
		~Action();
		int presses, absorbs;
		bool down, clicked;

		void toggle(bool pressed);
		void tick();

	private:
		friend class InputHandler;
};