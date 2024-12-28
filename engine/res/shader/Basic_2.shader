#vertex_shader
#version 330 core
        
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in float texIndex;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_Texture;
out float v_TexIndex;

void main()
{
    v_Color = color;
    v_Texture = texture;
    v_TexIndex = texIndex;
    gl_Position = u_MVP * position;
}

#fragment_shader
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_Texture;
in float v_TexIndex;

uniform sampler2D u_Texture;

void main()
{
    if (v_TexIndex < 0) {
        color = v_Color;
    } else {
        color = texture(u_Texture, v_Texture);
    }
}