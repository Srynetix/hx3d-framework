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

#ifndef HX3D_GRAPHICS_SHADER
#define HX3D_GRAPHICS_SHADER

#include "hx3d/graphics/gl.hpp"

#include "hx3d/utils/ptr.hpp"
#include "hx3d/utils/resource.hpp"

#include <glm/glm.hpp>

#include <string>
#include <map>

namespace hx3d {

class Shader: public Resource {

public:
  /**
  Create a shader from a path.
  The path must be without extension, e.g. shaders/test.

  This class will load the fragment and the vertex shader,
  using the extensions `.frag.glsl` and `.vert.glsl`.

  @param pathToShader Path to shader
  */
  explicit Shader(std::string pathToShader);

  /**
  Create a shader from a vertex shader and a fragment shader in text form.

  @param vert   Vertex shader code
  @param frag   Fragment shader code
  */
  Shader(std::string vert, std::string frag);
  ~Shader();

  /**
  Get the program ID.

  @return Program ID.
  */
  GLuint getProgramID() const;

  /**
  Send a single float to the shader.

  @param uniform  Uniform name
  @param value    Value
  */
  void setUniform1f(std::string uniform, float value);
  /**
  Send a vec2 to the shader.

  @param uniform  Uniform name
  @param vector   Values
  */
  void setUniform2f(std::string uniform, glm::vec2 vector);
  /**
  Send a vec3 to the shader.

  @param uniform  Uniform name
  @param vector   Values
  */
  void setUniform3f(std::string uniform, glm::vec3 vector);
  /**
  Send a vec4 to the shader.

  @param uniform  Uniform name
  @param vector   Values
  */
  void setUniform4f(std::string uniform, glm::vec4 vector);
  /**
  Send a mat4 to the shader.

  @param uniform  Uniform name
  @param matrix   Values
  */
  void setUniformMatrix4f(std::string uniform, glm::mat4 matrix);

  /**
  Get the wanted attribute id.

  @param name Name
  */
  GLint getAttribute(std::string name);
  /**
  Get the wanted uniform id.

  @param name Name
  */
  GLint getUniform(std::string name);

  ///////////////////////

  /**
  Use the shader as the current shader.

  @param shader Shader (Ptr)
  */
  static void use(Ptr<Shader> shader);

  /**
  Clear the current shader.
  */
  static void disable();

  /**
  Analyse the shaders (debug mode).

  @param value True/False
  */
  static void setProgramAnalyzing(bool value);

protected:

  /* No copy or affectation */
  Shader(const Shader& shader) = delete;
  Shader& operator=(const Shader& shader) = delete;

  /**
  Compile the vertex and fragment shaders.

  @param vert Vertex shader code
  @param frag Fragment shader code
  @return All good / Error
  */
  bool compile(const std::string& vert, const std::string& frag);

  /**
  Compile one shader using it's id, type and content.

  @param shaderId ID
  @param type     Shader type
  @param content  Shader code
  @return All good / Error
  */
  bool compile(GLuint &shaderId, GLenum type, const std::string& content);

  /**
  Create the shader program.

  @return All good / Error
  */
  bool createProgram();

  /**
  Analyze the shader attributes (debug mode).
  */
  void analyzeAttributes();
  /**
  Analyze the shader uniforms (debug mode).
  */
  void analyzeUniforms();
  /**
  Get the parameter type (debug mode).

  @return Parameter type
  */
  std::string getParameterType(GLenum type);

  GLuint _vertexID;
  GLuint _fragmentID;
  GLuint _programID;

  std::map<std::string, GLint> _activeAttributes;
  std::map<std::string, GLint> _activeUniforms;

  static bool _programsAnalyzed;
};

} /* hx3d */

#endif
