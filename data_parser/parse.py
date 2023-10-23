from OSM_data_utils import StreetsHandler, WayLenHandler
import pandas as pd
import sqlite3

# h = StreetsHandler()
h = WayLenHandler()
# download from https://download.geofabrik.de/index.html
osm_file = f"/Users/wikraman/germany-latest.osm.pbf"

print("Starting handler")
h.apply_file(osm_file, locations=True, idx='flex_mem')
# show stats
# print(f"num_relations: {handler.num_relations}")
# print(f"num_ways: {handler.num_ways}")
# print(f"num_nodes: {handler.num_nodes}")
print("completed")

print("Creating dataframes")
# street_relations_df = pd.DataFrame(h.street_relations)
# street_relation_members_df = pd.DataFrame(h.street_relation_members)
street_ways_df = pd.DataFrame(h.street_ways, columns=['w_id', 'geo'])
print("completed")

# street_ways_df.to_csv("germany_street_ways_xy.csv")

connection = sqlite3.connect("OSM_data.db")
crsr = connection.cursor()
print("Connected to the database")
street_ways_df.to_sql(name='germany_ways', con=connection, if_exists='fail')
connection.commit()



