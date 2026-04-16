#pragma once
UENUM()
enum class ECharacterState : uint8
{
	ECS_UNARMED,
	ECS_ArmedSword,
	ECS_ArmedTwoSword,
	ECS_ArmedBow,
};

UENUM()
enum class ECharacterState_montage : uint8
{
	ECS_Idle,
	ECS_Attack0,
	ECS_Attack1,
	ECS_StartDefend,
	ECS_Defend,
	ECS_Playing,
};

UENUM()
enum class EEnemyState : uint8
{
	EES_Idle,
	EES_Patrol,
	EES_Approach,
	EES_Chasing,
	EES_Fight,
	EES_Attacking,
	EES_Searching,
	EES_Dead,
	EES_GetHit
};

