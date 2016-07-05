#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_color;
varying vec2 v_texture;

uniform float u_borderWidth;
uniform vec2 u_quadSize;
uniform vec4 u_borderColor;

uniform sampler2D u_texture;

void main() {
  vec4 uv = texture2D(u_texture, v_texture);
  float bw = u_borderWidth / u_quadSize.x;
  float bh = u_borderWidth / u_quadSize.y;

  if ((v_texture.x >= 0.f) && (v_texture.x <= bw) ||
    (v_texture.x >= 1.f - bw) && (v_texture.x <= 1.f) ||
    (v_texture.y >= 0.f) && (v_texture.y <= bh) ||
    (v_texture.y >= 1.f - bh) && (v_texture.y <= 1.f))
  {
    gl_FragColor = u_borderColor;
  } else {
    gl_FragColor = uv * v_color;
  }
}
