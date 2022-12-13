#version 330 core
out vec4 FragColor;
in vec2 texCoord;
uniform sampler2D tex0;
void main()
{
   //FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
   FragColor = texture(tex0, texCoord);
}