#pragma once
#include <string>

class Texture;

class Sprite final
{
public:
	explicit Sprite( const std::string& filename, int nrCols = 1, int nrRows = 1, float frameSec = 0 );
	Sprite(const Sprite& rhs); // copy constructor
	Sprite& operator=(const Sprite& rhs); // assignment operator
	Sprite(Sprite&& rhs) noexcept; // move constructor
	Sprite& operator=(Sprite&& rhs) noexcept; //move assignment operator
	~Sprite( );

	void Update( float elapsedSec );
	void Draw( const Point2f& pos, float scale = 1.0f ) const;

	float GetFrameWidth( );
	float GetFrameHeight( );

private:
	Texture *m_pTexture;
	int m_Cols;
	int m_Rows;
	float m_FrameSec;
	float m_AccuSec;
	int   m_ActFrame;
	std::string m_FilePath;
};


