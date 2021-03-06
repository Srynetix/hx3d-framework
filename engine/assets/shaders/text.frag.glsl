#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_color;
varying vec2 v_texture;

uniform sampler2D u_texture;

void main() {
  vec4 uv = texture2D(u_texture, v_texture);

  gl_FragColor = vec4(v_color.rgb, v_color.a * uv.r);
}
