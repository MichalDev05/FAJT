#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1; // Texture to be tiled

void main() {
    // Define tile size (normalized)
    vec2 tileSize = vec2(1.0 / 10.0); // 10x10 grid

    // Calculate texture coordinates within the tile
    vec2 tileCoords = TexCoord / tileSize;

    // Sample the texture and assign it to the fragment color
    FragColor = texture(texture1, tileCoords);
}
