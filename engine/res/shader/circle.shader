#vertex_shader
#version 330 core

layout(location = 0) in vec2 aPos; // Vertex position

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); // Pass the vertex position directly to clip space
}

#fragment_shader
#version 330 core

out vec4 FragColor;

uniform vec2 uResolution; // Resolution of the viewport (window size)
uniform vec2 uCircleCenter; // Center of the circle in normalized coordinates [0, 1]
uniform float uCircleRadius; // Radius of the circle in normalized coordinates [0, 1]
uniform vec4 uCircleColor; // Circle color (RGBA)

void main()
{
        vec3 circleColor = vec3(0.85, 0.35, 0.2);
        float thickness = 0.5;
        float fade = 0.005;

        // Calculate distance and fill circle with white
        float distance = 1.0 - length(LocalPosVec3);
        vec3 color = vec3(smoothstep(0.0, fade, distance));
        color *= vec3(smoothstep(thickness + fade, thickness, distance));

        FragColor = vec4(color, 1.0);
        FragColor.rgb *= circleColor;
}