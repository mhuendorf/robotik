# Aufgabe 4.2

### Teil A

> Geben Sie die Matrizen A, B und H für den Kalman-Filter für die beschriebene Domäne an!

<!-- Analog zur VL -->

**Zustandsraum, Aktionsraum und Messraum:**

$$
\begin{aligned}
x:=\left(\begin{matrix}
x \\
z \\
\theta \\
\lambda \\
\beta 
\end{matrix}\right),~~

u:=\left(\begin{matrix}
\Delta x \\
\Delta z \\
\Delta \theta 
\end{matrix}\right),~~

Z:=\left(\begin{matrix}
x \\
z \\
\theta \\
\lambda
\end{matrix}\right)
\end{aligned}
$$

**Transitionsmodell, Aktionsmodell und Sensormodell:**

$$
\begin{aligned}
A:=I_5,~~

B:=\left(\begin{matrix}
1&0&0 \\
0&1&0 \\
0&0&1 \\
0&0&0 \\
\end{matrix}\right),~~

H:=\left(\begin{matrix}
1&0&0&0&0 \\
0&1&0&0&0 \\
0&0&1&0&0 \\
0&0&0&1&0 
\end{matrix}\right)
\end{aligned}
$$

### Teil B

> Modellieren Sie die Aktionen rot und tra:
> 
> - rot rotiert um den vorgegebenen Wert bei einer Standardabweichung von 0.02 und lässt x, z unverändert.
> - tra translatiert den Roboter um die vorgegebenen Werte bei einer Standardabweichung von 0.5 in beiden Dimensionen. Als Nebeneffekt ändert es möglicherweise die  Orientierung mit einer Standardabweichung von 0.01

**Rotation:**

$$
\begin{aligned}
P(x_{t+1}|u_t,x_t)&=n\cdot \left( Ax_t + Bf(u_t), RT_u  \right) \\ \\

RT&:=\left(\begin{matrix}
0&0&0&0&0 \\
0&0&0&0&0 \\
0&0&0.02&0&0 \\
0&0&0&0.001&0 \\
0&0&0&0&0 
\end{matrix}\right) \\
\end{aligned}
$$

$$
f\colon\mathbb{R}^{3}\to\mathbb{R}^{3},~f{\begin{pmatrix}a\\b\\c\end{pmatrix}}={\begin{pmatrix}0\\0\\c\end{pmatrix}}
$$

**Translation:**

$$
\begin{aligned}
P(x_{t+1}|u_t,x_t)&=n\cdot \left( Ax_t + Bf(u_t), TR_u  \right) \\ \\

TR&:=\left(\begin{matrix}
0.5 & 0 & 0 & 0 & 0 \\
0 & 0.5 & 0 & 0 & 0 \\
0 & 0 & 0.01 & 0 & 0 \\
0 & 0 & 0 & 0.001 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{matrix}\right)
\end{aligned}
$$

$$
f\colon\mathbb{R}^{3}\to\mathbb{R}^{3},~f{\begin{pmatrix}a\\b\\c\end{pmatrix}}={\begin{pmatrix}a\\b\\0\end{pmatrix}}
$$

### Teil C

> Im Startzustand befinde sich der Roboter an $(0, 0, 0)$, der Luftdruck sei 1000 hPa, und die Anzahl der Bundesländer sei 16. Berechnen Sie den Zustand (mehrdimensionaler Mittelwert und Standardabweichung), der sich ergibt, wenn der Roboter erst um 0.3 rad rotiert und anschließend um 2 Einheiten x und 3 Einheiten z translatiert. Geben Sie für alle vorkommenden Zustände die a-priori-Werte für Mittelwert und Varianz sowie die entsprechenden Kalman-Gewinnmatrizen an.

$$
x_0:=\begin{pmatrix}
0 \\
0 \\
0 \\
1000 \\
16 
\end{pmatrix}
$$

**Kovarianzmatrix:**

$$
\begin{aligned}
\Sigma_0&=I_5 \\

\Sigma_Z&=\begin{pmatrix}
\sigma_x^2 & 0 & 0 & 0 & 0 \\
0 & \sigma_z^2 & 0 & 0 & 0 \\
0 & 0 & \sigma_\theta^2 & 0 & 0 \\
0 & 0 & 0 & \sigma_\lambda^2 & 0 \\
0 & 0 & 0 & 0 & \sigma_\beta^2 
\end{pmatrix}
\end{aligned}
$$

**A-priori:**

$$
\begin{aligned}
\overline{x}_{t+1}&=Ax_t+Bu \\
\overline{\Sigma}_{t+1}&=A\Sigma_t A^T+\Sigma_u
\end{aligned}
$$

$$
\begin{aligned}
\overline{x}_{1}&=Ax_0+B \begin{pmatrix}0\\0\\0.3\end{pmatrix} \\
&=A \begin{pmatrix}0\\0\\0\\1000\\16\end{pmatrix} + B \begin{pmatrix}0\\0\\0.3\end{pmatrix} \\
&=\begin{pmatrix}0\\0\\0\\1000\\16\end{pmatrix}+\begin{pmatrix}0\\0\\0.3\\0\\0\end{pmatrix} \\
&=\begin{pmatrix}0\\0\\0.3\\1000\\16\end{pmatrix}
\end{aligned}
$$

$$
\begin{aligned}
\overline{\Sigma}_{1}&=A\Sigma_0 A^T+\Sigma_{u_{RT}} \\
&=I_5+\begin{pmatrix}
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0.02 & 0 & 0 \\
0 & 0 & 0 & 0.001 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{pmatrix} \\
&=\begin{pmatrix}
1 & 0 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 \\
0 & 0 & 1.02 & 0 & 0 \\
0 & 0 & 0 & 1.001 & 0 \\
0 & 0 & 0 & 0 & 1 
\end{pmatrix}
\end{aligned}
$$

**Kalman-Gewinnmatrix:**

$$
K_{t+1}=\Sigma_{t+1}+H^T(H\Sigma_{t+1}H^T+\Sigma_z)^{-1}
$$

TBD

<!--
\begin{pmatrix}
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{pmatrix}
-->