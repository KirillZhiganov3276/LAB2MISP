#include <locale>
#include <iostream>
#include "modAlphaCipher.h"
#include <sstream>
using namespace std;
// проверка, чтобы строка состояла только из прописных букв

std::wstring toValidtext(wstring& s)
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
            throw cipher_error(std::string("Text has invalid symbols: ")+st);
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}

int main(int argc, char **argv)
{
    try {
        locale loc("ru_RU.UTF-8");
        locale::global(loc);
        wstring key;
        wstring text;
        unsigned op;
        wcout<<"Cipher ready. Input key: ";
        wcin>>key;
        wcout<<"Key loaded\n";
        modAlphaCipher cipher(key);
        do {
            wcout<<"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
            wcin>>op;
            if (op > 2) {
                throw(cipher_error("Invalid opreration"));
            } else if (op >0) {
                wcout<<"Cipher ready. Input text: ";
                wcin>>text;
                std::wstring vtext=toValidtext(text);
                if (op==1) {
                    wcout<<"Encrypted text: "<<cipher.encrypt(vtext)<<endl;
                } else {
                    wcout<<"Decrypted text: "<<cipher.decrypt(vtext)<<endl;
                }
            }
        } while (op!=0);

    } catch(const cipher_error& e) {
        std::wcerr<<e.what()<<std::endl;
    }
    return 0;
}
