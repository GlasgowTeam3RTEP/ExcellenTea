/**A general class for simple HIGH/LOW sensors.
 *
 *  @version Excellentea 1.0
 *
 *  @author Simone Marcigaglia
 */
#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
    /** Class constructor 
    @param GPIO Raspberry pi pin connected to the sensor.
     */
    Sensor(short GPIO);

    /** Initialisation procedure with wiringPi library */
    virtual void initialise();

    /**Reads boolean status of the sensor*/
    bool readStatus();
protected:
    short pin; //< Raspberry GPIO connected to sensor (wiringPi convention)
};

#endif