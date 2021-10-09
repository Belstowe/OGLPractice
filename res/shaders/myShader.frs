#version 330 core
in vec2 myTexCoord;

out vec4 color;

uniform sampler2D baseTexture;
uniform sampler2D overlayTexture;

void main() {
    // color = mix(texture(baseTexture, myTexCoord), texture(overlayTexture, myTexCoord), 0.2);
    color = vec4(vec3(texture(overlayTexture, myTexCoord).a * texture(overlayTexture, myTexCoord) + (1 - texture(overlayTexture, myTexCoord).a) * texture(baseTexture, myTexCoord)), 1.0);
}
