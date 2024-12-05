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
    <li> Upload the code to your Aurdino </li>
  </li>
</ol>

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
Follow these steps to assemble the system components:
</p>

<ol>
  <li><strong>IR Sensors:</strong>
    <ul>
      <li>Position the two IR sensors at the entrance of the room.</li>
      <li>Senor 1 being the entrace connected to <code>pin 9</code> Sensor 2 being the exit connected to <code>pin 8</code> </li>
      <li>Ensure they are aligned correctly to detect motion effectively:
        <ul>
        </ul>
      </li>
      <li>Secure the sensors in place so they do not move or shift during use.</li>
    </ul>
  </li>
  <li><strong>LCD Display:</strong>
    <ul>
      <li>Connect the LCD to the Arduino's I2C pins:
        <ul>
          <li><strong>SDA:</strong> Connect to the Arduino's SDA pin.</li>
          <li><strong>SCL:</strong> Connect to the Arduino's SCL pin.</li>
        </ul>
      </li>
      <li>Secure the LCD where it can be easily viewed.</li>
    </ul>
  </li>
  <li><strong>Temperature Sensor:</strong>
    <ul>
      <li>Place the temperature sensor in the desired location to monitor room temperature.</li>
      <li>Connect the signal pin of the sensor to <code>A0</code> on the Arduino.</li>
    </ul>
  </li>
  <li><strong>Power and Ground:</strong>
    <ul>
      <li>Connect all components to a common ground pin on the Arduino.</li>
      <li>Power the system using a battery or a USB connection to the Arduino.</li>
    </ul>
  </li>
  <li><strong>Relay:</strong>
    <ul>
      <li>If using a relay, connect it to a designated pin on the Arduino for control.</li>
      <li>Connect the relay to the external device (e.g., lights or fans) as per the relay's specifications.</li>
    </ul>
  </li>
</ol>
<p>
Once all components are connected and secured, verify the wiring to ensure everything is in the correct place before powering on the Arduino.
</p>




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
