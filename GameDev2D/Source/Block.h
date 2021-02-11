#pragma once
#include <GameDev2D.h>
#include "Constants.h"
#include "Timer.h"

namespace GameDev2D
{
	class Block
	{
	public:
		//Constructor
		Block(float interval);

		//Destructor
		~Block();
		
		void Draw();
		void Update(double delta);

		//Level getter and setter (same as row)
		int GetLevel();
		void SetLevel(int level);

		//Column getter and setter
		int GetColumn();
		void SetColumn(int column);

		//Movement getter and setter
		bool GetIsMoving();
		void SetIsMoving(bool isMoving);

		//Controls movement
		void SetPositionX(int column);
		void SetPositionY(int level);

		//Starts the timer which controls the block's movement interval
		void StartTimer();

		//Places the block at its initial position
		void Restart();

	private:
		//Direction getter and setter
		float GetDirection();
		void SetDirection(float direction);

		//Member variables
		Sprite* m_Image;
		Timer* m_Timer;

		//Checks if block is currently in motion
		bool m_IsMoving = false;
		
		//The interval at which the block moves
		float m_Interval;

		//Which row the block is on. Doesn't change
		unsigned int m_Level;

		//Which column the block is currently on
		unsigned int m_Column = STARTCOLUMN;
		float m_Direction = MOVERIGHT;
	};
}