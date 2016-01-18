attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_texture;
attribute vec3 a_normal;

uniform struct Light {
  vec3 ambient;
  vec3 specular;
  vec3 position;
  vec3 color;
  float power;
} light;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

varying vec4 v_color;
varying vec2 v_texture;

varying vec3 v_light_direction;
varying vec3 v_normal_camera;
varying vec3 v_position_world;
varying vec3 v_eye_camera;

void main() {
  v_color = a_color;
  v_texture = a_texture;

  vec3 positionCamera = (u_view * u_model * vec4(a_position, 1)).xyz;
  vec3 lightPosCamera = (u_view * vec4(light.position, 1)).xyz;

  v_eye_camera = vec3(0, 0, 0) - positionCamera;
  v_normal_camera = normalize((u_view * u_model * vec4(a_normal, 0)).xyz);
  v_light_direction = normalize(lightPosCamera + v_eye_camera);
  v_position_world = (u_model * vec4(a_position, 1)).xyz;

  gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
