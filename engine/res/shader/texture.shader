#vertex_shader
#version 330 core
        
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in float texIndex;

out vec2 v_TexCoord;
out float v_texIndex;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    v_TexCoord = texture;
    v_texIndex = texIndex;
}

#fragment_shader
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_texIndex;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
    if (v_texIndex < 0) {
        color = u_Color;
    } else {
        color = texture(u_Texture, v_TexCoord);
    }
}