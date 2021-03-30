#pragma once
#include <memory.h>
#include "CommonUtilities/Vector2.hpp"

class RenderCommand;
class AnimationClip
{
public:
	AnimationClip(const char* aImagePath, const int aLayer, const int aAnimationClip);
	~AnimationClip() = default;

	void Init(const CommonUtilities::Vector2ui& aAmountOfFrames, const CommonUtilities::Vector2ui& aEndFrame);
	void UpdateAnimation(const CommonUtilities::Vector2f& aPos);
	
	const int GetAnimationTypeIndex() const;
	const RenderCommand& GetRenderCommand() const;
	RenderCommand& GetRenderCommand();
	
	//TestMethod
	void Render();

	//Animation Methods
	void Activate();
	void Deactivate();
	void ActivateLooping();
	void DeactivateLooping();
	void PlayReverseAnim();
	void ReverseAnim();

	void PlayAnimOnce(const float aSpeed = 0.08333f);
	void PlayAnimLoop(const float aSpeed = 0.08333f);

	const bool GetAnimIsLooping() const;
	const bool GetAnimIsDone() const;
	const bool GetAnimIsPlaying() const;
	const CommonUtilities::Vector2ui& GetCurrentFrame() const;
	//1.f, 1.f is normal scale.
	void SetScaleRelativeToFrame(const CommonUtilities::Vector2f& aScale);

	//Reset to frame (1, 1)
	void ResetAnimation();
	void SetFrame(const CommonUtilities::Vector2ui& aCurrentFrame);



private:
	void SetFrame();
	void PlayForward();
	void PlayBackward();


	bool myIsAnimating;
	bool myIsLooping;
	bool myIsPlayingBackwards;
	bool myAnimationIsDone;

	std::unique_ptr<RenderCommand> myRenderCommand;
	int myAnimationClipIndex;
	// Frames 
	int myFrameInAnimation;
	CommonUtilities::Vector2ui myCurrentFrame;
	CommonUtilities::Vector2ui myAmountOfFrames;
	CommonUtilities::Vector2ui myEndFrame;

	CommonUtilities::Vector2f myPosition;
	CommonUtilities::Vector2f mySize;
	CommonUtilities::Vector2f myOriginalSize;
	CommonUtilities::Vector2f myRectSize;

	float myCurrentAnimationTime;
	float myAnimationSpeed;
	
};

