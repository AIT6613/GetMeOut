#include "GameStateMachine.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::pushState(GameState* state) {
	//add to our vector ;)
	gameStates.push_back(state);
	//call onEnter on newest state
	gameStates.back()->onEnter();
}
void GameStateMachine::changeState(GameState* state) {
	if (!gameStates.empty()) {
		//if state same as what we're trying to change to, then exit early
		if (gameStates.back()->getStateID() == state->getStateID())
			return;

		//run onExit for top state in stack and then remove it
		if (gameStates.back()->onExit()) {
			delete gameStates.back(); //delete the dynamically allocated state in top position
			gameStates.pop_back(); //remove the now useless state pointer from our stack
		}
		else
		{
			cout << "Error running onExit for state: " << gameStates.back()->getStateID() << endl;
		}
	}
	//add the new state
	pushState(state);

}
void GameStateMachine::popState() {
	//remove top state
	if (!gameStates.empty()) {
		//run onExit for top state in stack and then remove it
		if (gameStates.back()->onExit()) {
			delete gameStates.back(); //delete the dynamically allocated state in top position
			gameStates.pop_back(); //remove the now useless state pointer from our stack
		}
		else
		{
			cout << "Error running onExit for state: " << gameStates.back()->getStateID() << endl;
		}
	}
}
void GameStateMachine::clearAll() {
	//delete all the dynamic memory first
	for (auto gs : gameStates) {
		delete gs;
	}
	//then clear stack
	gameStates.clear();
}

void GameStateMachine::update() {
	if (!gameStates.empty())
		gameStates.back()->update();
}
void GameStateMachine::render() {
	if (!gameStates.empty())
		gameStates.back()->render();
}
