#pragma once
class Texture;

class PowerUp final
{
public:
	enum class Type 
	{  
		green = 1, 
		brown = 2	
	};
	explicit PowerUp(const Point2f& center, PowerUp::Type type );
	~PowerUp();
	void Update( float elapsedSec );
	void Draw(); //const;
	bool IsOverlapping(const Rectf& rect ) const;

	float GetWidth();
	float GetHeight();
	

private:

	const Type m_Type;
	const Texture* m_pTexture;
	float m_TextureWidth;
	float m_TextureHeight;

	const float m_RotSpeed;
	Rectf m_TextClip;
	Circlef m_Shape;
	float m_Angle;
};


