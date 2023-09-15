#include <iostream>
#include <cstring>

class String{
    char *m_str;
    size_t m_len;
public:
    String( const char *str ){
        m_len = strlen(str);
        m_str = new char[m_len + 1];
        strcpy(m_str, str);
        m_str[m_len] = '\0';
        std::cout << "constructor " << m_str << std::endl;
    }

    String( const String &other ): String(other.m_str) {
        
    }

    ~String(){ // вызывается при явном или не явном удалении
        std::cout << "destructor " << m_str << std::endl;
        delete[] m_str;
        m_str = nullptr;
    }

    String& operator=(const String& string){
        if(this != &string){
            String tmp(string.m_str);
            std::swap(m_str, tmp.m_str);
            std::swap(m_len, tmp.m_len);
        }
        return *this;
    }

    friend std::ostream& operator<<( std::ostream& os, const String &string ){
        os << string.m_str;
        return os;
    }

};

int main(){

    String str0("Hello");
    String str1("World");

    String str2(str1);

    str0 = str1;

    std::cout << str0 << " " << str1 << std::endl;

    // String *string = new String("Hello World"); // выделение памяти в куче
    // std::cout << *string << std::endl;
    // delete string;

}