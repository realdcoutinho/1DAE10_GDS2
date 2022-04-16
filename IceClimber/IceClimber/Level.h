#pragma once
#include "Vector2f.h"
#include "utils.h"
#include "Texture.h"
#include "Blocks.h"
#include "Cloud.h"
#include "Bonus.h"
#include "WinningBird.h"
#include "Enemies.h"

#include "TextureManager.h"

#include <vector>

class Level final
{
public:
	explicit Level(float windowWidth, float windowHeight); //constructor
	Level(const Level& other) = delete; //copy constructor
	Level& operator=(const Level& other) = delete; // assignment operator
	Level(Level&& other) = delete; // move constructor
	Level& operator=(Level&& other) = delete; // move assignment operator
	~Level(); //destructor

	void Draw() const; // Draws all the Level Objects
	void Update(float elapsedSec); //updates
	void GetActorShape(const Rectf& actorShape); // hold the actor shape
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const; //handles collisons
	bool IsOnGround(const Rectf& actorShape, Vector2f& actorVelocity) const; //returns a bool value in case the player in on ground
	bool IsOnCloud(const Rectf& actorShape, Vector2f& actorVelocity) const; // is actor specifically on a cloud
	float GetScale() const; // return the scale
	void GetPlayerState(int state);
	Rectf GetBoundaries() const; // return the level boundries aka texture size
	std::vector<Vector2f> GetCloudVelocityVector() const; //return cloud velocity vector
	int GetCloudIndex() const; //returns cloud index
	Rectf GetBackgroundRect(); //returns texture rect
	bool IsWinning() const; 

	TextureManager* GetTextureManager() const;

private:
	void SetMeasures(); //sets measures variables inlcuding background rect
	void SetScale(); //sets the scale needed for the camera
	void SetSvgVertices(const std::string& svgPath, std::vector<std::vector<Point2f>>& svgVertices); // sets level collisons
	void InitializeBlocks(); // initializes blocks
	void InitializeClouds(); // initializes clouds
	void InitializeBonus(); // initializes bonus
	void InitializeEnemies(); // initializes Enemies
	void InitializeWinningBird(); // initializes winning Bird


	void DrawBackground() const; // draw multiple game objects
	void DrawForeground() const; // draw mountains (enemies will be bahind) and time
	void DrawGameObjects() const;
	void DrawNPC() const; //draws bonus

	void UpdateGameObjects(float elapsedSec); // updates clouds
	void UpdateNPC(float elapsedSec); //updates the enemy

	void HandleCollisionLevel(Rectf& actorShape, Vector2f& actorVelocity) const; //handles collision
	void HandleCollisionGameObjects(Rectf& actorShape, Vector2f& actorVelocity) const; //handles collision

	bool IsOnGroundLevel(const Rectf& actorShape, Vector2f& actorVelocity) const; //returns a bool when player in on the level
	bool IsOnGroundGameObjects(const Rectf& actorShape, Vector2f& actorVelocity) const; //return a bool when player in on blocks

	void GameObjectOverlap(const Rectf& actorShape);
	void NPCOverlap(const Rectf& actorShape);

	void SetCloudIndex(const Rectf& actorShape); // in which is the actor on top of?
	void DeleteTextures(); //deletes textures

	enum class BlockType //enum class of the various block types
	{
		green = 0,
		brown = 1,
		blue = 2
	};

	enum class CloudType //enum class of the cloud types
	{
		bottom = 0,
		top = 1,
	};

	float m_Scale; //holds the scale value

	float m_TextureHeight; //level height
	float m_TextureWidth; //level width
	float m_WindowWidth; 
	float m_WindowHeight;

	int m_CloudIndex; // which cloud is the player on

	int m_PlayerState;

	Rectf m_TextureRect; // game boundries
	Rectf m_ActorShape; // actor shape

	int m_NrOfObjects;
	std::vector<GameObject*> m_pGameObjects;

	int m_NrOfNPC;
	std::vector<NPC*> m_pNPC;

	TextureManager* m_pTextures;

	std::vector<Vector2f> m_CloudVelocity; //holds velocity vectors
	std::vector<std::vector<Point2f>> m_LevelCollison; // holds collison points
	const std::string m_LevelCollitionPath{ "./Images/IC_Level_Colission.svg" }; //file name path
};

