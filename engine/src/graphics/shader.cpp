/*
    Shader.
    Copyright (C) 2015 Denis BOURGE

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
    USA
*/

#include "hx3d/graphics/shader.hpp"

#include "hx3d/utils/file.hpp"
#include "hx3d/utils/log.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace hx3d {
namespace graphics {

bool Shader::_programsAnalyzed = false;

Shader::Shader(std::string pathToShader):
  _vertexID(0),
  _fragmentID(0),
  _programID(0)
{
  std::string vertexFile = pathToShader + ".vert.glsl";
  std::string fragmentFile = pathToShader + ".frag.glsl";

  std::string vertexContent = File::loadAsciiFile(vertexFile)->toString();
  std::string fragmentContent = File::loadAsciiFile(fragmentFile)->toString();

  if (vertexContent == "" || fragmentContent == "") {
    Log.Error("Shader ERROR !");
  }

  Log.Info("Loading shader `%s`...", pathToShader.c_str());

  if (compile(vertexContent, fragmentContent)) {
    Log.Info("Shader `%s` loaded.", pathToShader.c_str());
  } else {
    Log.Error("Shader `%s` has failed.", pathToShader.c_str());
  }
}

Shader::Shader(std::string vert, std::string frag):
  _vertexID(0),
  _fragmentID(0),
  _programID(0)
{
  compile(vert, frag);
}

Shader::~Shader() {

  if(glIsShader(_vertexID) == GL_TRUE)
      glDeleteShader(_vertexID);

  if(glIsShader(_fragmentID) == GL_TRUE)
      glDeleteShader(_fragmentID);

  if(glIsProgram(_programID) == GL_TRUE)
      glDeleteProgram(_programID);
}

bool Shader::compile(const std::string& vert, const std::string& frag) {

  if (!compile(_vertexID, GL_VERTEX_SHADER, vert)) {
    return false;
  }

  Log.Shader("\tVertex shader OK");

  if (!compile(_fragmentID, GL_FRAGMENT_SHADER, frag)) {
    return false;
  }

  Log.Shader("\tFragment shader OK");

  if (!createProgram())
    return false;

  Log.Shader("\tProgram OK");

  return true;
}

bool Shader::compile(GLuint &shaderId, GLenum type, const std::string& content) {

  shaderId = glCreateShader(type);
  const GLchar* code = content.c_str();

  glShaderSource(shaderId, 1, &code, 0);
  glCompileShader(shaderId);

  GLint error(0);
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &error);

  if (error != GL_TRUE) {
    GLint error_size(0);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &error_size);

    char* error_msg = new char[error_size + 1];
    glGetShaderInfoLog(shaderId, error_size, &error_size, error_msg);
    error_msg[error_size] = '\0';

    Log.Shader(error_msg);

    delete[] error_msg;
    glDeleteShader(shaderId);

    return false;
  }

  return true;
}

bool Shader::createProgram() {
  _programID = glCreateProgram();

  glAttachShader(_programID, _vertexID);
  glAttachShader(_programID, _fragmentID);

  glLinkProgram(_programID);

  GLint error(0);
  glGetProgramiv(_programID, GL_LINK_STATUS, &error);

  if (error != GL_TRUE) {
    GLint error_size(0);
    glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &error_size);

    char* error_msg = new char[error_size + 1];
    glGetShaderInfoLog(_programID, error_size, &error_size, error_msg);
    error_msg[error_size] = '\0';

    Log.Shader(error_msg);

    delete[] error_msg;
    glDeleteProgram(_programID);

    return false;
  }

  if (_programsAnalyzed) {
    Log.Shader("Shader analysis");
    Log.Shader("---------------");
  }

  analyzeAttributes();
  analyzeUniforms();

  if (_programsAnalyzed) {
    Log.Shader("---------------");
  }

  return true;
}

GLint Shader::getAttribute(std::string name) {
  if (_activeAttributes.find(name) != _activeAttributes.end()) {
    return _activeAttributes[name];
  } else {
    Log.Error("Attribute `%s` does not exists", name.c_str());
    return -1;
  }
}

GLint Shader::getUniform(std::string name) {
  if (_activeUniforms.find(name) != _activeUniforms.end()) {
    return _activeUniforms[name];
  } else {
    Log.Error("Uniform `%s` does not exists", name.c_str());
    return -1;
  }
}

void Shader::analyzeAttributes() {
  GLint attributesNum(0);
  GLint attributeMaxSize(0);

  glGetProgramiv(_programID, GL_ACTIVE_ATTRIBUTES, &attributesNum);
  glGetProgramiv(_programID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeMaxSize);

  if (_programsAnalyzed) {
    Log.Shader("Attributes: %d", attributesNum);
  }

  GLchar* buf = new char[attributeMaxSize + 1];

  for (GLint i = 0; i < attributesNum; ++i) {
    GLint size;
    GLenum type;

    glGetActiveAttrib(_programID, i, attributeMaxSize, nullptr, &size, &type, buf);

    if (_programsAnalyzed) {
      Log.Shader("- %s (%s)", buf, getParameterType(type).c_str());
    }

    GLint loc = glGetAttribLocation(_programID, buf);
    if (loc == -1) {
      Log.Error("Attribute location error: %s", buf);
    } else {
      _activeAttributes[buf] = loc;
      if (_programsAnalyzed) {
        Log.Shader("\tBound to %d", loc);
      }
    }
  }

  delete[] buf;
}

void Shader::analyzeUniforms() {
  GLint uniformsNum(0);
  GLint uniformMaxSize(0);

  glGetProgramiv(_programID, GL_ACTIVE_UNIFORMS, &uniformsNum);
  glGetProgramiv(_programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxSize);

  if (_programsAnalyzed) {
    Log.Shader("Uniforms: %d", uniformsNum);
  }

  GLchar* buf = new char[uniformMaxSize + 1];

  for (GLint i = 0; i < uniformsNum; ++i) {
    GLint size;
    GLenum type;

    glGetActiveUniform(_programID, i, uniformMaxSize, nullptr, &size, &type, buf);

    if (_programsAnalyzed) {
      Log.Shader("- %s (%s)", buf, getParameterType(type).c_str());
    }

    GLint loc = glGetUniformLocation(_programID, buf);
    if (loc == -1) {
      Log.Error("Uniform location error: %s", buf);
    } else {
      _activeUniforms[buf] = loc;

      if (_programsAnalyzed) {
        Log.Shader("\tBound to %d", loc);
      }
    }
  }

  delete[] buf;
}

std::string Shader::getParameterType(GLenum type) {

  switch (type) {

    case GL_FLOAT:
      return "float";
    case GL_FLOAT_VEC2:
      return "vec2";
    case GL_FLOAT_VEC3:
      return "vec3";
    case GL_FLOAT_VEC4:
      return "vec4";

    case GL_INT:
      return "int";
    case GL_INT_VEC2:
      return "ivec2";
    case GL_INT_VEC3:
      return "ivec3";
    case GL_INT_VEC4:
      return "ivec4";

    case GL_BOOL:
      return "bool";
    case GL_BOOL_VEC2:
      return "bvec2";
    case GL_BOOL_VEC3:
      return "bvec3";
    case GL_BOOL_VEC4:
      return "bvec4";

    case GL_FLOAT_MAT2:
      return "mat2";
    case GL_FLOAT_MAT3:
      return "mat3";
    case GL_FLOAT_MAT4:
      return "mat4";

    case GL_SAMPLER_2D:
      return "sampler2D";
    case GL_SAMPLER_CUBE:
      return "samplerCube";

    default:
      return "unknown";
  }
}

void Shader::use(Ptr<Shader> shader) {
  glUseProgram(shader->_programID);
}

void Shader::disable() {
  glUseProgram(0);
}

void Shader::setProgramAnalyzing(bool value) {
  _programsAnalyzed = value;
}


GLuint Shader::getProgramID() const {
  return _programID;
}

void Shader::setUniform1f(std::string uniform, float value) {
  int loc = glGetUniformLocation(_programID, uniform.c_str());
  glUniform1f(loc, value);
}

void Shader::setUniform2f(std::string uniform, glm::vec2 vector) {
  int loc = glGetUniformLocation(_programID, uniform.c_str());
  glUniform2f(loc, vector.x, vector.y);
}

void Shader::setUniform3f(std::string uniform, glm::vec3 vector) {
  int loc = glGetUniformLocation(_programID, uniform.c_str());
  glUniform3f(loc, vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(std::string uniform, glm::vec4 vector) {
  int loc = glGetUniformLocation(_programID, uniform.c_str());
  glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMatrix3f(std::string uniform, glm::mat3 matrix) {
  int loc = glGetUniformLocation(_programID, uniform.c_str());
  glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformMatrix4f(std::string uniform, glm::mat4 matrix) {
  int loc = glGetUniformLocation(_programID, uniform.c_str());
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

} /* graphics */
} /* hx3d */
