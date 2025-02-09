#vertex_shader
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in float texIndex;

uniform mat4 u_ViewProjMatrix;
uniform mat4 u_ModelMatrix;

out vec3 v_LocalSpace;

void main()
{
    gl_Position = u_ViewProjMatrix * u_ModelMatrix * vec4(position, 1.0);
    v_LocalSpace = position;
}

#fragment_shader
#version 330 core

out vec4 FragColor;

in vec3 v_LocalSpace;

void main()
{
    vec3 circleColor = vec3(0.85, 0.35, 0.2);
    float thickness = 0.1;
    float fade = 0.0000001;

    // Calculate distance and fill circle with white
    float distance = 1.0 - length(v_LocalSpace * 2);
    vec3 color = vec3(smoothstep(0.0, fade, distance));
    color *= vec3(smoothstep(thickness + fade, thickness, distance));

    FragColor = vec4(color, 1.0);
    FragColor.rgb *= circleColor;

    if (FragColor.r == 0 && FragColor.g == 0 && FragColor.b == 0) {
        FragColor.rgb = vec3(192.0 / 255.0, 194.0 / 255.0, 201.0 / 255.0);
    }

}