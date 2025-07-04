#pragma once
#include <cstdint>
#include <string>

#include "platform/opengl/opengl_gl.hpp"
namespace hm
{

struct ShaderPaths
{
  std::string Vertex {};
  std::string Fragment {};

  std::string GetPath() const;
};
class Shader
{
 public:
  Shader(const ShaderPaths& shader);

  ~Shader();
  std::string LoadShader(const std::string& path);
  bool CompileShader(GLuint& shaderId, GLenum shaderType, const GLchar* source);
  bool LinkProgram();
  bool LoadSource(const ShaderPaths& sourcePath);
  bool Load();
  void Reload();
  void Activate() const;
  uint32_t m_programId {};

 private:
  std::string m_resourcePath {};
  ShaderPaths m_shaderPaths {};
};
} // namespace hm
