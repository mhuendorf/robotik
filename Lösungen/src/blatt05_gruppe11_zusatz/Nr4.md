# Aufgabe 4

### Teil A

> Berechnen Sie die Aufenthaltswahrscheinlichkeit fur den Roboter für jede Zelle nach jedem einzelnen Schritt. In welcher Zelle ist demnach der Roboter vermutlich gestartet?

**Gegeben:**

Roboter detektiert Landmarke:

|           | $D$  |
| --------- | ----- |
| $L$       | $0.7$ |
| $\lnot L$ | $0.3$ |

Roboter detektiert Landmarke fälschlicherweise:

|           | $\lnot D$  |
| --------- | ----- |
| $L$       | $0.25$ |
| $\lnot L$ | $0.75$ |

NB: $L$ und $\lnot D$ mit $0.25$: Eine Landmarke wird fälschlicherweise mit 25% Wahrscheinlichkeit detektiert, obwohl keine existiert.

$$
\begin{aligned}
\operatorname{Bel}(x_0)=\frac{1}{16}
\end{aligned}
$$

**1. Der Roboter detektiert eine Landmarke:**

$$
\begin{aligned}
\overline{\operatorname{Bel}}(x_0)=\frac{1}{16}
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_1)&= \\
  \operatorname{Bel}(x_4)&= \\
  \operatorname{Bel}(x_6)&= \\
  \operatorname{Bel}(x_9)&= \\
  \operatorname{Bel}(x_{13})&=n\cdot 0.7\cdot\frac{1}{16} \\
  &=n\cdot 0.04375 \\
  &\to 2.56\cdot 0.04375=0.112
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_2)&= \\
  \operatorname{Bel}(x_3)&= \\
  \operatorname{Bel}(x_5)&= \\
  \operatorname{Bel}(x_7)&= \\
  \operatorname{Bel}(x_8)&= \\
  \operatorname{Bel}(x_{10})&= \\
  \operatorname{Bel}(x_{11})&= \\
  \operatorname{Bel}(x_{12})&= \\
  \operatorname{Bel}(x_{14})&= \\
  \operatorname{Bel}(x_{15})&= \\
  \operatorname{Bel}(x_{16})&=n\cdot 0.25\cdot\frac{1}{16} \\
  &=n\cdot 0.01563 \\
  &\to 2.56\cdot 0.01563=0.04
\end{aligned}
$$

Normalisieren:

$$
\begin{aligned}
  1&=n(5\cdot 0.04375+11\cdot 0.01563) \\
  n&=2.56
\end{aligned}
$$

**2. Der Roboter bewegt sich 2 Zellen im Uhrzeigersinn:**

$$
\begin{aligned}
  \overline{\operatorname{Bel}}(x_3)&= \\
  \overline{\operatorname{Bel}}(x_6)&= \\
  \overline{\operatorname{Bel}}(x_8)&= \\
  \overline{\operatorname{Bel}}(x_{11})&= \\
  \overline{\operatorname{Bel}}(x_{15})&=0.112
\end{aligned}
$$

$$
\begin{aligned}
  \overline{\operatorname{Bel}}(x_4)&= \\
  \overline{\operatorname{Bel}}(x_5)&= \\
  \overline{\operatorname{Bel}}(x_7)&= \\
  \overline{\operatorname{Bel}}(x_9)&= \\
  \overline{\operatorname{Bel}}(x_{10})&= \\
  \overline{\operatorname{Bel}}(x_{12})&= \\
  \overline{\operatorname{Bel}}(x_{13})&= \\
  \overline{\operatorname{Bel}}(x_{14})&= \\
  \overline{\operatorname{Bel}}(x_{16})&= \\
  \overline{\operatorname{Bel}}(x_{1})&= \\
  \overline{\operatorname{Bel}}(x_{2})&=0.04
\end{aligned}
$$

**3. Der Roboter detektiert wieder eine Landmarke:**

Beachte den letzten fehlerbehafteten Believe und korrigiere diesen:

Landmarke und richtig Erkannt:

$$
\begin{aligned}
  \operatorname{Bel}(x_6)&=n\cdot 0.7\cdot 0.112 \\
  &=0.0784 \\
  &\to 2.685\cdot 0.0784 = 0.21
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_1)&= \\
  \operatorname{Bel}(x_4)&= \\
  \operatorname{Bel}(x_9)&= \\
  \operatorname{Bel}(x_{13})&=n\cdot 0.7\cdot 0.04 \\
  &=0.028 \\
  &\to 2.685\cdot 0.028 = 0.0752
\end{aligned}
$$

Landmarke fälschlicherweise erkannt:

$$
\begin{aligned}
  \operatorname{Bel}(x_3)&= \\
  \operatorname{Bel}(x_8)&= \\
  \operatorname{Bel}(x_{11})&= \\
  \operatorname{Bel}(x_{15})&=n\cdot 0.25\cdot 0.112 \\
  &=n\cdot 0.028 \\
  &\to 2.685\cdot 0.028 = 0.0752
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_{2})&= \\
  \operatorname{Bel}(x_{5})&= \\
  \operatorname{Bel}(x_{7})&= \\
  \operatorname{Bel}(x_{10})&= \\
  \operatorname{Bel}(x_{12})&= \\
  \operatorname{Bel}(x_{14})&= \\
  \operatorname{Bel}(x_{16})&=n\cdot 0.25\cdot 0.04 \\
  &= 0.01 \\
  &\to 2.685\cdot 0.01 = 0.02685
\end{aligned}
$$

Normalisieren:

$$
\begin{aligned}
  1&=n(0.0784 + 4\cdot 0.028 + 4\cdot 0.028 + 7\cdot 0.01) \\
  n&=2.685
\end{aligned}
$$

**4. Der Roboter bewegt sich 4 Zellen im Uhrzeigersinn:**

$$
\begin{aligned}
  \overline{\operatorname{Bel}}(x_{10})&=0.21 \\\\

  \overline{\operatorname{Bel}}(x_5)&= \\
  \overline{\operatorname{Bel}}(x_8)&= \\
  \overline{\operatorname{Bel}}(x_{13})&= \\
  \overline{\operatorname{Bel}}(x_{1})&= \\
  \overline{\operatorname{Bel}}(x_7)&= \\
  \overline{\operatorname{Bel}}(x_{12})&= \\
  \overline{\operatorname{Bel}}(x_{15})&= \\
  \overline{\operatorname{Bel}}(x_{3})&=0.0752 \\\\

  \overline{\operatorname{Bel}}(x_{6})&= \\
  \overline{\operatorname{Bel}}(x_{9})&= \\
  \overline{\operatorname{Bel}}(x_{11})&= \\
  \overline{\operatorname{Bel}}(x_{14})&= \\
  \overline{\operatorname{Bel}}(x_{16})&= \\
  \overline{\operatorname{Bel}}(x_{2})&= \\
  \overline{\operatorname{Bel}}(x_{4})&=0.02685
\end{aligned}
$$

**5. Der Roboter detektiert keine Landmarke:**

$$
\begin{aligned}
  \operatorname{Bel}(x_{10})&=n\cdot 0.75\cdot 0.21 \\
  &=n\cdot 0.1575 \\
  &\to 1.5783\cdot 0.1575 = 0.2486
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_5)&= \\
  \operatorname{Bel}(x_8)&= \\
  \operatorname{Bel}(x_7)&= \\
  \operatorname{Bel}(x_{12})&= \\
  \operatorname{Bel}(x_{15})&= \\
  \operatorname{Bel}(x_{3})&=n\cdot 0.75\cdot 0.0752 \\
  &=n\cdot 0.0564 \\
  &\to 1.5783\cdot 0.0564 = 0.089
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_1)&= \\
  \operatorname{Bel}(x_{13})&=n\cdot 0.25\cdot 0.0752 \\
  &=n\cdot 0.0188 \\
  &\to 1.5783\cdot 0.0188 = 0.02967
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_{11})&= \\
  \operatorname{Bel}(x_{14})&= \\
  \operatorname{Bel}(x_{16})&= \\
  \operatorname{Bel}(x_{2})&=n\cdot 0.75\cdot 0.02685 \\
  &=0.02 \\
  &\to 1.5783\cdot 0.02 = 0.031566
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_{6})&= \\
  \operatorname{Bel}(x_{9})&= \\
  \operatorname{Bel}(x_{4})&=n\cdot 0.25\cdot 0.02685 \\
  &=n\cdot 0.0067 \\
  &\to 1.5783\cdot 0.0067 = 0.011
\end{aligned}
$$

Normalisieren:

$$
\begin{aligned}
  1&=n(0.1575 + 6\cdot 0.0564 + 2\cdot 0.0188 + 4\cdot 0.02 + 3\cdot 0.0067) \\
  n&=1.5783
\end{aligned}
$$

**Lösung:**

Der Roboter wird sich mit Wahrscheinlichkeit von ca. 25% in Zelle 10 befinden.

### Teil B

$$
\begin{aligned}
\operatorname{Bel}(x_0)=\frac{1}{16}
\end{aligned}
$$

**1. Der Roboter detektiert eine Landmarke:**

$$
\begin{aligned}
\overline{\operatorname{Bel}}(x_0)=\frac{1}{16}
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_1)&= \\
  \operatorname{Bel}(x_4)&= \\
  \operatorname{Bel}(x_6)&= \\
  \operatorname{Bel}(x_9)&= \\
  \operatorname{Bel}(x_{13})&=n\cdot 0.7\cdot\frac{1}{16} \\
  &=n\cdot 0.04375 \\
  &\to 2.56\cdot 0.04375=0.112
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_2)&= \\
  \operatorname{Bel}(x_3)&= \\
  \operatorname{Bel}(x_5)&= \\
  \operatorname{Bel}(x_7)&= \\
  \operatorname{Bel}(x_8)&= \\
  \operatorname{Bel}(x_{10})&= \\
  \operatorname{Bel}(x_{11})&= \\
  \operatorname{Bel}(x_{12})&= \\
  \operatorname{Bel}(x_{14})&= \\
  \operatorname{Bel}(x_{15})&= \\
  \operatorname{Bel}(x_{16})&=n\cdot 0.25\cdot\frac{1}{16} \\
  &=n\cdot 0.01563 \\
  &\to 2.56\cdot 0.01563=0.04
\end{aligned}
$$

Normalisieren:

Siehe oben (Teil A).

**2. Der Roboter bewegt sich 2 Zellen im Uhrzeigersinn:**

$$
\begin{aligned}
  \overline{\operatorname{Bel}}(x_{11})&= \\
  \overline{\operatorname{Bel}}(x_{15})&=0.112
\end{aligned}
$$

$$
\begin{aligned}
  \overline{\operatorname{Bel}}(x_{16})&= \\
  \overline{\operatorname{Bel}}(x_1)&= \\
  \overline{\operatorname{Bel}}(x_5)&= \\
  \overline{\operatorname{Bel}}(x_6)&= \\
  \overline{\operatorname{Bel}}(x_9)&= \\
  \overline{\operatorname{Bel}}(x_{10})&= \\
  \overline{\operatorname{Bel}}(x_{12})&= \\
  \overline{\operatorname{Bel}}(x_{13})&= \\
  \overline{\operatorname{Bel}}(x_{14})&=0.04
\end{aligned}
$$

Beide:

$$
\begin{aligned}
  \overline{\operatorname{Bel}}(x_4)&=\\
  \overline{\operatorname{Bel}}(x_6)&= \\

  \overline{\operatorname{Bel}}(x_2)&= \\
  \overline{\operatorname{Bel}}(x_3)&= \\
  \overline{\operatorname{Bel}}(x_8)&= \\
  \overline{\operatorname{Bel}}(x_7)&= 0.04\cdot 0.5+0.112cdot 0.5 \\
  &= 0.076
\end{aligned}
$$

**3. Der Roboter detektiert wieder eine Landmarke:**

$$
\begin{aligned}
  \operatorname{Bel}(x_{11})&= \\
  \operatorname{Bel}(x_{15})&=0.112\cdot 0.25=0.028
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_{16})&= \\
  \operatorname{Bel}(x_5)&= \\
  \operatorname{Bel}(x_{10})&= \\
  \operatorname{Bel}(x_{12})&= \\
  \operatorname{Bel}(x_{14})&=0.04\cdot 0.25=0.01
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_1)&= \\
  \operatorname{Bel}(x_6)&= \\
  \operatorname{Bel}(x_9)&= \\
  \operatorname{Bel}(x_{13})&=0.04\cdot 0.75=0.028
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_4)&=\\
  \operatorname{Bel}(x_6)&=0.076\cdot 0.7 = 0.0532\\
\end{aligned}
$$

$$
\begin{aligned}
  \operatorname{Bel}(x_2)&= \\
  \operatorname{Bel}(x_3)&= \\
  \operatorname{Bel}(x_8)&= \\
  \operatorname{Bel}(x_7)&=0.076\cdot 0.25=0.019
\end{aligned}
$$

Normalisieren:

$$
\begin{aligned}
  1&=(5\cdot 0.028+ 5\cdot 0.01+ 2\cdot 0.0532+ 4\cdot 0.019) \\
  n&=2,6853
\end{aligned}
$$

**4. Der Roboter bewegt sich 4 Zellen im Uhrzeigersinn:**

TBD
