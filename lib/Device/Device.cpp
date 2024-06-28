#include "Device.h"

Device::Device()
{
    isRegistered = false;
};
void Device::setRegisteredStatus(bool status)
{
    isRegistered = status;
}
bool Device::getRegisteredStatus()
{
    return isRegistered;
}
