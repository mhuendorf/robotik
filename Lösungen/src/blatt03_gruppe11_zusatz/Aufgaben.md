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

> Geben Sie einen passenden Kernel der Gr????e 5??5 f??r eine Gauss-Filterung an.

| 1   | 4   | 7   | 4   | 1   |
| --- | --- | --- | --- | --- |
| 4   | 16  | 26  | 16  | 4   |
| 7   | 26  | 41  | 26  | 7   |
| 4   | 16  | 26  | 16  | 4   |
| 1   | 4   | 7   | 4   | 1   |

> [...] Wie w??rde sich sich ein Kernel mit steigendem Sigma auf das Bild auswirken?

Das Bild w??rde immer mehr weichgezeichnet und entsprechend verschwommen. Die Farbwerte von benachtbarten Pixeln w??rden sich immer weiter ann??hern.

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

> Aus welchem Grund wird ein solcher Gau??-Filter [...] oft als erster Schritt in einer Pipline von weiteren Filtern verwendet?

Ein Gau??-Filter wird zum Weichzeichnen, also zu Gl??tung der unterschiedlichen Pixelwerte, verwendet. Mit der entsprechenden Konfiguration des Filters kann Bildrauschen eliminiert/vermindert werden, sodass bpsw. die verschiedenen Strukturen des Bildes miteinander verschmelzen.

### Teil F

> Wie w??rden Sie vorgehen, wenn Sie einen Filter nicht auf ein Graustufenbild mit 1 Kanal sondern auf auf 3 Kanal (RGB) Farbbild anwenden m??chten?

Die Farbwerte (RGB) werden entsprechend ihrere Intensit??t in Grauwerte umgerechnet. Andernfalls k??nnten die jeweiligen Schritte, die f??r die Grauwerte durchlaufen werden, f??r jeden Farbwert (R, G und B) einzeln durchlaufen werden ($\rightarrow$ 3x Matrizen). Anschlie??end wird ein einzelner RGB-Wert aus den Matrizen ermittelt.





### Nr 3

#### Teil A

> Welche Pixel werden als Keypoints ausgew??hlt

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

> Beschreiben Sie kurz, wie Sie damit ??hnliche Objekte in zwei gegebenen Bildern auffinden k??nnen.

??hnliche Objekte werden gefunden, indem die Nachbar-Region von Keypoints in beiden Bildern verglichen wird.

#### Teil D

> Was passiert wenn zwei unterschiedlich rotierte Bilder miteinander verglichen werden?

Das Verfahren zur Erkennung der Keypoints ??ndert sich nicht (siehe Teile A und C). Der Vergleich erfolgt ??ber die berechneten Keypoints.

#### Teil E

> Funktioniert SIFT immernoch, wenn Bilder miteinander verglichen werden, die aus unterschiedlichen Perspektiven aufgenommen wurden?

Ja, SIFT ist invariant gegen??ber Translation, Rotation und Skalierung.

