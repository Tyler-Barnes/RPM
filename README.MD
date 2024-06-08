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

The library provides a global variable named `RPM`, you use this variable to access the library methods. The methods provided in the RPM class are listed below.

### **Library functions**

#### **`RPM.pin( pin )`** 

To specify which pin you would like to read your RPM sensor with, call the `RPM.pin()` method, and pass in the PCINT compatible pin. 

```c++
#include <RPM.h>

void setup(){
  RPM.pin(3); 
}

void loop(){

}
```

A list of the PCINT compatible pins is provided in the file named `PCINT_Pins.MD`. 

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
  delay(250); 

}
```

### **Advanced features**

#### **`RPM.buffer(int value)`** 

The library implements a buffer in order to ensure there are enough samples to work with at low RPM. This buffer is dynamic, and changes it's size based on the current RPM value. 

If the RPM is slow, then the buffer size is increased in order to handle it. 

If the RPM is fast, then the buffer suize is reduced in order to increase the response time. 

You can change the buffer size to a constant value by using the `RPM.buffer()` method. It takes in a `int` which will set the number of milliseconds the buffer stays active capturing data. Capturing RPM data via `RPM.get()` will _still_ happen instantaniously, the buffer simply works in the background. 

The default value is the built in constant `DYNAMIC`. 

```c++
#include <RPM.h>

void setup(){
  Serial.begin(9600); 
  RPM.pin(3); 
  RPM.buffer(1000); 
}

void loop(){
  Serial.println(RPM.get());
  delay(250); 

}
```

### **An important note on performance and accuracy**

The faster you access the `RPM.get()` method, the less accurate the value will be. The library needs to accumulate enough samples to give you an accurate result. 

Low RPM values are intrinsically difficult, since the microcontroller operates at very fast speeds in comparison to the data being aquired. You will either need to increase the buffer size, or delay access to the `RPM.get()` method by doing some other processing in the meantime, or adding in a `delay()`. 

There will ultimately be a lower limit at which data will start to break down and give you glitches as the buffer resets.  
