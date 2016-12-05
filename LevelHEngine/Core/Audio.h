#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "Logging.h"

/**
@brief The namespace for all core code.
*/
namespace Core
{

	/**
	@brief Handles audio using SDL_Mixer.
	*/
	class Audio
	{
	public:
		/**
		@brief Constructs the Audio object.
		@param file The file to be loaded.
		*/
		Audio(std::string file);

		/**
		@brief Destructs the Audio object.
		*/
		~Audio();

		/**
		@brief Plays the sound effect.
		*/
		void playEffect();

	private:
		///Variable for the audio.
		Mix_Chunk* audio;
	};

}// End of Core namespace