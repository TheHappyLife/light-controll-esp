#ifndef DEVICE_H
#define DEVICE_H

class Device
{
private:
    bool isRegistered;

public:
    Device();
    void setRegisteredStatus(bool status);
    bool getRegisteredStatus();
};

#endif