#pragma once

#include <GameDev2D.h>
#include "Block.h"
#include "Constants.h"
#include "Timer.h"
#include <string>

namespace GameDev2D
{
	//Class definition
	class Game
	{
	public:
		Game();  //Constructor
		~Game(); //Destructor

		//Write game logic in the Update method
		void Update(double delta);

		//Render game objects in the Draw method
		void Draw();

		//Input methods
		void HandleLeftMouseClick(float mouseX, float mouseY);
		void HandleRightMouseClick(float mouseX, float mouseY);
		void HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY);
		void HandleKeyPress(Keyboard::Key key);
		void HandleKeyReleased(Keyboard::Key key);

		//Handles losses
		void Lose();
		
	private:
		//Member variables GO HERE 
		Sprite* m_Background;

		//Right and left UI sprites
		Sprite* m_uiR[LEVELAMT];
		Sprite* m_uiL[LEVELAMT];
		Sprite* m_uiWinnerR;
		Sprite* m_uiWinnerL;

		//Audio files
		Audio* m_Music;
		Audio* m_LevelUp;
		Audio* m_Victory;
		Audio* m_Strike;

		//Array of block objects
		Block* m_Blocks[LEVELAMT];

		//Keeps track of which block is currently controllable
		unsigned int m_CurrentBlock = 0;
	};
}
