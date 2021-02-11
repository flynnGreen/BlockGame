#include "Game.h"

namespace GameDev2D
{
	Game::Game() : 
		m_Background(nullptr),
		m_uiR{ nullptr },
		m_uiL{ nullptr },
		m_uiWinnerR(nullptr),
		m_uiWinnerL(nullptr),
		m_Music(nullptr),
		m_LevelUp(nullptr),
		m_Victory(nullptr),
		m_Strike(nullptr),
		m_Blocks{ nullptr }
	{
		//Textures
		LoadTexture("Background");
		LoadTexture("Block");
		LoadTexture("Level1");
		LoadTexture("Level2");
		LoadTexture("Level3");
		LoadTexture("Level4");
		LoadTexture("Level5");
		LoadTexture("Winner");

		//Audio
		LoadAudio("Music");
		LoadAudio("LevelUp");
		LoadAudio("Victory");
		LoadAudio("Strike");

		//Sprites
		m_Background = new Sprite("Background");
		m_uiWinnerR = new Sprite("Winner");
		m_uiWinnerL = new Sprite("Winner");

		//Audio
		m_Music = new Audio("Music");
		m_LevelUp = new Audio("LevelUp");
		m_Victory = new Audio("Victory");
		m_Strike = new Audio("Strike");

		//Cycles through every block and and UI sprite, winner UI excepted, and preps it
		for (int i = 0; i < LEVELAMT; i++)
		{
			//BLOCK INITIALIZATION SECTION
			//Initializes each block and sets its movement interval
			m_Blocks[i] = new Block(SPEEDS[i]);

			//Places each block on the correct level
			m_Blocks[i]->SetLevel(i);

			//Places each sprite in its correct level and column. They are not drawn yet
			m_Blocks[i]->SetPositionX(m_Blocks[i]->GetColumn());
			m_Blocks[i]->SetPositionY(m_Blocks[i]->GetLevel());

			//UI INITIALIZATION SECTION
			//Initializes UI sprites
			m_uiR[i] = new Sprite(UIFILENAMES[i]);
			m_uiL[i] = new Sprite(UIFILENAMES[i]);

			//Placess UI sprites at the correct location on either side of the screen, accounting for sprite width
			m_uiR[i]->SetPosition(GetScreenWidth() - m_uiR[i]->GetWidth() - UIBUFFER, UIBUFFER);
			m_uiL[i]->SetPosition(UIBUFFER, UIBUFFER);
		}

		//Sets Winner UI at the correct location, same as the regular UI
		m_uiWinnerR->SetPosition(GetScreenWidth() - m_uiWinnerR->GetWidth() - UIBUFFER, UIBUFFER);
		m_uiWinnerL->SetPosition(UIBUFFER, UIBUFFER);

		//Starts music and loops it
		m_Music->SetDoesLoop(true);
		m_Music->Play();

		//Sets the first block to its default state
		m_Blocks[0]->Restart();
	}

	Game::~Game()
	{
		SafeDelete(m_uiWinnerL);
		SafeDelete(m_uiWinnerR);
		SafeDelete(m_Strike);
		SafeDelete(m_Victory);
		SafeDelete(m_LevelUp);
		SafeDelete(m_Music);
		SafeDelete(m_Background);
		
		for (int i = 0; i < LEVELAMT; i++)
		{
			SafeDelete(m_Blocks[i]);

			SafeDelete(m_uiR[i]);
			SafeDelete(m_uiL[i]);
		}

		UnloadAudio("Strike");
		UnloadAudio("Victory");
		UnloadAudio("LevelUp");
		UnloadAudio("Music");

		UnloadTexture("Background");
		UnloadTexture("Block");
		UnloadTexture("Level1");
		UnloadTexture("Level2");
		UnloadTexture("Level3");
		UnloadTexture("Level4");
		UnloadTexture("Level5");
		UnloadTexture("Winner");
	}

	void Game::Update(double delta)
	{
		//Calls each block's update method every frame
		for (int i = 0; i < LEVELAMT; i++)
		{
			m_Blocks[i]->Update(delta);
		}
	}

	void Game::Draw()
	{
		//Draws the background sprite
		m_Background->Draw();

		//If the current block being controlled is after the final block, draw the winner screen
		if (m_CurrentBlock == LEVELAMT)
		{
			m_uiWinnerR->Draw();
			m_uiWinnerL->Draw();
		}
		//Else, draw the current block and the UI of the current level
		else
		{
			m_uiR[m_CurrentBlock]->Draw();
			m_uiL[m_CurrentBlock]->Draw();
			m_Blocks[m_CurrentBlock]->Draw();
		}

		//Loop through the past blocks, drawing them and the current controlled block
		for (int i = 0; i < m_CurrentBlock; i++)
		{
			m_Blocks[i]->Draw();
		}
	}

	void Game::HandleLeftMouseClick(float mouseX, float mouseY)
	{
		
	}

	void Game::HandleRightMouseClick(float mouseX, float mouseY)
	{

	}

	void Game::HandleMouseMove(float mouseX, float mouseY, float previousX, float previousY)
	{
		
	}

	void Game::HandleKeyPress(Keyboard::Key key)
	{
		//If spacebar is pressed, check if block should be stopped. If so, stop it
		if (key == Keyboard::Spacebar)
		{
			//If the current controlled block is not the final block
			if (m_CurrentBlock < LEVELAMT - 1)
			{
				//Loop through all blocks
				for (int i = 0; i < LEVELAMT; i++)
				{
					//Checks if the current controlled block has another block beneath it, or is the bottom block
					if (m_CurrentBlock == 0 || m_Blocks[m_CurrentBlock - 1]->GetColumn() == m_Blocks[i]->GetColumn())
					{
						//Checks if the block is currently in motion
						if (m_Blocks[i]->GetIsMoving() == true)
						{
							//Stop block from moving
							m_Blocks[i]->SetIsMoving(false);

							//Changes the block being controlled to the next level
							m_CurrentBlock++;

							//Starts movement of new current controlled block
							m_Blocks[m_CurrentBlock]->Restart();

							//Play level up SFX
							m_LevelUp->Play();

							break;
						}
					}
					//If current controlled block has an empty space beneath it, trigger a loss
					else
					{
						Lose();
						break;
					}
				}
			}
			//Checks if the current controlled block is the final block AND has another block beneath it, the game is won
			else if (m_Blocks[LEVELAMT - 1]->GetColumn() == m_Blocks[LEVELAMT - 2]->GetColumn())
			{
				/*Sets the current controlled block to the one after the final block,
				telling the winner UI sprite to be drawn in Update*/
				m_CurrentBlock = LEVELAMT;

				//Locks the final block in place
				m_Blocks[LEVELAMT - 1]->SetIsMoving(false);
				m_Victory->Play();
			}
			//If the final block has an empty space beneath it, triggers a loss
			else
			{
				Lose();
			}
		}

		//If R is pressed, reset game
		if (key == Keyboard::R)
		{
			//Loops through every block and resets each one
			for (int i = 0; i < LEVELAMT; i++)
			{
				//Sets each block to its initial state
				m_Blocks[i]->Restart();
				//Restart music
				m_Music->Play();
			}

			//Sets the current block to the bottom one
			m_CurrentBlock = 0;
		}
	}

	void Game::HandleKeyReleased(Keyboard::Key key)
	{

	}
	void Game::Lose()
	{
		//Loops through every completed block, and the current one, and resets each one
		for (int i = 0; i <= m_CurrentBlock; i++)
		{
			//Sets each completed block to its initial state
			m_Blocks[i]->Restart();
			//Play loss sound
			m_Strike->Play();
		}

		//Sets the current block to the bottom one
		m_CurrentBlock = 0;
	}
}