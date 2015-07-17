varying vec4 v_color;
varying vec2 v_texture;

uniform sampler2D u_texture;

void main() {
  vec4 uv = texture2D(u_texture, v_texture);

  gl_FragColor = uv * v_color;
}
