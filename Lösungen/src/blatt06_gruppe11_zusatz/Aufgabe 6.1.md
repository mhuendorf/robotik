# Aufgabe 6.1

## Teil A

Mit MCL berechnet man die Pose nicht direkt genau sondern aproximiert sie über mehrere Messugungen hinweg.
Zuerst werden auf der Karte Partikel mit einem Initialen Gewicht verteilt. Danach wird eine Messung gemacht und die Partikel in der Karte bekommen neue Gewichte abhängig davon wie wahrscheinlich sie für die letzte Messung waren. Partikel mit geringer Gewichtung sterben über die Zeit aus und werden replaziert. Dadurch konvergiert die Partikelmenge auf die reale Roboterspose.

## Teil B

Beim Resampling werden zufällig entsprechend ihrer Gewichtung Partikel gezogen und ihnen abhängig von Messdaten und eigene Position eine neue zugewiesen. 

## Teil C

Eine nicht-uniforme Rasterkarte würde Probleme bei der Gewichtung der einzelnen Partikel bereiten da z.B in Quadtrees ihre Nachbarschaft jeweils weiter unterteilt ist. Man müsste zuerst jede Nachbarschaft auflösen umd die Partikel Sinnvoll gewichten zu können.


## Teil D

Die Zahl der Partikel kann konstant sein. In der Vorlesung wurden Partikelmengen mit einer größe von 1.000-10.000 Partikeln beschrieben.
Jedoch wenn man in größere Gebiete bekommt spricht nichts dagegen diese Zahl dynamisch an die Umgebung anzupassen.

## Teil E

MCL ist nicht direkt auf topologischen Karten einstezbar. Dort werden Posen durch einen Graph und ihre Nachbarschaft ausgezeichnet. Man könnte also für ein zufällig platziertes Partikel nicht direkt die Position bestimmen oder Partikel würden sich nur auf Knoten befinden was aber MCL wieder obsolet macht wenn der Roboter diese sowieso direkt erkennt.

