
    class ComplexBase
    {
    public:
        virtual ~ComplexBase ();
        virtual double getRe() const = 0;
        virtual double getIm() const = 0;

        virtual ComplexBase* add(const ComplexBase& right) const = 0;
        virtual ComplexBase* mul(const ComplexBase& right) const = 0;
        virtual ComplexBase* neg() const = 0;
        virtual ComplexBase* sub(const ComplexBase& right) const = 0;
        virtual ComplexBase* sqrt() const = 0;
        virtual ComplexBase* div(const ComplexBase& right) const = 0;
        virtual bool equals(const ComplexBase& right) const = 0;

    };