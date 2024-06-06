# flash_storage
Library for writting to EEPROM 24LC04B using I2C.

# how to use
Please import the library and make a Flash object.
```c++
Flash flash;
```

Use the write_to_address methode to write max 8 Bytes to EEPROM.
```c++
// Writing to address 0x01
flash.write_to_address(0x01, data);
```

Use the read_from_address methode to read max 8 Bytes from EEPROM
```c++
// Saving data from address 0x01 to data
flash.read_from_address(0x01, data);
```

# wiring diagram
| 24LC04B | RP2040 |
| :---:   | :---:  |
| A0      | -      |
| A1      | -      |
| A2      | -      |
| Vss     | GND    |
| SDA     | GP4    |
| SCL     | GP5    |
| WP      | GND    |
| Vcc     | 3v3    |
