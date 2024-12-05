<h1>Occupancy and Relay System</h1>
 
<h2>How to Set Up the System</h2>
<h3>Hardware Requirements</h3>
Aurdino Uno
Two IR sensors
Relay
Wires
Battery/Power Source
LCD()
Temperature sensor

<h3>Hardware Setup</h3>
IR Sensors:<br>
 Sensor 1 (Entrace): Connect it to pin 9 <br>
 Sensor 2 (Exit): Connect it to pin 8 <br>
LCD Display:<br>
 Connect the LCD to the Arduino's I2c pins (SDA and SCL)<br>
Temperature Sensor:<br>
 Connect it to analog pin A0<br>
Power and Ground:<br>
 Ensure all compnents are connected to ground<br>
 Power the Arduino and Sensors<br>

 

<h3>Assembly</h3>
Position the two IR sensors and set them up on the door
Sensor 1(connected to pin 9) being Entrace and Sensor 2 (connected to pin 8) being the exit


<h3>Software Setup</h3>
Clone the repository to your machine 
Open the main.c file in your editor
Open main.c in Aurdino Ide and make sure you have the LiquidCrystal_I2C library installed.
(it can be installed by: Go to Sketch > Include Library > Manage Libraries and search and install for LiquidCrystal_I2C )

<h3>Schematics</h3>

