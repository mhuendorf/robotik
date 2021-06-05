# Aufgabe 4.1

<!-- NOTE: https://www.tu-chemnitz.de/informatik/KI/edu/robotik/ws2012/robotik_6_2.pdf -->

### Teil A

> Berechnen Sie die a-priori Wahrscheinlichkeitsverteilung für den ersten Tag, an dem Sie Ihre Beobachtungen starten ($t = 1$).

**t=0:**

$$
\begin{aligned}
\operatorname{Bel}(R_0)=P(R_0)&=0.5 \\
\operatorname{Bel}(S_0)=P(S_0)&=0.5 \\
\end{aligned}
$$

**t=1:**

$$
\begin{aligned}
\overline{\operatorname{Bel}}(R_1)&=P(R_1|R_0)\cdot \operatorname{Bel}(R_0) + P(R_1|S_0)\cdot \operatorname{Bel}(S_0) \\
&=0.7\cdot 0.5 + 0.3\cdot 0.5 \\
&=0.5 \\ \\

\overline{\operatorname{Bel}}(S_1)&=P(S_1|S_0)\cdot \operatorname{Bel}(S_0) + P(S_1|R_0)\cdot \operatorname{Bel}(R_0) \\
&=0.7\cdot 0.5 + 0.3\cdot 0.5 \\
&=0.5
\end{aligned}
$$

### Teil B

> Ausgehend von dieser Verteilung machen Sie die Beobachtung $u_1$ (der ”Direktor“ kommt mit dem Regenschirm). Wie sieht unter Berücksichtigung dieser Information die a-posteriori Wahrscheinlichkeitsverteilung für Tag 1 aus?

$$
\begin{aligned}
\operatorname{Bel}(R_1)&=n\cdot P(u_1|R_1)\cdot \overline{\operatorname{Bel}}(R_1) \\
&=n\cdot 0.9\cdot 0.5 \\
&=n\cdot 0.45 \\ \\

\operatorname{Bel}(S_1)&=n\cdot P(u_1|S_1)\cdot \overline{\operatorname{Bel}}(S_1) \\
&=n\cdot 0.2\cdot 0.5 \\
&=n\cdot 0.1 \\ \\
\end{aligned}
$$

**Normalisieren:**

$$
\begin{aligned}
1&=n\cdot(0.45 + 0.1) \\
1&=0.55n \\
n&=1.818
\end{aligned}
$$

$$
\begin{aligned}
\operatorname{Bel}(R_1)&=1.818\cdot 0.45 \\
&=0.8181 \\
\operatorname{Bel}(S_1)&=1.818\cdot 0.1 \\
&=0.1818
\end{aligned}
$$

### Teil C

> Berechnen Sie nun davon ausgehend die Wahrscheinlichkeitsverteilung $P (R_2 | u_1 )$, also die a-priori Wahrscheinlichkeit, dass es an Tag 2 regnet, wenn Sie an Tag 1 den Regenschirm gesehen haben.

$$
\begin{aligned}
\overline{\operatorname{Bel}}(R_2)&=P(R_2|R_1)\cdot \operatorname{Bel}(R_1)+ P(R_2|S_1)\cdot \operatorname{Bel}(S_1) \\
&=0.7\cdot 0.8181 + 0.3\cdot 0.1818 \\
&=0.62721 \\ \\

\overline{\operatorname{Bel}}(S_2)&=P(S_2|S_1)\cdot \operatorname{Bel}(S_1)+ P(S_2|R_1)\cdot \operatorname{Bel}(R_1) \\
&=0.7\cdot 0.1818 + 0.3\cdot 0.8181 \\
&=0.373
\end{aligned}
$$

### Teil D

> Wie sieht nun die a-posteriori Wahrscheinlichkeit $P (R_2 | u_1 , u_2 )$ aus, wenn Sie den Regenschirm an Tag 2 erneut beobachten?

$$
\begin{aligned}
\operatorname{Bel}(R_2)&=P(u_2|R_2)\cdot \overline{\operatorname{Bel}}(R_2) \\
&=0.9\cdot 0.62721 \\
&=0.565 \\ \\

\operatorname{Bel}(R_2)&=P(u_2|S_2)\cdot \overline{\operatorname{Bel}}(S_2) \\
&=0.2\cdot 0.373 \\
&=0.075
\end{aligned}
$$

**Normalisieren:**

$$
\begin{aligned}
1&=n\cdot(0.565 + 0.075) \\
1&=0.64n \\
n&=1.5625
\end{aligned}
$$

$$
\begin{aligned}
\operatorname{Bel}(R_2)&=1.5625\cdot 0.565=0.883 \\
\operatorname{Bel}(S_2)&=1.5625\cdot 0.075=0.117
\end{aligned}
$$

### Teil E

> Nehmen Sie nun an, dass der Regenschirm auch an allen Tagen nach Tag 2 zu sehen ist. Berechnen Sie den Fixpunkt, gegen den die Wahrscheinlichkeit für Regen unter dieser Annahme konvergiert.

Konvergiert gegen $0.9$, da die Wahrscheinlichkeit, dass ein Regenschirm mitgenommen wird unter der Bedingung, dass es regnet genau 90\% ist.

### Teil F

> Betrachten Sie nun den Fall, dass Sie den ”Direktor“ nach Tag 2 nicht mehr sehen. Welche Vorhersage für die Wahrscheinlichkeit von Regen können Sie nun für Tag 3 und 4 machen? Berechnen Sie auch hier den Fixpunkt, gegen den die Wahrscheinlichkeit für Regen konvergiert, wenn die Vorhersage ohne zusätzliche Beobachtungen weiter in die Zukunft gelegt wird.

Konvergiert gegen $0.5$, da der Sensor (Direktor) keinen Einfluss auf die Korrektur hat und entsprechend sich der Wert mit $t\to\infin$ auf die in der Aufgabenstellung gegebenen 50\% einpendeln wird.
