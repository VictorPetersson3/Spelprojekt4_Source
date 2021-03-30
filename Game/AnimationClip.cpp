#include "stdafx.h"
#include "AnimationClip.h"
#include "RenderCommand.h"
#include <assert.h>
#include "Timer.h"

AnimationClip::AnimationClip(const char* aImagePath, const int aLayer, const int aAnimationClip)
{
	myIsAnimating = false;
	myIsLooping = false;
	myIsPlayingBackwards = false;
	myAnimationIsDone = false;
	myRenderCommand = nullptr;
	myAnimationClipIndex = aAnimationClip;
	myFrameInAnimation = 1;
	myCurrentAnimationTime = 0;
	myAnimationSpeed = 0.08333f;
	mySize = mySize.One();
	myOriginalSize = mySize;
	myRenderCommand = std::make_unique<RenderCommand>(aImagePath, aLayer);
}

void AnimationClip::Init(const CommonUtilities::Vector2ui& aAmountOfFrames, const CommonUtilities::Vector2ui& aEndFrame)
{
	const float EPSILON = 0.00001f;
	myRectSize.x = (1 / static_cast<float>(aAmountOfFrames.x)) - EPSILON;
	myRectSize.y = (1 / static_cast<float>(aAmountOfFrames.y)) - EPSILON;
	myRenderCommand->SetTextureRect(myRectSize.x - myRectSize.x, myRectSize.y - myRectSize.y, myRectSize.x, myRectSize.y);
	mySize.x = mySize.x / static_cast<float>(aAmountOfFrames.x);
	mySize.y = mySize.y / static_cast<float>(aAmountOfFrames.y);
	myOriginalSize = mySize;
	myRenderCommand->SetSizeRelativeToImage(mySize);
	myAmountOfFrames = aAmountOfFrames;
	myEndFrame = aEndFrame;
}

void AnimationClip::UpdateAnimation(const CommonUtilities::Vector2f& aPos)
{
	myPosition = aPos;
	myRenderCommand->Update(aPos);
	if (myIsAnimating)
	{
		if (!myIsPlayingBackwards)
		{
			PlayForward();
		}
		else
		{
			PlayBackward();
		}
	}
}

const int AnimationClip::GetAnimationTypeIndex() const { return myAnimationClipIndex; }

const RenderCommand& AnimationClip::GetRenderCommand() const {	return *myRenderCommand; }
RenderCommand& AnimationClip::GetRenderCommand() {	return *myRenderCommand; }

void AnimationClip::Render()
{
	myRenderCommand->Render();
}

void AnimationClip::Activate() { myIsAnimating = true; }

void AnimationClip::Deactivate() { myIsAnimating = false; }

void AnimationClip::ActivateLooping(){ myIsLooping = true; }

void AnimationClip::DeactivateLooping(){ myIsLooping = false; }

void AnimationClip::PlayReverseAnim()
{
	myIsPlayingBackwards = !myIsPlayingBackwards;
	myIsAnimating = true;
	myAnimationIsDone = false;
}

void AnimationClip::ReverseAnim()
{
	myIsPlayingBackwards = !myIsPlayingBackwards;
}

void AnimationClip::PlayAnimOnce(const float aSpeed)
{
	myAnimationIsDone = false;
	myAnimationSpeed = aSpeed;
	myIsLooping = false;
	myCurrentFrame = { 1 , 1 };
	Activate();
}

void AnimationClip::PlayAnimLoop(const float aSpeed)
{
	myAnimationIsDone = false;
	myAnimationSpeed = aSpeed;
	myCurrentFrame = { 1 , 1 };
	myIsLooping = true;
	Activate();
}

const bool AnimationClip::GetAnimIsLooping() const
{
	return myIsLooping;
}

const bool AnimationClip::GetAnimIsDone() const{	return myAnimationIsDone;}

const bool AnimationClip::GetAnimIsPlaying() const{	return myIsAnimating;}

const CommonUtilities::Vector2ui& AnimationClip::GetCurrentFrame() const { return myCurrentFrame; }


void AnimationClip::SetScaleRelativeToFrame(const CommonUtilities::Vector2f& aScale)
{

	mySize = myOriginalSize * aScale;
	myRenderCommand->SetSizeRelativeToImage(mySize);
}

void AnimationClip::ResetAnimation()
{
	myCurrentFrame = { 1 , 1 };
}

void AnimationClip::SetFrame(const CommonUtilities::Vector2ui& aCurrentFrame)
{
	assert(aCurrentFrame.x != 0 || aCurrentFrame.y != 0 && "aCurrentFrame can not be 0");
	myCurrentFrame = aCurrentFrame;
	myRenderCommand->SetTextureRect(
		myRectSize.x * myCurrentFrame.x - myRectSize.x,	//TopLeftX Current Frame
		myRectSize.y * myCurrentFrame.y - myRectSize.y,	//TopLeftY Current Frame
		myRectSize.x * myCurrentFrame.x,				//BotLeftX Current Frame
		myRectSize.y * myCurrentFrame.y);				//BotLeftY Current Frame
}
//Internal Setter for the animator
void AnimationClip::SetFrame()
{
	myRenderCommand->SetTextureRect(
		myRectSize.x * myCurrentFrame.x - myRectSize.x,	//TopLeftX Current Frame
		myRectSize.y * myCurrentFrame.y - myRectSize.y,	//TopLeftY Current Frame
		myRectSize.x * myCurrentFrame.x,				//BotLeftX Current Frame
		myRectSize.y * myCurrentFrame.y);				//BotLeftY Current Frame
}

void AnimationClip::PlayForward()
{
	myCurrentAnimationTime += Timer::GetInstance().GetDeltaTime();
	if (myCurrentAnimationTime > myAnimationSpeed)
	{
		if (myCurrentFrame.y  == myAmountOfFrames.y)
		{
			if (myCurrentFrame.x < myEndFrame.x)
			{
				myCurrentFrame.x++;
			}
			else
			{
				if (myIsLooping)
				{
					myCurrentFrame.x = 1;
					myCurrentFrame.y = 1;
				}
				else
				{
					myIsAnimating = false;
					myAnimationIsDone = true;
				}
			}
		}
		else
		{
			if (myCurrentFrame.x < myAmountOfFrames.x)
			{
				myCurrentFrame.x++;
			}
			else 
			{
				myCurrentFrame.x = 1;
				myCurrentFrame.y++;
			}
		}
		myCurrentAnimationTime = 0;
	}
	SetFrame();
}

void AnimationClip::PlayBackward()
{
	myCurrentAnimationTime += Timer::GetInstance().GetDeltaTime();
	if (myCurrentAnimationTime > myAnimationSpeed)
	{
		if (myCurrentFrame.y == 1)
		{
			if (myCurrentFrame.x > 1)
			{
				myCurrentFrame.x--;
			}
			else
			{
				if (myIsLooping)
				{
					myCurrentFrame = myEndFrame;
				}
				else
				{
					myIsAnimating = false;
					myAnimationIsDone = true;
				}
			}
		}
		else
		{
			if (myCurrentFrame.x > 1)
			{
				myCurrentFrame.x--;
			}
			else
			{
				myCurrentFrame.x = myAmountOfFrames.x;
				myCurrentFrame.y--;
			}
		}
		myCurrentAnimationTime = 0;
	}
	SetFrame();
}



