#include "modAlphaCipher.h"

std::wstring modAlphaCipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(open_text);
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::vector<int> modAlphaCipher::convert(const std::wstring& s)
{
    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

std::wstring modAlphaCipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

std::wstring modAlphaCipher::getValidKey(const std::wstring & s)
{
    //setup converter
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    if (s.empty())
        throw cipher_error("Empty key");
    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    std::wstring tmp(s);
    std::string st = converter.to_bytes(s);
    
    for (auto & c:tmp) {
        if (!iswalpha(c))
            throw cipher_error(std::string("Key has invalid symbols: ")+st);
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}