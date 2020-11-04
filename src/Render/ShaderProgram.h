#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Math/Vector3.h"
#include "Math/Vector2.h"

#include "GL/glew.h" // ���������� glew ��� ����, ����� �������� ��� ����������� ������������ ����� OpenGL

class ShaderProgram
{
public:
    // ����������� ��������� � �������� ������
    ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
    {
        // 1. �������� �������� ��� ������� �� filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // �������������, ��� ifstream ������� ����� ���������� ����������
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // ��������� �����
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // ��������� ������ � ������
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // ��������� �����
            vShaderFile.close();
            fShaderFile.close();
            // ��������������� ������ � ������ GLchar
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        // 2. ������ ��������
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // ��������� ������
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // ���� ���� ������ - ������� ��
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        // ����������� ������
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // ���� ���� ������ - ������� ��
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // ��������� ���������
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        // ���� ���� ������ - ������� ��
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // ������� �������, ��������� ��� ��� � ��������� � ��� ������ �� �����.
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // ������������� ���������
    void Use()
    {
        glUseProgram(this->Program);
    }

    void SetUniform1f(const GLchar* uniformName, const float value)
    {
        glUniform1f(glGetUniformLocation(Program, uniformName), value);
    }

    void SetUniform1i(const GLchar* uniformName, const int value)
    {
        glUniform1i(glGetUniformLocation(Program, uniformName), value);
    }

    void SetUniform2f(const GLchar* uniformName, const Math::Vector2& vec2)
    {
        glUniform2f(glGetUniformLocation(Program, uniformName), vec2.x, vec2.y);
    }

    void SetUniform3f(const GLchar* uniformName, const Math::Vector3& vec3)
    {
        glUniform3f(glGetUniformLocation(Program, uniformName), vec3.x, vec3.y, vec3.z);
    }

    // TODO Vector4
    void SetUniform4f(const GLchar* uniformName, const Math::Vector3& vec4)
    {
        glUniform4f(glGetUniformLocation(Program, uniformName), vec4.x, vec4.y, vec4.z, 1.0f);
    }

public:
    // ������������� ���������
    GLuint Program;
};

#endif