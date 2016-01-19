#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_texture;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

varying vec4 v_color;
varying vec2 v_texture;

void main() {
  v_color = a_color;
  v_texture = a_texture;

  gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
