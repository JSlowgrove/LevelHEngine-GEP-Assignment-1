//DISCLAIMER - This a modified version of code from a previous assignment

#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "../Core/Logging.h"

/**
@brief Handles music using SDL_Mixer.
*/
class Music
{
public:
	/**
	@brief Constructs the Music object.
	@param file The file to be loaded.
	*/
	Music(std::string file);

	/**
	@brief Destructs the Music object.
	*/
	~Music();

	/**
	@brief Starts the Music playing, also checks if not playing and starts again.
	*/
	void startMusic();

	/**
	@brief Stops the Music playing.
	*/
	void stopMusic();

	/**
	@brief Mute the Music.
	*/
	void muteMusic();

	/**
	@brief Un-mute the Music.
	*/
	void unmuteMusic();

private:
	///Variable for the music.
	Mix_Music* music;
};