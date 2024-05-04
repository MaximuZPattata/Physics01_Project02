#pragma once
#include "pch.h"
#include <cControlGameEngine.h>

class cTieFighter
{
public:
	void Initialize(std::string meshName, std::string orbName, glm::vec3 position, float acceleration, float deceleration, float dampingFactor, float maxSpeed, float rotationSpeed);

    void UpdatePosition(cControlGameEngine gameEngine);
	void UpdateOrbPosition(cControlGameEngine gameEngine);

	glm::vec3 GetCamPosition();
	glm::vec3 GetPosition();

    void MoveForward(float deltaTime);
	void TurnLeft(float deltaTime);
	void TurnRight(float deltaTime);
	void SetCollision();

private:
	std::string mMeshName;
	std::string mOrbMeshName;

	glm::vec3 mPosition = glm::vec3(0.f);
	glm::vec3 mVelocity = glm::vec3(0.f);
	
	float mAcceleration = 0.f;   
	float mDeceleration = 0.f;   
	float mDampingFactor = 0.f;
    float mCurrentSpeed = 0.f;
	float mMaxSpeed = 0.f;
	float mRotationSpeed = 0.f;
	float mCurrentRotationSpeed = 0.f;
	float mMaxRotationAngle = glm::radians(45.0f);
	float mSpeedOffset = 0.6f;

	bool bMoveForward = false;
	bool bTurnLeft = false;
	bool bTurnRight = false;
	bool bCollision = false;
};

