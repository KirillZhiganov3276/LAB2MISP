#include <iostream>
#include "table.h"
#include <locale>
#include <typeinfo>
// проверка, чтобы строка состояла только из прописных букв

std::wstring toValid(std::wstring& s)
{
    //setup converter
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    
    if (s.empty())
        throw cipher_error("Empty text");
        
    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    for (auto & c:tmp) {
        if (!iswalpha(c))
            throw(cipher_error("Text has invalid symbols: "+st));
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}
int main(int argc, char **argv)
{
    try {
        std::locale loc("ru_RU.UTF-8");
        std::locale::global(loc);
        int key;
        std::wstring text;
        unsigned op;
        std::wcout<<"Cipher ready. Input key: ";
        std::wcin>>key;
        if (key <= 1) 
                throw(cipher_error("Invalid key"));
        std::wcout<<"Key loaded\n";
        Table cipher(key); //конструктор
        do {
            std::wcout<<"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
            std::wcin>>op;
            if (op > 2) {
                throw(cipher_error("Illegal operation"));
            } else if (op >0) {
                std::wcout<<"Cipher ready. Input text: ";
                std::wcin.ignore();
                std::getline(std::wcin,text);
                std::wstring vtext=toValid(text);
                if (op==1) {
                    std::wcout<<"Encrypted text: "<<cipher.encrypt(vtext)<<std::endl;
                } else {
                    std::wcout<<"Decrypted text: "<<cipher.decrypt(vtext)<<std::endl;
                }
            }
        } while (op!=0);

    } catch(const cipher_error& e) {
        std::wcerr<<e.what()<<std::endl;
    }
    return 0;
}
