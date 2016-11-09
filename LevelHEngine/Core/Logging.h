#pragma once

#include <string>
#include <SDL.h>
#include <fstream>
#include <time.h>

/**
@brief The namespace for all core code.
*/
namespace Core
{

	/**
	@brief A namespace that contains logging functions for use within the code.
	*/
	namespace Logging
	{

		/**
		@brief Logs the information message, this prints the message to the log file by default.
		@param message The message.
		*/
		void logI(std::string message);

		/**
		@brief Logs the error message, this prints the message to the log file by default.
		@param message The message.
		*/
		void logE(std::string message);

		/**
		@brief Logs the information message.
		@param message The message.
		@param printToLog A boolean for whether to print to the log.
		*/
		void logI(std::string message, bool printToLog);

		/**
		@brief Logs the error message.
		@param message The message.
		@param printToLog A boolean for whether to print to the log.
		*/
		void logE(std::string message, bool printToLog);

		/**
		@brief Prints the message out into the log file.
		@param message The message.
		*/
		void printToLogFile(std::string message);

		/**
		@brief Gets the current date and time in the form of a string.
		@returns The current date and time.
		*/
		std::string getCurrentDateAndTime();

		/**
		@brief Converts a boolean to a string.
		@param booleanIn The boolean to be converted.
		@returns The boolean as a string.
		*/
		std::string boolToString(bool booleanIn);

	}//End of Logging namespace

}//End of Core namespace