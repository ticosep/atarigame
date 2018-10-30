#version 400
layout(location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColors;

uniform mat4 model;

// output variable interpolated at fragment shader raster
out vec4 v2fcolor;


void main ()
{
    gl_Position = model * vPosition;
    // We could infer the depth of the model
    v2fcolor = vColors;
}
