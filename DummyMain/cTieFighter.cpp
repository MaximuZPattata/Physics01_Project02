#include "pch.h"
#include "cTieFighter.h"

void cTieFighter::Initialize(std::string meshName, std::string orbName, glm::vec3 position, float acceleration, float deceleration, float dampingFactor, float maxSpeed, float rotationSpeed)
{
    this->mMeshName = meshName;
    this->mAcceleration = acceleration;
    this->mDeceleration = deceleration;
    this->mDampingFactor = dampingFactor;
    this->mMaxSpeed = maxSpeed;
    this->mPosition = position;
    this->mRotationSpeed = rotationSpeed;
    this->mOrbMeshName = orbName;
}

void cTieFighter::UpdatePosition(cControlGameEngine gameEngine)
{
    if (!this->bCollision)
    {
        if (!this->bMoveForward)
            this->mCurrentSpeed = glm::max(this->mCurrentSpeed - this->mDeceleration * mSpeedOffset, 0.0f);
        else
            this->bMoveForward = false;

        if (this->bTurnRight || this->bTurnLeft)
        {
            gameEngine.RotateMeshModel(this->mMeshName, glm::degrees(this->mCurrentRotationSpeed), 0.0, 1.0, 0.0);
            this->mCurrentRotationSpeed = 0.f;
            this->bTurnRight = false;
            this->bTurnLeft = false;
        }

    
        //---------------------------Check Forward Direction-------------------------------------------------

        glm::quat tieFighterRotationQuat = gameEngine.GetQuatRotation(this->mMeshName);

        glm::vec3 forwardDirection = glm::rotate(tieFighterRotationQuat, glm::vec3(0.0f, 0.0f, -1.0f));

        forwardDirection = glm::normalize(forwardDirection);

        //-------------------------Calculate Speed and Position----------------------------------------------

        this->mCurrentSpeed *= this->mDampingFactor;

        this->mPosition += forwardDirection * this->mCurrentSpeed * mSpeedOffset;

        gameEngine.MoveModel(this->mMeshName, this->mPosition.x, this->mPosition.y, this->mPosition.z);
    }

    else
    {
        this->mPosition = glm::vec3(0.0, 200.0, 1000.0);

        glm::vec3 orbPos = glm::vec3(0.0, 200.0, 800.0);

        gameEngine.MoveModel(this->mMeshName, this->mPosition.x, this->mPosition.y, this->mPosition.z);
        gameEngine.MoveModel(this->mOrbMeshName, orbPos.x, orbPos.y, orbPos.z);
        gameEngine.ChangeModelPhysicsPosition(this->mOrbMeshName, orbPos.x, orbPos.y, orbPos.z);
        this->bCollision = false;
    }
}

void cTieFighter::UpdateOrbPosition(cControlGameEngine gameEngine)
{
    glm::quat tieFighterRotationQuat = gameEngine.GetQuatRotation(this->mMeshName);

    glm::vec3 frontDirection = glm::rotate(tieFighterRotationQuat, glm::vec3(0.0f, 0.0f, -1.0f));

    glm::vec3 fighterPos = gameEngine.GetModelPosition(this->mMeshName);
    
    glm::vec3 orbPos = fighterPos + frontDirection * 50.0f;

    gameEngine.MoveModel(this->mOrbMeshName, orbPos.x, orbPos.y, orbPos.z);
    gameEngine.ChangeModelPhysicsPosition(this->mOrbMeshName, orbPos.x, orbPos.y, orbPos.z);
}

void cTieFighter::MoveForward(float deltaTime)
{
    this->mCurrentSpeed = glm::min(this->mCurrentSpeed + this->mAcceleration * mSpeedOffset, this->mMaxSpeed);
    this->bMoveForward = true;
}

void cTieFighter::TurnLeft(float deltaTime)
{
    this->mCurrentRotationSpeed += this->mRotationSpeed * 0.05f;

    this->mCurrentRotationSpeed = glm::min(this->mCurrentRotationSpeed, this->mMaxRotationAngle);

    this->bTurnLeft = true;
}

void cTieFighter::TurnRight(float deltaTime)
{
    this->mCurrentRotationSpeed -= this->mRotationSpeed * 0.05f;

    this->mCurrentRotationSpeed = glm::max(this->mCurrentRotationSpeed, -this->mMaxRotationAngle);

    this->bTurnRight = true;
}

void cTieFighter::SetCollision()
{
    this->bCollision = true;
}

glm::vec3 cTieFighter::GetCamPosition()
{
    glm::vec3 offset = glm::vec3(0.0f, 75.0f, 450.0f);
    glm::vec3 camPos = this->mPosition + offset;

    return camPos;
}

glm::vec3 cTieFighter::GetPosition()
{
    return this->mPosition;
}

