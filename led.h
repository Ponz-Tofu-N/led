

class led
{
public:
    led(int _pin, int _interval);
    led(const led& other);
    ~led();

    int pin;
    int interval;

    bool isActive = false;

    void flash();
    void start();
    void stop();
    void pause();
    void turnOn();
    void turnOff();

private:
    std::thread t;
};
