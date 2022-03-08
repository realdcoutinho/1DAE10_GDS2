#include "pch.h"
#include "PowerUpManager.h"

PowerUpManager::PowerUpManager() 
{

}

PowerUpManager::~PowerUpManager()
{
	for (PowerUp* powerUp : m_pItems)
	{
		delete powerUp;
		powerUp = nullptr;
	}
}

PowerUp* PowerUpManager::AddItem(const Point2f& center, PowerUp::Type type)
{
	PowerUp* newPowerUp{ new PowerUp(center, type) };
	m_pItems.push_back(newPowerUp);
	return newPowerUp;
}

void PowerUpManager::Update(float elapsedSec)
{
	for (PowerUp* powerUp : m_pItems)
	{
		powerUp->Update(elapsedSec);
	}
}

void PowerUpManager::Draw() const
{
	for (PowerUp* powerUp : m_pItems)
	{
		powerUp->Draw();
	}
}

size_t PowerUpManager::Size() const
{
	return m_pItems.size();
}

bool PowerUpManager::HitItem(const Rectf& rect)
{
	int i{};
	for (PowerUp*& powerUp : m_pItems)
	{
		++i;
		if (powerUp->IsOverlapping(rect))
		{
			Swap(powerUp, m_pItems.at(Size() - 1));
			DeletePowerUp();
			return true;
		}
	}
	return false;
}

void PowerUpManager::Swap(PowerUp*& swapItem, PowerUp*& swapWithItem)
{
	std::swap(swapItem, swapWithItem);
}

void PowerUpManager::DeletePowerUp()
{
	delete m_pItems[Size() - 1];
	m_pItems[Size() - 1] = nullptr;
	m_pItems.pop_back();
}