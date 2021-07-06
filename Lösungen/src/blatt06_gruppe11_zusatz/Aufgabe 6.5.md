# Aufgabe 6.5

## Teil A

Da der Roboter selbst einen Radius von 10 cm hat, muss jedes Objekt um 10 cm vegrößert werden (Auch bei den Rundungen geht es dann noch in diagonal freie Zellen (Abstand zu dieser Zelle ist 9.XXX)).

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt06_gruppe11_zusatz/Bilder/Teil_A.png)

## Teil B

Start und Ziel sind hier als Originalzelle dargestellt, sind aber intern ohne besondere Betrachtung dieser, gleich der umliegenden Zelle.

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt06_gruppe11_zusatz/Bilder/Teil_B.png)

## Teil C

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt06_gruppe11_zusatz/Bilder/Teil_C.png)

Pfad A und ´B sollten beide befahrbar sein. Die Objekte sind dafür um 10 cm angepasst worden, sodass der Roboter als Punkt betrachtet werden kann. Auch wenn Pfad A und B nach dem Wavefront Algorithmus den selben Funktionswert haben, ist A in der Realität kürzer.

## Teil D

Wenn dynamisch ein Objekt hinzugefügt wird ist es möglich eine Alternativroute zu berechnen ohne die komplett Tour neu zu berechnen. Eine Objekt stört den Pfad an einem frühsten Punkt $A$ der Tour und an einem spätesten Punkt $B$ der Tour.  Bis zum Punkt $A$ und ab dem Punkt $B$ ist die Tour also befahrbar. Es kann also einfach ein neuer kürzester weg zwischen $A$ und $B$ berechnet werden und zwischen $A$ und $B$ in die alte Route eingefügt werden.
