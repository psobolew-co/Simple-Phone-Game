#pragma once

#include "SpriteBatch.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>
#include "Windows.h"
#include <list>
#include <vector>

using namespace DirectX;
using namespace std;

/*
The variables needed to properly manipulate this class outside of its internal methods are
animationState and shouldChangeAnimation.  These two must be changed in tandem to properly change the animation
of the sprite.  Furthermore, this class works under the assumption that the new animation is looping - that is,
the sprite will never switch to a different animation cycle automatically - it has to be triggered using the aforementioned variables.
Therefore, if you want an animation cycle to only run once, use the animationPlayedOnce variable to know when to change the loop back to something else.
*/
class Sprite
{
public:

	Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds);
	Sprite(ID3D11ShaderResourceView *m_Texture, XMFLOAT2 size, XMFLOAT2 position, Windows::Foundation::Rect* movementBounds, int rows, int columns,
		double framesPerSecond, int dividers[]);

	int currentFrame;

	int animationState; //value that controls which part of the sprite sheet to animate (therefore, created sprites MUST modify this value)
	bool shouldChangeAnimation; //this value works in tandem with animationState

	Windows::Foundation::Rect* movementBounds;
	Windows::Foundation::Rect* BoundingBox;
	XMFLOAT2 position;
	XMFLOAT2 size;

	void Draw(SpriteBatch* spriteBatch);
	virtual void Update(float timeTotal, float timeDelta);
	XMFLOAT2 Velocity;

	float getWidth();
	float getHeight();

private:
	int rows;
	int columns;
	int framesPerSecond;
	int totalFrames;
	double timeSinceLastFrame;

	Windows::Foundation::Rect* Sprite::CreateBoundingBoxFromPosition(XMFLOAT2 position);
	void UpdateAnimation(float timeTotal, float timeDelta);
	double SecondsBetweenFrames();

protected:
	bool animationPlayedOnce;
	int dividers[5];
	float Speed;
	ID3D11ShaderResourceView* m_Texture;

	bool Blocked(XMFLOAT2 newPosition);
};
