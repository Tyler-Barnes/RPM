## **RPM Library** for Arduino

**Written by:** _Tyler Barnes_. 

### **What is the RPM library?**

The RPM.h library was created to make it incredibly easy to read RPM sensors. Simply specify a PCINT capable pin, and start reading data. 



### **How to install it**

#### **Method 1** _(Recommended)_
To install the library, click on the `Sketch` tab within the Arduino IDE, click on `Include Library`, then click on `Manage Libraries...`. 

Once the library browser launches, type `RPM` into the search field, then click on the RPM library's `Install` button. 

#### **Method 2**
Alternatively, the RPM.h library can be downloaded from the releases section of the [github repository](https://github.com/Tyler-Barnes/RPM). 

Once the .zip file has been downloaded, click on the `Sketch` tab within the Arduino IDE, click on `Include Library`, then click on `Add .ZIP Library...`. 

The resulting dialog will allow you to locate the library within your computer's directories, and open it. 


### **How to use it**
To add its functionality to your sketch you'll need to reference the library header file. You do this by adding an include directive to the top of your sketch.

```c++
#include <RPM.h>

void setup(){

}

void loop(){

}

```

The library provides a global variable named `RPM`, you use this variable to access the library's methods. The methods provided in the RPM class are listed below.

### **Library functions**

#### **`RPM.pin(pin)`** 

To specify which pin you would like to read your RPM sensor with, call the `RPM.pin()` method, and pass in the PCINT compatible pin. 

```c++
#include <RPM.h>

void setup(){
    RPM.pin(3); 
}

void loop(){

}
```

A list of the PCINT compatible pins is provided in the file named [`PCINT_Pins.MD`](https://github.com/Tyler-Barnes/RPM/blob/main/PCINT_Pins.MD). 

#### **`RPM.get()`** 

The `RPM.get()` method returns a `uint32_t` containg the RPM value measured on the pin specified by `RPM.pin()`. 

```c++
#include <RPM.h>

void setup(){
    Serial.begin(9600); 
    RPM.pin(3); 
}

void loop(){
    Serial.println(RPM.get());
}
```

### **Advanced features**

#### **`RPM.buffer(int value)`** 

The library implements a buffer in order to ensure there are enough samples to work with at low RPM. This buffer is dynamic, and changes it's own size based on the current RPM value. 

If the RPM is slow, then the buffer size is increased in order to handle it. 

If the RPM is fast, then the buffer size is reduced in order to increase the response time. 

Capturing RPM data via `RPM.get()` will _still_ happen instantaniously, the buffer simply works in the background. The buffer size will dictate how long it takes for the returned value to settle into the correct value.

If you wish, you can change the buffer size to a constant value by using the `RPM.buffer()` method. It takes in a `int` which will set the size of the buffer in `milliseconds`.   

```c++
#include <RPM.h>

void setup(){
    Serial.begin(9600); 
    RPM.pin(3); 
    RPM.buffer(1000); 
}

void loop(){
    Serial.println(RPM.get());
}
```

To set the buffer back to the default dynamic mode, pass the built in constant `DYNAMIC` into the `RPM.buffer()` method. 

```c++
RPM.buffer(DYNAMIC); 
```  

### **An Important Note on Performance and Accuracy**

Accuracy overall is about ±1%, but some times there are fluctuations that appear that could be ±3%. There is some inaccuracy introduced by calling `micros()`, as well as by interrupts happening while calculations are made. 

The slower you access `RPM.get()`, the more accurate the value will be. 

Low RPM values are more difficult the measure than higher ones. There will ultimately be a lower limit at which data will start to break down the lower the RPM becomes. I have found that I can read down to 60RPM, but the time it takes to accumulate enough samples means that it takes some time to settle into the correct value. 

The highest RPM the library supports is somewhere near 65,000. RPMs above that quickly became irratic so I decided to store the RPM value as a `uint16_t` since anything above that was unreliable anyway.  

### **Using Multiple Sensors**

You can get a marginal improvement to performance by using multiple sensors. 

The library supports two sensors. (If you try to assign more than two, the program will halt)

The placement of the second sensor is important for accuracy. I suggest placing a second sensor 180° out of phase with the first one. This means if you are measuring a rotating object, then one sensor would be on either side. 

Once it is accurately placed, simply define another `RPM.pin()` and the library will start using both sensors to accumulate sample data. 

```c++
#include <RPM.h>

void setup(){
    Serial.begin(9600); 
    RPM.pin(3); 
    RPM.pin(5); 
}

void loop(){
    Serial.println(RPM.get());
}
```

#### **`RPM.mode(uint8_t mode)`** 

By default, the mode of operation is set to `AGGREGATE`. This will read in multiple sensors in order to gain more samples per revlution. 

If you instead want to read the RPM of two separate sources, then you can set the running mode to `SEPARATE`. 

```c++
#include <RPM.h>

void setup(){
    Serial.begin(9600); 
    RPM.mode(SEPARATE); 
    RPM.pin(3); 
    RPM.pin(5); 
}
```
In order to get the RPM values, pass the pin number into the `RPM.get()` method. 

```c++
#include <RPM.h>

void setup(){
    Serial.begin(9600); 
    RPM.mode(SEPARATE); 
    RPM.pin(3); 
    RPM.pin(5); 
}

void loop() {
    Serial.println(RPM.get(3));
    Serial.println(RPM.get(5));
}
```

#### **`RPM.redefine(uint8_t oldPin, uint8_t newPin)`** 

If you need to dynamically change the pin you want to read using the library, you can redefine a sensor pin using `RPM.redefine()`. 

Pass the pin you want to disable into the first argument, and the pin you want to enable into the second. 

```c++
RPM.redefine(5, 7);
```

Note that the library still needs some amount of time to accumulate samples, so you will not be able to switch between pins back and forth rapidly and expect the values to behave properly. 

### **`rpm_release_vectors`**

The library automatically defines `ISR()` functions in order to keep track on the incoming data. In order to make the library as easy to use and as universal as possible, it pre-defines every pin change interrupt (`PCINTn_vect`) available. 

If you try to define a `ISR()` function with a pin chanage interrupt, you will get an error explaining:

```
RPM:12:5: error: redefinition of 'void __vector_3()'
 ISR(PCINT0_vect){
     ^

``` 

If you would like to use a pin change interrupt for something other than the RPM library, you can define `rpm_release_vectors` above where you `#include` the `RPM.h` file. 

```c++
#define rpm_release_vectors
#include <RPM.h>
```

This will release the `ISR()` functions, and hand over the control to the end user. This means, however that you will need to manually setup the `ISR()` that the RPM library needs to use. 

To do this, start by finding which interrupt vector your chosen pin needs ot utilize. You can find a list of the pins and their vectors in the file named [`PCINT_Pins.MD`](https://github.com/Tyler-Barnes/RPM/blob/main/PCINT_Pins.MD). 

Once you have the vector id, add the function `incRPM()` into the `ISR()` function. 

```c++
#define rpm_release_vectors
#include <RPM.h>

ISR(PCINT0_vect) {
    incRPM(); 
}

ISR(PCINT1_vect){
    // whatever you want
}

void setup() {
    Serial.begin(9600); 
    RPM.pin(3); 
}

void loop() {
    Serial.println(RPM.get());
}

```

If you choose to use multiple sensors while also using `rpm_release_vectors`, make sure that the pins chosen are both on the same `PCINT_vector`. 



