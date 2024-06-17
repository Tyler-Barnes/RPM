## **RPM Library** for Arduino

**Written by:** _Tyler Barnes_. 

### **What is the RPM Library?**

The RPM.h library was created to make it incredibly easy to read RPM sensors. Simply call `RPM.start()` to initialize, and start reading data with `RPM.get()`. 

The library uses the input capture feature within the hardware timer of the microcontroller. This is an extremely accurate technique for measuring input signals, pulse width, and timing in general. 

### **Why Use This Over Other Options?**

The main focus for making this was creating something that returned an accurate and fresh value instantly without any waiting. It only takes a single revolution to calculate the RPM, which has already happened before calling `RPM.get()`. 

No setting up interrupts! Other libraries that I tried always required me to set up my own `ISR()`, and to `attachInterrupt()` manually. I might as well have written the entire thing myself at that point. So, that's what I did, so you don't have to. 

Also, accuracy was a big focus to get right. While there might be some variation from the CPU being slightly off from the rated clockspeed, it is often negligable. You can even fine tune the accuracy if you want to. 

The size of the library is also very compact. Using only 644 bytes of flash, and 15 bytes of RAM on an Arduino Nano. 

Lastly, the library does not take away the External Interrupts from the user. So you are free to use `attachInterrupt()` as you please. 

### **What are the Drawbacks?**

The library has to use a timer to function, so it may take away a PWM channel that happens to use the same timer. 

Here is a table containing which digital pins will lose the `analogWrite()` function. 

| Platform | Pins |
|-|-|
| UNO, Nano, Leonardo, Pro Mini, Micro, Fio, BT, Yun, Sparkfun Pro Micro | 9, 10 |
| Mega | 6, 7, 8 |
| Nano Every | 6 |

| AVR Chip | Pins |
|-|-|
| ATmega328P | PB1, PB2 |
| ATmega32U4 | PB5, PB6 |
| ATmega2560 | PH3, PH4, PH5 |
| ATmega4809 | PF4 |

### **Is My Arduino Compatible?**

Here is a list of boards I know to be compatible: 

| Platform | 
|-|
|UNO|
|Nano|
|Nano Every| 
|Leonardo|
|Pro Mini|
|Micro|
|Fio|
|BT|
|Yun|
|Sparkfun Pro Micro|

Here is a list of boards that are not compatible:

| Platform | 
|-|
|LilyPad|
|Gemma|
|DFRobot Beetle|
|DFRobot Beetle BLE|

### **How to Install It**

#### **Method 1** _(Recommended)_
To install the library, click on the `Sketch` tab within the Arduino IDE, click on `Include Library`, then click on `Manage Libraries...`. 

Once the library browser launches, type `RPM` into the search field, then click on the RPM library's `Install` button. 

#### **Method 2**
Alternatively, the RPM.h library can be downloaded from the releases section of the [github repository](https://github.com/Tyler-Barnes/RPM). 

Once the .zip file has been downloaded, click on the `Sketch` tab within the Arduino IDE, click on `Include Library`, then click on `Add .ZIP Library...`. 

The resulting dialog will allow you to locate the library within your computer's directories, and open it. 

### **Hookup Instructions**
The input capture method uses very specific pins on the Arduino. They usually do not overlap other powerful functions though. 

Here is a table outlining which pin to use on which platform. 

| Platform | Capture Pin |
|-|-|
| UNO, Nano, Pro Mini, Yun, Fio, BT | 8 |
| Nano Every | 6 |
| Micro, Leonardo, Sparkfun Pro Micro | 4 | 
| Mega | 49 |

If you are not using a premade developement board and instead using a compatible AVR microcontroller in your project, you can see which pin to use in this table: 

| AVR Chip | Capture Pin | 
|-|-|
| ATmega328P | PB0 |
| ATmega32U4 | PD4 | 
| ATmega2560 | PL0 | 
| ATmega4809 | PF4 | 


### **How To Use It**
To add its functionality to your sketch you'll need to reference the library header file. You do this by adding an include directive to the top of your sketch.

```c++
#include <RPM.h>

void setup(){

}

void loop(){

}

```

The library provides a global variable named `RPM`, you use this variable to access the library's methods. The methods provided in the RPM class are listed below.

### **Library Functions**

#### **`RPM.start()`** 

To initialize the library, call the `RPM.start()` method. This will set up the input capture registers and interrupts for you. 

```c++
#include <RPM.h>

void setup(){
    RPM.start(); 
}

void loop(){

}
```

#### **`RPM.get()`** 

The `RPM.get()` method returns a `uint16_t` containing the RPM value measured on the input capture pin.

```c++
#include <RPM.h>

void setup(){
    Serial.begin(9600); 
    RPM.start() 
}

void loop(){
    Serial.println(RPM.get());
}
```

#### **An Important Note on Performance and Accuracy**

Accuracy overall is about ±0.1% for general RPM ranges. 

Lower RPMs are more accurate than higher ones. 

The lowest RPM it will measure is 240RPM. 

The highest RPM is around 60,000RPM. 

The higher the RPM becomes, the less timer counts there are to measure. So, accuracy can drop when you are nearing 60,000.  

### **Advanced Features**

#### **`RPM.error(float value)`**

If the clock speed on your board is not running to specification, then the RPM calculation can be off. The input voltage will also have a direct effect on clockspeed, so it can vary from application. 

My Arduino Mega for example was pretty far off, so I've included a way to correct it. 

You can fine tune the RPM value by using the `RPM.error()` method. It takes in a `float` value. 

I will demonstrate now how to calculate the value you'd want to enter. 

First hook up a calibrated signal source to the input capture pin. I used a function generator set to a pulse wave. 

Set the frequency of the signal source somewere in the 50Hz to 200Hz range. I chose 100Hz in my testing. 

Convert the frequency into an RPM value by multiplying it by 60. 

`100Hz * 60 = 6000RPM`

Next, run a sketch that spits out the RPM value into the Serial Monitor. 

```c++
#include <RPM.h>

void setup() {
  Serial.begin(9600);
  RPM.start(); 
}

void loop() {
  Serial.println(RPM.get());
}
```

I got an output that looks like this:
```
6048
6048
6048
6048
6050
6050
6050
6050
6050
6050
...
```
Subract the measured value from the calculated one. 

`6000 - 6048 = -48`

Then divide the result by the calculated value. 

`-48 / 6000 = -0.008`

This is now the value you should pass into `RPM.error()`. 
```c++
#include <RPM.h>

void setup() {
  Serial.begin(9600);
  RPM.start(); 
  RPM.error(-0.008); 
}

void loop() {
  Serial.println(RPM.get());
}
```

The result should now be calibrated: 

```
5999
5999
6001
6001
6001
6001
...
```

