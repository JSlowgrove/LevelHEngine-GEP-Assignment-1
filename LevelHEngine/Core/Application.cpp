#include "Application.h"

namespace Core
{

	Application::Application(std::string title, Maths::Vec2 windowPos, Maths::Vec2 windowRes, bool fullscreen, float frameRate)
		: WindowFrame(title, windowPos, windowRes, fullscreen, frameRate)
	{
	}

	Application::~Application()
	{
	}

	void Application::init(int argc, char *argv[])
	{
		//Initialise SDL
		initSDL();
		initTTF();
		initMixer();

		// Set the OpenGL context profile
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


		if (getFullscreen())
		{
			//Create Window
			Maths::Vec2 windowPos = Maths::Vec2(0, 0);
			window = SDL_CreateWindow(getTitle().c_str(),
				(int)getWindowPos().x, (int)getWindowPos().y,
				(int)getWindowRes().x, (int)getWindowRes().y,
				SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else
		{
			//Create Window
			window = SDL_CreateWindow(getTitle().c_str(),
				(int)getWindowPos().x, (int)getWindowPos().y,
				(int)getWindowRes().x, (int)getWindowRes().y,
				SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		}

		//Create an OpenGL context for the renderer
		glcontext = SDL_GL_CreateContext(window);

		//Initialise GLEW
		initGLEW();

		//Enable the depth test to make sure triangles in front are always in front no matter the order they are drawn
		glEnable(GL_DEPTH_TEST);
	}

	void Application::run()
	{
		//Time Check
		unsigned int lastTime = SDL_GetTicks();

		//Start Game Loop
		bool go = true;
		while (go)
		{
			//Time Check
			unsigned int current = SDL_GetTicks();
			float deltaTime = (float)(current - lastTime) / 1000.0f;
			lastTime = current;

			//input
			go = tmpInput();

			//update

			//clear the frame-buffer to black
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			//write colour to the frame-buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//draw

			//display the window
			SDL_GL_SwapWindow(window);

			//Time Limiter
			if (deltaTime < (1.0f / getFrameRate()))
			{
				SDL_Delay((unsigned int)(((1.0f / getFrameRate()) - deltaTime) * 1000.0f));
			}
		}
	}

	void Application::destroy()
	{
		//Destroy data
		SDL_GL_DeleteContext(glcontext);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	bool Application::initGLEW()
	{
		//Temporary workaround to fix GLEW's problem with loading core OpenGL by enabling its experimental features (Details: https://www.opengl.org/wiki/OpenGL_Loading_Library)
		glewExperimental = GL_TRUE;

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			//Failed initialisation 
			Logging::logE("GLEW failed to initialise: " + std::string(reinterpret_cast<const char *>(glewGetErrorString(err))));
			return false;
		}

		//Log GLEW and OpenGL details
		Logging::logI("Using GLEW " + std::string(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION))));
		Logging::logI("OpenGL Vendor: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VENDOR))));
		Logging::logI("OpenGL Renderer: " + std::string(reinterpret_cast<const char *>(glGetString(GL_RENDERER))));
		Logging::logI("OpenGL Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_VERSION))));
		Logging::logI("OpenGL Shading Language Version: " + std::string(reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION))));

		return true;
	}

	bool Application::initSDL()
	{
		//Initialise SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			//Failed initialisation
			Logging::logE("SDL failed to initialise: " + std::string(SDL_GetError()));
			return false;
		}
		return true;
	}

	bool Application::initTTF()
	{
		//Initialise SDL_ttf
		if (TTF_Init() < 0)
		{
			//Failed initialisation
			Logging::logE("SDL_ttf failed to initialise: " + std::string(TTF_GetError()));
			return false;
		}
		return true;
	}

	bool Application::initMixer()
	{
		//Initialise SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			Logging::logE("SDL_mixer failed to initialise: " + std::string(Mix_GetError()));
			return false;
		}
		return true;
	}








	//ONLY TEMPORARY
	bool Application::tmpInput()
	{
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			switch (incomingEvent.type)
			{
			case SDL_QUIT: //If player closes the window, end the game loop

				return false;
				break;

			case SDL_KEYDOWN:

				switch (incomingEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE: //If Escape is pressed, end the game loop

					return false;
					break;
				}
			}
		}
		return true;
	}

}// End of Core namespace