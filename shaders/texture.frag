#version 130

uniform sampler2D tex;

in vec2 vert_coord;
in float frag_depth;
out vec4 color;

void main()
{
  color = texture(tex, vert_coord);
  if (color.a < 0.1f)
    gl_FragDepth = 1.0f;
  else
    gl_FragDepth = frag_depth;
}
