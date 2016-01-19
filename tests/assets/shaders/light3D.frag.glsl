#ifdef GL_ES
precision mediump float;
#endif

uniform struct Light {
  vec3 ambient;
  vec3 specular;
  vec3 position;
  vec3 color;
  float power;
} light;

uniform mat4 u_model;

varying vec4 v_color;
varying vec2 v_texture;

varying vec3 v_light_direction;
varying vec3 v_normal_camera;
varying vec3 v_position_world;
varying vec3 v_eye_camera;

uniform sampler2D u_texture;

void main() {

  float dist = length(light.position - v_position_world);
  float cosTheta = clamp(dot(v_normal_camera, v_light_direction), 0.0, 1.0);

  vec3 E = normalize(v_eye_camera);
  vec3 R = reflect(-v_light_direction, v_normal_camera);

  float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

  vec4 texColor = texture2D(u_texture, v_texture) * v_color;

  vec3 ambColor = light.ambient * texColor.rgb;
  vec3 difColor = texColor.rgb * light.color * light.power * cosTheta / (dist*dist);
  vec3 speColor = light.specular * light.color * light.power * pow(cosAlpha, 5.0) / (dist*dist);

  gl_FragColor = vec4(ambColor + difColor + speColor, texColor.a);
}
