# Aufgabe 5.5

In der Praxis werden häufig sogenannte Rasterkarten verwendet, um die Umgebung des Roboters zu representieren. Ein solche Karte wird in ROS mit der Message nav_msgs/OccupancyGrid dargestellt.

---

> (a) Machen Sie sich mit dieser Message vertraut. Welche Werte representieren belegte, freie oder unbekannte Zellen? Angenommen Sie möchten einen Punkt einer Punktwolke in dieser Karte vermerken. Wie können Sie die passende Zelle zu diesem Punkt finden?

Die Wahrscheinlichkeit , mit der eine Zelle belegt ist wird mit einem Wert von 0-100 angegeben. 100 bedeutet, dass die Zelle eindeutig belegt ist und 0 bedeutet, dass sie definitiv frei ist. Ist die Wahrscheinlichkeit, ob eine Zelle belegt ist nicht bekannt kann dies mit dem Wert -1 dargestellt werden.

---

> (b)  In ROS gibt es die Node map_server (http://wiki.ros.org/map_server), welche eine solche Karte von der Festplatte liest und sie in das ROS-System publisht. Eine Rasterkarte - passend zur AVZ-Gazebo-Simulation - befindet sich im Paket ceres_navigation unter maps/avz_6_floor_gazebo. Schreiben Sie eine Launch-File, die eine map_server-Node startet und diese Karte ins ROS-System
> lädt. Visualisieren Sie sich danach die Karte mit RViz.

- Code siehe `blatt05_gruppe11/src/launch/launch.launch`

- Visuaslisierung:
  
  ![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/map_server_viz.png)

---

> (c)  Warum haben sich solche Rasterkarten in der mobilen Robotik bewährt?

- Rastergröße, also die Größe der einzelnen Zellen kann je nach Anwendung passend groß gewählt werden

- Effiziente Speicherung möglich (z.B. Octree)

- Risikoabschätzung durch Wahrscheinlichkeiten möglich (ein Feld muss nicht besetzt oder frei sein, sondern kann auch dazwischen liegen)

---

> (d)  Welche Aufgaben/Probleme können mithilfe einer solchen Karte gelöst werden? Nennen Sie zwei Beispiele.

1. Roboternavigation/Wegplanung

2. Lokalisierung des Roboters

> (e)  Nennen Sie ein konkretes Anwendungsbeispiel aus der Robotik, in dem statt solcher Rasterkarten alternative Kartendarstellungen verwendet werden. Geben Sie zu diesem Beispiel auch die alternative Kartenform an.

In vielen Anwendungsfeldern, wie in Fabrik- oder Lagerhallen stehen CAD-Darstellungen zur Verfügung. Hier sind geometrische Modelle eine gute Wahl. Es können zum Beispiel eine Objektbasierte Karte verwendet werden.
