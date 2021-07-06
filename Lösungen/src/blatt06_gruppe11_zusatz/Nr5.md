# Aufgabe 6.5

### Teil A

Die Objekte müssten 2x vergrößert werden, sodass jedes Raster 20cm groß ist.

TODO: Soll Teil C auf der original Karte oder auf dieser neuen Karte berechnet werden?

### Teil C

- A: Dieser Pfad ist der kürzeste Pfad zwischen `S` und `Z`.
- B: Dieser Pfad ist die längste Route zwischen `S` und `Z` und muss ggf. abgeändert werden, wenn der Roboter größer als 10cm ist.
- C: Stellt eine längere Alternative zu Pfad A dar.
- D: Dieser Pfad macht keinen Sinn und sollte augrund der beiden Hindernisse nicht erlaubt sein, jedoch augrund der Moore-Nachbarschaft könnte dieser Pfad erreichnet werden. Modellierung: 1 -> 8, weil 8 keinen direkten Kontakt zu dem 1er Feld hat.

### Teil D

> [...] Erläutern Sie eine Möglichkeit, dieses Problem zu kompensieren, ohne bei jedes Mal komplett neu planen zu müssen.

- Robotor warten lassen
- lokal einen Umweg um das Objekt finden und auf die bisherige Route zurückkehren
- versuche das Objekt links bzw. rechts herum zu umfahren und kehre auf bisherige Route zurück

