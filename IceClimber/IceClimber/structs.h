#pragma once
#include <string>

struct Window
{
	explicit Window( const std::string& title = "Title", float width = 320.0f, 
		float height = 180.0f, bool isVSyncOn = true );

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f( );
	explicit Point2f( float x, float y );
	Point2f& operator*=(float scale);

	float x;
	float y;
};

struct Line2f
{
	Line2f();
	explicit Line2f(const Point2f& point1, const Point2f& point2);

	Point2f point1;
	Point2f point2;
};



struct Rectf //jesus code, thanks
{
	Rectf();
	explicit Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;

	void Log();
	void SetBottomLeft(const Point2f& point);
	Point2f GetBottomLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetBottomCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetBottomRight(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopRight(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenterLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenter() const;
	Point2f GetCenterRight(float offsetX = 0, float offsetY = 0) const;
};


struct Color4f
{
	Color4f( );
	explicit Color4f( float r, float g, float b, float a );
	
	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef( );
	explicit Circlef( const Point2f& center, float radius );
	explicit Circlef( float centerX, float centerY, float radius );

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef( );
	explicit Ellipsef( const Point2f& center, float radiusX, float radiusY );
	explicit Ellipsef( float centerX, float centerY, float radiusX, float radiusY );

	Point2f center;
	float radiusX;
	float radiusY;
};



