import serial
import sqlite3

con = sqlite3.connect("pop.db")
cur = con.cursor()
cur.execute("""
	CREATE TABLE IF NOT EXISTS tempii (
		id INTEGER PRIMARY KEY AUTOINCREMENT, 
		t TEXT
	)
	""")

with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as ser:
	x = ser.read()
	s = ser.read(10)
	while(True):
		line = ser.readline()
		print(line)
