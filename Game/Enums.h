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
	eResolutionMenu,
	eGame,
	eCutsceneManager
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
	eSize
};