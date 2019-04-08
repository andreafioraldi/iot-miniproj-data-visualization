import os
import csv

o = open("merged.csv", "w")
o.write("time,lat,long,alt,acc_x,acc_y,acc_z\n")

#gpsidx,accidx,date,time,speed,kspeed,accSpeed,d_sec,accdist,sentime,azimuth,pitch,roll,light,gps_lat,gps_lon,alti,accuracy,acc_x,acc_y,acc_z,kacc_x,kacc_y,kacc_z,mag_x,mag_y,mag_z,gyro_x,gyro_y,gyro_z,user_name

for fn in os.listdir("csv"):
    with open("csv/"+fn) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            o.write(",".join([row["d_sec"], row["gps_lat"], row["gps_lon"], row["alti"], row["acc_x"], row["acc_y"], row["acc_z"]]) + "\n")

o.close()
