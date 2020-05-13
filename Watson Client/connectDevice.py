
import time
import datetime
import sys
import platform
import json
import signal
import wiotp.sdk.device
#from uuid import getnode as get_mac


def interruptHandler(signal, frame):
    client.disconnect()
    sys.exit(0)


if __name__ == "__main__":
    signal.signal(signal.SIGINT, interruptHandler)

    # Seconds to sleep between readings
    interval = 6

    # Setup connection options
    client = None
    try:
        myConfig = {
            "identity": {"orgId": "w4s1it", "typeId": "RPi3", "deviceId": "iSMT"},
    	    "auth": {"token": "A)cDV(swojLqA66T9s"},
    	    "options": {
        		#"domain": "internetofthings.ibmcloud.com",
        		#"logLevel": "error|warning|info|debug",
        		#"mqtt": {
            		#"port": 8883,
            		#"transport": "tcp|websockets",
            		#"cleanStart": True|False,
            		#"sessionExpiry": 3600,
            		#"keepAlive": 60,
            		#"caFile": "/path/to/certificateAuthorityFile.pem"
        		}
    		}

        client = wiotp.sdk.device.DeviceClient(myConfig)
        client.connect()
    except Exception as e:
        print(str(e))
        sys.exit(1)

    print("(Press Ctrl+C to disconnect)")

    # Loop

    while True:
        time.sleep(interval)
        ts = time.time()
        st = datetime.datetime.fromtimestamp(ts).strftime('%Y-%m-%d %H:%M:%S')

        # Read temp and humidity from file
        try:
            # ambient humidity
            f = open("ambientHumidity.txt", "r")
            ambientHumidity = float(f.read(6))
            
            # ambient temperature
            f = open("ambientTemp.txt", "r")
            ambientTemp = float(f.read(6))
            
            # duct humidity
            f = open("ductHumidity.txt", "r")
            ductHumidity = float(f.read(6))
            
            # duct temperature
            f = open("ductTemp.txt", "r")
            ductTemp = float(f.read(6))
            
            # simulated temperature
            f = open("simulated.txt", 'r')
            simTemp = float(f.read(6))
            
        except Exception as e:
            print(str(e))
            #sys.exit(1)
        
        # Send data here
        
        # ambient humidity
        myData={'time' : st, 'humidity' : ambientHumidity, 'id' : "ambientHumidity"}
        client.publishEvent("ambientHumidity", "json", myData)
        
        # ambient temperature
        myData={'time' : st, 'temp' : ambientTemp, 'id' : "ambientTemp"}
        client.publishEvent("ambientTemp", "json", myData)
        
        # duct humidity
        myData={'time' : st, 'humidity' : ductHumidity, 'id' : "ductHumidity"}
        client.publishEvent("ductHumidity", "json", myData)
        
        # duct temperature
        myData={'time' : st, 'temp' : ductTemp, 'id' : "ductTemp"}
        client.publishEvent("ductTemp", "json", myData)
        
        # simulated temperature
        myData={'time' : st, 'temp' : simTemp, 'id' : "simTemp"}
        client.publishEvent("simTemp", "json", myData)
        
