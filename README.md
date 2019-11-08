# Struct
Class for interpreting byte arrays as C data types  
Written by Dan Oates (WPI Class of 2020)

### Description
The Struct class has similar functionality to the Python struct module. A struct instance takes a pointer to an array of uint8_t and an endian (msb_first or lsb_first) enum at construction. The template 'set' and 'get' methods pack and unpack arbitrarily-typed primitive data into and from the array, respectively, starting at the zeroth index of the array and incrementing up by the size of the packed or unpacked type. The index is automatically reset to zero when switching between 'get' and 'set' operations. Additional arrow and typecast operators are defined for more compact syntax, and most methods and operators return a reference to the Struct so that multiple methods can be called on one line.

### Example
Read two floats from Arduino Serial then write back their sum and integer product:
```
// Read data
uint8_t data[8];
Struct str(data, Struct::lsb_first);
Serial.readBytes(str.get_data(), 8);

// Process
float x, y;
str.get(x).get(y);	// (str >> x) >> y;
float s = x + y;
int16_t p = x * y;

// Write data
str.set(s).set(p);	// (str << s) << p;
Serial.writeBytes(str.get_data(), 6);
```

### References
- [Python struct](https://docs.python.org/2/library/struct.html)