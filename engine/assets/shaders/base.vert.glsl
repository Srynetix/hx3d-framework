attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_texture;

uniform mat4 u_modelview;
uniform mat4 u_projection;

varying vec4 v_color;
varying vec2 v_texture;

void main() {
  v_color = a_color;
  v_texture = a_texture;

  gl_Position = u_projection * u_modelview * vec4(a_position, 1.0);
}
