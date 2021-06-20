# Aufgabe 5.4

<!-- NOTE: https://www.tu-chemnitz.de/informatik/KI/edu/robotik/ws2012/robotik_6_2.pdf -->

## (a)

> Berechnen Sie die Aufenthaltswahrscheinlichkeit fur den Roboter fu ̈r jede Zelle nach jedem einzelnen Schritt. In welcher Zelle ist demnach der Roboter vermutlich gestartet?

### 1. Der Roboter detektiert eine Landmarke.

Für alle Felder mit Landmarke trage 0,7 ein und für alle ohne 0,25.

Danach normalisiere die Werte.

![Alt text](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_1.png)

### 2. Der Roboter bewegt sich 2 Zellen im Uhrzeigersinn.

Dafür müssen einfach alle Wahrscheinlichkeiten um 2 Felder im Uhrzeigersinn verschoben werden. Es wird angenommen, dass die Bewegung zu 100% verlässlich ist, da dazu nichts in der Aufgabe steht.

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_2.png)

### 3. Der Roboter detektiert wieder eine Landmarke.

Zunächst wird der nicht normalisierte Belief ausgerechnet:

- für all Felder ohne Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass falsch detektiert wurde (0,25).

- für alle Felder mit Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass richtig detektiert wurde (0,7).

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_3.1.png)

Anschließend müssen alle Werte normalisiert werden. Für $n$ gilt:

$$
1=n\cdot(7\cdot0,01+8\cdot0,028+0,0784)\\

\Rightarrow n\approx 2,685
$$

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_3.2.png)

### 4. Der Roboter bewegt sich 4 Zellen im Uhrzeigersinn.

Das selbe wie bei dem Schritt 2 nur mit 4 Felden statt 2.

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_4.png)

### 5. Der Roboter detektiert keine Landmarke.

Zunächst wird der nicht normalisierte Belief ausgerechnet:

- für all Felder ohne Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass richtig detektiert wurde ($1 - 0,25=0,75$).

- für alle Felder mit Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass falsch detektiert wurde ($1-0,7=0,3$).

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_5.1.png)

Anschließend müssen wieder alle Werte normalisiert werden. Für n gilt diesmal:

$$
1=n\cdot(4\cdot 0,021375+6\cdot 0,056385+0,157878+2\cdot 0,022554+3\cdot 0,008055)\\
\Rightarrow n\approx 1,536
$$

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_5.2.png)

### In welcher Zelle ist demnach der Roboter vermutlich gestartet?

Der Roboter ist vermutlich in Zelle 4 gestartet. Das Folgt daraus, dass es am Wahscheinlichsten ist, dass sich der Roboter am Ende mit einer Wahrscheinlichkeit von ca. 24,3% in der Zelle 10 befindet. Führt man von dieser Zelle die Aktionen in reversiver Reiohenfolge aus (also 6 insgesamt 6 Felder entgegen dem Uhrzeigersinn), landet man bei der Zelle 4. Der Roboter ist also mit einer Wahrscheinlichkiet von ca. 24,3% bei der Zelle 4 gestartet.

## (b)

> Nehmen Sie nun an, dass bei einer Bewegung des Roboters zwar bekannt ist, wie weit sich der Roboter bewegt hat, nicht aber in welche Richtung (im oder entgegen dem Uhrzeigersinn). Berechnen Sie auch hier die Aufenthaltswahrscheinlichkeiten.

### 1. Der Roboter detektiert eine Landmarke.

Hier ist noch alles das selbe wie bei (a).

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_1.png)

### 2. Der Roboter bewegt sich 2 Zellen.

Normalerweise müsste man die Wahrscheinlcikeiten der Zellen zwei weiter gegen den Uhrzeigersinn und zwei Felder weiter mit dem Uhrzeigersinn zusammenrechnen und später normalisieren. Das Normalisieren lässt sich hier aber ersparen, da auf jedes Feld immer genau zwei Wahrscheinlichkeiten treffen und daher durch ein halbieren dieser ein Normalisieren überflüssig macht.

- Fall 1: eine Zelle welches 2 entfernt ist wahrsch. 0,04 und andere 0,12: $\frac{0,04+0,112}{2}=0,076$

- Fall 2: beide Zellen welche 2 Felder entfernt sind wahrsch. 0,04: $\frac{2\cdot0,04}{2}=0,04$

- Fall 3: beide Zellen welche 2 Felder entfernt sind wahrsch. 0,12: $\frac{2\cdot0,12}{2}=0,12$

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_2b.png)

Weiterhin kann sich hier und auch im Folgenden Arbeit erspart werden, wenn nur eine Hälfte des Problems berechnet wird. Dies ist möglich, da die Karte symetrisch ist und durch die Vernachlässigung von Richtungen das Problem auch. Die symmetrieachse ist im folgenden als gestichelte Linie dargestellt. Beim Normalisieren müssen die Werte der anderen Hälfte dann natürlich mit einbezogen werden.

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Sym.png)

### 3. Der Roboter detektiert wieder eine Landmarke.

Zunächst wird der nicht normalisierte Belief ausgerechnet:

- für all Felder ohne Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass falsch detektiert wurde (0,25).

- für alle Felder mit Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass richtig detektiert wurde (0,7).

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_3.1b.png)

Anschließend müssen alle Werte normalisiert werden. Für n gilt:

$$
1=n\cdot(5\cdot0,01+4\cdot0,019+5\cdot0,028+2\cdot0,0532)\\
\Rightarrow n\approx 2,685
$$

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_3.2b.png)

### 4. Der Roboter bewegt sich 4 Zellen.

Das selbe vorgehen wie bei Schritt zwei, nur werden hier die beiden Zellen, die 4 entfernt sind betrachtet

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_4b.png)

### 5. Der Roboter detektiert keine Landmarke.

Zunächst wird der nicht normalisierte Belief ausgerechnet:

- für all Felder ohne Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass richtig detektiert wurde (1 - 0,25=0,75).

- für alle Felder mit Landmarke: rechne alten Belief mal der Wahrscheinlichkeit, dass falsch detektiert wurde (1-0,7=0,3).

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_5.1b.png)

Anschließend müssen wieder alle Werte normalisiert werden. Für n gilt diesmal:

$$
1=n\cdot(4\cdot 0,06362775+4\cdot 0,04732312+ 2\cdot 0,02919938+ 0,056385
+2\cdot 0,0153045 + 2\cdot 0,01167975+ 0,022554)\\
\Rightarrow n\approx 1,575
$$

![](/Users/marcelhundorf/Uni/Master/3.%20Semester/robotik/Lösungen/src/blatt05_gruppe11_zusatz/Bilder/Schritt_5.2b.png)
