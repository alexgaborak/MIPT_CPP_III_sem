#include <iostream>
#include <cmath>

class Complex{
    double m_re, m_im, m_modul, m_argument;
public:
    Complex( double re, double im ): m_re(re), m_im(im) {
        this->m_modul = mod();
        this->m_argument = arg();
    }

    Complex(): Complex(0, 0){
        // std::cout << this << std::endl;
    }

    Complex( const Complex &other ): Complex(other.m_re, other.m_im) {
        // std::cout << this << std::endl;
    }

    Complex& operator=(const Complex &other){
        if(this != &other){
            m_im = other.m_im;
            m_re = other.m_re;
            m_argument = other.m_argument;
            m_modul = other.m_modul;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &os, const Complex &complex){
        os << "Re: " << complex.m_re << ", Im: " << complex.m_im;
        return os;
    }

    double getMod(){
        return this->m_modul;
    }

    double getArg(){
        return this->m_argument;
    }

private:
    double mod(){
        return sqrt( m_re * m_re + m_im * m_im );
    }
    double arg(){
        return atan2(m_im, m_re);
    }
};
int main(){
    Complex complex(1, 2);
    Complex complex2(2, 3);
    Complex complex3;
    complex3 = complex = complex2;

    std::cout << complex3 << std::endl;

    // double mod = complex.getMod();
    // double arg = complex.getArg();
}