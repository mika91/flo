#version 330 core

//Entrees
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor_modelspace;

// Sortie
smooth out vec3  color;
smooth out float depth;

// Params
uniform mat4 modelMatrix;
//...

void main(){
  gl_Position = /*...*/ modelMatrix * vec4(vertexPosition_modelspace, 1.0);
  fragPos     = vec3(modelMatrix * vec4(vertexPosition_modelspace, 1.0));
  depth       = gl_Position.z;
  color       = vertexColor_modelspace;
  //...
}