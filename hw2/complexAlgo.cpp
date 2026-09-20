#include <cmath> 
#include "complexalgo.hpp"
#include "complexbase.hpp"

    // создадим класс "Комплексного числа" на базе double
    ComplexAlgo::ComplexAlgo(double Re, double Im)
    {
        this->Re = Re;
        this->Im = Im;
    }


    // Геттеры 
    double ComplexAlgo::getRe() const {
        return this->Re;
    }

    double ComplexAlgo::getIm() const {
        return this->Im;
    }
    
    ComplexBase* ComplexAlgo::add(const ComplexBase& right) const {
        return new ComplexAlgo(Re + right.getRe(), Im + right.getIm());
    }
    ComplexBase* ComplexAlgo::mul(const ComplexBase& right) const {
        return new ComplexAlgo(Re * right.getRe() - Im * right.getIm(),
                            Re * right.getIm() + Im * right.getRe());
    }
    ComplexBase* ComplexAlgo::neg() const {
        return  new ComplexAlgo(-Re, -Im);
    }
    ComplexBase* ComplexAlgo::sub(const ComplexBase& right) const {
        return new ComplexAlgo(Re - right.getRe(), Im - right.getIm());
    }
    ComplexBase* ComplexAlgo::sqrt() const {
        const double x = Re;
        const double y = Im;
        const double absZ = std::hypot(x, y);  //  sqrt (x^2 +y^2 ) 

        const double u = std::sqrt((absZ + x) / 2.0);
        const double v = std::sqrt((absZ - x) / 2.0) * (y >= 0 ? 1.0 : -1.0);

        return new ComplexAlgo(u, v);
    }
    ComplexBase* ComplexAlgo::div(const ComplexBase& right) const {
        const double rRe = right.getRe();
        const double rIm = right.getIm();
        const double denom = rRe * rRe + rIm * rIm;
        if (denom == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        return new ComplexAlgo(
            (Re * rRe + Im * rIm) / denom,
            (Im * rRe - Re * rIm) / denom
        );
    }
    bool ComplexAlgo::equals (const ComplexBase& right) const {
        return  (Re == right.getRe() && Im == right.getIm());
    }


 