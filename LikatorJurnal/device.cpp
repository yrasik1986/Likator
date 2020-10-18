#include "device.h"

Device::Device(QObject *parent)
    : QObject(parent)
    , _port (new QSerialPort(this))
{

}

bool Device::FindDevise(const quint16 unoVendorId, const quint16 unoProductId){
    bool sucsesfull = false;
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
           if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
               if(serialPortInfo.vendorIdentifier() == unoVendorId
                       && serialPortInfo.productIdentifier() == unoProductId) {
                   _port->setPortName(serialPortInfo.portName());
                   _port->open(QSerialPort::ReadOnly);
                   if (_port->isOpen()){
                       sucsesfull = true;
                   }
                   _port->setBaudRate(QSerialPort::Baud9600);
                   _port->setDataBits(QSerialPort::Data8);
                   _port->setParity(QSerialPort::NoParity);
                   _port->setStopBits(QSerialPort::OneStop);
                   _port->setFlowControl(QSerialPort::NoFlowControl);
               }
         }
      }
    return sucsesfull;
}

QSerialPort* Device::GetPort(){
    return _port;
}
