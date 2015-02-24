#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "color.hpp"
#include "texture.hpp"
#include "vector.hpp"

#include "glm/common.hpp"
#include "opengl_includes.hpp"

#include <memory>
#include <vector>

class ParticleData;
class ShaderProgram; 

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Init();
    void Terminate();
    void Update(const float deltaTime);

    void spawnBallParticles(size_t pCount, const glm::vec3& initialPosition, const glm::vec3& initialSpeed, const float speed, const Color::rgbp color, const float lifetime);
    void spawnParticle(const glm::vec3& initialPosition, const glm::vec3& initialSpeed, const float lifetime, const Color::rgbp color);

    void HandleMousePosition(float x, float y, float z);

private:
    std::unique_ptr<ParticleData> mParticleData;
    std::unique_ptr<ShaderProgram> mShaderProgram;
    GLuint mVaoId;
    GLuint mVboPositionId;
    GLuint mVboColorId;
    GLuint mTextureId;
    GLuint mSamplerId;
    glm::vec3 mMousePosition;
    Texture2D mParticleMask;
};

#endif
