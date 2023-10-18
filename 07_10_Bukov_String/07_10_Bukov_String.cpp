#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cassert>
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

    // Перезагрузка операторов []
    char& operator[] (size_t index);
    const char& operator[](size_t index) const;
    
    // Перегрузка оператора ()
    int operator()(char character) const;
    operator int() const;
};

// Реализация конструктора с инициализацией C-строкой
String::String(const char* cstr) : data(nullptr), length(0) 
{
    length = strlen(cstr);
    data = new char[length + 1];
    strncpy(data, cstr, length);
    data[length] = '\0';
    std::cout << "Конструктор с инициализацией C-строкой отработал по адресу " << this << std::endl;
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
    std::cout << "Констуктор перемещения отработал по адресу " << this << std::endl;
}


// Реализация деструктора
String::~String() 
{
    delete[] data;
    std::cout << "Деструктор отработал по адресу " << this << std::endl;
}


// Реализация метода c_str()
const char* String::c_str() const 
{
    return data;
}

// Реализация перегузок []
char& String::operator[] (size_t index) 
    {
        assert((index < length) and "Index out of range.");
        return data[index];
    }
const char& String::operator[](size_t index) const 
    {
        assert((index < length) and "Index out of range.");
        return data[index];
    }


// Реализация перегрузки()
int String::operator()(char character) const 
{
    for (size_t i = 0; i < length; ++i) 
    {
        if (data[i] == character) 
        {
            return int(i);
        }
    }
    return -1; // Возвращает -1, если символ не найден.
}

String::operator int() const 
{
    return int(length);
}

int main()
{
    setlocale(LC_ALL, "rus");
    const char* cstr = "Hello, World!";
    String str(cstr);

    String str2(std::move(str));

    std::cout << "Изначальная строка " << str2.c_str() << std::endl;

    str2[7] = '!'; // Изменение символа по индексу
    std::cout << "Строка после замены символа при помощи [] " << str2.c_str() << std::endl;

    int len = int(str2);
    std::cout << "Длина строки: " << len << std::endl;
    int index = str2('d');
    if (index != -1) 
    {
        std::cout << "Индекс символа 'd': " << index << std::endl;
    }
    else 
    {
        std::cout << "Символ не найден." << std::endl;
    }

    return 0;
}

