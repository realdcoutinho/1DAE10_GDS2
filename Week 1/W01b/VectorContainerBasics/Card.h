#pragma once
class Texture;



class Card final
{
public:
	enum class Suit
	{
		clubs = 1,
		diamonds = 2,
		hearts = 3,
		spades = 4
	};

	explicit Card( Suit suit, int rank );
	~Card();
	void Draw( const Rectf& destRect ); // const member functions is new, will be explained in the theory

	static const int minRank;
	static const int maxRank;
	float m_Scale{0.5f}; // do I need it?
	float GetWidth();// const member functions is new, will be explained in the theory
	float GetHeight();// const member functions is new, will be explained in the theory
private:
	float m_Width;
	float m_Height;
	const Texture *m_pTexture;
	const Suit m_Suit;
	const int m_Rank;
	std::string GetImagePath(Suit suit, int rank);// const member functions is new, will be explained in the theory (it was 
	Rectf GenerateSourceRectangleForSprite(Texture texture);
};