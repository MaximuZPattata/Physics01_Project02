#include "pch.h"
#include "cAnimationCommand.h"

cAnimationCommand::cAnimationCommand(std::string modelName, bool moveAnimation, bool rotateAnimation)
{
	if (moveAnimation)
		bMoveAnimation = true;

	if (rotateAnimation)
		bRotateAnimation = true;

	this->mMeshName = modelName;
}

void cAnimationCommand::MoveAnimation(glm::vec3 startXYZ, glm::vec3 endXYZ, float timeToMove)
{
	this->mStartingPos = startXYZ;
	this->mEndingPos = endXYZ;
	this->mTimeToMove = timeToMove;

	this->mTotalDistance = this->mEndingPos - this->mStartingPos;

	this->mMoveDirection = glm::normalize(this->mTotalDistance);

	float totalDistance = glm::distance(this->mEndingPos, this->mStartingPos);
	this->mSpeed = totalDistance / timeToMove;

	this->mVelocity = this->mMoveDirection * this->mSpeed;
}

void cAnimationCommand::RotateAnimation(float degrees, glm::vec3 rotationDirection, float timeToRotate)
{
	this->mTotalDegreesToBeRotated = degrees;
	this->mTimeToRotate = timeToRotate;
	this->mRotationDirection = rotationDirection;
}

void cAnimationCommand::UpdateAnimation(cControlGameEngine& gameEngine)
{
	this->mElapsedTine += gameEngine.deltaTime;

	if (bMoveAnimation)
	{
		glm::vec3 currentXYZ = gameEngine.GetModelPosition(this->mMeshName);

		currentXYZ += (this->mVelocity * (float)gameEngine.deltaTime);

		gameEngine.MoveModel(this->mMeshName, currentXYZ.x, currentXYZ.y, currentXYZ.z);
	}

	if (bRotateAnimation)
	{
		float rotationDegrees = ((mTotalDegreesToBeRotated / mTimeToRotate)* gameEngine.deltaTime);

		gameEngine.RotateMeshModel(this->mMeshName, rotationDegrees, this->mRotationDirection.x, this->mRotationDirection.y, this->mRotationDirection.z);
	}

	return;
}

bool cAnimationCommand::isAnimationDone(void)
{
	if (this->mElapsedTine >= this->mTimeToMove && this->mElapsedTine >= this->mTimeToRotate)
		return true;

	return false;
}

