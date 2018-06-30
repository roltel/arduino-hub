/*
  Teleduino328EthernetClientProxy.ino - Teleduino328EthernetClientProxy example
  Version 328-0.6.9
  Nathan Kennedy 2009 - 2014
  http://www.teleduino.org

  This sketch is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <EEPROM.h>
#include <Servo.h>
#include <Wire.h>
#include <Teleduino328.h>

#include <SPI.h>
#include <Ethernet.h>

// User configurable variables
byte useDhcp = true;
byte useDns = true;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress deviceIp(192, 168, 1, 100); // Only if useDhcp is false
IPAddress gatewayIp(192, 168, 1, 1); // Only if useDhcp is false
IPAddress dnsIp(192, 168, 1, 1); // Only if useDhcp is false
IPAddress subnet(255, 255, 255, 0); // Only if useDhcp is false
IPAddress serverIp(173, 230, 152, 173); // Only if useDns is false
char serverName[] = "us01.proxy.teleduino.org"; // Only if useDns is true
unsigned int serverPort = 5353; // Can be set to either 53 or 5353
byte statusLedPin = 3;

// User configurable key, this is used to authenticate with the proxy server
// This is checked against the EEPROM on boot and written if necessary
// The proxy server retreives the key from the EEPROM
byte key[] = { 0xB7, 0xEA, 0x94, 0x69,
               0xBC, 0x5B, 0xCD, 0x63,
               0xC1, 0xC3, 0xD9, 0xD6,
               0x15, 0x5A, 0x7B, 0x6E };

// Other required variables
byte data[257];
byte dataLength;
byte hexStage;
unsigned long lastInstruction = 0;
unsigned long lastRefresh = 0;
byte stage = 0;

// Declare client object
EthernetClient Client;

void setup()
{
  // Load presets
  Teleduino328.loadPresets();
  
  // Set status LED pin
  Teleduino328.setStatusLedPin(statusLedPin);

  Teleduino328.setStatusLed(1); // Initialisation
  // Check the EEPROM header and check to see if the key is correct
  // This is to ensure the key is not cleared from the EEPROM
  if(EEPROM.read(0) != '#')
  {
    EEPROM.write(0, '#');
  }
  if(EEPROM.read(1) != 0)
  {
    EEPROM.write(1, 0);
  }
  if(EEPROM.read(2) != '#')
  {
    EEPROM.write(2, '#');
  }
  if(EEPROM.read(160) != '#')
  {
    EEPROM.write(160, '#');
  }
  for(byte i = 0; i < 16; i++)
  {
    if(EEPROM.read(161 + i) != key[i])
    {
      EEPROM.write(161 + i, key[i]);
    }
  }
  if(EEPROM.read(177) != '#')
  {
    EEPROM.write(177, '#');
  }

  // Start network and attempt to connect to proxy server
  Teleduino328.setStatusLed(2); // Network configuration
  if(useDhcp)
  {
    if(!Ethernet.begin(mac))
    {
      Teleduino328.setStatusLed(2, false, 10000);
      Teleduino328.reset();
    }
  }
  else
  {
    Ethernet.begin(mac, deviceIp, dnsIp, gatewayIp, subnet);
  }
  delay(1000);

  Teleduino328.setStatusLed(3); // Connect to server
  if((useDns && !Client.connect(serverName, serverPort)) || (!useDns && !Client.connect(serverIp, serverPort)))
  {
    Teleduino328.setStatusLed(3, false, 10000);
    Teleduino328.reset();
  }
  lastInstruction = millis();
}

void loop()
{
  if(Client.connected())
  {
    // What we need to do depends on which 'stage' we are at
    switch(stage)
    {
      case 0: // Wait for start byte
        if(Client.available())
        {
          char c = Client.read();
          if(c == '?')
          {
            stage++;
          }
        }
        break;
      case 1: // Reset variables
        dataLength = 0;
        hexStage = 0;
        stage++;
        break;
      case 2: // Instruction byte
        if(Client.available())
        {
          char c = Client.read();
          if(c == '?')
          {
            stage = 1;
            break;
          }
          else if(c == '\r' || c == '\n' || c == '.')
          {
            stage = 0;
            break;
          }
          if(!hexStage)
          {
            data[0] = Teleduino328.hexDecode(c) * 16;
          }
          else
          {
            data[0] += Teleduino328.hexDecode(c);
          }
          hexStage = !hexStage;
          if(!hexStage)
          {
            stage++;
          }
        }
        break;
      case 3: // Data length byte
        if(Client.available())
        {
          char c = Client.read();
          if(c == '?')
          {
            stage = 1;
            break;
          }
          else if(c == '\r' || c == '\n' || c == '.')
          {
            stage = 0;
            break;
          }
          if(!hexStage)
          {
            data[1] = Teleduino328.hexDecode(c) * 16;
          }
          else
          {
            data[1] += Teleduino328.hexDecode(c);
          }
          hexStage = !hexStage;
          if(!hexStage)
          {
            stage++;
          }
        }
        break;
      case 4: // Data
        if(Client.available())
        {
          char c = Client.read();
          if(c == '?')
          {
            stage = 1;
            break;
          }
          else if(c == '\r' || c == '\n' || c == '.')
          {
            if(dataLength == data[1])
            {
              stage++;
              break;
            }
            else
            {
              stage = 0;
              break;
            }
          }
          if(!hexStage)
          {
            data[2 + dataLength] = Teleduino328.hexDecode(c) * 16;
          }
          else
          {
            data[2 + dataLength] += Teleduino328.hexDecode(c);
          }
          hexStage = !hexStage;
          if(!hexStage)
          {
            dataLength++;
          }
        }
        break;
      case 5: // Execute instruction and return result
        Teleduino328.instruction(data);
        Client.write('!');
        for(int i = 0; i < data[1] + 2; i++)
        {
          Client.write(Teleduino328.hexEncode(data[i] / 16));
          Client.write(Teleduino328.hexEncode(data[i] % 16));
        }
        Client.write('\n');
        lastInstruction = millis();
        stage = 0;
        break;
    }
  }
  else
  {
    Teleduino328.setStatusLed(10);
    Teleduino328.reset();
  }

  // Has the instruction timeout been reached?
  if(millis() - lastInstruction > 30000)
  {
    Client.flush();
    Client.stop();
    Teleduino328.setStatusLed(9);
    Teleduino328.reset();
  }

  // Process refreshes every 50ms
  if(millis() - lastRefresh >= 50)
  {
    Teleduino328.pinTimers();
    Teleduino328.shiftRegisterTimers();
    Teleduino328.shiftRegisters();
    lastRefresh = millis();
  }

  // Check to see if reset has been requested
  Teleduino328.checkReset();
}
