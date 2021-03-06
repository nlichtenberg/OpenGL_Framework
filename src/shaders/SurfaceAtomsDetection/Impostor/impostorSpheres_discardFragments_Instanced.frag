#version 450

in vec2 texCoord;
in vec4 passColor;
out vec4 fragColor;
uniform vec3 lightSrc = vec3(100,100,100);
flat in int passInstanceID;
out vec4 InstanceID;

void main() {
    if (length(texCoord) > 1) discard;
    fragColor = passColor;
    InstanceID = vec4(passInstanceID);
}
