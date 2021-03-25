#pragma once
enum class EStateType
{
	eNull,
	eMainMenu,
	eOptionsMenu,
	eControllerLayout,
	eLevelSelect,
	ePauseMenu,
	eEndOfLevelScreen,
	eGame
};
enum class EPlayerAnimationClips
{
	eIdleR,
	eIdleL,
	eRunR,
	eRunL,
	eSprintR,
	eSprintL,
	eJumpR,
	eJumpL,
	eLandR,
	eLandL,
	eWallIdleR,
	eWallIdleL,
	eWallDownR,
	eWallDownL,
	eWallUpR,
	eWallUpL,
	eWallJumpR,
	eWallJumpL,
	eDeathR,
	eDeathL,
	eDoubleJumpR,
	eDoubleJumpL,
	eGlideR,
	eGlideL
};

enum class EPowerUp
{
	Default = 1,
	DoubleJump = 2,
	Glide = 3
};







