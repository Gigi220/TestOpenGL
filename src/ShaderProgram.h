#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>; // Подключаем glew для того, чтобы получить все необходимые заголовочные файлы OpenGL

class ShaderProgram
{
public:
    // Конструктор считывает и собирает шейдер
    ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath)
    {
        // 1. Получаем исходный код шейдера из filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // Удостоверимся, что ifstream объекты могут выкидывать исключения
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try
        {
            // Открываем файлы
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Считываем данные в потоки
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // Закрываем файлы
            vShaderFile.close();
            fShaderFile.close();
            // Преобразовываем потоки в массив GLchar
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        // 2. Сборка шейдеров
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // Вершинный шейдер
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // Если есть ошибки - вывести их
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
        // Фрагментный шейдер
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // Если есть ошибки - вывести их
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Шейдерная программа
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        // Если есть ошибки - вывести их
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Удаляем шейдеры, поскольку они уже в программе и нам больше не нужны.
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    // Использование программы
    void Use()
    {
        glUseProgram(this->Program);
    }

    void SetUniform(const GLchar* uniformName, const GLfloat& greenValue)
    {
        GLint vertexColorLocation = glGetUniformLocation(Program, uniformName);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    }

public:
    // Идентификатор программы
    GLuint Program;
};

#endif