#include "device.h"

Device::Device(QObject *parent) : QObject(parent)
{
    port = new QSerialPort();

}

bool Device::FindDevise(const quint16 unoVendorId, const quint16 unoProductId){
    bool sucsesfull = false;
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
           if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
               if(serialPortInfo.vendorIdentifier() == unoVendorId
                       && serialPortInfo.productIdentifier() == unoProductId) {
                   port->setPortName(serialPortInfo.portName());
                   port->open(QSerialPort::ReadOnly);
                   if (port->isOpen()){
                       sucsesfull = true;
                   }
                   port->setBaudRate(QSerialPort::Baud9600);
                   port->setDataBits(QSerialPort::Data8);
                   port->setParity(QSerialPort::NoParity);
                   port->setStopBits(QSerialPort::OneStop);
                   port->setFlowControl(QSerialPort::NoFlowControl);
               }
         }
      }
    return sucsesfull;;
}

QSerialPort* Device::GetPort(){
    return port;
}
