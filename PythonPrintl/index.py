import serial
import sqlite3
import json
import time

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

# Работа с последовательным портом
try:
    with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as ser:
        print("Подключение к последовательному порту...")
        while True:
            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8').strip()
                try:
                    data = json.loads(line)
                    if isinstance(data, dict) and 't' in data and 'id' in data:
                        cur.execute("INSERT INTO tempii (t, name) VALUES (?, ?)", (data['t'], data['id']))
                        con.commit()
                        print(f"Данные записаны в БД: t={data['t']}, name={data['id']}")
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