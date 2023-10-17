#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

class String 
{
private:
    char* data;
    size_t length;

public:
    // Конструктор по умолчанию
    String() = default;

    // Конструктор с инициализацией C-строкой
    String(const char* cstr);

    // Конструктор перемещения
    String(String&& other);

    // Деструктор
    ~String();

    // Метод для получения указателя на данные
    const char* c_str() const;
};

// Реализация конструктора по умолчанию
String::String() : data(nullptr), length(0) {}

// Реализация конструктора с инициализацией C-строкой
String::String(const char* cstr) : data(nullptr), length(0) 
{
    length = strlen(cstr);
    data = new char[length + 1];
    strncpy(data, cstr, length);
    data[length] = '\0';
}

// Реализация конструктора перемещения
String::String(String&& other) : data(nullptr), length(0) 
{
    // Перемещаю  из other
    data = other.data;
    length = other.length;

    // Обнуляю other
    other.data = nullptr;
    other.length = 0;
}

// Реализация деструктора
String::~String() {
    delete[] data;
}

// Реализация метода c_str()
const char* String::c_str() const 
{
    return data;
}

int main() 
{
    const char* cstr = "Hello, World!";
    String str(cstr);

    String str2(std::move(str)); 

    std::cout << "str2: " << str2.c_str() << std::endl;

    return 0;
}
