#version 330 core


in vec3 oUv;
in vec4 oCol;
in vec3 oFragPos;
in vec3 TLP;
in vec3 TVP;
in vec3 TFP;
in vec3 rPos;
in vec3 oNorm;
in vec3 reflectVector;
in vec3 pass_normal;
in mat3 normMat;
in mat3 TBN;

uniform sampler2D tCol;
uniform sampler2D tNorm;
uniform vec3 lPos;
uniform vec3 lDiff;
uniform vec3 lSpec;
uniform float lRange;

out vec4 color;

void main(){

     float dis = abs(length(oFragPos-lPos));

    float dv = dis/lRange;

    if(dv>1.0) dv = 1.0;
    dv = 1.0-dv;

    vec3 df = vec3(dv,dv,dv);

    //
    vec2 uv;

    uv.x = oUv.x;
    uv.y = 1.0-oUv.y;
    
    vec3 normal = vec3(0.5,0.5,1);

      normal = texture2D(tNorm,uv).rgb;

    normal = normalize(normal * 2.0 - 1.0);

    vec3 ref_Norm = reflectVector;




    vec3 cTex = texture(tCol,uv).rgb;

    //

     vec3 lightDir = normalize(TLP - TFP);

    float diff = max(dot(lightDir,normal),0.0);

    vec3 diffuse = vec3(diff,diff,diff) * lDiff;

    diffuse = diffuse * cTex;

    vec3 viewDir = normalize(TVP-TFP);
    vec3 reflectDir = reflect(-lightDir,normal);
    vec3 halfwayDir = normalize(lightDir+viewDir);

    float spec = pow(max(dot(normal,halfwayDir),0.0),32.0);

    spec = spec;

    vec3 specular = ((lSpec) * spec); 

    //


    vec4 fc;

    fc.rgb = (diffuse + specular)*df;
    fc.a = 1.0;

    color = fc;

}