#ifdef GL_ES
  precision mediump float;
#endif

attribute vec2 vertex;
attribute vec2 aa_coord;
attribute vec4 fill_color;
attribute vec4 outline_color;

varying vec2 v_aa_coord;
varying vec4 v_fill_color;
varying vec4 v_outline_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main(void){
  gl_Position = u_projection * u_view * u_model * vec4(vertex, 0.0, 1.0);

  v_fill_color = fill_color;
  v_outline_color = outline_color;
  v_aa_coord = aa_coord;
}
