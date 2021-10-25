import serial
import time
import string
import paho.mqtt.publish as publish


# reading and writing data from and to arduino serially.
# rfcomm0 -> this could be different
ser_t1 = serial.Serial("/dev/rfcomm0", 9600)
ser_t2 = serial.Serial("/dev/rfcomm1", 9600)
ser_t1.write(str.encode('Start\r\n'))
ser_t2.write(str.encode('Start\r\n'))

while True:
 if ser_t1.in_waiting > 0:
    rawserial = ser_t1.readline()   
    cookedserial = rawserial.decode('utf-8').strip('\r\n')
    split_string = cookedserial.split(" ");
    output_1 = split_string[0]
    output_2 = split_string[1]
    output_3 = split_string[2]
    msg1=output_1+" "+output_2
    print(msg1)
    msgs=[{'topic':"Notification: ",'payload':msg1},]
    publish.multiple(msgs,hostname="localhost")
    
 if ser_t2.in_waiting>0:
    rawserial2 = ser_t2.readline()   
    cookedserial2 = rawserial2.decode('utf-8').strip('\r\n')
    split_string2 = cookedserial2.split(" ");
    output_4 = split_string2[0]
    output_5 = split_string2[1]
    output_6 = split_string2[2]
    msg2=output_4+" "+output_5
    print(msg2)
    
    msgs1=[{'topic':"Notification: ",'payload':msg2},]
    publish.multiple(msgs1,hostname="localhost")
    
    
    
    if int(output_6) ==2:
        ser_t1.write(b"Grandpa In\n")
    if int(output_6)==3:
        ser_t1.write(b"Admin In\n")
        ser_t2.write(b"Admin In\n")
