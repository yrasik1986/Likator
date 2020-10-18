#ifndef COMPORT_H
#define COMPORT_H
#pragma once
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    bool FindDevise(const quint16 unoVendorId, const quint16 unoProductId);
    QSerialPort* GetPort();

signals:
private:
    QSerialPort *_port;

};

#endif // COMPORT_H
