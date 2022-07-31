
#include <chrono>
#include <thread>
#include <vector>
#include <bcm2835.h>
// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
#include "led.h"

// MEMO
// ピンの状態は「raspi-gpio」コマンドを使用する
// 全部見たい時は「raspi-gpio get」コマンド
// 「pinout」コマンドでピン配を確認可能

// TODO
// ピン配を調べる。
// Lチカをbcm2835でやってみる

int main(int argc, char** argv)
{

    const int PIN17 = RPI_V2_GPIO_P1_11;
    const int PIN22 = RPI_V2_GPIO_P1_15;
    const int PIN27 = RPI_V2_GPIO_P1_13;
    // If you call this, it will not actually access the GPIO
    // Use for testing
//    bcm2835_set_debug(1);

    if (!bcm2835_init())
        return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN17, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN27, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN22, BCM2835_GPIO_FSEL_OUTP);

    // Blink
    led led1(PIN17, 500);
    led led2(PIN27, 500);
    led led3(PIN22, 500);

    std::vector<led> leds = { led1, led2, led3 };

    while (1)
    {
        for (auto&& l : leds)
        {
            l.start();
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(500ms);

            l.pause();
        }
    }

    // led1.start();
    // led2.start();
    // led3.start();

    // using namespace std::chrono_literals;
    // std::this_thread::sleep_for(8000ms);

    // led1.stop();
    // led2.stop();
    // led3.stop();

    bcm2835_close();
    return 0;
}
// #include <chrono>
// #include <thread>
// #include <bcm2835.h>
// // Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
// #include "led.h"

// // MEMO
// // ピンの状態は「raspi-gpio」コマンドを使用する
// // 全部見たい時は「raspi-gpio get」コマンド
// // 「pinout」コマンドでピン配を確認可能

// // TODO
// // ピン配を調べる。
// // Lチカをbcm2835でやってみる

// int main(int argc, char** argv)
// {

//     const int PIN17 = RPI_V2_GPIO_P1_11;
//     const int PIN22 = RPI_V2_GPIO_P1_15;
//     const int PIN27 = RPI_V2_GPIO_P1_13;
//     // If you call this, it will not actually access the GPIO
//     // Use for testing
// //    bcm2835_set_debug(1);

//     if (!bcm2835_init())
//         return 1;

//     // Set the pin to be an output
//     bcm2835_gpio_fsel(PIN17, BCM2835_GPIO_FSEL_OUTP);
//     bcm2835_gpio_fsel(PIN22, BCM2835_GPIO_FSEL_OUTP);
//     bcm2835_gpio_fsel(PIN27, BCM2835_GPIO_FSEL_OUTP);

//     // Blink
//     led led1(PIN17, 500);
//     led led2(PIN27, 250);
//     led led3(PIN22, 125);
//     led1.start();
//     led2.start();
//     led3.start();

//     using namespace std::chrono_literals;
//     std::this_thread::sleep_for(8000ms);

//     led1.stop();
//     led2.stop();
//     led3.stop();

//     bcm2835_close();
//     return 0;
// }