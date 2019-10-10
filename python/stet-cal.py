#!/usr/bin/env python
# stet-cal.py
# important reference http://icalendar.readthedocs.io/en/latest/usage.html

import os
import sys
from icalendar import Calendar, Event
from icalendar import vCalAddress, vText
from datetime import datetime
import re
import pytz
import hashlib

cal = Calendar()
cal.add('prodid', '-//The Horde Project//Horde iCalendar Library//DE')
cal.add('version', '2.0')
cal.add('X-WR-CALNAME', 'StET 2016')

def get_event_strings(lines):
    result_array = []    
    result = ""
    for i, line in enumerate(lines):
        if i % 7 == 0 and result:
            result_array += [result.strip().split("\n")]
            result = ""
        result += line
    return result_array

event_strings = []
with open(sys.argv[1]) as lines:
    event_strings = get_event_strings(lines)

#print(event_strings)

for event_string in event_strings:
    #print(event_string)
    event = Event()
    time_and_date = event_string[0] + ", " + event_string[1][len(event_string[1])-10:]
    if "-" not in time_and_date:
        #print(time_and_date)
        date = datetime.strptime(time_and_date, '%H:%M, %d.%m.%Y')
        #print(date)
    else:
        von = time_and_date[:5] + time_and_date[13:]
        bis = time_and_date[8:]    
        #print(von + " + " + bis)
        date_start = datetime.strptime(von, '%H:%M, %d.%m.%Y')
        date_end = datetime.strptime(bis, '%H:%M, %d.%m.%Y')
        event.add('dtstart', date_start)
        event.add('dtend', date_end)
        event.add('summary', event_string[2])
        event.add('dtstamp', datetime.now())
        event.add('location', event_string[3])
        hash_object = hashlib.sha1(time_and_date.encode())
        hex_dig = hash_object.hexdigest()
        event.add('uid', hex_dig)
    if 'dtstart' in event:
        cal.add_component(event)

f = open(os.path.join('.', 'example.ics'), 'wb')
f.write(cal.to_ical())
f.close()
