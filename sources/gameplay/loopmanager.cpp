#include "loopmanager.hpp"

#include "sea.hpp"
#include "seagull.hpp"

#include "../root.hpp"
#include "../camera.hpp"
#include "../visualdebug.hpp"

#include "../opengl_includes.hpp"

#include <assert.h>
#include <algorithm>

namespace Gameplay {

LoopManager::LoopManager()
: mSeagull(new Seagull())
, mSea(new Sea())
{}

LoopManager::~LoopManager()
{}

void LoopManager::Init()
{
	mSeagull->Init();
    mSea->Init();
}

void LoopManager::Terminate()
{
	mSeagull->Terminate();
    mSea->Terminate();
}

void LoopManager::FrameStep()
{
    mSea->FrameStep();
}

void LoopManager::Update(const float deltaTime)
{
    mSeagull->Update(deltaTime);
    mSea->Update(deltaTime);
}

void LoopManager::EventKey(int key, int action)
{
    if (GLFW_MOUSE_BUTTON_LEFT == key && GLFW_PRESS == action) {
        const Camera* camera = Root::Instance().GetCamera();
        const glm::vec3& mouseDirection = camera->MouseDirection();
        const glm::vec3 planeNormal(0, 0, 1.f);
        const float cosTheta = glm::dot(mouseDirection, planeNormal);
        if (0.f == cosTheta)
            return;
        const glm::vec3& cameraPosition = camera->Position();
        const float planeDistance = 25.f;
        const float t = -(glm::dot(cameraPosition, planeNormal) + planeDistance) / cosTheta;
        const Camera::perspective& parameter = camera->Perspective();
        if (t < parameter.zNear || parameter.zFar < t)
            return;
        const glm::vec3 intersect = cameraPosition + mouseDirection*t;
        mSeagull->SetTrackPosition(intersect);
    }
}

#ifdef IMGUI_ENABLE
void LoopManager::debug_GUI() const
{
    if (ImGui::CollapsingHeader("Seagull Module"))
    {
        mSeagull->debug_GUI();
    }
    if (ImGui::CollapsingHeader("Sea Module"))
    {
        mSea->debug_GUI();
    }
}
#endif

} //namespace Gameplay
