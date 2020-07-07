uniform mat4 uMVPMatrix;
uniform mat4 uMMatrix;
uniform vec3 uCamera;
uniform vec3 uLightLocation;

attribute vec3 aPosition;
attribute vec2 aTexCoor;
attribute vec3 aNormal;

varying vec2 vTextureCoord;
varying vec4 ambient;
varying vec4 diffuse;
varying vec4 specular;

void pointLight(in vec3 normal,
                inout vec4 ambient,
                inout vec4 diffuse,
                inout vec4 specular,
                in vec3 lightLocation,
                in vec4 lightAmbient,
                in vec4 lightDiffuse,
                in vec4 lightSpecular
                )
{
    ambient = lightAmbient;
    vec3 normalTarget = aPosition + normal;
    vec3 newNormal = (uMMatrix*vec4(normalTarget,1)).xyz
        - (uMMatrix*vec4(aPosition,1)).xyz;
    newNormal = normalize(newNormal);

    vec3 eye = normalize(uCamera-(uMMatrix*vec4(aPosition,1)).xyz);

    vec3 vp = normalize(lightLocation-(uMMatrix*vec4(aPosition,1)).xyz);
    vp = normalize(vp);
    vec3 halfVector = normalize(vp+eye);
    float shininess = 50.0;
    float nDotViewPosition = max(0.0,dot(newNormal,vp));
    diffuse = lightDiffuse*nDotViewPosition;
    float nDotViewHalfVector = dot(newNormal,halfVector);
    float powerFactor = max(0.0,pow(nDotViewHalfVector,shininess));
    specular=lightSpecular*powerFactor;
}

void main()
{
   gl_Position = uMVPMatrix * vec4(aPosition,1);

   vec4 ambientTemp, diffuseTemp, specularTemp;
   pointLight(normalize(aNormal),
              ambientTemp, diffuseTemp, specularTemp, uLightLocation,
              vec4(0.15,0.15,0.15,1.0),
              vec4(0.9,0.9,0.9,1.0),
              vec4(0.4,0.4,0.4,1.0));

   ambient = ambientTemp;
   diffuse = diffuseTemp;
   specular = specularTemp;

   vTextureCoord = aTexCoor;
}
