#include <bcm2835.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "led.h"

led::led(int _pin, int _interval)
    :pin(_pin), interval(_interval)
{}

led::led(const led& other)
    :pin(other.pin), interval(other.interval)
{}

led::~led() {}

void led::flash() {
    // Turn it on
    bcm2835_gpio_write(pin, HIGH);

    // wait a bit
    std::this_thread::sleep_for(std::chrono::milliseconds(interval));

    // turn it off
    bcm2835_gpio_write(pin, LOW);

    // wait a bit
    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
};

void led::start()
{
    isActive = true;
    // 別スレッドでループを回す。
    std::cout << t.joinable() << std::endl;

    if (!t.joinable()) {
        t = std::thread([this]() {
            while (isActive)
            {
                flash();
            }
            });
    }
}

void led::stop() {
    isActive = false;
    t.join();

    t = std::thread();
};

void led::pause() {
    isActive = false;
};

void led::turnOn() {
    isActive = true;
    bcm2835_gpio_write(pin, HIGH);
};
void led::turnOff() {
    isActive = false;
    bcm2835_gpio_write(pin, LOW);
};