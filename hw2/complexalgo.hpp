#include "complexbase.hpp"
class ComplexAlgo :public ComplexBase
{
    private: 
    double Re;
    double Im;

    public:
        ComplexAlgo( const double Re, const double Im);
         ~ComplexAlgo ();
         double getRe() const override;
         double getIm() const override;

         ComplexBase* add(const ComplexBase& right) const override;
         ComplexBase* mul(const ComplexBase& right) const override;
         ComplexBase* neg() const override;
         ComplexBase* sub(const ComplexBase& right) const override;
         ComplexBase* sqrt() const override;
         ComplexBase* div(const ComplexBase& right) const override;
         bool equals(const ComplexBase& right) const override;

    };