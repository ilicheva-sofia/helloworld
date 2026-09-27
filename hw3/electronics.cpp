#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <format>


template <typename T>
class Measurement{
    public:
    std::chrono::system_clock::time_point time;
    T value;
    double inaccuracy;
};

template <typename T, typename CharT>
struct std::formatter<Measurement<T>, CharT> {
    std::formatter<double, CharT> doubleFmt;
     constexpr auto parse(std::format_parse_context& ctx) {
        return doubleFmt.parse(ctx);
    }

    template <typename FormatContext>
    auto format(const Measurement<T>& m, FormatContext& ctx) const {
        // 1. Формируем строку времени "HH:MM:SS"
        std::time_t t = std::chrono::system_clock::to_time_t(m.time);
        std::tm tm{};
        localtime_r(&t, &tm);

        char timeBuf[16];
        std::strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &tm);

        // 2. Выводим: "значение ± погрешность ед (в HH:MM:SS)"
        auto out = ctx.out();

        out = doubleFmt.format(m.value.get_value(), ctx);

        out = std::format_to(out, " ± {:.4g} {} (в {})",
                            m.inaccuracy,
                            m.value.unit(),
                            timeBuf);
        return out;
    }
};


namespace Units{

    class Amper{
        private:
        double value;
        public:
        explicit Amper (double val): value(val){
            if (val < 0.0){
                throw std::invalid_argument("значение не может быть отрицательным");
            }
        }
        double get_value() const { return value; }
        const char* unit() const{ return "mA"; }



    }; 
    Amper operator""_mA (long double val){ return Amper (static_cast<double> (val) ); }

    class Volt{
        double value;
        public:
        explicit Volt (double val): value(val){}
        double get_value() const { return value; }
        const char* unit() const{ return "V"; }

    };
    Volt operator""_V(long double val){ return Volt (static_cast<double> (val) ); }


    class Ohm{
        double value;
        public:
        explicit Ohm (double val): value(val){
            if (val < 0.0){
                throw std::invalid_argument("значение не может быть отрицательным");
            }
        }
        double get_value() const { return value; }
        const char* unit() const { return "Ohm"; }

    };
    Ohm operator""_Ohm(long double val){ return Ohm (static_cast<double> (val) ); }
    

    class Watt{
        double value;
        public:
        explicit Watt (double val): value(val){
            if (val < 0.0){
                throw std::invalid_argument("значение не может быть отрицательным");
            }
        }
        double get_value() const { return value; }
        const char* unit() const { return "W"; }

    };
    Watt operator""_W(long double val){ return Watt (static_cast<double> (val) ); }
    

    class Joule{
        double value;
        public:
        explicit Joule (double val): value(val){
            if (val < 0.0){
                throw std::invalid_argument("значение не может быть отрицательным");
            }
        }
        double get_value() const { return value; }
        const char* unit() const { return "J"; }

    };
    Joule operator""_J (long double val){ return Joule (static_cast<double> (val) ); }
    

    class Seconds{
        double value;
        public:
        explicit Seconds (double val): value(val){
            if (val < 0.0){
                throw std::invalid_argument("значение не может быть отрицательным");
            }
        }
        double get_value() const { return value; }
        const char* unit() const { return "s"; }
    };
    Seconds operator""_s (long double val){ return Seconds (static_cast<double> (val) ); }

    Amper operator/(const Volt &u, const Ohm &r){ return Amper (static_cast<double> ( u.get_value() / r.get_value()) ); }
    Volt operator*(const Amper &i, const Ohm &r){ return Volt (static_cast<double> ( i.get_value() * r.get_value()) ); }
    Volt operator*( const Ohm &r, const Amper &i){ return Volt (static_cast<double> ( i.get_value() * r.get_value()) ); }
    Ohm operator/( const Volt &u, const Amper &i){ return Ohm (static_cast<double> ( u.get_value() / i.get_value()) ); }
    Watt operator*(const Amper &i, const Volt &u){ return Watt (static_cast<double> ( i.get_value() * u.get_value()) ); }
    Watt operator*( const Volt &u, const Amper &i){ return Watt (static_cast<double> ( i.get_value() * u.get_value()) ); }
    Joule operator*( const Watt &p, const Seconds &t){ return Joule (static_cast<double> ( p.get_value() * t.get_value()) ); }
    Joule operator*( const Seconds &t, const Watt &p){ return Joule (static_cast<double> ( p.get_value() * t.get_value()) ); }



}

namespace Device{
    class Voltmeter{
        private:
        double range;
        double accuracy;
        std::string id;

        public:
        explicit Voltmeter(double range, double accuracy, std::string id)
             : range(range), accuracy(accuracy), id(std::move(id)) {
        if (range <= 0.0)
            throw std::invalid_argument("Диапазон должен быть положительным");
        if (accuracy <= 0.0 || accuracy > 100.0)
            throw std::invalid_argument("Класс точности должен быть от 0 до 100%");
        if (id.empty())
            throw std::invalid_argument("Идентификатор не может быть пустым");
        }
        
        Measurement <Units::Volt> measure () const { 
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<> dist(0.0, range);

            double raw = dist(gen);
            double err = raw * (accuracy/ 100.0);

            return {std::chrono::system_clock::now(), Units::Volt(raw), err};
        }
        



    };
    class Ampermeter{
        private:
        double range;
        double accuracy;
        std::string id;
        public:
        explicit Ampermeter(double range, double accuracy, std::string id)
         : range(range), accuracy(accuracy), id(std::move(id)) {
        if (range <= 0.0)
            throw std::invalid_argument("Диапазон должен быть положительным");
        if (accuracy <= 0.0 || accuracy > 100.0)
            throw std::invalid_argument("Класс точности должен быть от 0 до 100%");
        if (id.empty())
            throw std::invalid_argument("Идентификатор не может быть пустым");
        }

        Measurement <Units::Volt> measure () const { 
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<> dist(0.0, range);

            double raw = dist(gen);
            double err = raw * (accuracy/ 100.0);

            return {std::chrono::system_clock::now(), Units::Volt(raw), err};
        }

    };
    class Multimeter{
        private:
        double range;
        double accuracy;
        std::string id;
        public:
        explicit Multimeter (double range, double accuracy, std::string id)
         : range(range), accuracy(accuracy), id(std::move(id)) {
        if (range <= 0.0)
            throw std::invalid_argument("Диапазон должен быть положительным");
        if (accuracy <= 0.0 || accuracy > 100.0)
            throw std::invalid_argument("Класс точности должен быть от 0 до 100%");
        if (id.empty())
            throw std::invalid_argument("Идентификатор не может быть пустым");
        }
        Measurement <Units::Ohm> measure () const { 
            std::mt19937 gen(std::random_device{}());
            std::uniform_real_distribution<> dist(0.0, range);

            double raw = dist(gen);
            double err = raw * (accuracy/ 100.0);

            return {std::chrono::system_clock::now(), Units::Ohm(raw), err};
        }


    };
}


int main(){
    using  namespace Units;
    using namespace Device;

    Volt u = 12.0_V;
    Amper i = 2.0_mA;
    Ohm r = 6.0_Ohm;
    Seconds t = 10.0_s;
    Watt p = 50.0_W;

    auto p1 = u * i;           // Volt * Ampere → Watt
    auto p2 = i * u;           // Ampere * Volt → Watt (работает!)

    auto e1 = p1 * t;          // Watt * Second → Joule
    auto e2 = t * p1;          // Second * Watt → Joule (работает!)

    // Закон Ома
    auto i2 = u / r;           // Volt / Ohm → Ampere
    auto u2 = i * r;           // Ampere * Ohm → Volt

    std::cout << "Мощность (u*i): " << p1.get_value() << " " << p1.unit() << "\n";
    std::cout << "Энергия (p*t): " << e1.get_value() << " " << e1.unit() << "\n";
    std::cout << "Ток (u/r): " << i2.get_value() << " " << i2.unit() << "\n";


    Voltmeter  vm(10.0, 1.0, "V-001");
    Ampermeter am(5.0, 1.5, "A-002");
    Multimeter mm(1000.0, 2.0, "M-003");

    auto mv = vm.measure();
    std::cout << std::format("{}",mv) << std::endl;

    auto ma = am.measure();
    std::cout << std::format("{}",ma) << std::endl;

   
    return 0;
};





