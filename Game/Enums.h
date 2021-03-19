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
	eSprint,
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
	eSize
};
