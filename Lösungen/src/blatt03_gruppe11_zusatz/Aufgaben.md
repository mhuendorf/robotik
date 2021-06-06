# Blatt 03

### Nr 1

### Teil A

**Horizontale Erkennung:**

| -1  | -1  | -1  |
| --- | --- | --- |
| 2   | 2   | 2   |
| -1  | -1  | -1  |

**Vertikale Erkennung:**

| -1  | 2   | -1  |
| --- | --- | --- |
| -1  | 2   | -1  |
| -1  | 2   | -1  |

### Teil B

**Horizontale Erkennung:**

```
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,255,255,255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,255,255,255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
```

**Vertikale Erkennung:**

```
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  255,0,  0,  255,0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
```

### Teil C

> Geben Sie einen passenden Kernel der Größe 5×5 für eine Gauss-Filterung an.

| 1   | 4   | 7   | 4   | 1   |
| --- | --- | --- | --- | --- |
| 4   | 16  | 26  | 16  | 4   |
| 7   | 26  | 41  | 26  | 7   |
| 4   | 16  | 26  | 16  | 4   |
| 1   | 4   | 7   | 4   | 1   |

> [...] Wie würde sich sich ein Kernel mit steigendem Sigma auf das Bild auswirken?

Das Bild würde immer mehr weichgezeichnet und entsprechend verschwommen. Die Farbwerte von benachtbarten Pixeln würden sich immer weiter annähern.

### Teil D

```
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
```

### Teil E

> Aus welchem Grund wird ein solcher Gauß-Filter [...] oft als erster Schritt in einer Pipline von weiteren Filtern verwendet?

Ein Gauß-Filter wird zum Weichzeichnen, also zu Glätung der unterschiedlichen Pixelwerte, verwendet. Mit der entsprechenden Konfiguration des Filters kann Bildrauschen eliminiert/vermindert werden, sodass bpsw. die verschiedenen Strukturen des Bildes miteinander verschmelzen.

### Teil F

> Wie würden Sie vorgehen, wenn Sie einen Filter nicht auf ein Graustufenbild mit 1 Kanal sondern auf auf 3 Kanal (RGB) Farbbild anwenden möchten?

Die Farbwerte (RGB) werden entsprechend ihrere Intensität in Grauwerte umgerechnet. Andernfalls könnten die jeweiligen Schritte, die für die Grauwerte durchlaufen werden, für jeden Farbwert (R, G und B) einzeln durchlaufen werden ($\rightarrow$ 3x Matrizen). Anschließend wird ein einzelner RGB-Wert aus den Matrizen ermittelt.





### Nr 3

#### Teil A

> Welche Pixel werden als Keypoints ausgewählt

1. verwende das Difference of Gaussian-Verfahren (DoG) und klassifiziere lokale Extrema als Keypoint-Kanidaten
2. berechne mehrere DoG-Ebenen mit unterschiedlicher Varianz
3. suche nach Extrema und betrachte diese Stellen in den anderen Ebenen
4. verwende Taylorreihen-Expansion, um den Fehler der Skalisierung zu beheben und die Position im Bild zu korrigieren
5. filtere Kandidaten auf Kanten analog zu Harris-Corners

> und wie bestimmt man deren Orientierung?

1. berechne den Gradienten um die gefundenen Keypoints
2. aus dem resultierenden Histogramm wird das Maximum (also die Orientierung) abgelesen

#### Teil B

> Beschreiben Sie den Aufbau eines SIFT-Diskriptors und wie dieser berechnet wird.

- SIFT-Diskriptor beschreibt den Fingerprint des Keypoints
- erstelle ein Array von Gradientenhistogrammen, welches in mehrere Matrizen aufgeteilt ist

#### Teil C

> Beschreiben Sie kurz, wie Sie damit ähnliche Objekte in zwei gegebenen Bildern auffinden können.

Ähnliche Objekte werden gefunden, indem die Nachbar-Region von Keypoints in beiden Bildern verglichen wird.

#### Teil D

> Was passiert wenn zwei unterschiedlich rotierte Bilder miteinander verglichen werden?

Das Verfahren zur Erkennung der Keypoints ändert sich nicht (siehe Teile A und C). Der Vergleich erfolgt über die berechneten Keypoints.

#### Teil E

> Funktioniert SIFT immernoch, wenn Bilder miteinander verglichen werden, die aus unterschiedlichen Perspektiven aufgenommen wurden?

Ja, SIFT ist invariant gegenüber Translation, Rotation und Skalierung.

