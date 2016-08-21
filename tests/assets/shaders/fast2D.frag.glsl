#version 300 es

#ifdef GL_ES
precision mediump float;
#endif

in vec4 vertColor;
in vec2 vertTexture;

out vec4 color;

uniform sampler2D u_texture;

void main() {
 vec4 uv = texture(u_texture, vertTexture);
 color = uv * vertColor;
}
