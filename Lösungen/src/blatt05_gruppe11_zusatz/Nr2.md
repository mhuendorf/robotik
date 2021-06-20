# Aufgabe 5.2

### Teil A

> Was für Voraussetzungen müssen gegeben sein, damit man beim iterativen Scanmatching mit den durch diese Regeln ermittelten Korrespondenzen sinnvolle Ergebnisse erzielen kann?

Die initiale Position des Robotors muss bekannt sein und die weiteren Schätzungen der Positionsveränderungen müssen möglichst genau sein.

### Teil B

> In den Vorlesungsfolien steht, dass der ICP-Algorithmus [...]

In langen Bürofluren, die einen sehr ähnlichen Aufbau besitzen ist eine lokale Positionsbestimmung sehr gut möglich, aber die globale Position kann aufgrund der redundanten Merkmale des Flurs falsch sein.

> Wo könnte der Ansatz von ICP fehlschlagen

Wenn es mehrere Objekte/Merkmale gibt, die gleich bzw. sehr ähnlich aussehen.

### Teil C

> Fallen Ihnen alternative Ansätze ein, mit denen man die Korrespondenzen zwischen Datenpunkten und Modellpunkten bestimmen könnte?

- Merkmalsbasierte Lokalisierung (bspw. PCA oder SIFT)
- Lokalisierung an Linien

### Teil D

> Welche der Ihnen bekannten Filterverfahren bietet sich grundsätzlich vor dem eigentlichen Scanmatching an?

- Medianfilter
- Reduktionsfilter

Diese Filter reduzieren die Anzahl an Messwerten und somit den Aufwand bei der anschließenden Verarbeitung dieser.
