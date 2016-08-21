#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;
uniform vec2 pixel_size;

uniform sampler2D u_texture;

varying vec4 v_color;
varying vec2 v_texture;

vec4 pixelate(vec2 size) {
    float dx = size.x * (1.0 / resolution.x);
    float dy = size.y * (1.0 / resolution.y);
    vec2 coord = vec2(dx * floor(v_texture.x/dx), dy * floor(v_texture.y/dy));
    return texture2D(u_texture, coord);
}

void main() {
    float time_value = max(0.1, abs(sin(time)));
    vec4 outcolor = v_color;

    if (time_value > 0.1) {
       outcolor *= pixelate(pixel_size * time_value);
    } else {
       outcolor *= texture2D(u_texture, v_texture);
    }

    gl_FragColor = outcolor;
}
