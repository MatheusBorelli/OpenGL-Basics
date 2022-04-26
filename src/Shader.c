#include "Shader.h"
#include "Renderer.h"

#include <string.h>

typedef struct{
    char* VertexSource;
    char* FragmentSource;
}ShaderProgramSource;

void ShaderDelete(Shader *shader)
{
    GLCall(glDeleteProgram(shader->m_RendererID));
}

unsigned int FSize(FILE *source)
{
    rewind(source);
    unsigned int i = 0;
    while(fgetc(source) != EOF)
        i++;
    rewind(source);
    return i;
}

ShaderProgramSource ParseShader(const char* filePath)
{
    FILE *shaderFile = fopen(filePath,"rb");
    ShaderProgramSource *result;
    char* sourceCode;

    unsigned fileSize = FSize(shaderFile);//Gets the size of file
    
    //checks the path of shader code
    if(shaderFile == NULL)
    {
        printf("Failed to find shader path:\n");
        printf("%s\n",filePath);
        result = NULL;
        return (*result);
    }
    //allocation of memory to fit shader code
    sourceCode = (char *)malloc(fileSize * sizeof(char));
    
    result = (ShaderProgramSource*)malloc(fileSize * sizeof(char)+1);

    //copy file to a variable
    for(unsigned i = 0; i < fileSize;i++)
        sourceCode[i] = fgetc(shaderFile);

    sourceCode[strnlen(sourceCode,fileSize)] = '\0';
    //Parse Fisrt Code
    char *VertexCode = strstr(sourceCode,"#shader vertex")+15;
    char *FragmentCode = strstr(sourceCode,"#shader fragment")+17;
    
    if(strlen(VertexCode) > strlen(FragmentCode))
        VertexCode[strnlen(VertexCode,fileSize)-strlen(FragmentCode)-17] = '\0';
    else
        FragmentCode[strnlen(VertexCode,fileSize)-strlen(FragmentCode)-15] = '\0';

    result->VertexSource = VertexCode;
    result->FragmentSource = FragmentCode;
    
    fclose(shaderFile);
    return (*result);
}

unsigned int CompilerShader(unsigned int type,char *source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source;
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id , GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id,length, &length, message);
        printf("Failed To Compile %s Shader\n",type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
        printf("%s",message);
        glDeleteShader(id);
        free(message);
        return 0;
    }    

    return id;
}

unsigned int CreateShader(char *vertexShader,char *fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int vs = CompilerShader(GL_VERTEX_SHADER  , vertexShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void ShaderInit(Shader *shader,char* filepath){
    shader->m_filepath = filepath;
    shader->cacheLocation = InitHashTable();
    ShaderProgramSource source = ParseShader((const char*)filepath);
    //source.VertexSource[strlen(source.VertexSource)] = '\0';
    //source.FragmentSource[strlen(source.VertexSource)] = '\0';
    shader->m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

void ShaderBind(Shader *shader){
    GLCall(glUseProgram(shader->m_RendererID));
}
void ShaderUnbind(){
    GLCall(glUseProgram(0));
}

//Get Uniform Location
int GetUniformLocation(Shader *shader, char* name)
{
    if(SearchHashTable(name, shader->cacheLocation))
        return ReturnNumberData(name, shader->cacheLocation);

    GLCall(int location = glGetUniformLocation(shader->m_RendererID,name));
    
    if(location == -1)  
        printf("Warning: Uniform %s doesn't exist!",name);
    
    Data temp;
    temp.text = name;
    temp.number = location;
    AddHashTable(temp, &(shader->cacheLocation));
    
    return location;
}
//Set Uniforms
void SetUniform1i(Shader *shader,char* name, int value){
    GLCall(glUniform1i(GetUniformLocation(shader,name), value));
}

void SetUniform1iv(Shader *shader,char* name, int* values, int count){
    GLCall(glUniform1iv(GetUniformLocation(shader,name), count ,values));
}

void SetUniform1f(Shader *shader,char* name, float value){
    GLCall(glUniform1f(GetUniformLocation(shader,name), value));
}

void SetUniform4f(Shader *shader,char* name, float v0,float v1,float v2,float v3){
    GLCall(glUniform4f(GetUniformLocation(shader,name), v0, v1, v2, v3));
}

void SetUniformMat4f(Shader *shader,char* name, mat4* matrix){
    GLCall(glUniformMatrix4fv(GetUniformLocation(shader,name), 1, GL_FALSE, matrix[0][0]));
}

