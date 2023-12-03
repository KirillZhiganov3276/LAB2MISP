#include "table.h"

Table::Table(const uint skey)
{
    key = skey;
}

std::wstring Table::encrypt(std::wstring& open_text)
{
    size_t pos = 0;
    std::wstring dectext=L"";
    std::wstring alpha;
    while (open_text.size()%key!=0) {
        open_text+=L" ";
    }
    size_t size=open_text.size()/key;
    for (size_t i=1; i<=size; i++) {
        std::wstring sub = open_text.substr(pos, key);
        subNum[i]=sub;
        pos=pos+key;
    }
    for (int stolb=key; stolb>=1; stolb--) {
        for (size_t str=1; str<=size; str++) {
            alpha = subNum[str][stolb-1];
            if(alpha==L" ")
                dectext+=L"*";
            else
                dectext+=alpha;
        }
    }
    return dectext;
}

std::wstring Table::decrypt(const std::wstring& cipher_text)
{
    size_t size=cipher_text.size()/key;
    size_t pos = 0;
    std::wstring text=L"", restext;
    std::wstring alpha;
    for (int i=1; i<=key; i++) {
        std::wstring sub = cipher_text.substr(pos, size);
        resubNum[i]=sub;
        pos=pos+size;
    }
    for (size_t stolb=1; stolb<=size; stolb++) {
        for (size_t str=key; str>=1; str--) {
            text+=resubNum[str][stolb-1];
        }
    }
    restext=text;
    for (size_t i= text.size()-1; i>=0; i--) {
        alpha=text[i];
        if (alpha==L"*") {
            restext.erase(i, 1);
        } else {
            break;
        }
    }
    return restext;
}
