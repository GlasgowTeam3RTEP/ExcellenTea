#include <iostream>
#include <fstream>
#include <sstream>
#include <wiringPi.h>
#include <cstdlib>

#include "Sensor.h"
#include "DS18B20.h"

DS18B20::DS18B20(short GPIO, std::string dev_id) : Sensor(GPIO)
{
	pin = GPIO;
	device_id = dev_id;
}

void DS18B20::initialise()
{
	std::system("sudo modprobe w1-gpio"); //Activate one-wire interface 
	std::system("sudo modprobe w1-therm"); //^^	
}

double DS18B20::readTemp()
{
	//Reads temperature data from sensor DS18B20 and displays it in console
	//One-wire bus on PIN 7 of the R-Pi
	std::ifstream w1_file;
	std::string raw;
	int temp;

	//Opens file and checks success of operation
	w1_file.open("/sys/bus/w1/devices/" + device_id + "/w1_slave");
	if (!w1_file)
	{
		std::cerr << "Unable to open file!\n";
		return 1;
	}

	//Content of the file is as follows when the sensor is connected:
	//0d 01 4b 46 7f ff 0c 10 89 : crc=89 YES
	//0d 01 4b 46 7f ff 0c 10 89 t=16812

	while (w1_file >> raw)
	{
		//Exit if the sensor is not connected
		if (raw == "NO")
		{
			std::cerr << "Sensor disconnected!!\n";
			return 1;
		}
	}
	w1_file.close();

	//remove "t=" from raw string
	raw = raw.substr(2);

	//cast to integer
	std::stringstream str(raw);
	str>>temp;

	return temp / 1000.0;
}