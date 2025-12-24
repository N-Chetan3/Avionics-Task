# Avionics-Task

1) Introduction to Fin Control
   
i) Motor Position Control with reset

Link to tinkercad : https://www.tinkercad.com/things/2mh5t4mPnVO-fin-control-reset?sharecode=undefined

ii) Motor Position Control without reset

Link to tinkercad : https://www.tinkercad.com/things/5yNexolpspz-fin-control-no-reset?sharecode=undefined


## Pin Connections

### Arduino UNO → L293D Motor Driver
- D5  → L293D Input 2 
- D6  → L293D Input 1
- D9  → Enable Pin (EN 1 & 2)

### Motor
- Motor terminal 1 → L293D OUT1
- Motor terminal 2 → L293D OUT2

### Potentiometer
- One end → 5V
- Other end → GND
- Middle pin → A0

### Encoder
- Channel A → D2
- Channel B → D3
- VCC → 5V
- GND → GND

### Power
- Arduino 5V → L293D VCC1
- Arduino GND → Common Ground
