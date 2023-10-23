import osmium
import shapely.wkb as wkblib


# Class to fully extract the data from the pbf file (ways, relations)
class StreetsHandler(osmium.SimpleHandler):
    def __init__(self):
        osmium.SimpleHandler.__init__(self)
        self.num_nodes = 0
        self.num_relations = 0
        self.num_ways = 0
        self.street_relations = []
        self.street_relation_members = []
        self.street_ways = []
        # A global factory that creates WKB from a osmium geometry
        self.wkbfab = osmium.geom.WKBFactory()

    def way(self, w):
        if w.tags.get("highway") is not None and w.tags.get("name") is not None:
            try:
                wkb = self.wkbfab.create_linestring(w)
                geo = wkblib.loads(wkb, hex=True)
            except:
                return
            row = {"w_id": w.id, "geo": geo.xy}

            for key, value in w.tags:
                row[key] = value

            self.street_ways.append(row)
            self.num_ways += 1

    def relation(self, r):
        if r.tags.get("type") == "associatedStreet" and r.tags.get("name") is not None:
            row = {"r_id": r.id}
            for key, value in r.tags:
                row[key] = value
            self.street_relations.append(row)

            for member in r.members:
                self.street_relation_members.append({
                    "r_id": r.id,
                    "ref": member.ref,
                    "role": member.role,
                    "type": member.type, })
                self.num_relations += 1


# Simplified handler to extract way_id and geo data from pbf
class WayLenHandler(osmium.SimpleHandler):
    def __init__(self):
        osmium.SimpleHandler.__init__(self)
        self.total = 0
        self.num_ways = 0
        self.street_ways = []
        self.wkbfab = osmium.geom.WKBFactory()

    def way(self, w):
        self.wkb = self.wkbfab.create_linestring(w)
        geo = wkblib.loads(self.wkb, hex=True)

        row = { "w_id": w.id, "geo_xy": geo.xy }

#       for key, value in w.tags:
#           row[key] = value

        self.street_ways.append(row)
        self.num_ways += 1


