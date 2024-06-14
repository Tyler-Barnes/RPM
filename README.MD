## **RPM Library** for Arduino

**Written by:** _Tyler Barnes_. 

### **What is the RPM Library?**

The RPM.h library was created to make it incredibly easy to read RPM sensors. Simply call `RPM.start()` to initialize, and start reading data with `RPM.get()`. 

The library uses the input capture feature within the hardware timer of the microcontroller. This is an extremely accurate technique for measuring input signals, pulse width, and timing in general. 

### **Why Use This Over Other Options?**

The main focus for making this was creating something that returned an accurate and fresh value instantly without any waiting. It only takes a single revolution to calculate the RPM. 

Also, accuracy was a big focus to get right. While there might be some variation from the CPU being slightly off from the rated clockspeed, it is negligable.

The size of the library is also very compact. Using only 738 bytes of flash, and 12 bytes of RAM on an Arduino Nano. 

Lastly, the library does not take away the External Interrupts from the user. So you are free to use `attachInterrupt()` as you please. 

### **What are the Drawbacks?**

The library uses Timer1 on the UNO and Nano, so you will no longer be able to call `analogWrite()` on pins 9 or 10.

The library uses Timer4 on the Mega, so you will no longer be able to call `analogWrite()` on pins 6, 7, or 8. 

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

On the Uno, or Nano, the input capture pin is 8. 
On the Leonardo, Or Sparkfun Pro Micro, the input capture pin is 4. 
On the Mega the input capture pin used is pin 48.

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

The `RPM.get()` method returns a `uint16_t` containg the RPM value measured on the pin specified by `RPM.pin()`. 

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

The higher the RPM becomes, the less timer counts there are to measure. So, accuracy can drop to 0.5% when you are nearing 60,000.  




