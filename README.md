# Veluta monitor

Since 2004, the Asian hornet has invaded Europe, first appearing in France and now spreading further north and east.
This invasive species poses significant threats as a single nest can consume 11.2 kg of insects in a season, with a diet consisting of 38% honeybees, 30% flies, and 20% social wasps, among other insects. 
Asian hornets have larger nests compared to native European hornets, are more aggressive, and can produce 50 to 700 new queens annually, leading to rapid population growth. 
This impacts fruit farming, beekeeping, and biodiversity, prompting the EU to mandate control measures against this species.

Currently, Asian hornets are established in the southern provinces of the Netherlands, with nests discovered in various locations, including Meppel, Apeldoorn, and Friesland. 
Detection efforts involve both professionals and volunteers. Volunteers use bait traps to capture and mark the hornets, then track their flight direction and timing to estimate nest locations—a time-consuming and frustrating process.
Professionals, on the other hand, attach transmitters to captured hornets to trace them back to their nests, but this method is costly and not always successful.

To improve this process, the goal of this project is developing the Veluta monitor in collaboration with Nicola from Switzerland and Marijn from Zwolle. 
This device detects and captures Asian hornets and aims to automatically mark them, determine flight direction, and time their return to pinpoint nest locations. 
By enabling communication between multiple monitors, we can achieve automatic triangulation of nest sites. 
This innovation will save time and allow professionals to focus on nest removal rather than detection.
Within this project we will focus on the communication process and the locating part of the hornet nest. 


## In this project
* **Trilaterate GPS coordinates**
* **LoRaWan Communication**
* **Flash storage**
* **Raspberry pi Pico**
* **Converting _vespa velutina_ flying time to to distance**
* **C/C++**

---

### Made for KBS IOT Windesheim (2024). Finalized as of 16-6-2024. 
**[Winning project for Winnovation green award!](https://liveadminwindesheim.sharepoint.com/sites/Nieuws/SitePages/Sam,-Matz,-Jay-en-Jens-winnen-de-Green-Award-tijdens-Winnovation-2024!.aspx)**
**Watch a demonstration [here](https://www.youtube.com/watch?v=ZwA5_NCvS_0)**

**Made By**
* **[Jay](https://github.com/jkl46)**
* **[Matz](https://github.com/MatzLeeflang)**
* **[Jens](https://github.com/jenshobo)**
* **[Sam](https://github.com/SamNiehuis)**

# Installation
### Compiling & development
* **PlatformIO**
* **[Wiz-io board manager](https://github.com/Wiz-IO/platform-wizio)**

**Clone this repository. Compile and upload with platformIO**

### hardware
_**3 modules with:**_
* **Raspberry pi pico**
* **LoRa (RFM95)**
* **GPS (atgm33gh)**
* **3x pushButton**

### Wiring

| ATGM336H(GPS)  | Rasberri Pi Pico  |
| ----------- | ----------- |
| TX | GP5 |
| RX | GP4 | 
| VCC | VCC |
| GND | GND |

| LoRa-E5 mini | Rasberri Pi Pico  |
| ----------- | ----------- |
| TX | GP0 |
| RX | GP1 | 
| | **RFM95 (lora)** |
| VCC | VCC |
| GND | GND |

| LoRa(RFM95) | Rasberri Pi Pico  |
| ----------- | ----------- |
| VCC | 3.3v |
| GND | GND | 
| SCK | GPIO18 |
| MOSI | GPIO19 |
| MISO | GPIO16 |
| DIO0 | GPIO7 |
| NSS | GPIO8 |
| RESET | GPIO9 |
| DIO1 | GPIO10 |

###### BUTTONS (connect with pushbutton)
| Raspberry pi pico | Rasberri Pi Pico  |
| ----------- | ----------- |
| GPIO11  | GND |
| GPIO14  | GND |
| GPIO15  | GND |

---
### Overwriting coordinates used by monitors
**Required**
* Python 3+
* Google earth pro

Use python script in util/trilaterateMarkers/main.py. Export google earth markers as kml. Set filename input in main\.py and run. Place the output switch case in the beginning of void handle_hornet_data(lora_data* data). 
