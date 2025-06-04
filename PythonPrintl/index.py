import serial
import sqlite3
import json
import time
import re

con = sqlite3.connect("pop.db")
cur = con.cursor()

cur.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='tempii'")
if not cur.fetchone():
    print("Таблица не существует, создаем новую...")
    cur.execute("""
        CREATE TABLE tempii (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            t REAL,
            name TEXT
        )
    """)
    con.commit()
    print("Таблица создана")
else:
    print("Таблица уже существует")

cur.execute("SELECT * FROM tempii")
record = cur.fetchall()
print(f"Всего строк {len(record)}")
for row in record:
	print(f"ID: {row[0]}")
	print(f"t: {row[1]}")
	print(f"Name: {row[2]}")

# Работа с последовательным портом
try:
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as ser:
        print("Подключение к последовательному порту...")
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8')
                try:
                    t = re.split(r"['':,\s]", line)
                    if len(t) > 0:
                        cur.execute("INSERT INTO tempii (t, name) VALUES (?, ?)", (t[4], t[10]))
                        con.commit()
                        print(f"Данные записаны в БД")
                    else:
                        print("Некорректный формат данных:", line)
                except json.JSONDecodeError:
                    print("Ошибка декодирования JSON:", line)
            time.sleep(0.1)
except serial.SerialException as e:
    print("Ошибка подключения к последовательному порту:", e)
except KeyboardInterrupt:
    print("Программа завершена!!!")
finally:
    con.close()
