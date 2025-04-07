#include <iostream>
#include <string>
#include <vector>

// TODO: implement

namespace rustykitty {
    class BigInt {
    private:
        std::vector<bool> bits;
    public:
        BigInt(const std::string&);
        BigInt(long long int);
        BigInt(unsigned long long int);
        BigInt(const BigInt&);

        BigInt operator+(const BigInt&) const;
        BigInt operator-(const BigInt&) const;
        BigInt operator*(const BigInt&) const;
        BigInt operator/(const BigInt&) const;
        BigInt operator%(const BigInt&) const;

        BigInt operator&(const BigInt&) const;
        BigInt operator|(const BigInt&) const;
        BigInt operator^(const BigInt&) const;
        BigInt operator~() const;
        BigInt operator<<(const BigInt&) const;
        BigInt operator>>(const BigInt&) const;

        bool operator<(const BigInt&) const;
        bool operator>(const BigInt&) const;
        bool operator==(const BigInt&) const;

        friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt);
    };

    BigInt pow (const BigInt&, const BigInt&);
}
