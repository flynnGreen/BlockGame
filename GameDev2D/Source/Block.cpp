#include "Block.h"

GameDev2D::Block::Block(float interval) :
	m_Image(nullptr),
	m_Timer(nullptr)
{
	m_Image = new Sprite("Block");
	m_Timer = new Timer(interval, true);
}

GameDev2D::Block::~Block()
{
	SafeDelete(m_Image);
	SafeDelete(m_Timer);
}

void GameDev2D::Block::Draw()
{
	m_Image->Draw();
}

void GameDev2D::Block::Update(double delta)
{
	//If the block is currently in motion, update its timer
	if (m_IsMoving == true)
	{
		m_Timer->Update(delta);

		//If the timer is done, move the block to the next column
		if (m_Timer->IsDone())
		{
			//If the block hits the left or rightmost column, reverse its direction
			if (m_Column >= COLUMNAMT - 1 || m_Column <= 0)
			{
				//If block is currently moving right, switch its movement multiplier to left
				if (GetDirection() == MOVERIGHT)
				{
					SetDirection(MOVELEFT);
				}
				//If block is currently moving left, switch its movement multiplier to right
				else if (GetDirection() == MOVELEFT)
				{
					SetDirection(MOVERIGHT);
				}
			}

			//Allows block to keep track of which column its in
			SetColumn(GetColumn() + m_Direction);
			SetPositionX(GetColumn());

			//Restarts the timer
			m_Timer->Restart();
		}
	}
}

int GameDev2D::Block::GetLevel()
{
	return m_Level;
}

void GameDev2D::Block::SetLevel(int level)
{
	m_Level = level;
}

int GameDev2D::Block::GetColumn()
{
	return m_Column;
}

void GameDev2D::Block::SetColumn(int column)
{
	m_Column = column;
}

float GameDev2D::Block::GetDirection()
{
	return m_Direction;
}

void GameDev2D::Block::SetDirection(float direction)
{
	m_Direction = direction;
}

bool GameDev2D::Block::GetIsMoving()
{
	return m_IsMoving;
}

void GameDev2D::Block::SetIsMoving(bool isMoving)
{
	m_IsMoving = isMoving;
}

void GameDev2D::Block::SetPositionX(int column)
{
	//Loops through all columns and checks which column the block is currently in
	for (int i = 0; i < COLUMNAMT; i++)
	{
		if (i == column)
		{
			//Moves the sprite to the correct column
			m_Image->SetPositionX(COLUMNS[i]);
			break;
		}
	}
	//Updates the column variable to the current column
	SetColumn(column);
}

//Only called when the block is initialized, since a block's level doesn't change
void GameDev2D::Block::SetPositionY(int level)
{
	//Loops through all levels and checks which one the block is currently on
	for (int i = 0; i < LEVELAMT; i++)
	{
		if (i == level)
		{
			//Moves the sprite to the correct level
			m_Image->SetPositionY(LEVELS[i]);
		}
	}
	//Updates the level variable to the block's level
	SetLevel(level);
}

void GameDev2D::Block::StartTimer()
{
	m_Timer->Start();
}

void GameDev2D::Block::Restart()
{
	//Restarts timer
	m_Timer->Restart();
	//Enables block movement
	SetIsMoving(true);
	//Moves the block to its starting column
	SetColumn(STARTCOLUMN);
	//Sets block's direction to right
	m_Direction = MOVERIGHT;
}
