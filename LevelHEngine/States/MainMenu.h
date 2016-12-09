#pragma once

#include <SDL.h>
#include <iostream>
#include "State.h"
#include "StateManager.h"
#include "../ResourceManagement/ResourceManager.h"
#include "../States/MainMenu.h"


/**
@brief A State that contains and runs the Main Menu.
*/
class MainMenu : public State
{
public:
	/**
	@brief Constructs the State object.
	@param stateManager A pointer to the StateManager.
	@param window A pointer to the window in use.
	*/
	MainMenu(StateManager* stateManager, SDL_Window* window);

	/**
	@brief Destructs the State object.
	*/
	~MainMenu();

	/**
	@brief Handles the State input.
	@returns If false then quit the State.
	*/
	bool input();

	/**
	@brief A function to update the State.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief A function to draw the State to the screen.
	*/
	void draw();

private:
	///The background music id.
	std::string backgroundMusicID;
	///The sphere input bools
	bool s1F, s1B, s1L, s1R;
	bool s2F, s2B, s2L, s2R;
};