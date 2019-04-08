#!/usr/bin/env python2

f = open("mean_std_data")

o = []

for line in f:
    line = map(float, line.split(","))
    v = line[2]
    mean = line[3]
    std = line[4]
    #print " >>", line
    if v < (mean + std*3) or v > (mean + std*3):
        if v < (mean + std*2) or v > (mean + std*2):
            if v < (mean - std) or v > (mean + std):
                #print v, mean, std
                print 1, line[0], line[1]
                o.append([1, line[0], line[1]])
            else:
                print 2, line[0], line[1]
                o.append([2, line[0], line[1]])
        else:
            print 3, line[0], line[1]
            o.append([3, line[0], line[1]])

import json
with open("anomalies.json","w") as f:
    json.dump(o, f)
