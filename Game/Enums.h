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
	eCutsceneManager,
	eCharacterSelection,
	eEndOfGameCutscene
};
enum class EWorldLevel
{
	eWorld1,
	eWorld2,
	eWorld3,
	eWorld4
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
	ePowerR,
	ePowerL
};

enum class EPowerUp
{
	Default = 1,
	DoubleJump = 2,
	Glide = 3
};







