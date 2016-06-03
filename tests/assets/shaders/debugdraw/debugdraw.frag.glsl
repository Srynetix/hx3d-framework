#ifdef GL_ES
  precision mediump float;
#endif

uniform float u_outline_coef;

varying vec2 v_aa_coord;
varying vec4 v_fill_color;
varying vec4 v_outline_color;

float aa_step(float t1, float t2, float f)
{
  return smoothstep(t1, t2, f);
}

void main(void)
{
  float l = length(v_aa_coord);

  // Different pixel size estimations are handy.
  //float fw = fwidth(l);
  //float fw = length(vec2(dFdx(l), dFdy(l)));
  float fw = length(fwidth(v_aa_coord));

  // Outline width threshold.
  float ow = 1.0 - fw;//*u_outline_coef;

  // Fill/outline color.
  float fo_step = aa_step(max(ow - fw, 0.0), ow, l);
  vec4 fo_color = mix(v_fill_color, v_outline_color, fo_step);

  // Use pre-multiplied alpha.
  float alpha = 1.0 - aa_step(1.0 - fw, 1.0, l);
  gl_FragColor = fo_color*(fo_color.a*alpha);
}
