#version 300 es

#ifdef GL_ES
precision mediump float;
#endif

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texture;
layout (location = 3) in mat4 a_model;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec4 vertColor;
out vec2 vertTexture;

void main() {
  vertColor = a_color;
  vertTexture = a_texture;

  gl_Position = u_projection * u_view * a_model * vec4(a_position, 1.0);
}
