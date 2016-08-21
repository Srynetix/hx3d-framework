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

#pragma once

#include "hx3d/graphics/gl.hpp"

#include "hx3d/utils/reference.hpp"
#include "hx3d/utils/resource.hpp"

#include <glm/mat3x3.hpp>
#include <string>
#include <map>

namespace hx3d {
namespace graphics {

/**
@brief Shader definition class.

Manage vertex and fragment shader.
*/
class Shader: public Resource {
  HX3D_PTR(Shader)

public:
  /**
  @brief Create a shader from a path.
  The path must be without extension, e.g. shaders/test.

  This class will load the fragment and the vertex shader,
  using the extensions `.frag.glsl` and `.vert.glsl`.

  @param pathToShader Path to shader
  */
  explicit Shader(std::string pathToShader);

  /**
  @brief Create a shader from a vertex shader and a fragment shader in text form.

  @param vert   Vertex shader code
  @param frag   Fragment shader code
  */
  Shader(std::string vert, std::string frag);
  ~Shader();

  /**
  @brief Get the program ID.

  @return Program ID.
  */
  GLuint getProgramID() const;

  /**
  @brief Send a single float to the shader.

  @param uniform  Uniform name
  @param value    Value
  */
  void setUniform1f(std::string uniform, float value);
  /**
  @brief Send a vec2 to the shader.

  @param uniform  Uniform name
  @param vector   Values
  */
  void setUniform2f(std::string uniform, glm::vec2 vector);
  /**
  @brief Send a vec3 to the shader.

  @param uniform  Uniform name
  @param vector   Values
  */
  void setUniform3f(std::string uniform, glm::vec3 vector);
  /**
  @brief Send a vec4 to the shader.

  @param uniform  Uniform name
  @param vector   Values
  */
  void setUniform4f(std::string uniform, glm::vec4 vector);
  /**
  @brief Send a mat3 to the shader.

  @param uniform  Uniform name
  @param matrix   Values
  */
  void setUniformMatrix3f(std::string uniform, glm::mat3 matrix);
  /**
  @brief Send a mat4 to the shader.

  @param uniform  Uniform name
  @param matrix   Values
  */
  void setUniformMatrix4f(std::string uniform, glm::mat4 matrix);

  /**
  @brief Get the wanted attribute id.

  @param name Name

  @return Attribute ID
  */
  GLuint getAttribute(std::string name);
  /**
  @brief Get the wanted uniform id.

  @param name Name

  @return Attribute ID
  */
  GLint getUniform(std::string name);

  ///////////////////////

  /**
  @brief Use the shader as the current shader.

  @param shader Shader (Ptr)
  */
  static void use(Pointer<Shader> shader);

  /**
  @brief Clear the current shader.
  */
  static void disable();

  /**
  @brief Analyse the shaders (debug mode).

  @param value True/False
  */
  static void setProgramAnalyzing(bool value);

protected:
  Shader(const Shader& shader) = delete;
  Shader& operator=(const Shader& shader) = delete;

  /**
  @brief Compile the vertex and fragment shaders.

  @param vert Vertex shader code
  @param frag Fragment shader code

  @return All good / Error
  */
  bool compile(const std::string& vert, const std::string& frag);

  /**
  @brief Compile one shader using it's id, type and content.

  @param shaderId ID
  @param type     Shader type
  @param content  Shader code

  @return All good / Error
  */
  bool compile(GLuint &shaderId, GLenum type, const std::string& content);

  /**
  @brief Create the shader program.

  @return All good / Error
  */
  bool createProgram();

  /**
  @brief Analyze the shader attributes (debug mode).
  */
  void analyzeAttributes();
  /**
  @brief Analyze the shader uniforms (debug mode).
  */
  void analyzeUniforms();
  /**
  @brief Get the parameter type (debug mode).

  @param type Type

  @return Parameter type
  */
  std::string getParameterType(GLenum type);

  /// @brief Vertex shader ID
  GLuint _vertexID;
  /// @brief Fragment shader ID
  GLuint _fragmentID;
  /// @brief Shader program ID
  GLuint _programID;

  /// @brief Active attributes map
  std::map<std::string, GLint> _activeAttributes;
  /// @brief Active uniforms map
  std::map<std::string, GLint> _activeUniforms;
  /// @brief Are the programs analyzed ?
  static bool _programsAnalyzed;
};

} /* graphics */
} /* hx3d */
