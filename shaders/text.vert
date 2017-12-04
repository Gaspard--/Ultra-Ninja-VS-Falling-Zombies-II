#version 130

uniform vec2 dim;

in vec2 coord;
in vec2 pos;
in float depth;
out float frag_depth;
out vec2 vert_coord;

void main()
{
  vert_coord = coord;
  frag_depth = depth;
  gl_Position = vec4(pos.xy * dim, 0.0f, 1.0f);
}
