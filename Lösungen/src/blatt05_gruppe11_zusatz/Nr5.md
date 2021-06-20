# Aufgabe 5

### Teil A

> Machen Sie sich mit dieser Message (`nav_msgs/OccupancyGrid`) vertraut. Welche Werte representieren belegte, freie oder unbekannte Zellen? Angenommen Sie möchten einen Punkt einer Punktwolke in dieser Karte vermerken.

```
# This represents a 2-D grid map, in which each cell represents the probability of
# occupancy.

Header header 

#MetaData for the map
MapMetaData info

# The map data, in row-major order, starting with (0,0).  Occupancy
# probabilities are in the range [0,100].  Unknown is -1.
int8[] data
```

mit `MapMetaData`:

```
# This hold basic information about the characterists of the OccupancyGrid

# The time at which the map was loaded
time map_load_time
# The map resolution [m/cell]
float32 resolution
# Map width [cells]
uint32 width
# Map height [cells]
uint32 height
# The origin of the map [m, m, rad].  This is the real-world pose of the
# cell (0,0) in the map.
geometry_msgs/Pose origin
```

> Welche Werte representieren belegte, freie oder unbekannte Zellen?

- `1-100`: belegt
- `0`: frei
- `-1`: unbekannt

> Wie können Sie die passende Zelle zu diesem Punkt finden?

```
cellX = pose.x / info.resolution
cellY = pose.y / info.resolution
```

Dabei muss ggf. eine TF2-Transformation vorher ausgeführt werden, um in ein anderes Koordinatensystem zu transformieren.

### Teil D

> Warum haben sich solche Rasterkarten in der mobilen Robotik bewährt?

Vorteile:

- speicherbar als 2D-(Byte-)Array mit Werten von 0-255 (bspw. für den Wahrscheinlichkeitswert)
- einfache Anwendung für Algorithmen auf dem Array
- Cache optimal, insb. Nachbarfelder finden etc
- Verwendung von Quadtrees möglich
- bieten die Möglichkeit, Unsicherheiten in Sensorwerten sowie transiente Informationen zu repräsentieren

> Welche Aufgaben/Probleme können mithilfe einer solchen Karte gelöst werden? Nennen Sie zwei Beispiele.

- Lokalisierung/Pfadplanung eines Fahrzeuges innerhalb einer gegebenen Karte
- Berechnung der Trajektorie bei gegebener Karte

### Teil E

> Nennen Sie ein konkretes Anwendungsbeispiel aus der Robotik, in dem statt solcher Rasterkarten alternative Kartendarstellungen verwendet werden. Geben Sie zu diesem Beispiel auch die alternative Kartenform an.

Merkmalskarten, um bspw. Objekte zu erkennen, die sich innerhalb der Karte befinden, und zur Repräsentation vom 3D-Raum.
