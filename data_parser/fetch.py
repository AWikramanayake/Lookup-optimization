import sqlite3
import pandas as pd

connection = sqlite3.connect("OSM_data.db")
crsr = connection.cursor()
print("Connected to the database")

lookup = "SELECT\n\tw_id\nFROM\n\tgermany_ways"
res = crsr.execute(lookup)
outlist = res.fetchall()
connection.close()

df = pd.DataFrame(outlist)
df.to_csv('way_id_list.csv', index=False)
