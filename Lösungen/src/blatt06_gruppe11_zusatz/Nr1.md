# Aufgabe 6.1

### Teil A

> Beschreiben Sie die Idee der Monte-Carlo-Lokalisierung (MCL).

Bei der MCL wird die Position des Roboters über eine Partikelwolke repräsentiert, die eine gewisse Wahrscheinlichkeit pro Punkt speichert. Im Gegensatz zur Markow-Lokalisierung ist die Anzahl der Punke (Partikel) eingeschränkt. Diese Partikel werden nach und nach aktualisiert, sodass sich mit der Zeit Cluster bilden, indem der Robotor sich mit hoher Wahrscheinlichkeit befindet. Partikel mit geringer Wahrscheinlichkeit werden eliminiert. Die Position des Robotors wird entsprechend durch die Partikel mit der höhsten Gewichtung repräsentiert.

### Teil B

> Wozu dient dabei der Resampling-Schritt?

Der Resampling-Schritt (bspw. Roulette-Rad-Verfahren) dient der Normierung der Gewichte von Parkikeln. Positionen mit hoher Gewichtung werden zusätzliche Partikel zugeordnet, sodass sich Cluster bilden, indem der Robotor sich mit hoher Wahrscheinlichkeit befindet. Partikel mit geringer Wahrscheinlichkeit werden dadurch eliminiert.

### Teil C

> Sind nicht-uniforme Rasterkarten (beispielsweise eine Quadtree-Repräsentation) für die MCL sinnvoll verwendbar? Wenn ja, wie? Wenn nein, warum nicht?

???

Nein, weil für MCL eine 2D-Matrix benötigt wird, die die jeweiligen Partikel repräsentiert. Bspw. bei einem Quadtree würden die vier zusätzlichen Felder keine Verwendung finden.

### Teil D

> Ist die Zahl der Partikel konstant oder variabel? Begründen Sie Ihre Antwort.

Die Anzahl der Partikel sind aufgrund des Resampling-Schritts variabel. Partikel werden entsprechend ihrere Gewichtung vermehrt oder entfernt.

### Teil F

Siehe Grafik.
