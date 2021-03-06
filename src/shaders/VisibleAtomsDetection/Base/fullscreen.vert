#version 430

in vec4 pos;
out vec3 passPosition;
out int passInstanceID;

void main() {
	passPosition = pos.xyz;
        gl_Position = vec4(pos.xy * 2 - 1, 0, 1);
        passInstanceID = gl_InstanceID;
}
