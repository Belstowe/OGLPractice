#version 330 core
in vec2 myTexCoord;

out vec4 color;

uniform sampler2D baseTexture;
uniform sampler2D overlayTexture;

void main() {
    color = vec4(vec3(texture(overlayTexture, myTexCoord).a * texture(overlayTexture, myTexCoord) + (1 - texture(overlayTexture, myTexCoord).a) * texture(baseTexture, myTexCoord)), max(texture(overlayTexture, myTexCoord).a, texture(baseTexture, myTexCoord).a));
}
