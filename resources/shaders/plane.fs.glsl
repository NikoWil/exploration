#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Color;
in vec3 FragPos;

uniform vec3 lightDir;
uniform vec3 viewPos;

void main()
{
    float ka = 0.2;
    float kd = 0.6;
    float ks = 0.2;

    vec3 N = normalize(Normal);
    vec3 L = normalize(-lightDir);
    vec3 V = normalize(viewPos - FragPos);

    float diff = max(dot(N, L), 0);
    vec3 RL = reflect(-L, N);

    float phong_exp = 8;
    float spec = pow(max(dot(V, RL), 0.0), phong_exp);

    vec3 ambient = ka * Color;
    vec3 diffuse = kd * diff * Color;
    vec3 specular = ks * spec * vec3(1);

    FragColor = vec4(ambient + diffuse + specular, 1);
}
