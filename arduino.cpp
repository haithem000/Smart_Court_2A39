#include "arduino.h"
#include <QDebug>
arduino::arduino()

{
data="";
arduino_is_available =false;
Serial=new QSerialPort;
}
QString arduino::getarduino_port_name()
{
  return  arduino_port_name ;
}
int arduino::connect_arduino()
{
    foreach(const QSerialPortInfo& serial_port_info,QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {

          if(serial_port_info.vendorIdentifier() ==arduino_uno_vendor_id && serial_port_info.productIdentifier()==arduino_uno_vendor_id)

           {

            arduino_is_available=true;
            arduino_port_name =serial_port_info.portName();
          }
        }

    }
    qDebug()<<"arduino port name:"<<arduino_port_name;
    if( arduino_is_available)
    {
         Serial->setPortName( arduino_port_name);
       if(Serial->open(QSerialPort::ReadWrite))
       {
           Serial->setBaudRate(QSerialPort::Baud9600);
           Serial->setDataBits(QSerialPort::Data8);
           Serial->setParity(QSerialPort::NoParity);
           Serial->setStopBits(QSerialPort::OneStop);
           Serial->setFlowControl(QSerialPort::NoFlowControl);
           return 0;

       }
return 1;
    }
    return -1;
}
int arduino::close_arduino()
{
    if(Serial->isOpen())
    {
        Serial->close();
        return 0;
    }

    return 1;
}
int arduino ::write_to_arduino(QByteArray x)
{
   if(Serial->isWritable())
   {
       Serial->write(x);

   }
   else
       qDebug()<<"error en ecriture";

}
QByteArray arduino::read_from_arduino()
{

    data=Serial->readAll();
    return data ;
}
QSerialPort* arduino::getserial(){return  Serial;}

