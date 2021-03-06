#version 450

out vec4 fragColor;

//coherent layout(rgba16f, binding = 0) uniform uimageBuffer collectedIDsBuffer;
coherent layout(r8ui) uniform uimage1D collectedIDsBuffer;
coherent layout(rgba32f) uniform image3D intervalBuffer;

uniform int level = 0;

void main() {

        // how many intervals were found in this pixel?
        float numberOfIntervals = int(imageLoad(intervalBuffer, ivec3(gl_FragCoord.xy, 63)).r);
      //  if (numberOfIntervals <= 0)
          //  discard;

        // for each interval, flag the included Instance IDs as visible
        for (int i = 0; i < numberOfIntervals; i++)
        {
            int ID1 = int(imageLoad(intervalBuffer, ivec3(gl_FragCoord.xy, i)).z);
            imageStore(collectedIDsBuffer, int(ID1), uvec4(1));
        }
        fragColor = vec4(numberOfIntervals);
}
