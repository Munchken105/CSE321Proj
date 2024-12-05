<h1>Occupancy and Relay System</h1>
<p>
This is a C-based embedded system utilizing two IR sensors connected to an Arduino to determine the room occupancy. The system tracks the people entering and exiting the room by maintaining a count and displaying the data on an LCD. Temperature readings are also monitored using a temperature sensor.
</p>

<h2>How to Set Up the System</h2>

<h3>Hardware Requirements</h3>
<ul>
  <li>Arduino Uno</li>
  <li>Two IR sensors</li>
  <li>Relay</li>
  <li>Wires</li>
  <li>Battery/Power Source</li>
  <li>LCD</li>
  <li>Temperature sensor</li>
</ul>

<h3>Hardware Setup</h3>
<ul>
  <li><strong>IR Sensors:</strong>
    <ul>
      <li>Sensor 1 (Entrance): Connect it to pin 9</li>
      <li>Sensor 2 (Exit): Connect it to pin 8</li>
    </ul>
  </li>
  <li><strong>LCD Display:</strong> Connect the LCD to the Arduino's I2C pins (SDA and SCL)</li>
  <li><strong>Temperature Sensor:</strong> Connect it to analog pin A0</li>
  <li><strong>Power and Ground:</strong>
    <ul>
      <li>Ensure all components are connected to ground</li>
      <li>Power the Arduino and sensors</li>
    </ul>
  </li>
</ul>

<h3>Assembly</h3>
<p>
Position the two IR sensors and set them up on the door.<br>
Sensor 1 (connected to pin 9) is the entrance sensor, and Sensor 2 (connected to pin 8) is the exit sensor.
</p>

<h3>Software Setup</h3>
<ol>
  <li>Clone the repository to your machine.</li>
  <li>Open the <code>main.c</code> file in your editor.</li>
  <li>Open <code>main.c</code> in Arduino IDE and make sure you have the <code>LiquidCrystal_I2C</code> library installed.</li>
  <li>To install the library:
    <ul>
      <li>Go to <strong>Sketch > Include Library > Manage Libraries</strong>.</li>
      <li>Search for and install <code>LiquidCrystal_I2C</code>.</li>
    </ul>
  </li>
</ol>

<h3>How It Works</h3>
<ul>
  <li><strong>Occupancy Tracking:</strong>
    <ul>
      <li>Sensors detect entry (<code>pin 9</code>) and exit (<code>pin 8</code>) motions.</li>
      <li>A finite state machine updates the occupancy count based on the detected transitions.</li>
    </ul>
  </li>
  <li><strong>Temperature Monitoring:</strong>
    <ul>
      <li>Reads analog input from the temperature sensor.</li>
      <li>Displays temperature on the LCD.</li>
    </ul>
  </li>
  <li><strong>LCD Display:</strong>
    <ul>
      <li>Continuously updates with the current occupancy count and temperature.</li>
    </ul>
  </li>
</ul>


<h3>Schematics</h3>
<p>
Refer to the wiring diagram provided in the repository for detailed schematics.
</p>
