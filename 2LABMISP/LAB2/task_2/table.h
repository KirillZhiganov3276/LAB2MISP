#pragma once
#include <vector>
#include <string>
#include <map>
#include <codecvt>
#include <iostream>

class Table
{
private:
    std::map <int, std::wstring> subNum; //ассоциативный массив "субстрока по номеру"
    std::map <int, std::wstring> resubNum; //ассоциативный массив "субстрока по номеру"
    int key; //ключ
public:
    Table()=delete; //запретим конструктор без параметров
    Table(const uint skey); //конструктор для установки ключа
    std::wstring encrypt(std::wstring& open_text); //зашифрование
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
};

class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
       std::invalid_argument(what_arg) {}
};

