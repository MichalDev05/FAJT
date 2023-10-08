#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

void main() {
    // Define tile size and colors
    vec2 tileSize = vec2(1.0 / 10.0); // 10x10 grid
    vec3 tileColor1 = vec3(0.8, 0.8, 0.8); // Light gray
    vec3 tileColor2 = vec3(0.2, 0.2, 0.2); // Dark gray

    // Calculate tile indices
    ivec2 tileIndices = ivec2(TexCoord / tileSize);

    // Determine tile color based on indices
    vec3 tileColor = mix(tileColor1, tileColor2, mod(tileIndices.x + tileIndices.y, 2));

    FragColor = vec4(tileColor, 1.0);
}
