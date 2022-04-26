#shader vertex
#version 330 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoord;
layout(location = 3) in float a_TextureIndex;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_TextureCoord;
flat out float v_TextureIndex;

void main()
{
   gl_Position = u_MVP * a_Position;

   v_Color = a_Color;
   v_TextureCoord = a_TextureCoord;
   v_TextureIndex = a_TextureIndex;
};
 
#shader fragment
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec4 v_Color;
in vec2 v_TextureCoord;
flat in float v_TextureIndex;

uniform sampler2D u_Textures[16];
uniform float u_TilingFactor;

void main()
{
   for(float index = 0; index <= v_TextureIndex ; index++){
      fragColor = texture(u_Textures[int(index)], v_TextureCoord * u_TilingFactor);
   }
};