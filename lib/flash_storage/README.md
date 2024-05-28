# flash_storage
Library for writting to EEPROM 24LC04B using I2C.

# how to use
Please import the library and make a Flash object.
```
Flash flash;
```

Use the write_to_address methode to write max 8 Bytes to EEPROM.
```
// Writing to address 0x01
flash.write_to_address(0x01, data);
```

Use the read_from_address methode to read max 8 Bytes from EEPROM
```
// Saving data from address 0x01 to data
flash.read_from_address(0x01, data);
```

# wiring diagram
| 24LC04B | RP2040 | 3V battry |
| :---:   | :---:  | :---:     |
| Vcc     | -      | Vcc       |
| Vss     | -      | GND       |
| SDA     | GP4    | -         |
| SCL     | GP5    | -         |
| WP      | GND    | -         |
